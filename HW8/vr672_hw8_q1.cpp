#include <iostream>
using namespace std;

int minInArray(int arr[], int arrSize);

int main() {
    const int SIZE = 20;
    int min;
    int arr[SIZE];

    cout << "Please enter 20 integers separated by a space: " << endl;
    for (int i = 0; i < SIZE; i++) {
        cin >> arr[i];
    }
    min = minInArray(arr, SIZE);

    cout << "The minimum value is " << min << ", and it is located in the following indices: ";
    for (int i = 0; i < SIZE; i++) {
        if (arr[i] == min) {
            cout << i << " ";
        }
    }
    cout << endl;

    return 0;
}

int minInArray(int arr[], int arrSize) {
    int min = arr[0];
    for (int i = 0; i < arrSize; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}
