#include <iostream>
#include <string>

using namespace std;

// abstreact character class or model class
class Character
{
public:
    virtual string getAbility() = 0;
    virtual ~Character() {}
};

class MarioCharacter : public Character
{
public:
    string getAbility() override
    {
        return "this is mario";
    }
};

class Decorator : public Character
{
protected:
    Character *ch;

public:
    Decorator(Character *character)
    {
        this->ch = character;
    }
};

class MarioWithHeight : public Decorator
{
public:
    MarioWithHeight(Character *ch) : Decorator(ch) {}

    string getAbility() override
    {
        return ch->getAbility() + " hight up";
    }
};

class MarioWithJump : public Decorator
{
public:
    MarioWithJump(Character *ch) : Decorator(ch) {}

    string getAbility() override
    {
        return ch->getAbility() + " long jump";
    }
};

class MarioWithGloves : public Decorator
{
public:
    MarioWithGloves(Character *ch) : Decorator(ch) {}

    string getAbility() override
    {
        return ch->getAbility() + " with Gloves";
    }
};

int main(void)
{
    Character *mario = new MarioCharacter();
    mario->getAbility();

    mario = new MarioWithGloves(mario);
    cout << mario->getAbility() << endl;

    mario = new MarioWithHeight(mario);
    cout << mario->getAbility() << endl;

    return 0;
}