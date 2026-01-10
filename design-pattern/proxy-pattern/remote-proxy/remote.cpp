#include <iostream>

using namespace std;

class IDataService
{
public:
    virtual void fetchData() = 0;
};

class RealDataService : public IDataService
{
public:
    void fetchData() override
    {
        cout << "making api request to fetch data" << endl;
    }
};

class RemoteProxy : public IDataService
{
private:
    RealDataService *realDataService;

public:
    RemoteProxy(RealDataService *r1)
    {
        this->realDataService = r1;
    };

    void fetchData()
    {
        this->realDataService->fetchData();
    }
};

int main(void)
{
    RealDataService *r1 = new RealDataService();
    RemoteProxy *proxy = new RemoteProxy(r1);
    proxy->fetchData();
    return 0;
}