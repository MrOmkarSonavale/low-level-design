;
;
var Channel = /** @class */ (function () {
    function Channel(name) {
        this.subscriberList = [];
        this.latestVideo = "";
        this.name = "";
        this.name = name;
    }
    ;
    Channel.prototype.subscribe = function (subscribe) {
        this.subscriberList.push(subscribe);
    };
    ;
    Channel.prototype.unsubscribe = function (subscribe) {
        this.subscriberList.filter(function (i) { return i != subscribe; });
    };
    ;
    Channel.prototype.notify = function (video) {
        this.latestVideo = video;
        console.log("new video uploaded by" + this.name);
        this.subscriberList.forEach(function (i) { return i.update(); });
    };
    Channel.prototype.getLatestVideo = function () {
        return this.latestVideo;
    };
    ;
    return Channel;
}());
var Subscriber = /** @class */ (function () {
    function Subscriber(name, channelcurr) {
        this.name = "";
        this.name = name;
        this.subscribedChannel = channelcurr;
    }
    ;
    Subscriber.prototype.update = function () {
        this.subscribedChannel.getLatestVideo();
    };
    ;
    return Subscriber;
}());
;
var omkarsonavale = new Channel("omkarfun");
var nickolodean = new Channel("nickolodean");
var user1 = new Subscriber("user1", omkarsonavale);
var user2 = new Subscriber("user2", omkarsonavale);
var user3 = new Subscriber("user3", omkarsonavale);
var user4 = new Subscriber("user4", omkarsonavale);
omkarsonavale.notify("i am uploading s3 video");
