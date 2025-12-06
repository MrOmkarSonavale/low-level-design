
//interface for the walkable streategy
interface walkAble {
    walk(): void;
};

//concreate bheviour
class noWalkRobot implements walkAble {
    walk(): void {
        console.log("no walk robot");
    }
};


class walkRobot implements walkAble {
    walk(): void {
        console.log('this robot can walk')
    }
};

interface talkAble {
    talk(): void;
};


class noTalkRobot implements talkAble {
    talk(): void {
        console.log("no talk robot");
    }
};


class talkRobot implements talkAble {
    talk(): void {
        console.log('robot is talking')
    }
};


class Robot {
    private walkAble: walkAble;
    private talkAble: talkAble;

    constructor(walk: walkAble, talk: talkAble) {
        this.walkAble = walk;
        this.talkAble = talk;
    };

    walk(): void {
        this.walkAble.walk();
    }

    talk(): void {
        this.talkAble.talk();
    }
};

const robotR1 = new Robot(new noWalkRobot(),
    new noTalkRobot())
robotR1.walk();
robotR1.talk();





