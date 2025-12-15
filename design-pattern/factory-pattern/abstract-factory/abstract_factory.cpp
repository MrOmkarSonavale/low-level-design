#include <iostream>
using namespace std;

class Burger
{
public:
    virtual void prepare() = 0;
    virtual ~Burger() {};
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
    void prepare() override
    {
        cout << "Preparing a standard burger with lettuce and tomato." << endl;
    }
};

class PremiumBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Preparing a premium burger with cheese, bacon, and avocado." << endl;
    }
};

class WheatBasicBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Preparing a wheat basic burger." << endl;
    }
};

class WheatStandardBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Preparing a wheat standard burger with lettuce and tomato." << endl;
    }
};

class WheatPremiumBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Preparing a wheat premium burger with cheese, bacon, and avocado." << endl;
    }
};

class GarlicBread
{
public:
    virtual void prepare() = 0;
    virtual ~GarlicBread() {};
};

class BasicGarlicBread : public GarlicBread
{
public:
    void prepare() override
    {
        cout << "Preparing basic garlic bread." << endl;
    }
};

class StandardGarlicBread : public GarlicBread
{
public:
    void prepare() override
    {
        cout << "Preparing standard garlic bread with butter and garlic." << endl;
    }
};

class PremiumGarlicBread : public GarlicBread
{
public:
    void prepare() override
    {
        cout << "Preparing premium garlic bread with herbs and cheese." << endl;
    }
};

class WheatBasicGarlicBread : public GarlicBread
{
public:
    void prepare() override
    {
        cout << "Preparing wheat basic garlic bread." << endl;
    }
};

class WheatStandardGarlicBread : public GarlicBread
{
public:
    void prepare() override
    {
        cout << "Preparing wheat standard garlic bread with butter and garlic." << endl;
    }
};

class WheatPremiumGarlicBread : public GarlicBread
{
public:
    void prepare() override
    {
        cout << "Preparing wheat premium garlic bread with herbs and cheese." << endl;
    }
};

class factory
{
public:
    virtual Burger *createBurger(string &type) = 0;
    virtual GarlicBread *createGarlicBread(string &type) = 0;
    virtual ~factory() {};
};

class OmkarFactory : public factory
{
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
            cout << "Unknown burger type: " << type << endl;
            return nullptr;
        }
    }

    GarlicBread *createGarlicBread(string &type)
    {
        if (type == "basic")
        {
            return new BasicGarlicBread();
        }
        else if (type == "standard")
        {
            return new StandardGarlicBread();
        }
        else if (type == "premium")
        {
            return new PremiumGarlicBread();
        }
        else
        {
            cout << "Unknown garlic bread type: " << type << endl;
            return nullptr;
        }
    }
};

class kingFactory : public factory
{
public:
    Burger *createBurger(string &type)
    {
        if (type == "basic")
        {
            return new WheatBasicBurger();
        }
        else if (type == "standard")
        {
            return new WheatStandardBurger();
        }
        else if (type == "premium")
        {
            return new WheatPremiumBurger();
        }
        else
        {
            cout << "Unknown burger type: " << type << endl;
            return nullptr;
        }
    }

    GarlicBread *createGarlicBread(string &type)
    {
        if (type == "basic")
        {
            return new WheatBasicGarlicBread();
        }
        else if (type == "standard")
        {
            return new WheatStandardGarlicBread();
        }
        else if (type == "premium")
        {
            return new WheatPremiumGarlicBread();
        }
        else
        {
            cout << "Unknown garlic bread type: " << type << endl;
            return nullptr;
        }
    };
};

int main(void)
{
    string burderType = "basic";
    string garlicBreadType = "basic";

    factory *myFactory = new OmkarFactory();
    Burger *myBurger = myFactory->createBurger(burderType);

    GarlicBread *myGarlicBread = myFactory->createGarlicBread(garlicBreadType);

    myBurger->prepare();
    myGarlicBread->prepare();
    return 0;
}