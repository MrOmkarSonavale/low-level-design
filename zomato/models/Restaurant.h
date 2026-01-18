#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <iostream>
#include <string>
#include <vector>
#include "MenuItem.h"

class Restaurant
{
private:
    static int nextRestaurantId;
    int restaurantId;
    string name;
    string location;
    vector<MenuItem> menu;

public:
    Restaurant(const string &name, const string &location)
    {
        this->name = name;
        this->location = location;
        this->restaurantId = ++nextRestaurantId;
    };

    ~Restaurant()
    {
        cout << "Destroying Restaurant" << name << ", and clearing its menu." << endl;
        menu.clear();
    };

    string getName()
    {
        return name;
    };

    void setName(const string &localName)
    {
        name = localName;
    };

    void setLocation(const string &loc)
    {
        location = loc;
    };

    void addMenuItem(const MenuItem &item)
    {
        menu.push_back(item);
    };

    vector<MenuItem> &getMenu()
    {
        return menu;
    }
};

int Restaurant::nextRestaurantId = 0;

#endif