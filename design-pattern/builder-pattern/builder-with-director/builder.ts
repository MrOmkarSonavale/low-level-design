class HttpReq {
    public url: string = "";
    public method: string = "";
    public body: Map<string, string> = new Map();
    public timeout: number = NaN;

    public request(): void {
        console.log(
            "The request is made with " + this.url +
            " and method is " + this.method
        );
    }
}

class HttpReqBuilder {
    private httpreq: HttpReq;

    constructor() {
        this.httpreq = new HttpReq();
    }

    setUrl(url: string): HttpReqBuilder {
        this.httpreq.url = url;
        return this;
    }

    setMethod(method: string): HttpReqBuilder {
        this.httpreq.method = method;
        return this;
    }

    setBody(key: string, value: string): HttpReqBuilder {
        this.httpreq.body.set(key, value); // ✅ fixed
        return this;
    }

    build(): HttpReq {
        if (!this.httpreq.url) {
            throw new Error("URL not found");
        }
        return this.httpreq;
    }
}

class HttpReqBuilderDirector {
    static getMethod(url: string): HttpReq {
        return new HttpReqBuilder()
            .setUrl(url)
            .setMethod("GET") // ✅ added
            .build();
    }

    static postMethod(url: string, key: string, value: string): HttpReq {
        return new HttpReqBuilder()
            .setUrl(url)
            .setMethod("POST")
            .setBody(key, value)
            .build();
    }
}

// Usage
const client = new HttpReqBuilder()
    .setUrl("www.google.com")
    .setMethod("GET")
    .build();

client.request();

const clientOne = HttpReqBuilderDirector.postMethod(
    "www.google.com",
    "name",
    "omkar"
);

clientOne.request();