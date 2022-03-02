#include <iostream>
using namespace std;

int main() {
    string firstName, middleName, lastName;

    cout << "Please enter a name (first, middle, last): ";
    cin >> firstName >> middleName >> lastName;
   
    cout << lastName << ", " << firstName << " " << middleName[0] << "." << endl;
    return 0;
}