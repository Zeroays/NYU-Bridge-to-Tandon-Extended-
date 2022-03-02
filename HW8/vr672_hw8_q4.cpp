#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void printSequence(string msg, int arr[], int arrSize);
void printArray(int arr[], int arrSize);
void generateRandomArray(int maxNum, int arr[], int arrSize);
bool match(string userInput, const string PIN, int randomSequence[], int arrSize);

int main() {
    const string PIN = "12345";
    const int MAX_RANDOM_NUM = 3;
    const int SIZE = 10;

    int pinSequence[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int randomSequence[SIZE];
    srand(time(0));

    string userInput;

    cout << "Please enter your PIN according to the following mapping: " << endl;
    printSequence("PIN: ", pinSequence, SIZE);
    generateRandomArray(MAX_RANDOM_NUM, randomSequence, SIZE);
    printSequence("NUM: ", randomSequence, SIZE);

    cin >> userInput;

    if (match(userInput, PIN, randomSequence, SIZE)) {
        cout << "Your PIN is correct" << endl;
    } else {
        cout << "Your PIN is incorrect" << endl;
    }

    return 0;
}

void printSequence(string msg, int arr[], int arrSize) {
    cout << msg;

    printArray(arr, arrSize);
    cout << endl;
}

void printArray(int arr[], int arrSize) {
    for (int i = 0; i < arrSize; i++) {
        cout << arr[i] << " ";
    }
}

void generateRandomArray(int maxNum, int arr[], int arrSize) {
    for (int i = 0; i < arrSize; i++) {
        arr[i] = (rand() % maxNum) + 1;
    }
}

bool match(string userInput, const string PIN, int randomSequence[], int arrSize) {
    bool isMatch = true;

    for (int i = 0; i < PIN.length(); i++) {
        //Converts digit in PIN into a numerical index
        int pinDigit = PIN[i] - '0';
        //Converts mapped number to a character
        int mappedDigit = (char)(randomSequence[pinDigit] + '0');

        if (userInput[i] != mappedDigit) {
            isMatch = false;
        }
    }
    return isMatch;
}