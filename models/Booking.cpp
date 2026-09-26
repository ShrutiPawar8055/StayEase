// booking Model - stores booking data
// this is part of the model layer in our basic system design

#include <iostream>
#include <string>
using namespace std;

class Booking {
public:
    int bookingId;
    int customerId;
    string customerName;
    int roomNumber;
    string roomType;
    int nights;
    int totalCost;

    // default constructor
    Booking() {
        bookingId = 0;
        customerId = 0;
        customerName = "";
        roomNumber = 0;
        roomType = "";
        nights = 0;
        totalCost = 0;
    }

    // display booking info
    void display() {
        cout << "    Booking #" << bookingId
             << "  |  Customer: " << customerName
             << "  |  Room: " << roomNumber
             << "  |  " << nights << " nights"
             << "  |  " << totalCost << " Rs" << endl;
    }
};
