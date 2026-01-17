#ifndef CART_H
#define CART_H

#include <iostream>
#include <vector>
#include <string>
#include "../models/MenuItem.h";
#include "../models/Restaurant.h";

using namespace std;

class Cart
{
private:
    Restaurant *restaurant;
    vector<MenuItem> items;

public:
    Cart()
    {
        restaurant = nullptr;
    };

    void addItem(MenuItem &item)
    {
        if (!restaurant)
        {
            cout << "Cart: set a restaurant before adding items" << endl;
        };

        items.push_back(item);
    };

    double getTotalCost()
    {
        double sum = 0;

        for (const auto &it : items)
        {
            sum += it.getPrice();
        };

        return sum;
    };

    bool isEmpty()
    {
        return !restaurant || items.empty();
    };

    void clear()
    {
        items.clear();
        restaurant = nullptr;
    };

    void setResturant(Restaurant *r)
    {
        restaurant = r;
    };

    Restaurant *getRestaurant()
    {
        return restaurant;
    };

    vector<MenuItem> getIteam()
    {
        return items;
    };
};

#endif;
