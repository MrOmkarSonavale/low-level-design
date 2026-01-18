#ifndef SCHEDULED_ORDER_FACTORY_H
#define SCHEDULED_ORDER_FACTORY_H

#include "OrderFactory.h"
#include "../models/DeliveryOrder.h"
#include "../models/PickupOrder.h"
#include "../utils/TimeUtils.h"

using namespace std;

class ScheduledOrderFactory : public OrderFactory
{
private:
    string scheduleTime;

public:
    ScheduledOrderFactory(string scheduleTime)
    {
        this->scheduleTime = scheduleTime;
    };

    Order *createOrder(User *user, Cart *cart, Restaurant *restaurant, const vector<MenuItem> &menuItems, PaymentStreategy *paymentStreategy, double totalcost, const string &orderType) override
    {
        Order *order = nullptr;

        if (orderType == "Delivery")
        {
            auto deliveryOrdre = new DeliveryOrder();
            deliveryOrder->setUserAddress(user->getAddress());

            order = deliveryOrder;
        }
        else
        {
            auto pickupOrder = new PickupOrder();
            pickupOrder->setRestaurantAddress(restaurant->getLocation());
        };

        order->setUser(user);
        order->setRestaurant(restaurant);
        order->setItems(menuItems);
        order->setPaymentStrategy(paymentStreategy);
        order->setScheduled(scheduleTime);
        order->setTotal(totalcost);
        return order;
    };
};

#endif