// room Model - stores room data
// this is part of the model layer 

#include <iostream>
#include <string>
using namespace std;

class Room {
public:
    int roomNumber;
    string roomType;     // Standard, Deluxe, Suite
    int pricePerNight;
    bool isAvailable;

    // default constructor
    Room() {
        roomNumber = 0;
        roomType = "";
        pricePerNight = 0;
        isAvailable = true;
    }

    // constructor with values
    Room(int num, string type, int price, bool available) {
        roomNumber = num;
        roomType = type;
        pricePerNight = price;
        isAvailable = available;
    }

    // display room info
    void display() {
        cout << "    Room " << roomNumber << "  |  " << roomType
             << "  |  " << pricePerNight << " Rs/night  |  "
             << (isAvailable ? "Available" : "Booked") << endl;
    }
};
