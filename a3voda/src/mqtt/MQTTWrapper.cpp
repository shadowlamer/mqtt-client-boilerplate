/**
 * @file MQTTWrapper.cpp
 * @brief Реализация класса MQTTWrapper.
 * @author Vadim Cherenev
 * @date 21.02.2019
 * @copyright MIT License
 */

#include <utility>
#include <MQTTWrapper.h>

int midSale = 0;

/**
 * @param _id Идентификатор MQTT клиента
 * @param _host Адрес хоста MQTT брокера для подключения
 * @param _port Порт MQTT брокера для подключения
 * @param _topics Список топиков, на которые необходимо подписаться
 */
MQTTWrapper::MQTTWrapper(const char* _id, const char* _host, int _port, vector<string> _topics) :
        mosquittopp(_id),
        topics(move(_topics)),
        nc(),
        host(_host),
        port(_port)
{
    mosqpp::lib_init();
}

MQTTWrapper::~MQTTWrapper() {
    disconnect();
    if (loop_stop() != MOSQ_ERR_SUCCESS) {
        std::cout << "loop_stop failed" << std::endl;
    }
    mosqpp::lib_cleanup();
}

/**
 * @brief Подписать получателя на сообщения.
 * Сообщения полученные из топиков, на которые подписался MQTTWrapper
 * Будут передаваться в метод processAction получателя сообщений
 * @sa ActionListener
 * @param listener Получатель сообщений
 */
void MQTTWrapper::subscribeAction(ActionListener &listener) {
    nc.addObserver(
            Observer<ActionListener, Serializable>(listener, &ActionListener::processAction)
    );
}

/**
 * @brief Подключиться к MQTT брокеру.
 * @throws runtime_error Не удалось запустить цикл обработки сообщений.
 */
void MQTTWrapper::connect(void) {
    connect_async(host.c_str(), port, -1);
    if (loop_start() != MOSQ_ERR_SUCCESS)
        throw runtime_error("Can't start MQTT loop");
}

/**
 * @brief Обработчик события подключения к MQTT брокеру.
 * Подписывается на топики, переданные в конструктор.
 * @throws runtime_error Не удалось подписаться на топик
 * @param rc Результат подключения
 */
void MQTTWrapper::on_connect(int rc) {
    if (rc!=0) return;
    for (vector<string>::const_iterator topicIt = topics.begin();topicIt != topics.end(); topicIt++) {
        if (subscribe(&midSale,topicIt->c_str(),QOS)  != MOSQ_ERR_SUCCESS)
        throw runtime_error("Can't subscribe to topic " + *topicIt);
    }
}

/**
 * @brief Опубликовать сообщение.
 * @param topic Топик для публкации
 * @param message Нагрузка сообщения
 */
void MQTTWrapper::publish(string topic, string message) {
    mosquittopp::publish(&midSale, topic.c_str(), message.size(), message.c_str());
}

/**
 * @brief Опубликовать сообщение.
 * @param topic Топик для публкации
 * @param entity Нагрузка сообщения
 */
void MQTTWrapper::publish(string topic, Serializable entity) {
    publish(topic, entity.Serialize());
}

/**
 * @brief Обработчик MQTT сообщения.
 * @param message Сообщение
 * @throws runtime_error Ошибка при обработке сообщения
 */
void MQTTWrapper::on_message(const struct mosquitto_message* message) {
    string topic = message->topic;
    if (message->payloadlen < 1) {
        cerr << "No payload found. Returning...\n";
        return;
    }

    string payload = string((const char*) message->payload, message->payloadlen);
    try {
        Serializable *notification = new Serializable(payload);
        notification->forceSetName(topic);
        nc.postNotification(notification);
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
}
