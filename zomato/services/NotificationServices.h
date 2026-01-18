#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVICE_H

#include <iostream>
#include "../models/Order.h"

class NotificationService
{
public:
    static void notify(Order *order)
    {
        cout << "\n Notification: New" << order->getType() << "order placed" << endl;
        cout << "-------------------------------------" << endl;

        cout << "Order Id: " << order->getOrderId() << endl;
        cout << "Customer: " << order->getUser()->getName() << endl;
        cout << "Restaturant: " << order->getRestaurant()->getName() << endl;
        cout << "Items Ordered:\n";

        const vector<MenuItem> &items = order->getItems();

        for (const auto &item : items)
        {
            cout << "    - " << item.getName() << " ($" << item.getPrice() << ")\n";
        };

        cout << "Total: $" << order->getTotal() << endl;
        cout << "Scheduled For: " << order->getScheduled() << endl;
        cout << "-------------------------------------------"
             << endl;
    }
};

#endif