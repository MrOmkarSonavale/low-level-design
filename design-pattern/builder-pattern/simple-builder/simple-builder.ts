class HttpRequest {
    public url: string = "";
    public method: string = "";
    public header: Map<string, string> = new Map();
    public timeOut: number = 0;

    public request(): void {
        console.log(
            "Request accepted with URL: " +
            this.url +
            " and Method: " +
            this.method
        );
    }
}

class HttpReqBuilder {
    private req: HttpRequest;

    constructor() {
        this.req = new HttpRequest();
    }

    setUrl(url: string): HttpReqBuilder {
        this.req.url = url;
        return this;
    }

    setMethod(method: string): HttpReqBuilder {
        this.req.method = method;
        return this;
    }

    setTimeOut(timer: number): HttpReqBuilder {
        this.req.timeOut = timer;
        return this;
    }

    build(): HttpRequest {
        // validation
        if (!this.req.url) {
            throw new Error("URL not found");
        }
        return this.req;
    }
}

// Usage
const newReq = new HttpReqBuilder()
    .setUrl("www.omkar.com")
    .setMethod("GET")
    .setTimeOut(1000)
    .build();

newReq.request();