#ifndef USER_H
#define USER_H

#include <string>
#include "Cart.h"

class User
{
private:
    int userId;
    string name;
    string address;
    Cart *cart;

public:
    User(int userId, const string &name, const string &address)
    {
        this->userId = userId;
        this->name = name;
        this->address = address;
        cart = new Cart();
    };

    ~User()
    {
        delete cart;
    };

    string getName()
    {
        return name;
    };

    void setName(const string &name)
    {
        name = name;
    };

    string getAddress()
    {
        return address;
    };

    void setAddress(const string &address)
    {
        address = address;
    };

    Cart *getCart()
    {
        return cart;
    };
};

#endif