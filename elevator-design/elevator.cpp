#include <iostream>
#include <set>

using namespace std;

enum Direction
{
    IDLE,
    UP,
    DOWN
};

class Elevator
{
private:
    int currentFloor;
    int totalFloor;
    bool doorOpen;

    Direction direction;

    set<int> upReq;
    set<int, greater<int>> downReq;

public:
    Elevator(int size)
    {
        currentFloor = 0;
        totalFloor = size;
        direction = IDLE;
        doorOpen = false;
    }

    bool openDoor()
    {
        doorOpen = true;

        cout << "Door Opening" << endl;

        return true;
    }

    bool closeDoor()
    {
        doorOpen = false;

        cout << "Door Closing" << endl;

        return true;
    }

    void moveUp()
    {
        currentFloor++;

        cout << "Moving Up to Floor "
             << currentFloor << endl;
    }

    void moveDown()
    {
        currentFloor--;

        cout << "Moving Down to Floor "
             << currentFloor << endl;
    }

    void addRequest(int floor)
    {
        if (floor > currentFloor)
        {
            upReq.insert(floor);
        }
        else if (floor < currentFloor)
        {
            downReq.insert(floor);
        }

        processReq();
    }

    void processReq()
    {
        // UP direction first
        while (!upReq.empty())
        {
            direction = UP;

            int target = *upReq.begin();

            while (currentFloor < target)
            {
                moveUp();
            }

            openDoor();
            closeDoor();

            upReq.erase(target);
        }

        // DOWN direction
        while (!downReq.empty())
        {
            direction = DOWN;

            int target = *downReq.begin();

            while (currentFloor > target)
            {
                moveDown();
            }

            openDoor();
            closeDoor();

            downReq.erase(target);
        }

        direction = IDLE;
    }
};

int main()
{
    Elevator e1(5);

    e1.addRequest(3);
    e1.addRequest(4);
    e1.addRequest(1);
    e1.addRequest(5);
    e1.addRequest(2);

    return 0;
}