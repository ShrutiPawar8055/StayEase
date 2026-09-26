// Password class - handles admin authentication
// Keeps it simple with a 4-digit password

#include <iostream>
using namespace std;

class password {

private:
  int a = 0; // stored password (0 means not set yet)

public:
  // set a new password
  void Set_Pass_W(void) {
    int b;
    int p;
    cout << "    Set password (4 digit)    : ";
    cin >> p;
  label:
    cout << "    Verify password (4 digit) : ";
    cin >> b;
    if (p == b) {
      a = p;
      cout << "    Password created successfully!" << endl;
    } else {
      cout << endl;
      cout << "        Passwords don't match! Try again." << endl;
      cout << endl;
      goto label;
    }
  }

  // check password - returns true if correct, false if wrong
  bool Pass_W(void) {
    int b;
    cout << "    Enter password (4 digit) : ";
    cin >> b;
    if (a == b) {
      return true;
    } else {
      cout << endl;
      cout << "        Wrong password!" << endl;
      cout << endl;
      return false;
    }
  }

  // check if password has been set
  bool isPasswordSet() {
    return a != 0;
  }
};