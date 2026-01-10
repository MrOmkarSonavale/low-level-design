interface IMediator {
    sendAll(from: string, msg: string): void;
    sendPrivate(from: string, to: string, msg: string): void;
    registerUser(u: Colleague): void;
}

abstract class Colleague {
    protected mediator: IMediator;

    constructor(m: IMediator) {
        this.mediator = m;
        this.mediator.registerUser(this);
    }

    abstract getName(): string;
    abstract receiveMessage(from: string, msg: string): void;

    sendAll(msg: string): void {
        this.mediator.sendAll(this.getName(), msg);
    }

    sendPrivate(to: string, msg: string): void {
        this.mediator.sendPrivate(this.getName(), to, msg);
    }
}

class Mediator implements IMediator {
    private users: Colleague[] = [];
    private muted: { receiver: string; sender: string }[] = [];

    registerUser(u: Colleague): void {
        this.users.push(u);
    }

    muteUser(receiver: string, sender: string): void {
        this.muted.push({ receiver, sender });
    }

    private isMuted(receiver: string, sender: string): boolean {
        return this.muted.some(
            m => m.receiver === receiver && m.sender === sender
        );
    }

    sendAll(from: string, msg: string): void {
        for (const user of this.users) {
            if (user.getName() === from) continue;

            if (!this.isMuted(user.getName(), from)) {
                user.receiveMessage(from, msg);
            }
        }
    }

    sendPrivate(from: string, to: string, msg: string): void {
        for (const user of this.users) {
            if (user.getName() === to) {
                if (this.isMuted(to, from)) {
                    console.log(`${to} has muted ${from}`);
                    return;
                }
                user.receiveMessage(from, msg);
                return;
            }
        }
    }
}

class User extends Colleague {
    private name: string;

    constructor(name: string, m: IMediator) {
        super(m);
        this.name = name;
    }

    getName(): string {
        return this.name;
    }

    receiveMessage(from: string, msg: string): void {
        console.log(`[${this.name}] received from ${from}: ${msg}`);
    }
}

// ---- Usage ----
const mediator = new Mediator();

const user1 = new User("omkar", mediator);
const user2 = new User("shubham", mediator);
const user3 = new User("ravi", mediator);
const user4 = new User("suresh", mediator);

user1.sendAll("Hello everyone, Omkar here");
user2.sendAll("Hello everyone, Shubham here");

mediator.muteUser("ravi", "shubham");

user3.sendAll("Hello everyone, Ravi here");
user2.sendPrivate("ravi", "Hello Ravi");
