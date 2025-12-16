#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Isubscriber
{
public:
    virtual void update() = 0;
};

class Ichannel
{
public:
    virtual void subscribe(Isubscriber *isub) = 0;
    virtual void unsubscribe(Isubscriber *isub) = 0;
    virtual void notify() = 0;
    virtual ~Ichannel() {};
};

class Channel : public Ichannel
{
private:
    vector<Isubscriber *> subscribers;
    string name;
    string videoTitle;

public:
    Channel(string name)
    {
        this->name = name;
    }

    void subscribe(Isubscriber *isub) override
    {
        subscribers.push_back(isub);
    }

    void unsubscribe(Isubscriber *isub) override
    {
        auto it = find(subscribers.begin(), subscribers.end(), isub);
        if (it != subscribers.end())
        {
            subscribers.erase(it);
        }
    };

    void notify() override
    {
        for (auto sub : subscribers)
        {
            sub->update();
        }
    }

    void uploadVideo(string title)
    {
        videoTitle = title;
        cout << "new video realeses " << name << endl;
        this->notify();
    };

    string getNameOfUpload()
    {
        return this->videoTitle;
    }
};

class Subscriber : public Isubscriber
{
private:
    Channel *channel1;
    string name;

public:
    Subscriber(Channel *c1, string name)
    {
        this->channel1 = c1;
        this->name = name;
    }

    void update() override
    {
        cout << channel1->getNameOfUpload() << endl;
    }
};

int main(void)
{
    Channel *c1 = new Channel("omkar13");
    Channel *c2 = new Channel("mukesh12");

    Subscriber *s1 = new Subscriber(c1, "omkar");
    Subscriber *s2 = new Subscriber(c1, "omkar1");
    Subscriber *s3 = new Subscriber(c1, "omkar2");

    c1->subscribe(s1);
    c1->subscribe(s2);
    c1->subscribe(s3);

    c1->uploadVideo("this is my tour video");
};