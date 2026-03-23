#include <iostream>
#include <string>
#include <map>

using namespace std;

class HttpReq
{
private:
    string url;
    string method;
    int timeout = 0;
    map<string, string> body;
    map<string, string> header;

public:
    void setUrl(string u) { url = u; }
    void setMethod(string m) { method = m; }
    void setHeader(string k, string v) { header[k] = v; }
    void setBody(string k, string v) { body[k] = v; }
    void setTimeout(int t) { timeout = t; }

    void request()
    {
        cout << "Request to URL: " << url
             << " with method: " << method << endl;
    }
};

// Forward declarations
class MethodStep;
class HeaderStep;
class OptionalStep;

// Step 1
class UrlStep
{
public:
    virtual MethodStep *withUrl(string url) = 0;
};

// Step 2
class MethodStep
{
public:
    virtual HeaderStep *withMethod(string method) = 0;
};

// Step 3
class HeaderStep
{
public:
    virtual OptionalStep *withHeader(string key, string value) = 0;
};

// Step 4
class OptionalStep
{
public:
    virtual OptionalStep *withBody(string key, string value) = 0;
    virtual OptionalStep *withTimeout(int time) = 0;
    virtual HttpReq *build() = 0;
};

// Builder inherite all interfaces
class HttpReqBuilder : public UrlStep,
                       public MethodStep,
                       public HeaderStep,
                       public OptionalStep
{
private:
    HttpReq *req;

public:
    HttpReqBuilder()
    {
        req = new HttpReq();
    }

    MethodStep *withUrl(string url) override
    {
        req->setUrl(url);
        return this;
    }

    HeaderStep *withMethod(string method) override
    {
        req->setMethod(method);
        return this;
    }

    OptionalStep *withHeader(string key, string value) override
    {
        req->setHeader(key, value);
        return this;
    }

    OptionalStep *withBody(string key, string value) override
    {
        req->setBody(key, value);
        return this;
    }

    OptionalStep *withTimeout(int time) override
    {
        req->setTimeout(time);
        return this;
    }

    HttpReq *build() override
    {
        return req;
    }

    // to get the httpreqBuilder object
    static UrlStep *getBuilder()
    {
        return new HttpReqBuilder();
    }
};

int main()
{
    HttpReq *req = HttpReqBuilder::getBuilder()
                       ->withUrl("www.google.com")
                       ->withMethod("GET")
                       ->withHeader("Auth", "token")
                       ->withBody("key", "value")
                       ->withTimeout(5000)
                       ->build();

    req->request();

    delete req;
}