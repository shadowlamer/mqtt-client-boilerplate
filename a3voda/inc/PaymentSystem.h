/**
 * @file PaymentSystem.h
 * @brief Заголовочный файл для класса PaymentSystem.
 * @author Vadim Cherenev
 * @date 28.02.2019
 * @copyright MIT License
 */

#ifndef MQTT_CLIENT_BOILERPLATE_PAYMENTSYSTEM_H
#define MQTT_CLIENT_BOILERPLATE_PAYMENTSYSTEM_H

#include <ActionListener.h>
#include <Payment.h>
#include <MQTTWrapper.h>

/**
 * @brief Топик для получения запроса на использование платежной стсиемы
 */
#define LOCAL_REQUEST_TOPIC   "local/pay/request"
/**
 * @brief Топик для отправки ответов
 */
#define LOCAL_RESPONSE_TOPIC  "local/pay/response"
/**
 * @brief Топик для получения запроса на платежную операцию
 */
#define LOCAL_PROCESS_TOPIC   "local/pay/process"
/**
 * @brief Топик для отправки запроса на внесение средств
 */
#define LOCAL_DEPOSITE_TOPIC  "local/pay/depo"
/**
 * @brief Топик для отправки извещений
 */
#define LOCAL_ALERT_TOPIC     "local/alert"

/**
 * @class PaymentSystem PaymentSystem.h
 * @brief Базовый класс платежной системы.
 * Для реализации своей платежной системы необходимо переопределить методы
 * PaymentSystem::checkPresence, PaymentSystem::processPayment, PaymentSystem::processDeposite.
 * Смотри пример реализации.
 */
class PaymentSystem : public ActionListener {
public:
    PaymentSystem(MQTTWrapper &mqtt);
    void processAction(Serializable *s) override;
    void alert(string message);
    virtual bool checkPresence();
    virtual double processPayment(double amount);
    virtual double processDeposite(double amount);
    virtual void requestDeposite(double remain);

private:
    MQTTWrapper &mqtt;
};

#endif //MQTT_CLIENT_BOILERPLATE_PAYMENTSYSTEM_H
