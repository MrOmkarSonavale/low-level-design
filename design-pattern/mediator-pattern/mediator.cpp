#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Colleague;

class IMediator
{
public:
    virtual void registerUser(Colleague *user) = 0;
    virtual void muteUser(const string &receiver, const string &sender) = 0;
    virtual void sendAll(const string &from, const string &msg) = 0;
    virtual void sendPrivate(const string &from, const string &to, const string &msg) = 0;
    virtual ~IMediator() = default;
};

class Colleague
{
protected:
    IMediator *mediator;

public:
    Colleague(IMediator *m) : mediator(m)
    {
        mediator->registerUser(this);
    }

    virtual string getName() const = 0;
    virtual void receive(const string &from, const string &msg) = 0;

    virtual void sendAll(const string &msg)
    {
        mediator->sendAll(getName(), msg);
    }

    virtual void sendPrivate(const string &to, const string &msg)
    {
        mediator->sendPrivate(getName(), to, msg);
    }

    virtual ~Colleague() = default;
};

class Mediator : public IMediator
{
private:
    vector<Colleague *> users;
    vector<pair<string, string>> muted; // {receiver, sender}

public:
    void registerUser(Colleague *user) override
    {
        users.push_back(user);
    }

    void muteUser(const string &receiver, const string &sender) override
    {
        muted.push_back({receiver, sender});
    }

    bool isMuted(const string &receiver, const string &sender)
    {
        for (auto &m : muted)
        {
            if (m.first == receiver && m.second == sender)
                return true;
        }
        return false;
    }

    void sendAll(const string &from, const string &msg) override
    {
        for (auto user : users)
        {
            if (user->getName() == from)
                continue;

            if (!isMuted(user->getName(), from))
            {
                user->receive(from, msg);
            }
        }
    }

    void sendPrivate(const string &from, const string &to, const string &msg) override
    {
        for (auto user : users)
        {
            if (user->getName() == to)
            {
                if (isMuted(to, from))
                {
                    cout << to << " has muted " << from << endl;
                    return;
                }
                user->receive(from, msg);
                return;
            }
        }
    }
};

class User : public Colleague
{
private:
    string name;

public:
    User(const string &name, IMediator *m) : Colleague(m), name(name) {}

    string getName() const override
    {
        return name;
    }

    void receive(const string &from, const string &msg) override
    {
        cout << "[" << name << "] received from " << from << ": " << msg << endl;
    }
};

int main()
{
    IMediator *mediator = new Mediator();

    User *u1 = new User("omkar", mediator);
    User *u2 = new User("shubham", mediator);
    User *u3 = new User("ravi", mediator);
    User *u4 = new User("pavan", mediator);

    u1->sendAll("Hello everyone");
    mediator->muteUser("ravi", "shubham");

    u2->sendAll("Hi, this is shubham");
    u3->sendPrivate("shubham", "Hey shubham");
    u4->sendPrivate("ravi", "Hello ravi");

    delete mediator;
    return 0;
}
