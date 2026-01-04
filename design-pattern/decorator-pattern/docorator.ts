abstract class Character {
    abstract getAbility(): string;
};


class Mario extends Character {
    getAbility(): string {
        return "Mario ";
    }
};

abstract class Decorator extends Character {
    protected character: Character;

    constructor(character: Character) {
        super();
        this.character = character;
    };

};

class MarioWithFireFlower extends Decorator {

    getAbility(): string {
        return this.character.getAbility() + "with Fire Flower ";
    };
};


class MarioWithJumpBoost extends Decorator {
    getAbility(): string {
        return this.character.getAbility() + "with Jump Boost ";
    };
};


class MarioWithShield extends Decorator {
    getAbility(): string {
        return this.character.getAbility() + "with Shield ";
    };
};


const mario = new Mario();

const fireMario = new MarioWithFireFlower(mario);
console.log(fireMario.getAbility());

const jumpBoostedMario = new MarioWithJumpBoost(fireMario);
console.log(jumpBoostedMario.getAbility());