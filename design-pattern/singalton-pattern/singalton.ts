
class Singalton {
    static instance: Singalton | null = null;

    constructor() {
        console.log('this is singalton');
    };

    static getInstance(): Singalton {
        if (this.instance == null) {
            this.instance = new Singalton();
        }

        return this.instance;
    };
};

const singalton1 = Singalton.getInstance();
const singalton2 = Singalton.getInstance();

if (singalton1 == singalton2) {
    console.log("both are same");
} else {
    console.log("both are different")
}