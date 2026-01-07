#include <iostream>

using namespace std;

class PowerSupply
{
public:
    void on()
    {
        cout << "Power Supply On" << endl;
    }
};

class CPU
{
public:
    void start()
    {
        cout << "CPU Started" << endl;
    }
};

class Memory
{
public:
    void load()
    {
        cout << "Memory Loaded" << endl;
    }
};

class HardDrive
{
public:
    void read()
    {
        cout << "Hard Drive Read" << endl;
    }
};

class Bios
{
public:
    void initialize(Memory &memory, CPU &cpu, HardDrive &hardDrive)
    {
        cout << "Bios Initialized" << endl;
        memory.load();
        cpu.start();
        hardDrive.read();
    }
};

class Facade
{
private:
    PowerSupply powerSupply;
    CPU cpu;
    Memory memory;
    HardDrive hardDrive;

public:
    void startComputer()
    {
        powerSupply.on();
        Bios bios;
        bios.initialize(memory, cpu, hardDrive);
    }
};

int main(void)
{
    Facade facade;
    facade.startComputer();
    return 0;
}