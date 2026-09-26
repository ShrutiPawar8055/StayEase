// ========================================================================
// Hotel Taj - Hotel Management System
// ========================================================================
// Basic System Design:
//   - Models Layer    : models/Room.cpp, models/Booking.cpp (data classes)
//   - Service Layer   : services/RoomService.cpp, services/BookingService.cpp (business logic)
//   - UI Layer        : main.cpp (user interface), Menu.cpp (menu card)
//   - Auth            : password.cpp (admin authentication)
//   - Storage         : File-based (INFO.txt, Bookings.txt, Rooms.txt, BILL.txt)
// ========================================================================

#include "Menu.cpp"
#include "services/BookingService.cpp"
#include "password.cpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

// Customer class - stores customer information and saves to file
class Customer {
private:
  string name;
  int age;
  long phone;
  string email;
  string address;

public:
  int ID = 0;

  // setter for customer name (used by login)
  void setName(string n) {
    name = n;
  }

  // register a new customer
  void set() {
    ofstream w;
    w.open("INFO.txt", ios_base::app);
    cout << "Enter your name        : ";
    cin >> name;

    cout << "Enter your age         : ";
    cin >> age;

    cout << "Enter your phone number: ";
    cin >> phone;

    cout << "Enter your email       : ";
    cin >> email;

    cout << "Enter your address     : ";
    cin >> address;

    // count existing customers to generate ID
    int cnt = 0;
    string s;
    ifstream r("INFO.txt", ios_base::in);
    while (getline(r, s)) {
      cnt++;
    }
    r.close();
    ID = cnt;
    w << setw(10) << "#f01" << cnt << "  " << setw(15) << name << " "
      << setw(10) << age << " " << setw(10) << phone << " " << setw(15) << email
      << " " << setw(15) << address << endl;
    w.close();
  }

  // getter for customer name (used by booking)
  string getName() {
    return name;
  }
};

// PAGE class - main UI controller that connects all features together
class PAGE : public Customer {
  char a;
  menu s;                        // menu card service
  BookingService bookingService; // room booking service
  password p;                    // admin authentication

public:
  // main home screen
  void show() {
    cout << endl;
    cout << "=================================================================="
            "============"
         << endl;
    cout << "                               Welcome to Hotel AESTHETIC               "
            "            "
         << endl;
    cout << "                                  A) About                        "
            "            "
         << endl;
    cout << "                                  B) Register                     "
            "            "
         << endl;
    cout << "                                  C) Login                        "
            "            "
         << endl;
    cout << "                                  D) Help                         "
            "            "
         << endl;
    cout << "                                  E) Setting                      "
            "            "
         << endl;
    cout << "                                  F) Exit                         "
            "            "
         << endl;
    cout << "                            (Enter character to move on)          "
            "            "
         << endl;
    cout << "=================================================================="
            "============"
         << endl;
    cin >> a;
    open();
  }

  // display About page from file
  void About() {
    ifstream inputFile("About.txt");
    string line;
    while (getline(inputFile, line)) {
      cout << line << endl;
    }
    inputFile.close();
    char a;
    cout << "Press any Key : ";
    cin >> a;
    show();
  }

  // display Help page from file
  void Help() {
    ifstream inputFile("Help.txt");
    string line;
    while (getline(inputFile, line)) {
      cout << line << endl;
    }
    inputFile.close();
    char a;
    cout << "Press any Key : ";
    cin >> a;
    show();
  }

  // login an existing customer using ID and phone number
  void login() {
    cout << endl;
    cout << "    ================================================" << endl;
    cout << "                      CUSTOMER LOGIN                " << endl;
    cout << "    ================================================" << endl;
    cout << "    Enter your Customer ID   : ";
    int loginId;
    cin >> loginId;
    cout << "    Enter your Phone Number  : ";
    long loginPhone;
    cin >> loginPhone;

    // search in INFO.txt for matching ID and Phone
    ifstream file("INFO.txt");
    string line;
    bool found = false;
    int lineNum = 0;

    while (getline(file, line)) {
      if (line.length() == 0) continue;
      // check if this line matches the customer ID
      if (lineNum == loginId) {
        // check if phone number exists in this line
        if (line.find(to_string(loginPhone)) != string::npos) {
          found = true;
          // extract name from the line (after #f01<id> and spaces)
          // parse the stored data
          string temp;
          int storedAge;
          long storedPhone;
          string storedEmail, storedAddress, storedName;
          istringstream iss(line);
          iss >> temp >> storedName >> storedAge >> storedPhone >> storedEmail >> storedAddress;
          ID = loginId;
          setName(storedName);
          break;
        }
      }
      lineNum++;
    }
    file.close();

    if (found) {
      cout << endl;
      cout << "    Login Successful! Welcome back, " << getName() << "!" << endl;
      info();
    } else {
      cout << endl;
      cout << "    Login Failed! Invalid ID or Phone Number." << endl;
      cout << "    Press 1) Try Again  2) Go to Home" << endl;
      int ch;
      cin >> ch;
      if (ch == 1) {
        login();
      } else {
        show();
      }
    }
  }

