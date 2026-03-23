#include <iostream>
#include <map>
#include <string>
#include <stdexcept>

using namespace std;

class HttpReq
{
private:
    string url;
    string method;
    map<string, string> body;
    int timeOut;

    // Allow builder to access private members
    friend class HttpReqBuilder;

public:
    void request()
    {
        cout << "URL: " << url << ", Method: " << method
             << ", Timeout: " << timeOut << endl;

        if (!body.empty())
        {
            cout << "Body:\n";
            for (auto &p : body)
            {
                cout << p.first << " : " << p.second << endl;
            }
        }
    }
};

class HttpReqBuilder
{
private:
    HttpReq *req;

public:
    HttpReqBuilder()
    {
        req = new HttpReq();
    }

    HttpReqBuilder *setUrl(string url)
    {
        req->url = url;
        return this;
    }

    HttpReqBuilder *setMethod(string method)
    {
        req->method = method;
        return this;
    }

    HttpReqBuilder *setTimeOut(int num)
    {
        req->timeOut = num;
        return this;
    }

    HttpReqBuilder *setBody(string key, string value)
    {
        req->body[key] = value;
        return this;
    }

    HttpReq *build()
    {
        if (req->url.empty())
        {
            throw runtime_error("URL is required");
        }
        return req;
    }
};

class HttpReqBuilderDirector
{
public:
    static HttpReq *HttpGetMethod(string url)
    {
        return (new HttpReqBuilder())
            ->setUrl(url)
            ->setMethod("GET")
            ->build();
    }

    static HttpReq *HttpPostMethod(string url, string key, string value)
    {
        return (new HttpReqBuilder())
            ->setUrl(url)
            ->setMethod("POST")
            ->setBody(key, value)
            ->build();
    }
};

int main()
{
    // Direct builder usage
    HttpReq *req1 = (new HttpReqBuilder())
                        ->setUrl("www.google.com")
                        ->setMethod("GET")
                        ->setTimeOut(100)
                        ->build();

    req1->request();

    // Using Director
    HttpReq *req2 = HttpReqBuilderDirector::HttpGetMethod("www.github.com");
    req2->request();

    HttpReq *req3 = HttpReqBuilderDirector::HttpPostMethod(
        "www.api.com", "id", "123");

    req3->request();

    return 0;
}