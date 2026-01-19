
interface command {
    run(): void;
    undo(): void;
}

class Light {
    on() {
        console.log("light is on");
    }

    off() {
        console.log("light is off");
    }
}

class Fan {
    on() {
        console.log("fan is on");
    }

    off() {
        console.log("fan is off");
    }
}

class LightCommand implements command {
    private light: Light;

    constructor(light: Light) {
        this.light = light;
    }

    run(): void {
        this.light.on();
    }

    undo(): void {
        this.light.off();
    }
}

class FanCommand implements command {
    private fan: Fan;

    constructor(fan: Fan) {
        this.fan = fan;
    }

    run(): void {
        this.fan.on();
    }

    undo(): void {
        this.fan.off();
    }
}

class RemoteController {
    private static readonly numButton: number = 6;
    private buttons: (command | null)[] = new Array(RemoteController.numButton);

    private buttonPressed: boolean[] = new Array(RemoteController.numButton);

    constructor() {
        for (let i = 0; i < RemoteController.numButton; i++) {
            this.buttons[i] = null;
            this.buttonPressed[i] = false;
        }
    }

    setCommand(index: number, cmd: command): void {
        if (index >= 0 && index < RemoteController.numButton) {
            this.buttons[index] = cmd;
            this.buttonPressed[index] = false;
        } else {
            console.log("Invalid button index");
        }
    }

    pressButton(index: number): void {
        if (
            index >= 0 &&
            index < RemoteController.numButton &&
            this.buttons[index]
        ) {
            if (!this.buttonPressed[index]) {
                this.buttons[index]!.run();
            } else {
                this.buttons[index]!.undo();
            }

            this.buttonPressed[index] = !this.buttonPressed[index];
        } else {
            console.log("Invalid button index or command not set");
        }
    }
}


const livingLight = new Light();

const remonte = new RemoteController();

remonte.setCommand(0, new LightCommand(livingLight));

remonte.pressButton(0);
remonte.pressButton(0);