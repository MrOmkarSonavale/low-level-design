#include <iostream>
using namespace std;

class MoneyDispenser
{
protected:
    MoneyDispenser *next;

public:
    MoneyDispenser() : next(nullptr) {}

    void setHandler(MoneyDispenser *m)
    {
        next = m;
    }

    virtual void cashDispenser(int amount) = 0;
    virtual ~MoneyDispenser() {}
};

class ThousandHandler : public MoneyDispenser
{
    int numnotes;

public:
    ThousandHandler(int notes) : numnotes(notes) {}

    void cashDispenser(int amount) override
    {
        int notesNeed = amount / 1000;

        if (notesNeed > numnotes)
            notesNeed = numnotes;

        numnotes -= notesNeed;

        if (notesNeed > 0)
            cout << "Dispensing " << notesNeed << " notes of 1000\n";

        int remaining = amount - notesNeed * 1000;

        if (remaining > 0 && next)
            next->cashDispenser(remaining);
        else if (remaining > 0)
            cout << "Cannot dispense remaining amount: " << remaining << endl;
    }
};

class HundredHandler : public MoneyDispenser
{
    int numnotes;

public:
    HundredHandler(int notes) : numnotes(notes) {}

    void cashDispenser(int amount) override
    {
        int notesNeed = amount / 100;

        if (notesNeed > numnotes)
            notesNeed = numnotes;

        numnotes -= notesNeed;

        if (notesNeed > 0)
            cout << "Dispensing " << notesNeed << " notes of 100\n";

        int remaining = amount - notesNeed * 100;

        if (remaining > 0 && next)
            next->cashDispenser(remaining);
        else if (remaining > 0)
            cout << "Cannot dispense remaining amount: " << remaining << endl;
    }
};

class FiftyHandler : public MoneyDispenser
{
    int numnotes;

public:
    FiftyHandler(int notes) : numnotes(notes) {}

    void cashDispenser(int amount) override
    {
        int notesNeed = amount / 50;

        if (notesNeed > numnotes)
            notesNeed = numnotes;

        numnotes -= notesNeed;

        if (notesNeed > 0)
            cout << "Dispensing " << notesNeed << " notes of 50\n";

        int remaining = amount - notesNeed * 50;

        if (remaining > 0)
            cout << "Cannot dispense remaining amount: " << remaining << endl;
    }
};

int main()
{
    MoneyDispenser *M1 = new ThousandHandler(5);
    MoneyDispenser *M2 = new HundredHandler(15);
    MoneyDispenser *M3 = new FiftyHandler(20);

    M1->setHandler(M2);
    M2->setHandler(M3);

    M1->cashDispenser(2500);

    delete M1;
    delete M2;
    delete M3;
}
