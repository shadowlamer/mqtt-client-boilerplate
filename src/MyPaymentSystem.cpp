//
// Created by sl on 28.02.2019.
//

#include <MyPaymentSystem.h>

MyPaymentSystem::MyPaymentSystem(MQTTWrapper &mqtt) : PaymentSystem(mqtt) {}

/**
 * Checks payment system availability
 * Demo payment system always working.
 * @return  true if payment system is in working state
 */
bool MyPaymentSystem::checkPresence() {
    return true;
}

/**
 * Checks if payment should be accepted
 * Demo payment system always accepts payments
 * @param amount Requested payment amount
 * @return PAYMENT_CANCELLED if payment not accepted, PAYMENT_OK if accepted but remain balance not available or remain balance
 */
double MyPaymentSystem::processPayment(double amount) {
    cerr << "Payment accepted. Amount: " << amount << endl;
    return PAYMENT_OK;
}
