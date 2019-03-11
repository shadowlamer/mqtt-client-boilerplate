///
#include <Payment.h>

Payment::Payment(string json) : Serializable(json) {}

Payment::Payment() : Serializable() {}
Payment::Payment(Serializable &s) : Serializable(s) {}
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
