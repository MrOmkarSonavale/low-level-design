#include <iostream>
using namespace std;

class IDocumentReader
{
public:
    virtual void unlock_document() = 0;
    virtual ~IDocumentReader() {}
};

class RealDocument : public IDocumentReader
{
public:
    void unlock_document() override
    {
        cout << "You are reading the document" << endl;
    }
};

class User
{
public:
    string name;
    bool premiumMembership;

    User(string name, bool membership)
    {
        this->name = name;
        this->premiumMembership = membership;
    }
};

class ProxyDocument : public IDocumentReader
{
private:
    User *user;
    RealDocument realDoc;

public:
    ProxyDocument(User *user)
    {
        this->user = user;
    }

    void unlock_document() override
    {
        if (user->premiumMembership)
        {
            realDoc.unlock_document();
        }
        else
        {
            cout << "Access denied: Premium membership required" << endl;
        }
    }
};

int main()
{
    User *user = new User("Omkar", true);

    IDocumentReader *doc = new ProxyDocument(user);
    doc->unlock_document();

    delete doc;
    delete user;
}
