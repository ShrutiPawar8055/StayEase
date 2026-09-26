#include <bits/stdc++.h>
#include <fstream>
#include <iomanip>
using namespace std;
class menu {
private:
  int rate[7] = {20, 40, 50, 30, 25, 10, 20};
  vector<string> Item;
  vector<int> cost;
  vector<int> quantity;
  int count = 0;
  int C;       // menu number
  int sum = 0; // total bill
  int a;       // quantity
  int Cust_id;

public:
  void Card(int id) {
    Cust_id = id;
    cout << endl;
    cout << "=================================================================="
            "============"
         << endl;
    cout << "                              Welcome to Hotel AESTHETIC                "
            "            "
         << endl;
    cout << "                            Item       Code     Value             "
            "            "
         << endl;
    cout << "                         # Vadapav     (1)    20.00 Rs            "
            "            "
         << endl;
    cout << "                         # MisalPav    (2)    40.00 Rs            "
            "            "
         << endl;
    cout << "                         # Vadasamber  (3)    50.00 Rs            "
            "            "
         << endl;
    cout << "                         # kanda bhji  (4)    30.00 Rs            "
            "            "
         << endl;
    cout << "                         # Mirchi bhji (5)    25.00 Rs            "
            "            "
         << endl;
    cout << "                         # Tea         (6)    10.00 Rs            "
            "            "
         << endl;
    cout << "                         # Coffee      (7)    20.00 Rs            "
            "            "
         << endl;
    cout << "                         # ORDER       (8)    ########            "
            "            "
         << endl;
    cout << "    (Enter respective code number to chosse menu and then press "
            "ORDER code)   "
         << endl;
    cout << "=================================================================="
            "============"
         << endl;
    cout << endl;
    inti();
  }
  void bill(void) {
    cout << "Enter Quantity   :";
    cin >> a;
    cout << endl;
    int sum1 = a * rate[C - 1];
    sum = sum + sum1;
    quantity.push_back(a);
    cost.push_back(sum1);
    string s;
    if (C == 1) {
      s = "Vadapav    ";
    } else if (C == 2) {
      s = "MisalPav   ";
    } else if (C == 3) {
      s = "Vadasamber ";
    } else if (C == 4) {
      s = "kanda bhji ";
    } else if (C == 5) {
      s = "Mirchi bhji";
    } else if (C == 6) {
      s = "Tea        ";
    } else if (C == 7) {
      s = "Coffee     ";
    }
    Item.push_back(s);
    inti();
  }
  void bill_display(void) {
    cout << "=================================================================="
            "============"
         << endl;
    cout << "                                    Hotel AESTHETIC Bill                         "
            "            "
         << endl;
    cout << "                         ---------------------------------        "
            "            "
         << endl;
    cout << "                         Item          quantity  cost(Rs.)        "
            "            "
         << endl;
    cout << "                         ---------------------------------        "
            "            "
         << endl;
    ofstream write;
    write.open("BILL.txt", ios_base::app);
    for (int i = 0; i < count; i++) {
      cout << "                         " << Item[i] << "        "
           << quantity[i] << "     " << cost[i] << endl;
      write << setw(10) << "#f01" << Cust_id << "      " << setw(11) << Item[i]
            << "    " << setw(2) << quantity[i] << "        " << setw(5)
            << cost[i] << endl;
    }
    write.close();
    cout << "                         ---------------------------------        "
            "            "
         << endl;
    cout << "                         TOTAL BILL               :" << sum
         << " Rs." << endl;
    cout << "                         THANK YOU FOR VISITING........!          "
            "             "
         << endl;
    cout << "=================================================================="
            "============"
         << endl;
    cout << endl;
  }

  void inti(void) {
    cout << "Enter number for placing order:     :";
    cin >> C;
    if (C >= 1 && C < 8) {
      count++;
      bill();
    } else if (C == 8) {
      bill_display();
    } else {
      cout << endl;
      cout << "----------------------------------------------------------------"
              "--------------"
           << endl;
      cout << "                     WARNING :: USER NOT FOUND                  "
              "              "
           << endl;
      cout << "----------------------------------------------------------------"
              "--------------"
           << endl;
      inti();
      cout << endl;
    }
  }
};