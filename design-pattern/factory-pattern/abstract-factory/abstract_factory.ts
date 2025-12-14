interface Burger {
    prepareBurger(): void;
};

class BasicBurger implements Burger {
    prepareBurger(): void {
        console.log("preparing the basic burger")
    };
};

class StandardBurger implements Burger {
    prepareBurger(): void {
        console.log("preparing the standard burger");
    }
};

class PremiumBurger implements Burger {
    prepareBurger(): void {
        console.log("preparing the premium burger");
    }
};

class BasicWheatBurger implements Burger {
    prepareBurger(): void {
        console.log("preparing the basic wheat burger");
    }
};

class StandardWheatBurger implements Burger {
    prepareBurger(): void {
        console.log("preparing the standard wheat burger");
    }
};

class PremiumWheatBurger implements Burger {
    prepareBurger(): void {
        console.log("preparing the premium wheat burger");
    };
};


interface Pizza {
    preparePizza(): void;
};

class BasicPizza implements Pizza {
    preparePizza(): void {
        console.log("preparing the basic pizza");
    }
}

class StandardPizza implements Pizza {
    preparePizza(): void {
        console.log("preparing the standard pizza")
    }
};

class PremiumPizza implements Pizza {
    preparePizza(): void {
        console.log("preparing the premium pizza")
    };
};

class BasicWheatPizza implements Pizza {
    preparePizza(): void {
        console.log("preparing the basic wheat pizza")
    }
};

class StandardWheatPizza implements Pizza {
    preparePizza(): void {
        console.log("preparing the standard wheat pizza")
    }
};

class PremiumWheatPizza implements Pizza {
    preparePizza(): void {
        console.log("preparing the premium wheat pizza")
    }
};

interface factory {
    createBurger(type: string): Burger | null;
    createPizza(type: string): Pizza | null;
};


class NormarlFactory implements factory {
    createBurger(type: string): Burger | null {
        if (type == "basic") {
            return new BasicBurger();
        }
        else if (type == "standard") {
            return new StandardBurger();
        } else if (type == "premium") {
            return new PremiumBurger();
        } else {
            return null;
        }
    };

    createPizza(type: string): Pizza | null {
        if (type == "basic") {
            return new BasicPizza();
        } else if (type == "standard") {
            return new StandardPizza();
        } else if (type == "premium") {
            return new PremiumPizza();
        } else {
            return null;
        }
    }
};

class PremiumFactory implements factory {
    createBurger(type: string): Burger | null {
        if (type == "basic") {
            return new BasicWheatBurger();
        }
        else if (type == "standard") {
            return new StandardWheatBurger();
        } else if (type == "premium") {
            return new PremiumWheatBurger();
        } else {
            return null;
        }
    };

    createPizza(type: string): Pizza | null {
        if (type == "basic") {
            return new BasicWheatPizza();
        } else if (type == "standard") {
            return new StandardWheatPizza();
        } else if (type == "premium") {
            return new PremiumWheatPizza();
        } else {
            return null;
        }
    }
};


let burger_type: string = "standard";
let pizza_type: string = "premium";
const testFactory = new NormarlFactory();

const burger = testFactory.createBurger(burger_type);
const pizza = testFactory.createPizza(pizza_type)

burger?.prepareBurger();
pizza?.preparePizza();