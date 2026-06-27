#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

enum class VehicleType
{
    BIKE,
    CAR,
    TRUCK
};

class Vehicle
{
private:
    string number;
    VehicleType type;

public:
    Vehicle(string num, VehicleType t)
    {
        number = num;
        type = t;
    }

    string getNumber()
    {
        return number;
    }

    VehicleType getType()
    {
        return type;
    }
};

class ParkingSpot
{
private:
    int id;
    VehicleType type;
    bool occupied;

public:
    ParkingSpot(int id, VehicleType type)
    {
        this->id = id;
        this->type = type;
        occupied = false;
    }

    int getId()
    {
        return id;
    }

    VehicleType getType()
    {
        return type;
    }

    bool isOccupied()
    {
        return occupied;
    }

    void park()
    {
        occupied = true;
    }

    void remove()
    {
        occupied = false;
    }
};

class Ticket
{
private:
    int ticketId;
    string vehicleNumber;
    int parkingSpotId;

public:
    Ticket() {}

    Ticket(int ticketId, string vehicleNumber, int parkingSpotId)
    {
        this->ticketId = ticketId;
        this->vehicleNumber = vehicleNumber;
        this->parkingSpotId = parkingSpotId;
    }

    int getTicketId()
    {
        return ticketId;
    }

    int getParkingSpotId()
    {
        return parkingSpotId;
    }

    string getVehicleNumber()
    {
        return vehicleNumber;
    }
};

class ParkingLot
{
private:
    vector<ParkingSpot> spots;

    unordered_map<int, Ticket> activeTickets;

    unordered_map<VehicleType, queue<int>> freeSpots;

    int ticketCounter;

public:
    ParkingLot(int bikeCount, int carCount, int truckCount)
    {

        ticketCounter = 1;

        int spotId = 0;

        // Bike Spots
        for (int i = 0; i < bikeCount; i++)
        {
            spots.push_back(ParkingSpot(spotId, VehicleType::BIKE));
            freeSpots[VehicleType::BIKE].push(spotId);
            spotId++;
        }

        // Car Spots
        for (int i = 0; i < carCount; i++)
        {
            spots.push_back(ParkingSpot(spotId, VehicleType::CAR));
            freeSpots[VehicleType::CAR].push(spotId);
            spotId++;
        }

        // Truck Spots
        for (int i = 0; i < truckCount; i++)
        {
            spots.push_back(ParkingSpot(spotId, VehicleType::TRUCK));
            freeSpots[VehicleType::TRUCK].push(spotId);
            spotId++;
        }
    }

    int parkVehicle(Vehicle vehicle)
    {

        VehicleType type = vehicle.getType();

        // Check availability
        if (freeSpots[type].empty())
        {
            cout << "No space available for vehicle\n";
            return -1;
        }

        // Allocate spot
        int spotId = freeSpots[type].front();
        freeSpots[type].pop();

        // Mark occupied
        spots[spotId].park();

        // Generate Ticket
        int ticketId = ticketCounter++;

        Ticket ticket(ticketId,
                      vehicle.getNumber(),
                      spotId);

        activeTickets[ticketId] = ticket;

        cout << "Vehicle Parked Successfully\n";
        cout << "Ticket ID: " << ticketId << endl;
        cout << "Spot ID: " << spotId << endl;

        return ticketId;
    }

    void unparkVehicle(int ticketId)
    {

        // Ticket validation
        if (activeTickets.find(ticketId) == activeTickets.end())
        {
            cout << "Invalid Ticket\n";
            return;
        }

        Ticket ticket = activeTickets[ticketId];

        int spotId = ticket.getParkingSpotId();

        // Free spot
        spots[spotId].remove();

        VehicleType type = spots[spotId].getType();

        // Add back to free queue
        freeSpots[type].push(spotId);

        // Remove ticket
        activeTickets.erase(ticketId);

        cout << "Vehicle Removed Successfully\n";
        cout << "Freed Spot ID: " << spotId << endl;
    }

    void displayAvailableSpots()
    {

        cout << "\nAvailable Spots:\n";

        cout << "Bike: "
             << freeSpots[VehicleType::BIKE].size()
             << endl;

        cout << "Car: "
             << freeSpots[VehicleType::CAR].size()
             << endl;

        cout << "Truck: "
             << freeSpots[VehicleType::TRUCK].size()
             << endl;
    }
};

int main()
{

    ParkingLot parkingLot(2, 3, 1);

    Vehicle car1("MH12AB1234", VehicleType::CAR);
    Vehicle bike1("MH14XY9999", VehicleType::BIKE);
    Vehicle truck1("MH20TR1111", VehicleType::TRUCK);

    int ticket1 = parkingLot.parkVehicle(car1);

    int ticket2 = parkingLot.parkVehicle(bike1);

    int ticket3 = parkingLot.parkVehicle(truck1);

    parkingLot.displayAvailableSpots();

    parkingLot.unparkVehicle(ticket2);

    parkingLot.displayAvailableSpots();

    return 0;
}