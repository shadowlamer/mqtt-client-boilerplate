//
// Created by sl on 28.02.2019.
//

#ifndef MQTT_CLIENT_BOILERPLATE_PAYMENTSYSTEM_H
#define MQTT_CLIENT_BOILERPLATE_PAYMENTSYSTEM_H

#include <domain/ActionListener.h>
#include <domain/Payment.h>
#include <mqtt/MQTTWrapper.h>

#define LOCAL_REQUEST_TOPIC   "local/pay/request"
#define LOCAL_RESPONSE_TOPIC  "local/pay/response"
#define LOCAL_PROCESS_TOPIC   "local/pay/process"
#define LOCAL_DEPOSITE_TOPIC  "local/pay/depo"
#define LOCAL_ALERT_TOPIC     "local/alert"

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
