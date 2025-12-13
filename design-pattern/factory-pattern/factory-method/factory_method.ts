interface Burger {
    prepareBurger(): void
};

class BasicBurger implements Burger {
    prepareBurger(): void {
        console.log("cooking basic burger");
    };
}

class StandardBurger implements Burger {
    prepareBurger(): void {
        console.log("cooking the standard burger");
    };
};

class PremiumBurger implements Burger {
    prepareBurger(): void {
        console.log("cooking the Premium burger")
    }
};

class BasicWheatBurger implements Burger {
    prepareBurger(): void {
        console.log("preparing the basic wheat burger");
    };
};

class StandardWheatBurger implements Burger {
    prepareBurger(): void {
        console.log("preparing the standard wheat burger")
    };
};

class PrepareWheatBurger implements Burger {
    prepareBurger(): void {
        console.log("preparing the premium wheat burger")
    };
};

interface burgerFactory {
    createBurger(type: string): Burger | null
};

class planBurger implements burgerFactory {
    createBurger(type: string): Burger | null {
        if (type == "basic") {
            return new BasicBurger();
        } else if (type == "standard") {
            return new StandardBurger();
        } else if (type == "premium") {
            return new PremiumBurger();
        } else {
            return null;
        }
    }
}

class wheatBurger implements burgerFactory {
    createBurger(type: string): Burger | null {
        if (type == "basic") {
            return new BasicWheatBurger();
        } else if (type == "standard") {
            return new StandardWheatBurger();
        } else if (type == "premium") {
            return new PrepareWheatBurger();
        } else {
            return null;
        }
    }
};


const burgerFactory = new wheatBurger();
let type: string = "premium";
const burgerTry = burgerFactory.createBurger(type);
burgerTry?.prepareBurger();