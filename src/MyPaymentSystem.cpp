/**
 * @file MyPaymentSystem.cpp
 * @brief Implementation of MyPaymentSystem
 * @author Vadim Cherenev
 * @date 28.02.2019
 * @copyright MIT License
 */


#include <MyPaymentSystem.h>

MyPaymentSystem::MyPaymentSystem(MQTTWrapper &mqtt) : PaymentSystem(mqtt),
    kbd(KBDHelper::findDeviceByName("sunxi-keyboard")) {}

/**
 * Checks payment system availability
 * Demo payment system always working.
 * @return  true if payment system is in working state
 */
/// [Check pay system]
bool MyPaymentSystem::checkPresence() {
// Demo system is always working
    return true;
}
/// [Check pay system]

/**
 * Checks if payment should be accepted
 * @param amount Requested payment amount
 * @return PAYMENT_CANCELLED if payment not accepted, PAYMENT_OK if accepted but remain balance not available or remain balance
 */
 /// [Process payment]
double MyPaymentSystem::processPayment(double amount) {
// Check remain
    double remain = credit - amount;
    if (remain >= 0) {
        cerr << "Payment accepted. Amount: " << amount << ", Remain balance: " << remain << endl;
        credit = remain;
    } else {
        //You can show additional messages on terminal LCD.
        //They will be shown after system messages.
/// [Show message]
        alert(Utf8ToCp1251Converter::utfToCp(" YOU DON'T HAVE "    //  two
                                             "  ENOUGH MONEY  ")); //  lines
//                                           |<-- 16 chars -->|
/// [Show message]
        cerr << "Not enough money" << endl;
    }
    return remain;
}
/// [Process payment]

/**
 * Accepts deposite
 * @param amount Requested deposite amount
 * @return Remain balance
 */
/// [Process depo]
double MyPaymentSystem::processDeposite(double amount) {
    double remain = credit - amount; //deposite amount is negative
    cerr << "Deposite accepted. Amount: " << -amount << ", Remain balance: " << remain << endl;
    credit = remain;
    return remain;
}
/// [Process depo]

/**
 * Runs every 200ms.
 * @see MQTTTask.cpp
 */
/// [Main loop]
void MyPaymentSystem::loop() {
/// [Request depo]
    kbd.getDigit();
    if (kbd.checkSpecial(KBD_ENTER)) {
        requestDeposite(credit); //request deposite on event. E.g. card inserted or key pressed.
    }
/// [Request depo]
}
/// [Main loop]
