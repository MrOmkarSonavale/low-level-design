abstract class IRemoteService {
    abstract FetchData(): void;
}

class RemoteServer extends IRemoteService {
    FetchData(): void {
        console.log("fetching data from remote service");
    }
};

class RemoteProxy extends IRemoteService {
    private remoteserver: RemoteServer;

    constructor() {
        super();
        this.remoteserver = new RemoteServer();
    }

    FetchData(): void {
        this.remoteserver.FetchData();
    };
};

const proxy = new RemoteProxy();
proxy.FetchData();