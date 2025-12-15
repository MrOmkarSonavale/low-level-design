#include <iostream>

using namespace std;

class Singalton
{
private:
    static Singalton *instance;

    Singalton()
    {
        cout << "this is singalton" << endl;
    };

public:
    static Singalton *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Singalton();
        }

        return instance;
    }
};

Singalton *Singalton::instance = nullptr;

int main(void)
{
    Singalton *Singalton1 = Singalton::getInstance();
    Singalton *Singalton2 = Singalton::getInstance();

    if (Singalton1 == Singalton2)
    {
        cout << "Both instances are the same" << endl;
    }
    else
    {
        cout << "Instance are difference" << endl;
    };

    return 0;
}