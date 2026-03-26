
interface VendingState {
    insertCoin(machine: VendinMachine, coin: number): VendingState;
    selectItem(machine: VendinMachine): VendingState;
    dispensItem(machine: VendinMachine): VendingState;
    returnCoin(machine: VendinMachine): VendingState;
    refillQuant(machine: VendinMachine, quant: number): VendingState;
    stateStatus(): string;
};

class VendinMachine {
    private currState: VendingState;
    private noCoinState: VendingState;
    private hasCoinState: VendingState;
    private dispenseState: VendingState;
    private soldoutState: VendingState;
    private quatity: number = 0;
    private price: number = 0;
    private currentCoin: number = 0;

    constructor(quant: number, price: number) {
        this.quatity = quant
        this.price = price;
        this.currentCoin = 0;


        this.noCoinState = new NoCoinState();
        this.hasCoinState = new HasCoinState();
        this.dispenseState = new DispenseState();
        this.soldoutState = new SoldoutState();

        if (this.quatity > 0) {
            this.currState = new NoCoinState();
        } else {
            this.currState = new SoldoutState();
        }
    };

    insertCoin(coin: number): void {
        this.currState = this.currState.insertCoin(this, coin);
    }
    selectItem(): void {
        this.currState = this.currState.selectItem(this);
    }

    dispensItem(): void {
        this.currState = this.currState.dispensItem(this);
    }
    returnCoin(): void {
        this.currState = this.currState.returnCoin(this);
    }
    refillQuant(quant: number): void {
        this.currState = this.currState.refillQuant(this, quant);
    };

    getNoCoinState() { return this.noCoinState; }
    getHasCoinState() { return this.hasCoinState; }
    getDispenseState() { return this.dispenseState; }
    getSoldOutState() { return this.soldoutState; }

    getItemCount() { return this.quatity; }
    decrementItem() { this.quatity--; }
    incrementItem(qty: number) { this.quatity += qty; }

    getBalance() { return this.currentCoin; }
    setBalance(amount: number) { this.currentCoin = amount; }
    addBalance(amount: number) { this.currentCoin += amount; }

    getPrice() { return this.price; }


    stateStatus(): void {
        console.log("\n--- VENDING MACHINE STATUS ---");
        console.log("Items remaining:", this.quatity);
        console.log("Balance:", this.currentCoin);
        console.log("State:", this.currState.stateStatus());
    }
};

class NoCoinState implements VendingState {
    insertCoin(machine: VendinMachine, coin: number): VendingState {
        machine.setBalance(coin);
        console.log(`Coin inserted: Rs ${coin}`);
        return machine.getHasCoinState();
    }
    selectItem(machine: VendinMachine): VendingState {
        console.log("please insert the coin");
        return machine.getNoCoinState();
    }
    dispensItem(machine: VendinMachine): VendingState {
        console.log("please insert the coin");
        return machine.getNoCoinState();
    }
    returnCoin(machine: VendinMachine): VendingState {
        console.log("please insert the coin");
        return machine.getNoCoinState();
    }
    refillQuant(machine: VendinMachine, quant: number): VendingState {
        console.log("item refilling");
        machine.incrementItem(quant);
        return machine.getNoCoinState();
    }
    stateStatus(): string {
        return "NO_COIN_STATE"
    }
};

class HasCoinState implements VendingState {
    insertCoin(machine: VendinMachine, coin: number): VendingState {
        machine.addBalance(coin);
        console.log(`Added coin. Balance: Rs ${machine.getBalance()}`);
        return this;
    }

    selectItem(machine: VendinMachine): VendingState {
        if (machine.getItemCount() === 0) {
            console.log("Machine is sold out!");
            return machine.getSoldOutState();
        }

        if (machine.getBalance() >= machine.getPrice()) {
            console.log("Item selected. Preparing to dispense...");

            const change = machine.getBalance() - machine.getPrice();
            if (change > 0) {
                console.log(`Returning change: Rs ${change}`);
            }

            machine.setBalance(0);
            return machine.getDispenseState();
        } else {
            const needed = machine.getPrice() - machine.getBalance();
            console.log(`Insufficient balance. Need Rs ${needed} more.`);
            return this;
        }
    }

    dispensItem(): VendingState {
        console.log("Please select item first!");
        return this;
    }

    returnCoin(machine: VendinMachine): VendingState {
        console.log(`Returning coin: Rs ${machine.getBalance()}`);
        machine.setBalance(0);
        return machine.getNoCoinState();
    }

    refillQuant(): VendingState {
        console.log("Cannot refill while transaction is in progress.");
        return this;
    }

    stateStatus(): string {
        return "HAS_COIN";
    }
}

// DispenseState
class DispenseState implements VendingState {
    insertCoin(_: VendinMachine, coin: number): VendingState {
        console.log(`Please wait. Dispensing... Coin returned: Rs ${coin}`);
        return this;
    }

    selectItem(): VendingState {
        console.log("Already dispensing item...");
        return this;
    }

    dispensItem(machine: VendinMachine): VendingState {
        console.log("Item dispensed!");
        machine.decrementItem();

        if (machine.getItemCount() > 0) {
            return machine.getNoCoinState();
        } else {
            console.log("Machine is now SOLD OUT!");
            return machine.getSoldOutState();
        }
    }

    returnCoin(): VendingState {
        console.log("Cannot return coin while dispensing!");
        return this;
    }

    refillQuant(): VendingState {
        console.log("Cannot refill during dispensing.");
        return this;
    }

    stateStatus(): string {
        return "DISPENSING";
    }
}

// SoldOutState
class SoldoutState implements VendingState {
    insertCoin(_: VendinMachine, coin: number): VendingState {
        console.log(`Machine sold out. Returning Rs ${coin}`);
        return this;
    }

    selectItem(): VendingState {
        console.log("Machine is sold out!");
        return this;
    }

    dispensItem(): VendingState {
        console.log("Machine is sold out!");
        return this;
    }

    returnCoin(): VendingState {
        console.log("No coin inserted.");
        return this;
    }

    refillQuant(machine: VendinMachine, quantity: number): VendingState {
        machine.incrementItem(quantity);
        console.log("Machine refilled.");
        return machine.getNoCoinState();
    }

    stateStatus(): string {
        return "SOLD_OUT";
    }
}

// ---------------- MAIN ----------------

const machine = new VendinMachine(2, 20);

console.log("=== VENDING MACHINE START ===");

machine.stateStatus();

console.log("\n1. Select without coin:");
machine.selectItem();
machine.stateStatus();

console.log("\n2. Insert coin:");
machine.insertCoin(10);
machine.stateStatus();

console.log("\n3. Select with insufficient funds:");
machine.selectItem();
machine.stateStatus();

console.log("\n4. Add more coins:");
machine.insertCoin(10);
machine.stateStatus();

console.log("\n5. Select item:");
machine.selectItem();
machine.stateStatus();

console.log("\n6. Dispense item:");
machine.dispensItem();
machine.stateStatus();

console.log("\n7. Buy last item:");
machine.insertCoin(20);
machine.selectItem();
machine.dispensItem();
machine.stateStatus();

console.log("\n8. Try using sold-out machine:");
machine.insertCoin(5);

console.log("\n9. Refill machine:");
machine.refillQuant(2);
machine.stateStatus();