#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class INotification
{
public:
    virtual string getContent() const = 0;
    virtual ~INotification() {};
};

class SimpleNotification : public INotification
{
private:
    string text;

public:
    SimpleNotification(const string &msg)
    {
        text = msg;
    };

    string getContent() const override
    {
        return text;
    }
};

class INotificationDecorator : public INotification
{
protected:
    INotification *notification;

public:
    INotificationDecorator(INotification *n)
    {
        notification = n;
    };

    virtual ~INotificationDecorator()
    {
        delete notification;
    }
};

class TimeStampDecorator : public INotificationDecorator
{

public:
    TimeStampDecorator(INotification *n) : INotificationDecorator(n) {};

    string getContent() const override {
        return "[2025-04-13 14:22:00] " + notification -> getContent()
    };
};

class SignatureDecorator : public INotificationDecorator
{
private:
    string signature;

public:
    SignatureDecorator(INotification *n, string sig) : INotificationDecorator(n)
    {
        signature = sig;
    };

    string getContent() const override
    {
        return notification->getContent() + "\n--" + signature + "\n\n";
    }
};

class IObserver
{
public:
    virtual void update() = 0;

    ~Iobserver() {};
};

class IObservable
{
public:
    virtual void addObserver(IObserver *observer) = 0;
    virtual void removeObserver(IObserver *observer) = 0;
    virtual void notifyOberser() = 0;
};

class NotificationObservable : public IObservable
{
private:
    vector<IObserver *> observers;
    INotification *notification;

public:
    NotificationObservable()
    {
        notification = nullptr;
    };

    void addObserver(IObserver *obs) override
    {
        this->observers = obs;
    };

    void removeObserver(IObservable *obs) override {
        observers.erase(remove(observers.begin(), observers.end(), obs), observers.end())
    };

    void notifyOberser() override
    {
        for (int i = 0; i < observers.size(); i++)
        {
            observers[i]->update();
        }
    };

    void setNotification(INotification *i)
    {
        if (notification != nullptr)
        {
            delete notification;
        }
        notification = i;
        notifyOberser();
    };

    string getNotificationContent()
    {
        return notification->getContent();
    }

    ~NotificationObservable()
    {
        if (notification != nullptr)
        {
            delete notification;
        }
    };
};

class Logger : public IObserver
{
private:
    NotificationObservable *observable;

public:
    Logger(NotificationObservable *obs)
    {
        this->observable = obs;
    };

    void update()
    {
        cout << "Logging new Notification : \n"
             << observable->getNotificationContent();
    };
};

class INotificationStreategy
{
public:
    virtual void sendNotification(string content) = 0;
};

class EmailStreategy : public INotificationStreategy
{
private:
    string emailId;

public:
    EmailStretegy(string email) : emailId(email) {};

    void sendNotification(string content) override
    {
        cout << "sending email notification to:" << emailId << "\n"
             << content;
    }
};

class SMSStrategy : public INotificationStrategy
{
private:
    string mobileNumber;

public:
    SMSStrategy(string mobileNumber)
    {
        this->mobileNumber = mobileNumber;
    }

    void sendNotification(string content) override
    {
        // Simulate the process of sending an SMS notification,
        // representing the dispatch of messages to users via SMS.​
        cout << "Sending SMS Notification to: " << mobileNumber << "\n"
             << content;
    }
};

class PopUpStrategy : public INotificationStreategy
{
public:
    void sendNotification(string content) override
    {
        cout << "Sending popup notification : \n"
             << content;
    };
};

class NotificationEngine : public IObserver
{
private:
    NotificationObservable *observable;
    vector<INotificationStreategy *> strategies;

public:
    NotificationEngine(NotificationObservable *obser)
    {
        this->observable = obser;
    };

    void addNotificationStrategies(INotificationStreategy *n) {
        this.strategies.push_back(n)
    };

    void update()
    {
        string notificationContent = observable->getNotificationContent();

        for (auto s : strategies)
        {
            s->sendNotification(notificationContent);
        }
    };
};

class NotificationService
{
private:
    NotificationObservable *obs;
    static NotificationService *instance;
    vector<INotification *> notification;

    NotificationService()
    {
        obs = new NotificationObservable();
    };

public:
    static NotificationService *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new NotificationService();
        }

        return instance;
    };

    NotificationObservable *getObservable()
    {
        return obs;
    };

    void sendNotification(INotification *noti)
    {
        notification.push_back(noti);
        obs->setNotification(noti);
    };

    ~NotificationService()
    {
        delete obs;
    }
};

NotificationService *NotificationService::instance = nullptr;

int main()
{
    // Create NotificationService.
    NotificationService *notificationService = NotificationService::getInstance();

    // Get Observable
    NotificationObservable *notificationObservable = notificationService->getObservable();

    // Create Logger Observer
    Logger *logger = new Logger(notificationObservable);

    // Create NotificationEngine observers.
    NotificationEngine *notificationEngine = new NotificationEngine(notificationObservable);

    notificationEngine->addNotificationStrategies(new EmailStreategy("random.person@gmail.com"));
    notificationEngine->addNotificationStrategies(new SMSStrategy("+91 9876543210"));
    notificationEngine->addNotificationStrategies(new PopUpStrategy());

    // Attach these observers.
    notificationObservable->addObserver(logger);
    notificationObservable->addObserver(notificationEngine);

    // Create a notification with decorators.
    INotification *notification = new SimpleNotification("Your order has been shipped!");
    notification = new TimestampDecorator(notification);
    notification = new SignatureDecorator(notification, "Customer Care");

    notificationService->sendNotification(notification);

    delete logger;
    delete notificationEngine;
    return 0;
}