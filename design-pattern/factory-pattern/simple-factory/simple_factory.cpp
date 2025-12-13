#include <iostream>

using namespace std;

class Burger
{
public:
    virtual void prepareBurger() = 0;
    virtual ~Burger() {};
};

class BasicBurger : public Burger
{
public:
    void prepareBurger()
    {
        cout << "preparing the basic burger" << endl;
    }
};

class StandardBurger : public Burger
{
public:
    void prepareBurger()
    {
        cout << "preparing the standard burger" << endl;
    }
};

class PremiumBurger : public Burger
{
public:
    void prepareBurger()
    {
        cout << "preparing the premium burger" << endl;
    }
};

class BurgerFactory
{
private:
    Burger *myburger;

public:
    Burger *createBurger(string &type)
    {
        if (type == "basic")
        {
            return new BasicBurger();
        }
        else if (type == "standard")
        {
            return new StandardBurger();
        }
        else if (type == "premium")
        {
            return new PremiumBurger();
        }
        else
        {
            cout << "unknown burger type" << endl;
            return nullptr;
        }
    };
};

int main(void)
{
    BurgerFactory f1;
    Burger *myburger;
    string type;
    type = "premium";

    myburger = f1.createBurger(type);

    myburger->prepareBurger();
    return 0;
};