// hello_name_cin.cpp

//
// This reads in the users name using cin, which only reads in the first word.
//

#include <iostream>
#include <string>

using namespace std;

int main()
{
    cout << "What's your name? ";
    string name; // defines the variable name
    cin >> name;
    cout << "Hello, " << name << "\n";
}
