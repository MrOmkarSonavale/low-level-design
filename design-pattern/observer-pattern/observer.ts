

interface Isubscriber {
    update(): void;
};

interface Ichannel {
    subscribe(subscribe: Isubscriber): void;
    unsubscribe(subscribe: Isubscriber): void;
    notify(video: string): void;
};

class Channel implements Ichannel {
    private subscriberList: Isubscriber[] = [];
    private latestVideo: string = "";
    private name: string = ""

    constructor(name: string) {
        this.name = name;
    };

    subscribe(subscribe: Isubscriber): void {
        this.subscriberList.push(subscribe);
    };

    unsubscribe(subscribe: Isubscriber): void {
        this.subscriberList.filter(i => i != subscribe);
    };

    notify(video: string): void {
        this.latestVideo = video;
        console.log("new video uploaded by " + this.name);


        this.subscriberList.forEach(i => i.update());
    }

    getLatestVideo(): string {
        return this.latestVideo;
    };
}

class Subscriber implements Isubscriber {
    private name: string = "";
    private subscribedChannel: Channel;

    constructor(name: string, channelcurr: Channel) {
        this.name = name;
        this.subscribedChannel = channelcurr;
    };

    update(): void {
        this.subscribedChannel.getLatestVideo();
    };
};

const omkarsonavale = new Channel("omkarfun");
const nickolodean = new Channel("nickolodean");

const user1 = new Subscriber("user1", omkarsonavale);
const user2 = new Subscriber("user2", omkarsonavale);
const user3 = new Subscriber("user3", omkarsonavale);
const user4 = new Subscriber("user4", omkarsonavale);

omkarsonavale.notify("i am uploading s3 video");