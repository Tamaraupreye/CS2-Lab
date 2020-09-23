#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void wait() {
    string c;
    cout << "Press <Return> to continue... ";
    cin.ignore();
    getline(cin, c);
}

int main() {

}
