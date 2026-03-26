#include <iostream>
#include <string>

using namespace std;

class VendingMachine;
class VendingState;

// states
class NocoinState;
class HascoinState;
class DispanceState;
class SoldoutState;

// abstract class
class VendingState
{
    virtual VendingState *insertCoin(VendingMachine *machine, int coin) = 0;
    virtual VendingState *selectItem(VendingMachine *machine) = 0;
    virtual VendingState *dispenseItem(VendingMachine *machine) = 0;
    virtual VendingState *ReturnCoin(VendingMachine *machine) = 0;
    virtual VendingState *Refil(VendingMachine *machine, int quant) = 0;
    virtual string printStatus() = 0;
};

class VendingMachine
{
private:
    VendingState *currState;
    int quantity;
    int price;
    int insertedCoin;

    // state object
    VendingState *noCoinState;
    VendingState *hasCoinState;
    VendingState *dispenseState;
    VendingState *soldOutState;

public:
    VendingMachine(int quantity, int price);

    void insertCoin(int coin);
    void selectItem();
    void dispenseItem();
    void ReturnCoin();
    void Refil(int quant);
    void printStatus();

    // curd operation
    VendingState *getNoCoinState()
    {
        return NocoinState;
    };

    VendingState *getHasCoinState()
    {
        return HascoinState;
    };

    VendingState *getDispenseState()
    {
        return DispanceState;
    };

    VendingState *getSoldOutState()
    {
        return SoldoutState;
    };

    int getQuantity()
    {
        this->quantity;
    };

    int getInstertedCoin()
    {
        this->insertedCoin;
    };

    void setInsertCoin(int coin)
    {
        this->insertedCoin += coin;
    };

    void addCoin(int coin)
    {
        this->insertedCoin = coin
    }

    void
    insertQuantity(int quant)
    {
        this->quantity += quant;
    };

    void removeQuantity()
    {
        this->quantity--;
    }

    int getPrice()
    {
        this->price;
    }

    void setPrice(int price)
    {
        this->price = price;
    }
};

class NocoinState : public VendingState
{
    VendingState *insertCoin(VendingMachine *machine, int coin) override
    {
        machine->addCoin(coin);
        cout << "the coin is inserted" << coin << endl;
        return machine->getHasCoinState();
    };

    VendingMachine *selectItem(VendingMachine *machine) override
    {
        cout << "please insert the coin" << endl;
        return machine->getNoCoinState();
    };

    VendingMachine *dispenseItem(VendingMachine *machine) override
    {
        cout << "please insert the coin" << endl;
        return machine->getNoCoinState();
    };

    VendingMachine *ReturnCoin(VendingMachine *machine) override
    {
        cout << "please insert the coin" << endl;
        return machine->getNoCoinState();
    };

    VendingMachine *Refil(VendingMachine *machine, int quant) override
    {
        cout << "item is refilling" << endl;
        machine->insertQuantity(quant);
        return machine->getNoCoinState();
    };

    string printStatus() override
    {
        return "NO_COIN";
    }
};

class HascoinState : public VendingState
{
    VendingState *insertCoin(VendingMachine *machine, int coin) override
    {
        machine->setInsertCoin(coin);
        cout << "the coin is inserted" << coin << endl;
        return machine->getHasCoinState();
    };

    VendingMachine *selectItem(VendingMachine *machine) override
    {
        if (machine->getInstertedCoin() >= machine->getPrice())
        {
            cout << "item is dispensing"

                int amount = machine->getInstertedCoin() - machine->getPrice();

            if amount
                > 0
                {
                    cout << "change is returning with amount : " << amount << endl;
                }
            machine->setInsertedCoin(0);

            return machine->getDispenseState();
        }
        else
        {
            int needed = machine->getPrice() - machine->getInsertedCoin();
            cout << "Insufficient funds. Need Rs " << needed << " more." << endl;
            return machine->getHasCoinState(); // Stay in same state
        }
    };

    VendingMachine *dispenseItem(VendingMachine *machine) override
    {
        cout << "please select the item to dispense" << endl;
        return machine->getHasCoinState();
    };

    VendingMachine *ReturnCoin(VendingMachine *machine) override
    {
        cout << "amount inserted is : " << machine->getInstertedCoin();
        << endl;
        cout << machine->addCoin(0);
        return machine->getNoCoinState();
    };

    VendingMachine *Refil(VendingMachine *machine, int quant) override
    {
        cout << "can't refill in this state" << endl;
        return machine->getHasCoinState();
    };

    string printStatus() override
    {
        return "NO_COIN";
    }
};

class DispanceState : public VendingState
{
    VendingState *insertCoin(VendingMachine *machine, int coin) override
    {
        cout << "sorry wait for ieam to dispense" << coin << endl;
        return machine->getDispenseState();
    };

