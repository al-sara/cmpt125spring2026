// separator_check.cpp

#include <iostream>

using namespace std;

int main()
{
    char sep;
    cout << "Enter a character: ";
    cin >> sep;
    switch(sep)
    {
    case ',':
        cout << "definitely a separator";
        break;
    case '-': // minus sign
    case '_': // underscore
        cout << "maybe a separator";
        break;
    default:
        cout << "not a separator";
    }
}
