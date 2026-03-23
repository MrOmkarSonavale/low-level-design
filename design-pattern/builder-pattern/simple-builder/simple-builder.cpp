#include <iostream>
#include <string>
#include <map>

using namespace std;

class HttpsReq
{
private:
    string url;
    string method;
    map<string, string> header;
    map<string, string> query;
    int timeout;

public:
    friend class HttpReqBuilder;

    void request()
    {
        cout << "Request is processing with " << url << " : " << method << endl;
    }
};

class HttpReqBuilder
{
private:
    HttpsReq *req;

public:
    // Constructor to initialize req
    HttpReqBuilder()
    {
        req = new HttpsReq();
    }

    HttpReqBuilder &getUrl(string url)
    {
        req->url = url;
        return *this;
    }

    HttpReqBuilder &getMethod(string method)
    {
        req->method = method;
        return *this;
    }

    HttpReqBuilder &getHeader(string key, string value)
    {
        req->header[key] = value;
        return *this;
    }

    HttpReqBuilder &getQuery(string key, string value)
    {
        req->query[key] = value;
        return *this;
    }

    HttpReqBuilder &getTime(int time)
    {
        req->timeout = time;
        return *this;
    }

    HttpsReq *build()
    {
        if (req->url.empty())
        {
            throw runtime_error("URL cannot be empty");
        }
        return req;
    }
};

int main()
{
    HttpsReq *newReq = HttpReqBuilder()
                           .getUrl("www.omkar.com")
                           .getMethod("GET")
                           .getTime(1000)
                           .build();

    newReq->request();

    return 0;
}