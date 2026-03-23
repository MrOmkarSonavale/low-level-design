class HttpReq {
    private url: string = "";
    private method: string = "";
    private timeout: number = 0;
    private body: Map<string, string> = new Map();
    private header: Map<string, string> = new Map();


    //seeter for all fields
    setUrl(url: string) { this.url = url; }
    setMethod(method: string) { this.method = method; }
    setHeader(key: string, value: string) { this.header.set(key, value); }
    setBody(key: string, value: string) { this.body.set(key, value); }
    setTimeout(timeout: number) { this.timeout = timeout; }

    request(): void {
        console.log(`Request to ${this.url} with method ${this.method}`);
    }
}

/* STEP INTERFACES */

interface UrlStep {
    withUrl(url: string): MethodStep;
}

interface MethodStep {
    withMethod(method: string): HeaderStep;
}

interface HeaderStep {
    withHeader(key: string, value: string): OptionalStep;
}

interface OptionalStep {
    withBody(key: string, value: string): OptionalStep;
    withTimeout(timeout: number): OptionalStep;
    build(): HttpReq;
}

/* BUILDER */

class HttpReqBuilder implements UrlStep, MethodStep, HeaderStep, OptionalStep {
    private req: HttpReq;

    private constructor() {
        this.req = new HttpReq();
    }

    static getBuilder(): UrlStep {
        return new HttpReqBuilder();
    }

    withUrl(url: string): MethodStep {
        this.req.setUrl(url);
        return this;
    }

    withMethod(method: string): HeaderStep {
        this.req.setMethod(method);
        return this;
    }

    withHeader(key: string, value: string): OptionalStep {
        this.req.setHeader(key, value);
        return this;
    }

    withBody(key: string, value: string): OptionalStep {
        this.req.setBody(key, value);
        return this;
    }

    withTimeout(timeout: number): OptionalStep {
        this.req.setTimeout(timeout);
        return this;
    }

    build(): HttpReq {
        return this.req;
    }
}

/* USAGE */

const req = HttpReqBuilder.getBuilder()
    .withUrl("https://google.com")
    .withMethod("GET")
    .withHeader("Authorization", "Bearer token")
    .withBody("key", "value")
    .withTimeout(5000)
    .build();

req.request();