  // route to correct page based on user choice
  void open() {
    switch (a) {
    case 'A':
    case 'a':
      About();
      break;
    case 'B':
    case 'b':
      set();
      cout << endl;
      cout << "    Registration Successful! Your Customer ID is: " << ID << endl;
      cout << "    (Remember your ID and Phone Number for login)" << endl;
      info();
      break;
    case 'C':
    case 'c':
      login();
      break;
    case 'D':
    case 'd':
      Help();
      break;
    case 'E':
    case 'e':
      settingsMenu();
      break;
    case 'F':
    case 'f':
      cout << endl;
      cout << "    Thank you for using Hotel Taj Management System!" << endl;
      cout << "    Goodbye!" << endl;
      cout << endl;
      exit(0);
      break;
    default:
      cout << "----------------------------------------------------------------"
              "--------------"
           << endl;
      cout << "                     WARNING :: PLEASE ENTER A VALID CHARACTER  "
              "              "
           << endl;
      cout << "----------------------------------------------------------------"
              "--------------"
           << endl;
      show();
      break;
    }
  }

  // customer dashboard - after registration
  void info() {
    cout << endl;
    cout << "=================================================================="
            "============"
         << endl;
    cout << "                    Choose correct option for What do Want?       "
            "            "
         << endl;
    cout << "                              Press 1) Menu Card                  "
            "            "
         << endl;
    cout << "                              Press 2) Booking                    "
            "            "
         << endl;
    cout << "                              Press 3) BACK TO HOME               "
            "            "
         << endl;
    cout << "=================================================================="
            "============"
         << endl;
    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
      s.Card(ID);
      info();
      break;
    case 2:
      bookingMenu();
      info();
      break;
    case 3:
      show();
      break;
    default:
      cout << "----------------------------------------------------------------"
              "--------------"
           << endl;
      cout << "                     WARNING :: PLEASE ENTER A VALID CHARACTER  "
              "              "
           << endl;
      cout << "----------------------------------------------------------------"
              "--------------"
           << endl;
      info();
      break;
    }
  }

  // room booking menu for customers
  void bookingMenu() {
    cout << endl;
    cout << "=================================================================="
            "============"
         << endl;
    cout << "                              ROOM BOOKING                        "
            "            "
         << endl;
    cout << "                         1) View Available Rooms                  "
            "            "
         << endl;
    cout << "                         2) Book a Room                           "
            "            "
         << endl;
    cout << "                         3) View My Bookings                      "
            "            "
         << endl;
    cout << "                         4) Cancel Booking                        "
            "            "
         << endl;
    cout << "                         5) Back                                  "
            "            "
         << endl;
    cout << "=================================================================="
            "============"
         << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
      bookingService.showAvailableRooms();
      bookingMenu();
      break;
    case 2:
      bookingService.bookRoom(ID, getName());
      bookingMenu();
      break;
    case 3:
      bookingService.viewBookings(ID);
      bookingMenu();
      break;
    case 4:
      bookingService.cancelBooking(ID);
      bookingMenu();
      break;
    case 5:
      return;
    default:
      cout << "    Invalid choice! Please try again." << endl;
      bookingMenu();
      break;
    }
  }

  // settings - admin login
  void settingsMenu() {
    cout << endl;
    cout << "=================================================================="
            "============"
         << endl;
    cout << "                              ADMIN SETTINGS                      "
            "            "
         << endl;
    cout << "=================================================================="
            "============"
         << endl;

    // if password not set, ask to create one first
    if (!p.isPasswordSet()) {
      cout << "    First time setup - Please create admin password" << endl;
      cout << endl;
      p.Set_Pass_W();
      adminPanel();
    } else {
      // ask for password (3 attempts)
      for (int i = 0; i < 3; i++) {
        if (p.Pass_W()) {
          adminPanel();
          return;
        }
        cout << "    Attempts left: " << (2 - i) << endl;
      }
      cout << "    Too many wrong attempts! Returning to home." << endl;
      show();
    }
  }

  // admin panel - manage hotel
  void adminPanel() {
    cout << endl;
    cout << "=================================================================="
            "============"
         << endl;
    cout << "                              ADMIN PANEL                         "
            "            "
         << endl;
    cout << "                         1) Change Password                       "
            "            "
         << endl;
    cout << "                         2) View All Bookings                     "
            "            "
         << endl;
    cout << "                         3) View All Customers                    "
            "            "
         << endl;
    cout << "                         4) View Total Revenue                    "
            "            "
         << endl;
    cout << "                         5) View All Rooms                        "
            "            "
         << endl;
    cout << "                         6) Back to Home                          "
            "            "
         << endl;
    cout << "=================================================================="
            "============"
         << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
      p.Set_Pass_W();
      adminPanel();
      break;
    case 2:
      bookingService.viewAllBookings();
      adminPanel();
      break;
    case 3:
      viewAllCustomers();
      adminPanel();
      break;
    case 4:
      cout << endl;
      cout << "    ================================================" << endl;
      cout << "    Total Revenue  : " << bookingService.getTotalRevenue() << " Rs" << endl;
      cout << "    Total Bookings : " << bookingService.getTotalBookings() << endl;
      cout << "    ================================================" << endl;
      adminPanel();
      break;
    case 5:
      bookingService.showAllRooms();
      adminPanel();
      break;
    case 6:
      show();
      break;
    default:
      cout << "    Invalid choice!" << endl;
      adminPanel();
      break;
    }
  }

  // view all registered customers (admin feature)
  void viewAllCustomers() {
    ifstream file("INFO.txt");
    string line;
    cout << endl;
    cout << "    All Registered Customers:" << endl;
    cout << "    ====================================================" << endl;
    bool found = false;
    while (getline(file, line)) {
      if (line.length() > 0) {
        cout << "    " << line << endl;
        found = true;
      }
    }
    if (!found) {
      cout << "    No customers registered yet." << endl;
    }
    cout << "    ====================================================" << endl;
    file.close();
  }
};

int main() {
  PAGE a;
  a.show();
  return 0;
}