#include <iostream>
#include <string>

using namespace std;

class Itarget
{
public:
    virtual string getJsonData() = 0;
};

class XmlDataProvider
{
public:
    string getXmlData()
    {
        return "<data><item>Item1</item><item>Item2</item></data>";
    }
};

class Adaptee : public Itarget
{
private:
    XmlDataProvider *xmlDataProvider;

public:
    Adaptee(XmlDataProvider *provider)
    {
        this->xmlDataProvider = provider;
    }

    string getJsonData() override
    {
        string xmlData = xmlDataProvider->getXmlData();

        // Simple conversion logic (for demonstration purposes)

        string jsonData = "{\"data\": {\"item\": [\"Item1\", \"Item2\"]}}";

        return jsonData;
    }
};

int main()
{
    Itarget *adapter = new Adaptee(new XmlDataProvider());
    cout << adapter->getJsonData() << endl;
}