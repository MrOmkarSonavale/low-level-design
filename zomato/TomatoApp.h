#ifndef TOMATO_APP_H
#define TOMATO_APP_H

#include <vector>
#include <string>
#include "models/User.h"
#include "models/Restaurant.h"
#include "models/Cart.h"
#include "managers/RestaurantManager.h"
#include "managers/OrderManager.h"
#include "strategies/PaymentStrategy.h"
#include "strategies/UpiPaymentStrategy.h"
#include "factories/NowOrderFactory.h"
#include "factories/ScheduleOrderFactory.h"
#include "services/NotificationServices.h"
#include "utils/TimeUtils.h"

using namespace std;

class TomatoApp
{
public:
    TomatoApp()
    {
        initializeRestaurants();
    }

    void initializeRestaurants()
    {
        Restaurant *restaurant1 = new Restaurant("Bikaner", "Delhi");
        restaurant1->addMenuItem(MenuItem("P1", "Chole Bhature", 120));
        restaurant1->addMenuItem(MenuItem("P2", "Samosa", 15));

        Restaurant *restaurant2 = new Restaurant(
            "Haldiram", "Kolkata");
        restaurant2->addMenuItem(MenuItem("P1", "Raj Kachori", 80));
        restaurant2->addMenuItem(MenuItem("P2", "Pav Bhaji", 100));
        restaurant2->addMenuItem(MenuItem("P3", "Dhokla", 50));

        Restaurant *restaurant3 = new Restaurant("Saravana Bhavan", "Chennai");
        restaurant3->addMenuItem(MenuItem("P1", "Masala Dosa", 90));
        restaurant3->addMenuItem(MenuItem("P2", "Idli Vada", 60));
        restaurant3->addMenuItem(MenuItem("P3", "Filter Coffee", 30));

        RestaurantManager *restaurantManager = RestaurantManager::getInstance();
        restaurantManager->addRestaurant(restaurant1);
        restaurantManager->addRestaurant(restaurant2);
        restaurantManager->addRestaurant(restaurant3);
    };

    vector<Restaurant *> searchRestaurants(const string &location)
    {
        return RestaurantManager::getInstance()->searchByLocation(location);
    };

    void selectRestaurant(User *user, Restaurant *restaurant)
    {
        Cart *cart = user->getCart();
        cart->setRestaurant(restaurant);
    };

    void addToCart(User *user, const string &itemCode)
    {
        Restaurant *restaurant = user->getCart()->getRestaurant();

        if (!restaurant)
        {
            cout << "Please select a restaurant first" << endl;
            return;
        };

        for (const auto &item : restaurant->getMenu())
        {
            if (item.getCode() == itemCode)
            {
                user->getCart()->addItem(item);
                break;
            }
        };
    };

    Order *checkoutNow(User *user, const string &orderType, PaymentStrategy *paymentStrategy)
    {
        return checkout(user, orderType, PaymentStrategy, new NowOrderFactory());
    };

    Order *checkoutScheduled(User *user, const string &prderType, PaymentStrategy *paymentStrategy, const string &scheduleTime)
    {
        return checkout(user, orderType, paymentStrategy, new ScheduledOrderFactory(scheduleTime));
    };

    Order *checkout(User *user, const string &orderType, PaymentStrategy *paymentStrategy, OrderFactory *orderFactory)
    {
        if (user->getCart()->isEmpty())
            return nullptr;

        Cart *userCart = user->getCart();
        Restaurant *orderRestaurant = userCart->getRestaurant();

        vector<MenuItem> iteamOrdered = userCart->getIteam();

        double totalCost = userCart->getTotalCost();

        Order *order = OrderFactory->createOrder(user, userCart, orderRestaurant, iteamOrdered, paymentStrategy, totalCost, orderType);

        OrderManager::getInstance()->addOrder(order);

        return order;
    };

    void payForOrder(User *user, Order *order)
    {
        bool isPaymentSuccess = order->processPayment();

        if (isPaymentSuccess)
        {
            NotificationService *notification = new NotificationService();
            notification->notify(order);
            user->getCart()->clear();
        }
    };

    void printUserCart(User *user)
    {
        cout << "Items in cart:" << endl;
        cout << "------------------------------------" << endl;
        for (const auto &item : user->getCart()->getIteam())
        {
            cout << item.getCode() << " : " << item.getName() << " : ₹" << item.getPrice() << endl;
        }
        cout << "------------------------------------" << endl;
        cout << "Grand total : ₹" << user->getCart()->getTotalCost() << endl;
    }
};

#endif