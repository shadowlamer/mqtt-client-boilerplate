//
// Created by sl on 28.02.2019.
//

#ifndef MQTT_CLIENT_BOILERPLATE_DEMOPAYMENTSYSTEM_H
#define MQTT_CLIENT_BOILERPLATE_DEMOPAYMENTSYSTEM_H

#include <PaymentSystem.h>
#include <StateMachine.h>
#include <KBDHelper.h>
#include <Utf8ToCp1251Converter.h>

class MyPaymentSystem : public PaymentSystem, public StateMachine {
public:
    MyPaymentSystem(MQTTWrapper &mqtt);
    bool checkPresence() override;
    double processPayment(double amount) override;
    double processDeposite(double amount) override;
    void loop() override;
private:
    KBDHelper kbd;
    double credit = 100;
};

#endif //MQTT_CLIENT_BOILERPLATE_DEMOPAYMENTSYSTEM_H
