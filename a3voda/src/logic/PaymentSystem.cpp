//
// Created by sl on 28.02.2019.
//

#include <logic/PaymentSystem.h>

void PaymentSystem::processAction(Serializable *s) {
    if (s->name() == LOCAL_REQUEST_TOPIC) {
        if (checkPresence()) {
            Payment paymentOk(PAYMENT_OK);
            mqtt.publish(LOCAL_RESPONSE_TOPIC, paymentOk);
        } else {
            Payment paymentFail(PAYMENT_CANCELLED);
            mqtt.publish(LOCAL_RESPONSE_TOPIC, paymentFail);
        }
    }

    if (s->name() == LOCAL_PROCESS_TOPIC) {
        Payment incomingPayment(*s);
        double amount = incomingPayment.getAmount();
        double remain = processPayment(amount);
        incomingPayment.setRemain(remain);
        mqtt.publish(LOCAL_RESPONSE_TOPIC, incomingPayment);
    }
}

bool PaymentSystem::checkPresence() {
    return false;
}

double PaymentSystem::processPayment(double amount) {
    (void) amount;
    return PAYMENT_CANCELLED;
}

PaymentSystem::PaymentSystem(MQTTWrapper &_mqtt) : ActionListener(), mqtt(_mqtt) {}
