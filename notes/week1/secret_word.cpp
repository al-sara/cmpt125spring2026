// secret_word.cpp

#include <iostream>
#include <string>

using namespace std;

int main() {
    const string secret_word = "cat";
    string guess;
    cout << "Enter a guess: ";
    cin >> guess;
    if (guess == secret_word) 
    {
        cout << "You guessed the secret word!\n";
    }

    cout << "\ndone\n";
}