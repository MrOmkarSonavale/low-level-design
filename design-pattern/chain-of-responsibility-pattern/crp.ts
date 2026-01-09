abstract class CashDispenser {
    protected cashdispenser: CashDispenser | null;

    constructor() {
        this.cashdispenser = null;
    }

    setHandler(handler: CashDispenser): void {
        this.cashdispenser = handler;
    }

    abstract moneyDispense(amount: number): void;
}


class ThounsandDispenser extends CashDispenser {
    private number_of_notes: number;

    constructor(numnotes: number) {
        super();
        this.number_of_notes = numnotes;
    }

    moneyDispense(amount: number): void {
        let notes_need: number = Math.floor(amount / 1000);

        if (notes_need > this.number_of_notes) {
            notes_need = this.number_of_notes;
        }

        this.number_of_notes -= notes_need;

        if (notes_need > 0) {
            console.log(`dispensing ${notes_need} of $1000 from atm`);
        }

        let remaining_amount = amount - (notes_need * 1000);

        if (remaining_amount > 0) {
            if (this.cashdispenser) {
                this.cashdispenser.moneyDispense(remaining_amount);
            } else {
                console.log(`notes not available to proceed : amount $${remaining_amount}`);
            }
        }
    }
}


class HundredDispenser extends CashDispenser {
    private number_of_notes: number;

    constructor(numnotes: number) {
        super();
        this.number_of_notes = numnotes;
    }

    moneyDispense(amount: number): void {
        let notes_need: number = Math.floor(amount / 100);

        if (notes_need > this.number_of_notes) {
            notes_need = this.number_of_notes;
        }

        this.number_of_notes -= notes_need;

        if (notes_need > 0) {
            console.log(`dispensing ${notes_need} of $100 from atm`);
        }

        let remaining_amount = amount - (notes_need * 100);

        if (remaining_amount > 0) {
            if (this.cashdispenser) {
                this.cashdispenser.moneyDispense(remaining_amount);
            } else {
                console.log(`notes not available to proceed : amount $${remaining_amount}`);
            }
        }
    }
}


class FiftyDispenser extends CashDispenser {
    private number_of_notes: number;

    constructor(numnotes: number) {
        super();
        this.number_of_notes = numnotes;
    }

    moneyDispense(amount: number): void {
        let notes_need: number = Math.floor(amount / 50);

        if (notes_need > this.number_of_notes) {
            notes_need = this.number_of_notes;
        }

        this.number_of_notes -= notes_need;

        if (notes_need > 0) {
            console.log(`dispensing ${notes_need} of $50 from atm`);
        }

        let remaining_amount = amount - (notes_need * 50);

        if (remaining_amount > 0) {
            console.log(`notes not available to proceed : amount $${remaining_amount}`);
        }
    }
}


// setup
const hundredHandler = new HundredDispenser(10);
const thoundsandHandler = new ThounsandDispenser(15);
const fiftyHandler = new FiftyDispenser(20);

thoundsandHandler.setHandler(hundredHandler);
hundredHandler.setHandler(fiftyHandler);

// test
const moneyTodispense = 2500;
thoundsandHandler.moneyDispense(moneyTodispense);
