//
// Created by sl on 28.02.2019.
//

#include <PaymentSystem.h>

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
        if (amount >= 0) {
            double remain = processPayment(amount);
            if (remain < 0)
                incomingPayment.setAmount(PAYMENT_CANCELLED);
            incomingPayment.setRemain(remain);
            mqtt.publish(LOCAL_RESPONSE_TOPIC, incomingPayment);
        } else {
            double remain = processDeposite(amount);
            if (remain >= 0) { //publish deposite only if remain balance positive
                incomingPayment.setRemain(remain);
                mqtt.publish(LOCAL_DEPOSITE_TOPIC, incomingPayment);
            }
        }
    }
}

void PaymentSystem::alert(string message) {
    mqtt.publish(LOCAL_ALERT_TOPIC, message);
}

bool PaymentSystem::checkPresence() {
    return false;
}

double PaymentSystem::processPayment(double amount) {
    (void) amount;
    return PAYMENT_CANCELLED;
}

double PaymentSystem::processDeposite(double amount) {
    (void) amount;
    return PAYMENT_CANCELLED;
}

void PaymentSystem::requestDeposite(double remain) {
    Payment depoRequest(PAYMENT_OK, PT_CARD, remain);
    mqtt.publish(LOCAL_DEPOSITE_TOPIC, depoRequest);
}

PaymentSystem::PaymentSystem(MQTTWrapper &_mqtt) : ActionListener(), mqtt(_mqtt) {}
