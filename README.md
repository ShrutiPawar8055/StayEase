# GuestEase - Hotel Taj Management System

A console-based Hotel Management System built in C++ that allows customers to register, login, order food, book rooms, and provides an admin panel for hotel staff. This project demonstrates **basic system design principles** like layered architecture, separation of concerns, and file-based persistence.

---

## Table of Contents

- [Features](#features)
- [System Architecture](#system-architecture)
- [Project Structure](#project-structure)
- [How Each Layer Works](#how-each-layer-works)
- [Data Flow Diagrams](#data-flow-diagrams)
- [File Storage Schema](#file-storage-schema)
- [How to Run](#how-to-run)
- [Screenshots / Flow](#screenshots--flow)
- [Design Decisions](#design-decisions)
- [Future Improvements](#future-improvements)

---

## Features

### Customer Features
- **Register** — Create a new account with name, age, phone, email, address
- **Login** — Login using Customer ID + Phone Number
- **Food Ordering** — Browse menu, add items, view itemized bill
- **Room Booking** — View available rooms, book by room number and nights
- **View Bookings** — See all your current room bookings
- **Cancel Booking** — Cancel a booking and free up the room

### Admin Features (Password Protected)
- **View All Bookings** — See every booking in the system
- **View All Customers** — See all registered customers
- **View Total Revenue** — Total earnings from room bookings
- **View All Rooms** — See status of all 10 rooms (Available/Booked)
- **Change Password** — Update admin password

### Room Types
| Type | Rooms | Price/Night |
|------|-------|-------------|
| Standard | 1-5 | ₹1,000 |
| Deluxe | 6-8 | ₹2,000 |
| Suite | 9-10 | ₹3,500 |

### Food Menu
| Item | Code | Price |
|------|------|-------|
| Vadapav | 1 | ₹20 |
| MisalPav | 2 | ₹40 |
| Vadasamber | 3 | ₹50 |
| Kanda Bhji | 4 | ₹30 |
| Mirchi Bhji | 5 | ₹25 |
| Tea | 6 | ₹10 |
| Coffee | 7 | ₹20 |

---

## System Architecture

This project follows a **3-Layer Architecture** pattern where each layer has a single responsibility:

```
┌─────────────────────────────────────────────────────────────┐
│                      UI LAYER (Presentation)                │
│                                                             │
│   main.cpp          - Home screen, navigation, dashboards   │
│   Menu.cpp          - Food menu display and ordering        │
│   password.cpp      - Admin authentication prompts          │
│                                                             │
│   Responsibility: Display menus, take user input,           │
│                   show output — NO business logic here      │
├─────────────────────────────────────────────────────────────┤
│                    SERVICE LAYER (Business Logic)            │
│                                                             │
│   services/BookingService.cpp  - Booking CRUD operations    │
│   services/RoomService.cpp     - Room management operations │
│                                                             │
│   Responsibility: All business rules, calculations,         │
│                   data validation, file read/write           │
├─────────────────────────────────────────────────────────────┤
│                     MODEL LAYER (Data)                       │
│                                                             │
│   models/Room.cpp     - Room data structure                 │
│   models/Booking.cpp  - Booking data structure              │
│                                                             │
│   Responsibility: Define what data looks like               │
│                   (fields, constructors, display)            │
├─────────────────────────────────────────────────────────────┤
│                   STORAGE LAYER (Persistence)                │
│                                                             │
│   INFO.txt       - Customer records                         │
│   Rooms.txt      - Room inventory and status                │
│   Bookings.txt   - Booking records                          │
│   BILL.txt       - Food order bills                         │
│                                                             │
│   Responsibility: Persist data between program runs         │
│                   (acts as a simple file-based database)     │
└─────────────────────────────────────────────────────────────┘
```

### Key Design Principle: Each Layer Only Talks to the Layer Below It

```
   User Input
      │
      ▼
   UI Layer  ──────────►  Does NOT read/write files directly
      │
      ▼
   Service Layer  ─────►  Contains all logic, reads/writes files
      │
      ▼
   Model Layer  ────────►  Data structures used by services
      │
      ▼
   Storage (.txt files) ►  Flat-file persistence
```

---

## Project Structure

```
Genesis/
│
├── main.cpp                  # Entry point + UI controller (PAGE class)
├── Menu.cpp                  # Food menu and ordering (menu class)
├── password.cpp              # Admin authentication (password class)
│
├── models/
│   ├── Room.cpp              # Room model (roomNumber, type, price, status)
│   └── Booking.cpp           # Booking model (bookingId, custId, room, nights, cost)
│
├── services/
│   ├── RoomService.cpp       # Room CRUD operations (init, read, update, check)
│   └── BookingService.cpp    # Booking operations (book, cancel, view, revenue)
│
├── About.txt                 # Hotel information (displayed in About page)
├── Help.txt                  # User guide (displayed in Help page)
│
├── INFO.txt                  # [Auto-generated] Customer database
├── Rooms.txt                 # [Auto-generated] Room inventory
├── Bookings.txt              # [Auto-generated] Booking records
├── BILL.txt                  # [Auto-generated] Food order bills
│
└── README.md                 # This file
```

---

## How Each Layer Works

### 1. Model Layer — "What does the data look like?"

**Room.cpp**
```cpp
class Room {
    int roomNumber;      // 1-10
    string roomType;     // Standard, Deluxe, Suite
    int pricePerNight;   // 1000, 2000, 3500
    bool isAvailable;    // true = free, false = booked
};
```

**Booking.cpp**
```cpp
class Booking {
    int bookingId;       // unique booking number
    int customerId;      // links to customer
    string customerName;
    int roomNumber;      // which room
    string roomType;
    int nights;          // duration of stay
    int totalCost;       // nights × price
};
```

### 2. Service Layer — "What are the business rules?"

**RoomService.cpp** handles:
- `initRooms()` — Creates 10 rooms in Rooms.txt on first run
- `getAllRooms()` — Reads all rooms from file into a vector
- `showAvailableRooms()` — Filters and displays only free rooms
- `isRoomAvailable(roomNum)` — Checks if a specific room is free
- `getRoomByNumber(roomNum)` — Returns a Room object
- `updateRoomStatus(roomNum, status)` — Marks room as booked/available

**BookingService.cpp** handles:
- `bookRoom(custId, name)` — Full booking flow with validation
- `viewBookings(custId)` — Shows bookings for one customer
- `cancelBooking(custId)` — Deletes booking + frees room
- `viewAllBookings()` — Admin: shows all bookings
- `getTotalRevenue()` — Admin: sums all booking costs
- `getTotalBookings()` — Admin: counts bookings

### 3. UI Layer — "What does the user see?"

**main.cpp (PAGE class)** — Controller that connects everything:
- `show()` — Home screen with 6 options
- `login()` — Customer login (ID + Phone verification)
- `info()` — Customer dashboard (Menu / Booking / Back)
- `bookingMenu()` — Room booking sub-menu
- `settingsMenu()` — Admin login with password
- `adminPanel()` — Admin dashboard

**Menu.cpp** — Food ordering system:
- `Card()` — Display menu items
- `inti()` — Take order input
- `bill()` — Calculate item cost
- `bill_display()` — Show final bill and save to BILL.txt

---

## Data Flow Diagrams

### Registration Flow
```
User → enters name, age, phone, email, address
  │
  ▼
Customer.set() → counts lines in INFO.txt → generates ID
  │
  ▼
Appends to INFO.txt: "#f01<ID>  <name> <age> <phone> <email> <address>"
  │
  ▼
Shows: "Your Customer ID is: <ID>"
  │
  ▼
Goes to Customer Dashboard
```

### Login Flow
```
User → enters Customer ID + Phone Number
  │
  ▼
login() → reads INFO.txt line by line
  │
  ▼
Finds line at position = ID → checks if phone number exists in that line
  │
  ├── Match Found → "Welcome back, <name>!" → Customer Dashboard
  │
  └── No Match → "Invalid ID or Phone" → Retry or Home
```

### Room Booking Flow
```
Customer picks "Book a Room"
  │
  ▼
BookingService.bookRoom() called
  │
  ▼
RoomService.showAvailableRooms()     ← reads Rooms.txt
  │
  ▼
User enters room number
  │
  ▼
RoomService.isRoomAvailable(num)     ← validates room
  │
  ├── NOT available → "Sorry!" → return
  │
  └── Available →
       │
       ▼
      RoomService.getRoomByNumber(num) ← gets price
       │
       ▼
      User enters number of nights
       │
       ▼
      Calculates: total = nights × pricePerNight
       │
       ▼
      Shows summary → "Confirm? (Y/N)"
       │
       ├── N → "Cancelled" → return
       │
       └── Y →
            │
            ▼
           Appends to Bookings.txt                    ← saves booking
           RoomService.updateRoomStatus(num, false)   ← marks room booked
            │
            ▼
           "Booking Confirmed! ID: <bookingId>"
```

### Cancel Booking Flow
```
Customer picks "Cancel Booking"
  │
  ▼
BookingService.cancelBooking() called
  │
  ▼
Shows customer's bookings (reads Bookings.txt, filters by custId)
  │
  ▼
User enters Booking ID to cancel
  │
  ▼
Reads ALL lines from Bookings.txt into vector
  │
  ▼
Loops through:
  - Matching line → SKIP (delete) + note the room number
  - Other lines → KEEP
  │
  ▼
Rewrites Bookings.txt with remaining lines
  │
  ▼
RoomService.updateRoomStatus(room, true)    ← frees the room
  │
  ▼
"Booking cancelled!"
```

### Food Ordering Flow
```
Customer picks "Menu Card"
  │
  ▼
menu.Card() → displays 7 items with codes
  │
  ▼
User enters item code (1-7) → enters quantity
  │
  ▼
Calculates: cost = quantity × rate[item]
Stores in vectors: Item[], quantity[], cost[]
  │
  ▼
User enters code 8 (ORDER)
  │
  ▼
bill_display() → shows itemized bill
  │
  ▼
Saves to BILL.txt: custId, item, quantity, cost
```

### Admin Panel Flow
```
User picks "Setting" from Home
  │
  ▼
password.isPasswordSet()?
  │
  ├── NO (first time) → Set new 4-digit password → Admin Panel
  │
  └── YES → Enter password (3 attempts)
       │
       ├── Wrong 3 times → "Locked out!" → Home
       │
       └── Correct → Admin Panel
            │
            ▼
       ┌─────────────────────────────┐
       │  1. Change Password          │  → password.Set_Pass_W()
       │  2. View All Bookings        │  → reads Bookings.txt
       │  3. View All Customers       │  → reads INFO.txt
       │  4. View Total Revenue       │  → sums costs from Bookings.txt
       │  5. View All Rooms           │  → reads Rooms.txt
       │  6. Back to Home             │  → show()
       └─────────────────────────────┘
```

---

## File Storage Schema

### INFO.txt (Customer Database)
```
  #f010     yash        23   9876543210    yash@email.com        pune
  #f011      raj        30   9123456789     raj@email.com      mumbai
```
Format: `#f01<ID>  <name> <age> <phone> <email> <address>`

### Rooms.txt (Room Inventory)
```
1 Standard 1000 1
2 Standard 1000 1
3 Standard 1000 0
6 Deluxe 2000 1
9 Suite 3500 0
```
Format: `<roomNumber> <type> <pricePerNight> <isAvailable (1/0)>`

### Bookings.txt (Booking Records)
```
1 0 yash 3 Standard 2 2000
2 0 yash 9 Suite 1 3500
```
Format: `<bookingId> <custId> <custName> <roomNum> <roomType> <nights> <totalCost>`

### BILL.txt (Food Orders)
```
  #f010      Vadapav      3          60
  #f010      Tea          2          20
```
Format: `<custId> <item> <quantity> <cost>`

---

## How to Run

### Prerequisites
- **g++ compiler** (MinGW on Windows)
- **Terminal / Command Prompt**

### Compile & Run
```bash
cd "path/to/Genesis"
g++ -o Genesis main.cpp
./Genesis.exe
```

### Fresh Start (Clear Old Data)
```bash
del INFO.txt Rooms.txt Bookings.txt BILL.txt 2>nul
g++ -o Genesis main.cpp
./Genesis.exe
```

> **Note:** `Rooms.txt` is auto-created with 10 default rooms on first run. Other `.txt` files are created as data is added.

---

## Screenshots / Flow

### Home Screen
```
========================================================================
                               Welcome to Hotel Taj
                                  A) About
                                  B) Register
                                  C) Login
                                  D) Help
                                  E) Setting
                                  F) Exit
                            (Enter character to move on)
========================================================================
```

### Customer Dashboard
```
========================================================================
                    Choose correct option for What do Want?
                              Press 1) Menu Card
                              Press 2) Booking
                              Press 3) BACK TO HOME
========================================================================
```

### Booking Menu
```
========================================================================
                              ROOM BOOKING
                         1) View Available Rooms
                         2) Book a Room
                         3) View My Bookings
                         4) Cancel Booking
                         5) Back
========================================================================
```

### Admin Panel
```
========================================================================
                              ADMIN PANEL
                         1) Change Password
                         2) View All Bookings
                         3) View All Customers
                         4) View Total Revenue
                         5) View All Rooms
                         6) Back to Home
========================================================================
```

---

## Design Decisions

| Decision | Why |
|----------|-----|
| **3-Layer Architecture** | Separates UI, logic, and data — easy to understand and modify |
| **File-based Storage** | Simple alternative to databases, easy to debug by opening .txt files |
| **Each entity has its own file** | Mimics how real systems separate data (like microservices owning their DB) |
| **Service classes** | Business logic in one place, UI doesn't need to know about file formats |
| **Model classes** | Clean data structures so services work with objects, not raw strings |
| **Separate RoomService & BookingService** | Single Responsibility — each service manages its own data |
| **BookingService uses RoomService** | Delegation pattern — booking delegates room operations instead of duplicating logic |
| **Password class** | Authentication is separated from admin logic |

---

## Future Improvements

If this project were to be scaled further:

1. **Replace file storage with a database** (MySQL/SQLite) — for concurrent access and better queries
2. **Add proper user authentication** — hashed passwords instead of plain text
3. **REST API layer** — so a web/mobile frontend can connect
4. **Separate into microservices** — BookingService and RoomService as independent services
5. **Add message queue** — for booking confirmations and notifications
6. **Add caching** — for frequently accessed room availability data
7. **Add logging** — track all operations for debugging and auditing
8. **Input validation** — handle edge cases like negative numbers, special characters

---

## Tech Stack

- **Language:** C++
- **Storage:** File-based (`.txt` files)
- **Architecture:** 3-Layer (UI → Service → Model)
- **Build:** g++ (single compilation unit via `#include`)

---

*Built as a System Design learning project demonstrating layered architecture, separation of concerns, and file-based persistence in C++.*
