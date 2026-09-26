// booking Service - handles all booking related operations
// this is part of the Service layer in our basic system design
// it uses RoomService for room operations and stores bookings in Bookings.txt

#include "../models/Booking.cpp"
#include "RoomService.cpp"
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class BookingService {
private:
    RoomService roomService;

    // get the next booking ID by finding max ID in file
    int getNextBookingId() {
        ifstream file("Bookings.txt");
        int maxId = 0;
        int bid, cid, rn, n, tc;
        string cn, rt;
        while (file >> bid >> cid >> cn >> rn >> rt >> n >> tc) {
            if (bid > maxId) maxId = bid;
        }
        file.close();
        return maxId + 1;
    }

public:
    // constructor - initialize rooms when service starts
    BookingService() {
        roomService.initRooms();
    }

    // show available rooms (delegates to RoomService)
    void showAvailableRooms() {
        roomService.showAvailableRooms();
    }

    // show all rooms (delegates to RoomService)
    void showAllRooms() {
        roomService.showAllRooms();
    }

    // book a room for a customer
    void bookRoom(int custId, string custName) {
        roomService.showAvailableRooms();

        cout << "\n    Enter room number to book: ";
        int roomNum;
        cin >> roomNum;

        // check if room is available
        if (!roomService.isRoomAvailable(roomNum)) {
            cout << "\n    Sorry! Room " << roomNum << " is not available." << endl;
            return;
        }

        // get room details
        Room room = roomService.getRoomByNumber(roomNum);
        if (room.roomNumber == 0) {
            cout << "\n    Room not found!" << endl;
            return;
        }

        cout << "    Enter number of nights: ";
        int nights;
        cin >> nights;

        if (nights <= 0) {
            cout << "    Invalid number of nights!" << endl;
            return;
        }

        int totalCost = nights * room.pricePerNight;

        // show booking summary
        cout << "\n    ================================================" << endl;
        cout << "    Booking Summary:" << endl;
        cout << "    Customer     : " << custName << endl;
        cout << "    Room         : " << roomNum << " (" << room.roomType << ")" << endl;
        cout << "    Price        : " << room.pricePerNight << " Rs/night" << endl;
        cout << "    Nights       : " << nights << endl;
        cout << "    Total Cost   : " << totalCost << " Rs" << endl;
        cout << "    ================================================" << endl;

        cout << "    Confirm booking? (Y/N): ";
        char confirm;
        cin >> confirm;

        if (confirm == 'Y' || confirm == 'y') {
            int bookingId = getNextBookingId();

            // save booking to file
            ofstream file("Bookings.txt", ios_base::app);
            file << bookingId << " " << custId << " " << custName << " "
                 << roomNum << " " << room.roomType << " " << nights << " " << totalCost << endl;
            file.close();

            // mark room as booked
            roomService.updateRoomStatus(roomNum, false);

            cout << "\n    Booking confirmed! Your Booking ID: " << bookingId << endl;
            cout << "    Thank you " << custName << "!" << endl;
        } else {
            cout << "\n    Booking cancelled." << endl;
        }
    }

    // view bookings for a specific customer
    void viewBookings(int custId) {
        ifstream file("Bookings.txt");
        int bid, cid, rn, n, tc;
        string cn, rt;
        bool found = false;

        cout << "\n    Your Bookings:" << endl;
        cout << "    ================================================" << endl;

        while (file >> bid >> cid >> cn >> rn >> rt >> n >> tc) {
            if (cid == custId) {
                cout << "    Booking #" << bid
                     << "  |  Room: " << rn << " (" << rt << ")"
                     << "  |  " << n << " nights"
                     << "  |  " << tc << " Rs" << endl;
                found = true;
            }
        }
        file.close();

        if (!found) {
            cout << "    No bookings found for your account." << endl;
        }
        cout << "    ================================================" << endl;
    }

    // cancel a booking
    void cancelBooking(int custId) {
        viewBookings(custId);

        cout << "\n    Enter Booking ID to cancel (0 to go back): ";
        int bookingId;
        cin >> bookingId;

        if (bookingId == 0) return;

        // read all bookings from file
        ifstream file("Bookings.txt");
        vector<string> lines;
        string line;
        int roomToFree = -1;
        bool found = false;

        while (getline(file, line)) {
            if (line.length() == 0) continue;
            int bid, cid, rn, n, tc;
            string cn, rt;
            istringstream iss(line);
            if (iss >> bid >> cid >> cn >> rn >> rt >> n >> tc) {
                if (bid == bookingId && cid == custId) {
                    roomToFree = rn;
                    found = true;
                    // dont add this line back (it gets deleted)
                } else {
                    lines.push_back(line);
                }
            }
        }
        file.close();

        if (found) {
            // rewrite file without the cancelled booking
            ofstream outFile("Bookings.txt");
            for (int i = 0; i < lines.size(); i++) {
                outFile << lines[i] << endl;
            }
            outFile.close();

            // free the room
            if (roomToFree != -1) {
                roomService.updateRoomStatus(roomToFree, true);
            }

            cout << "    Booking #" << bookingId << " cancelled successfully!" << endl;
        } else {
            cout << "    Booking not found or does not belong to you!" << endl;
        }
    }

    // view all bookings (for admin use)
    void viewAllBookings() {
        ifstream file("Bookings.txt");
        int bid, cid, rn, n, tc;
        string cn, rt;
        bool found = false;

        cout << "\n    All Bookings:" << endl;
        cout << "    ====================================================" << endl;

        while (file >> bid >> cid >> cn >> rn >> rt >> n >> tc) {
            cout << "    #" << bid
                 << "  |  " << cn << " (ID:" << cid << ")"
                 << "  |  Room:" << rn << " (" << rt << ")"
                 << "  |  " << n << " nights"
                 << "  |  " << tc << " Rs" << endl;
            found = true;
        }
        file.close();

        if (!found) {
            cout << "    No bookings yet." << endl;
        }
        cout << "    ====================================================" << endl;
    }

    // calculate total revenue from all bookings (for admin use)
    int getTotalRevenue() {
        ifstream file("Bookings.txt");
        int total = 0;
        int bid, cid, rn, n, tc;
        string cn, rt;

        while (file >> bid >> cid >> cn >> rn >> rt >> n >> tc) {
            total += tc;
        }
        file.close();
        return total;
    }

    // count total bookings
    int getTotalBookings() {
        ifstream file("Bookings.txt");
        int count = 0;
        int bid, cid, rn, n, tc;
        string cn, rt;

        while (file >> bid >> cid >> cn >> rn >> rt >> n >> tc) {
            count++;
        }
        file.close();
        return count;
    }
};
