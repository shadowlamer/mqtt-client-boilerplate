/**
 * @file PaymentSystem.cpp
 * @brief Реализация класса PaymentSystem.
 * @author Vadim Cherenev
 * @date 28.02.2019
 * @copyright MIT License
 */


#include <PaymentSystem.h>

/**
 * @brief Обработчик запросов
 * @sa ActionListener
 * @param s Запрос (нагрузка MQTT сообщения).
 */
void PaymentSystem::processAction(Serializable *s) {

/// Если пришел запрос на использование платежной системы,
/// вызывает метод PaymentSystem::checkPresence для проверки готовности платежной системы.
/// Результат проверки публикует в топик заданный #LOCAL_RESPONSE_TOPIC
    if (s->name() == LOCAL_REQUEST_TOPIC) {
        if (checkPresence()) {
            Payment paymentOk(PAYMENT_OK);
            mqtt.publish(LOCAL_RESPONSE_TOPIC, paymentOk);
        }
    }

/// Если пришел запрос на платежную операцию
/// и сумма операции больше нуля, то вызывает метод PaymentSystem::processPayment.
/// Если остаток денежных средств не позволяет совершить операцию, то отклоняет платеж.
/// Иначе публикует результат операции в топик, заданный #LOCAL_RESPONSE_TOPIC.
/// Если сумма операции меньше нуля, то вызывает метод PaymentSystem::processDeposite.
/// Результат операции публикует в топик, заданный #LOCAL_DEPOSITE_TOPIC.
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

/**
 * @brief Отправляет извещение, которое будет показано на экране автомата.
 * Публикует сообщение в топик, заданный #LOCAL_ALERT_TOPIC
 * @param message Текст извещения.
 * @sa LcdHelper
 * @sa Utf8ToCp1251Converter
 */

void PaymentSystem::alert(string message) {
/// Пример отправки сообщения:
/// @snippet MyPaymentSystem.cpp Show message
    mqtt.publish(LOCAL_ALERT_TOPIC, message);
}

/**
 * @brief Проверяет работоспособность платежной системы.
 * Метод нужно переопределить для проверки состояния реальной платежной системы.
 * @return true, если платежная система доступна.
 */
bool PaymentSystem::checkPresence() {
    return false;
}

/**
 * @brief Обрабатывает платежную операцию.
 * Метод нужно переопределить для совершения реальных платежных операций.
 * @param amount Сумма операции (положительная).
 * @return Остаток средств после совершения операции (возможно отрицательный), или #PAYMENT_OK, или #PAYMENT_CANCELLED
 */
double PaymentSystem::processPayment(double amount) {
    (void) amount;
    return PAYMENT_CANCELLED;
}

/**
 * @brief Обрабатывает зачисление средств.
 * Метод нужно переопределить для совершения реальных операций по зачислению.
 * @param amount Сумма операции (отрицательная)
 * @return Остаток средств после совершения операции, или #PAYMENT_OK, или #PAYMENT_CANCELLED
 */
double PaymentSystem::processDeposite(double amount) {
    (void) amount;
    return PAYMENT_CANCELLED;
}

/**
 * @brief Запрашивает процедуру зачисления средств по внешнему событию.
 * Например при поднесении карты к считывателю.
 * @param remain Текущий остаток средств, будет показан на дисплее.
 */
void PaymentSystem::requestDeposite(double remain) {
/// Пример запроса зачисления средств:
/// @snippet MyPaymentSystem.cpp Request depo
    Payment depoRequest(PAYMENT_OK, Payment::PaymentType::PT_CARD, remain);
    mqtt.publish(LOCAL_DEPOSITE_TOPIC, depoRequest);
}

/**
 * @param _mqtt экземпляр MQTTWrapper для публикации сообщений.
 */
PaymentSystem::PaymentSystem(MQTTWrapper &_mqtt) : ActionListener(), mqtt(_mqtt) {}

/**
 * @example MyPaymentSystem.cpp
 * Пример реализации платежной системы.
 */