    VendingMachine *selectItem(VendingMachine *machine) override
    {
        cout << "wait you already select the item" << endl;

        return machine->getDispenseState();
    };

    VendingMachine *dispenseItem(VendingMachine *machine) override
    {
        cout << "item is dispensed" << endl;

        machine->removeQuantity();

        if (machine->getQuantity() > 0)
        {
            return machine->getNoCoinState();
        }
        else
        {
            cout << "Sorry Item is OutOfStock" << endl;

            return machine->getSoldOutState();
        }
    };

    VendingMachine *ReturnCoin(VendingMachine *machine) override
    {
        cout << "you can't get coin this state : ";
        << endl;
        return machine->getDispenseState();
    };

    VendingMachine *Refil(VendingMachine *machine, int quant) override
    {
        cout << "can't refill in this state" << endl;
        return machine->getDispenseState();
    };

    string printStatus() override
    {
        return "DISPENSE_ITEM";
    }
};

class SoldOutState : public VendingState
{
    VendingState *insertCoin(VendingMachine *machine, int coin) override
    {
        cout << "the item is sold out" << coin << endl;
        return machine->getSoldOutState();
    };

    VendingMachine *selectItem(VendingMachine *machine) override
    {
        cout << "the item is sold out" << endl;

        return machine->getSoldOutState();
    };

    VendingMachine *dispenseItem(VendingMachine *machine) override
    {
        cout << "ithe item is sold out" << endl;
        return machine->getSoldOutState();
    };

    VendingMachine *ReturnCoin(VendingMachine *machine) override
    {
        cout << " sorry the iteam is out of stock ";
        << endl;
        return machine->getSoldOutState();
    };

    VendingMachine *Refil(VendingMachine *machine, int quant) override
    {
        machine->insertQuantity(quant);
        return machine->getNoCoinState();
    };

    string printStatus() override
    {
        return "SOLD_OUT";
    };
};

VendingMachine::VendingMachine(int item, int price)
{
    this->quantity = item;
    this->price = price;
    this->insertedCoin = 0;

    nocoinState = new NocoinState();
    hasCoinState = new HascoinState();
    dispenseState = new DispanceState();
    soldOutState = new SoldOutState();

    if (item > 0)
    {
        currState = noCoinState;
    }
    else
    {
        currState = soldOutState;
    }
};

void VendingMachine::insertCoin(int coin)
{
    currState = currState->insertCoin(this, coin);
}

void VendingMachine::selectItem()
{
    currentState = currentState->selectItem(this);
}

void VendingMachine::dispenseItem()
{
    currentState = currentState->dispenseItem(this);
}

void VendingMachine::ReturnCoin()
{
    currentState = currentState->ReturnCoin(this);
}

void VendingMachine::refill(int quantity)
{
    currentState = currentState->refill(this, quantity);
}

void VendingMachine::printStatus()
{
    cout << "\n--- Vending Machine Status ---" << endl;
    cout << "Items remaining: " << itemCount << endl;
    cout << "Inserted coin: Rs " << insertedCoins << endl;
    cout << "Current state: " << currentState->getStateName() << endl
         << endl;
}

int main(void)
{
    int itemCount = 5;
    int itemPrice = 10;

    VendingMachine machine(itemCount, itemPrice);
    machine.printStatus();

    cout << "1. Trying to select item without coin:" << endl;
    machine.selectItem(); // Should ask for coin, no state change
    machine.printStatus();

    cout << "2. Inserting coin:" << endl;
    machine.insertCoin(10); // State changes to HAS_COIN
    machine.printStatus();

    cout << "3. Selecting item with insufficient funds:" << endl;
    machine.selectItem(); // Insufficient funds, stays in HAS_COIN
    machine.printStatus();

    cout << "4. Adding more coins:" << endl;
    machine.insertCoin(10); // Add more money, stays in HAS_COIN
    machine.printStatus();

    cout << "5. Selecting item Now" << endl;
    machine.selectItem(); // State changes to SOLD
    machine.printStatus();

    cout << "6. Dispensing item:" << endl;
    machine.dispenseItem(); // State changes to NO_COIN (items remaining)
    machine.printStatus();

    cout << "7. Buying last item:" << endl;
    machine.insertCoin(20); // State changes to HAS_COIN
    machine.selectItem();   // State changes to SOLD
    machine.dispenseItem(); // State changes to SOLD_OUT (no items left)
    machine.printStatus();

    cout << "8. Trying to use sold out machine:" << endl;
    machine.insertCoin(5); // Coin returned, stays in SOLD_OUT

    cout << "9. Trying to use sold out machine:" << endl;
    machine.refill(2);
    machine.printStatus(); // State changes NO_COIN

    return 0;
};