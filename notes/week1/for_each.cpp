// for_each.cpp

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> nums = {5, 6, 3, -2, 0, 5};
    // for-each
    for (int n : nums)
    {
        cout << n << "\n";
    }
}

// do {
//     cout << n << "\n";
// } while (n < 10);
