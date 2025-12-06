#include <iostream>

using namespace std;

// abstract streategy
class walkableRobot
{
public:
    virtual void walk() = 0;
    virtual ~walkableRobot() {};
};

class normalwalk : public walkableRobot
{
public:
    void walk() override
    {
        cout << "normal robot" << endl;
    }
};

class nowalk : public walkableRobot
{
public:
    void walk() override
    {
        cout << "robot is not walking " << endl;
    }
};

class talkableRobot
{
public:
    virtual void talk() = 0;
    virtual ~talkableRobot() {};
};

class normalTalk : public talkableRobot
{
public:
    void talk()
    {
        cout << "normal robot is talking" << endl;
    }
};

class noTalk : public talkableRobot
{
public:
    void talk()
    {
        cout << "robot is not talking" << endl;
    }
};

class Robot
{
protected:
    walkableRobot *walkRobot;
    talkableRobot *talkRobot;

public:
    Robot(walkableRobot *walk, talkableRobot *talk)
    {
        this->talkRobot = talk;
        this->walkRobot = walk;
    };

    void walk()
    {
        walkRobot->walk();
    }

    void talk()
    {
        talkRobot->talk();
    }
};

int main(void)
{
    // dynamicaly changing the behaviour
    Robot *r1 = new Robot(new nowalk(), new normalTalk());

    r1->talk();
    r1->walk();

    return 0;
};