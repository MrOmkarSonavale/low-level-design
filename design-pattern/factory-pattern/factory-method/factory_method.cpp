#include <iostream>
using namespace std;

class Burger
{
public:
    virtual void prepareBurger() = 0;
    virtual ~Burger() {}
};

class BasicBurger : public Burger
{
public:
    void prepareBurger() override
    {
        cout << "Preparing the basic burger" << endl;
    }
};

class StandardBurger : public Burger
{
public:
    void prepareBurger() override
    {
        cout << "Preparing the standard burger" << endl;
    }
};

class PremiumBurger : public Burger
{
public:
    void prepareBurger() override
    {
        cout << "Preparing the premium burger" << endl;
    }
};

class BasicWheatBurger : public Burger
{
public:
    void prepareBurger() override
    {
        cout << "preparing the basic WheatBurger" << endl;
    }
};

class StandardWheatBurger : public Burger
{
public:
    void prepareBurger() override
    {
        cout << "preparing the standard WheatBurger" << endl;
    }
};

class PremiumWheatBurger : public Burger
{
public:
    void prepareBurger() override
    {
        cout << "preparing the premium WheatBurger" << endl;
    }
};

class BurgerFactory
{
public:
    virtual Burger *createBurger(string type) = 0;
    virtual ~BurgerFactory() {}
};

class SimpleBurgerFactory : public BurgerFactory
{
public:
    Burger *createBurger(string type) override
    {
        if (type == "basic")
            return new BasicBurger();
        else if (type == "standard")
            return new StandardBurger();
        else if (type == "premium")
            return new PremiumBurger();
        return nullptr;
    }
};

class WheatBurgerFactory : public BurgerFactory
{
public:
    Burger *createBurger(string type) override
    {
        if (type == "basic")
            return new BasicWheatBurger();
        else if (type == "standard")
            return new StandardWheatBurger();
        else if (type == "premium")
            return new PremiumWheatBurger();
        return nullptr;
    }
};

int main()
{
    BurgerFactory *factory = new WheatBurgerFactory();
    string type = "premium";

    Burger *myBurger = factory->createBurger(type);
    if (myBurger)
        myBurger->prepareBurger();

    delete myBurger;
    delete factory;

    return 0;
}
