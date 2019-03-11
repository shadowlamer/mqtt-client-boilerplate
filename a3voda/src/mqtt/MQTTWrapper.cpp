#include <utility>
#include <MQTTWrapper.h>

int midSale = 0;

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

void MQTTWrapper::subscribeAction(ActionListener &listener) {
    nc.addObserver(
            Observer<ActionListener, Serializable>(listener, &ActionListener::processAction)
    );
}

void MQTTWrapper::connect(void) {
    connect_async(host.c_str(), port, -1);
    if (loop_start() != MOSQ_ERR_SUCCESS)
        throw runtime_error("Can't start MQTT loop");
}

void MQTTWrapper::on_connect(int rc) {
    if (rc!=0) return;
    for (vector<string>::const_iterator topicIt = topics.begin();topicIt != topics.end(); topicIt++) {
        if (subscribe(&midSale,topicIt->c_str(),QOS)  != MOSQ_ERR_SUCCESS)
        throw runtime_error("Can't subscribe to topic " + *topicIt);
    }
}

void MQTTWrapper::publish(string topic, string message) {
    mosquittopp::publish(&midSale, topic.c_str(), message.size(), message.c_str());
}

void MQTTWrapper::publish(string topic, Serializable entity) {
    publish(topic, entity.Serialize());
}

void MQTTWrapper::on_message(const struct mosquitto_message* message) {
    string topic = message->topic;
    if (message->payloadlen < 1) {
        cerr << "No payload found. Returning...\n";
        return;
    }

    string payload = string((const char*) message->payload, message->payloadlen);
//    cerr << topic << " - " << payload << endl;
    try {
        Serializable *notification = new Serializable(payload);
        notification->forceSetName(topic);
        nc.postNotification(notification);
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
}
