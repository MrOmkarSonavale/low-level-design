#include <iostream>
#include <string>

using namespace std;

class Engine
{
public:
    virtual void startEngine() = 0;
};

class PetrolEngine : public Engine
{
public:
    void startEngine()
    {
        cout << "petrol engine is starting" << endl;
    }
};

class DisealEngine : public Engine
{
public:
    void startEngine()
    {
        cout << "Diseal Engine is starting" << endl;
    };
};

class ElectricEngine : public Engine
{
public:
    void startEngine()
    {
        cout << "motor is rotating" << endl;
    };
};

class Vehicle
{
protected:
    Engine *engine;

public:
    Vehicle(Engine *engine) : engine(engine) {};

    virtual void startCar() = 0;
};

class Sedan : public Vehicle
{
public:
    Sedan(Engine *engine) : Vehicle(engine) {};

    void startCar() override
    {
        engine->startEngine();
    }
};

class SUV : public Vehicle
{
public:
    SUV(Engine *engine) : Vehicle(engine) {};

    void startCar() override
    {
        engine->startEngine();
    }
};

int main(void)
{
    Engine *petrolEngine = new PetrolEngine();
    Vehicle *bmw = new SUV(petrolEngine);
    bmw->startCar();
    return 0;
}
