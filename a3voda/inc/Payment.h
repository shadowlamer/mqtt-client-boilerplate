#pragma once

#include <iostream>
#include <Serializable.h>

#define PAYMENT_OK 0.0
#define PAYMENT_CANCELLED -1.0

enum {
 PT_CASH = 0,
 PT_CARD
};

class Payment : public Serializable {
public:
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
