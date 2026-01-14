#include <iostream>

using namespace std;

// command interface
class command
{
public:
    virtual void execute() = 0; // Pure virtual function
    virtual void undo() = 0;    // Pure virtual function
    virtual ~command() {}       // Virtual destructor
};

// receiver classes
class Light
{
public:
    void on()
    {
        cout << "Light is ON" << endl;
    }

    void off()
    {
        cout << "Light is OFF" << endl;
    }
};

class Fan
{
public:
    void on()
    {
        cout << "Fan is ON" << endl;
    }

    void off()
    {
        cout << "Fan is OFF" << endl;
    }
};

// concrete command classes

class LightOnCommand : public command
{
private:
    Light *light;

public:
    LightOnCommand(Light *l) : light(l) {};

    void execute() override
    {
        light->on();
    }

    void undo() override
    {
        light->off();
    }
};

class FanOnCommand : public command
{
private:
    Fan *fan;

public:
    FanOnCommand(Fan *f) : fan(f) {};

    void execute() override
    {
        fan->on();
    }

    void undo() override
    {
        fan->off();
    }
};

// invoker class Remote Controller with static 2d array of 6 button

class RemoteController
{
private:
    static const int numButtons = 6;
    command *buttons[numButtons];   // 2D array for commands and undo command
    bool buttonPressed[numButtons]; // Track button pressed state
public:
    RemoteController()
    {
        for (int i = 0; i < numButtons; i++)
        {
            buttons[i] = nullptr;
            buttonPressed[i] = false;
        }
    }

    void setCommand(int index, command *cmd)
    {
        if (index >= 0 && index < numButtons)
        {
            if (buttons[index] != nullptr)
            {
                delete buttons[index]; // Clean up previous command
                buttons[index] = cmd;
                buttonPressed[index] = false; // Reset button state
            }
        };
    };

    void pressButton(int index)
    {
        if (index >= 0 && index < numButtons && buttons[index] != nullptr)
        {
            if (buttonPressed[index] == false)
            {
                buttons[index]->execute(); // Mark button as pressed
            }
            else
            {
                buttons[index]->undo(); // Undo the command if already pressed
            }

            buttonPressed[index] = !buttonPressed[index]; // Toggle button state
        }
        else
        {
            cout << "Invalid button index or command not set." << endl;
        }
    }

    ~RemoteController()
    {
        for (int i = 0; i < numButtons; i++)
        {
            delete buttons[i]; // Clean up all commands
        }
    };
};

int main(void)
{
    Light *livingLight = new Light();
    Fan *ceilingFan = new Fan();

    RemoteController *remote = new RemoteController();

    remote->setCommand(0, new LightOnCommand(livingLight));

    remote->setCommand(1, new FanOnCommand(ceilingFan));

    // Pressing button 0 to turn on the light
    remote->pressButton(0); // Output: Light is ON
    // Pressing button 0 again to turn off the light
    remote->pressButton(0); // Output: Light is OFF
}