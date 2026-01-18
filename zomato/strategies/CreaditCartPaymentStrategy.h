#ifndef CREDIT_CARD_PAYMENT_STRATEGY_H
#define CREDIT_CARD_PATMENT_STRATEGY_H

#include "PaymentStrategy.h"
#include <iostream>
#include <string>

using namespace std;

class CreditCardPaymentStrategy : public PaymentStrategy
{
private:
    string cardNumber;

public:
    CreditCardPaymentStrategy(const string &card)
    {
        cardNumber = card;
    };

    void pay(double amount) override
    {
        cout << "PAID $" << amount << "using credit card (" << cardNumber << ")" << endl;
    };
};

#endif