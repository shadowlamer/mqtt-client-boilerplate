//
// Created by sl on 28.02.2019.
//

#include <MyPaymentSystem.h>

MyPaymentSystem::MyPaymentSystem(MQTTWrapper &mqtt) : PaymentSystem(mqtt), kbd("/dev/input/event1") {}

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
 * @param amount Requested payment amount
 * @return PAYMENT_CANCELLED if payment not accepted, PAYMENT_OK if accepted but remain balance not available or remain balance
 */
double MyPaymentSystem::processPayment(double amount) {
    double remain = credit - amount;
    if (remain >= 0) {
        cerr << "Payment accepted. Amount: " << amount << ", Remain balance: " << remain << endl;
        credit = remain;
    } else {
        //You can show additional messages on terminal LCD.
        //They will be shown after system messages.
        alert(Utf8ToCp1251Converter::utfToCp(" YOU DON'T HAVE "    //  two
                                             "  ENOUGH MONEY  ")); //  lines
//                                           |<-- 16 chars -->|
        cerr << "Not enough money" << endl;
    }
    return remain;
}

/**
 * Accepts deposite
 * @param amount Requested deposite amount
 * @return Remain balance
 */
double MyPaymentSystem::processDeposite(double amount) {
    double remain = credit - amount; //deposite amount is negative
    cerr << "Deposite accepted. Amount: " << -amount << ", Remain balance: " << remain << endl;
    credit = remain;
    return remain;
}

/**
 * Runs every 200ms.
 * @see MQTTTask.cpp
 */
void MyPaymentSystem::loop() {
    kbd.getDigit();
    if (kbd.checkSpecial(KBD_ENTER)) {
        requestDeposite(credit); //request deposite on event. E.g. card inserted or key pressed.
    }
}
