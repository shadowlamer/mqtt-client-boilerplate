//
// Created by sl on 28.02.2019.
//

#ifndef MQTT_CLIENT_BOILERPLATE_DEMOPAYMENTSYSTEM_H
#define MQTT_CLIENT_BOILERPLATE_DEMOPAYMENTSYSTEM_H

#include <logic/PaymentSystem.h>

class MyPaymentSystem : public PaymentSystem {
public:
    MyPaymentSystem(MQTTWrapper &mqtt);
    bool checkPresence() override;
    double processPayment(double amount) override;
};

#endif //MQTT_CLIENT_BOILERPLATE_DEMOPAYMENTSYSTEM_H
