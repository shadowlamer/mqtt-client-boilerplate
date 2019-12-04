/**
 * @file Payment.cpp
 * @brief Реализация класса Payment.
 * @author Vadim Cherenev
 * @date 21.02.2019
 * @copyright MIT License
 */

#include <Payment.h>

Payment::Payment(string json) : Serializable(json) {}

Payment::Payment() : Serializable() {}
Payment::Payment(Serializable &s) : Serializable(s) {}

/**
 * @param amount Сумма платежной операции.
 * @param paymentType Тип платежной операции
 * @param remain Остаток средств.
 * @param price Цена.
 * @param quantity Количество товара.
 * @sa Payment::PaymentType
 */
Payment::Payment(double amount, int paymentType, double remain, double price, double quantity) : Serializable() {
    setAmount(amount);
    setPaymentType(paymentType);
    setRemain(remain);
    setPrice(price);
    setQuantity(quantity);
}

GETTER_SETTER(double, Payment, getAmount, setAmount, "amount")
GETTER_SETTER(int, Payment, getPaymentType, setPaymentType, "paymentType")
GETTER_SETTER(double, Payment, getRemain, setRemain, "remain")
GETTER_SETTER(double, Payment, getQuantity, setQuantity, "quantity")
GETTER_SETTER(double, Payment, getPrice, setPrice, "price")
