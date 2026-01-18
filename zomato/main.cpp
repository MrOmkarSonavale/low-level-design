#include <iostream>
#include "TomatoApp.h"

int main()
{
    TomatoApp *tomato = new TomatoApp();

    User *user = new User(101, "Omkar", "Pune");
    cout << "User: " << user->getName() << " is active" << endl;

    vector<Restaurant *> restaurantList = tomato->searchRestaurants("puen");

    if (restaurantList.empty())
    {
        cout << "No restaurants found!" << endl;
        return 0;
    }
    cout << "Found Restaurants:" << endl;
    for (auto restaurant : restaurantList)
    {
        cout << " - " << restaurant->getName() << endl;
    };

    tomato->selectRestaurant(user, restaurantList[0]);

    cout << "Selected restaurant: " << restaurantList[0]->getName() << endl;

    tomato->addToCart(user, "P1");
    tomato->addToCart(user, "P2");

    tomato->printUserCart(user);

    Order *order = tomato->checkoutNow(user, "Delivery", new UpiPaymentStrategy("1234567890"));

    // User pay for the cart. If payment is success, notification is sent.
    tomato->payForOrder(user, order);

    // Cleanup Code.
    delete tomato;
    delete user;

    return 0;
}