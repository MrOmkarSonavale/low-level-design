
interface Burger {
    prepareBurger(): void;
};

class BasicBurger implements Burger {
    prepareBurger(): void {
        console.log("preparing the basic burger");
    }
};

class StandardBurger implements Burger {
    prepareBurger(): void {
        console.log("preparing the standard burger");
    }
};


class PremiumBurger implements Burger {
    prepareBurger(): void {
        console.log("preparing the Premium burger");
    }
};


class BurgerFactory {

    createBurger(type: string): Burger | null {
        if (type == "basic") {
            return new BasicBurger();
        } else if (type == 'standard') {
            return new StandardBurger();
        } else if (type == 'premium') {
            return new PremiumBurger();
        } else {
            console.log("Unknown burger type");
            return null;
        }
    }
}

const factory = new BurgerFactory();
let type: string = "basic";

let burger = factory.createBurger(type);
burger?.prepareBurger();