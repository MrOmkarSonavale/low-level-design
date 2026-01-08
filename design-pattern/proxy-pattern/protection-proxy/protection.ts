abstract class DocumentReader {
    abstract unlockPdf(): void
};

class RealDocumentReader extends DocumentReader {
    public unlockPdf(): void {
        console.log("you are reading this pdf")
    }
};

class User {
    public name: string;
    public isSubscribed: boolean;

    constructor(name: string, subscribed: boolean) {
        this.name = name;
        this.isSubscribed = subscribed;
    }
};

class ProtectionProxy extends DocumentReader {
    private documentReader: RealDocumentReader;
    private user: User;

    constructor(user: User) {
        super();
        this.user = user;
        this.documentReader = new RealDocumentReader();
    };

    unlockPdf(): void {
        if (this.user.isSubscribed) {
            this.documentReader.unlockPdf();
        } else {
            console.log("you are authorized to access this pdf");
        }
    }
};

const user = new User("omkar", true);
const proxy = new ProtectionProxy(user);
proxy.unlockPdf();

