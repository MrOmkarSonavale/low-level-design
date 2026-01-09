abstract class Engine {
    abstract StartEngine(): void;
};

class PetrolEngine extends Engine {
    StartEngine(): void {
        console.log("starting the petrol engine")
    };
};

class DisealEngine extends Engine {
    StartEngine(): void {
        console.log("starting the Diseal Engine");
    }
};

class ElectricMotor extends Engine {
    StartEngine(): void {
        console.log("Starting the Electric motor");
    }
};


abstract class Vechicle {
    protected engine: Engine;

    constructor(engine: Engine) {
        this.engine = engine;
    }

    abstract StartVechicle(): void;
};

class Sedan extends Vechicle {

    constructor(engine: Engine) {
        super(engine);
    };

    StartVechicle(): void {
        this.engine.StartEngine();
    }
};

class Suv extends Vechicle {
    constructor(engine: Engine) {
        super(engine);
    }

    StartVechicle(): void {
        this.engine.StartEngine();
    }
}


const engine = new PetrolEngine();
const suv = new Suv(engine);
suv.StartVechicle();