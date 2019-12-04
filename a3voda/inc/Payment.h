/**
 * @file Payment.h
 * @brief Заголовочный файл для класса Payment.
 * @author Vadim Cherenev
 * @date 21.02.2019
 * @copyright MIT License
 */

#pragma once

#include <iostream>
#include <Serializable.h>

/**
 * Результат операции: операция прошла успешно.
 */
#define PAYMENT_OK 0.0
/**
 * Результат операции: операция отклонена.
 */
#define PAYMENT_CANCELLED -1.0

/**
 * @class Payment Payment.h
 * @brief Доменная сущность. Описывает операцию "Продажа".
 *   - Аттрибуты сущности:
 *     -# double amount,
 *     -# int paymentType,
 *     -# double remain,
 *     -# double price,
 *     -# double quantity
 */
class Payment : public Serializable {
public:
    /**
     * @enum PaymentType
     * @brief Тип платежа.
     */
    enum PaymentType {
        PT_CASH = 0,  /**< Платеж наличными */
        PT_CARD       /**< Безналичный платеж */
    };

    Payment();
    explicit Payment(string json);
    explicit Payment(Serializable &s);
    explicit Payment(double amount, int paymentType = PT_CARD, double remain = 0.0, double price = 0.0, double quantity = 0.0);

    GETTER_SETTER_HEADER(double, getAmount, setAmount, PAYMENT_OK)
    GETTER_SETTER_HEADER(int, getPaymentType, setPaymentType, 0)
    GETTER_SETTER_HEADER(double, getRemain, setRemain, 0.0)
    GETTER_SETTER_HEADER(double, getPrice, setPrice, 0.0)
    GETTER_SETTER_HEADER(double, getQuantity, setQuantity, 0.0)
};
