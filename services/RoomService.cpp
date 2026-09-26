// Room Service - handles all room related operations
// This is part of the Service layer in our basic system design
// It reads/writes room data from Rooms.txt file (file-based storage)

#include "../models/Room.cpp"
#include <fstream>
#include <vector>
using namespace std;

class RoomService {
public:
    // create Rooms.txt with default rooms if it does not exist
    void initRooms() {
        ifstream check("Rooms.txt");
        if (check.good()) {
            check.close();
            return; // file already exists, no need to create
        }
        check.close();

        // creating 10 rooms: 5 Standard, 3 Deluxe, 2 Suite
        ofstream file("Rooms.txt");
        file << "1 Standard 1000 1" << endl;
        file << "2 Standard 1000 1" << endl;
        file << "3 Standard 1000 1" << endl;
        file << "4 Standard 1000 1" << endl;
        file << "5 Standard 1000 1" << endl;
        file << "6 Deluxe 2000 1" << endl;
        file << "7 Deluxe 2000 1" << endl;
        file << "8 Deluxe 2000 1" << endl;
        file << "9 Suite 3500 1" << endl;
        file << "10 Suite 3500 1" << endl;
        file.close();
    }

    // read all rooms from file
    vector<Room> getAllRooms() {
        vector<Room> rooms;
        ifstream file("Rooms.txt");
        int num, price, avail;
        string type;
        while (file >> num >> type >> price >> avail) {
            Room r(num, type, price, avail == 1);
            rooms.push_back(r);
        }
        file.close();
        return rooms;
    }

    // show only available rooms
    void showAvailableRooms() {
        vector<Room> rooms = getAllRooms();
        cout << endl;
        cout << "    Available Rooms:" << endl;
        cout << "    ------------------------------------------------" << endl;
        int count = 0;
        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i].isAvailable) {
                rooms[i].display();
                count++;
            }
        }
        if (count == 0) {
            cout << "    No rooms available right now!" << endl;
        }
        cout << "    ------------------------------------------------" << endl;
        cout << "    Total available: " << count << endl;
    }

    // show all rooms (both available and booked)
    void showAllRooms() {
        vector<Room> rooms = getAllRooms();
        cout << endl;
        cout << "    All Rooms:" << endl;
        cout << "    ------------------------------------------------" << endl;
        for (int i = 0; i < rooms.size(); i++) {
            rooms[i].display();
        }
        cout << "    ------------------------------------------------" << endl;
    }

    // update room status (available or booked)
    void updateRoomStatus(int roomNum, bool available) {
        vector<Room> rooms = getAllRooms();
        ofstream file("Rooms.txt");
        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i].roomNumber == roomNum) {
                rooms[i].isAvailable = available;
            }
            file << rooms[i].roomNumber << " " << rooms[i].roomType << " "
                 << rooms[i].pricePerNight << " " << (rooms[i].isAvailable ? 1 : 0) << endl;
        }
        file.close();
    }

    // check if a specific room is available
    bool isRoomAvailable(int roomNum) {
        vector<Room> rooms = getAllRooms();
        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i].roomNumber == roomNum) {
                return rooms[i].isAvailable;
            }
        }
        return false;
    }

    // get room details by room number
    Room getRoomByNumber(int roomNum) {
        vector<Room> rooms = getAllRooms();
        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i].roomNumber == roomNum) {
                return rooms[i];
            }
        }
        return Room(); // return empty room if not found
    }

    // count available rooms
    int countAvailableRooms() {
        vector<Room> rooms = getAllRooms();
        int count = 0;
        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i].isAvailable) {
                count++;
            }
        }
        return count;
    }
};
