#include <iostream>
using namespace std;

int sumOfSquares(int arr[], int arrSize);
bool isSorted(int arr[], int arrSize);

int main() {
    const int ARR_SIZE = 4;
    int arr[ARR_SIZE] = {2, -1, 3, 10};

    const int ARR_SIZE_2 = 5;
    int arr2[ARR_SIZE_2] = {4, 2, 3, 4, 8};

    cout << sumOfSquares(arr, ARR_SIZE) << endl;
    cout << isSorted(arr2, ARR_SIZE_2) << endl;

    return 0;
}

int sumOfSquares(int arr[], int arrSize) {
    if (arrSize <= 0)
        return 0;
    return arr[arrSize - 1] * arr[arrSize - 1] + sumOfSquares(arr, arrSize - 1);
}

bool isSorted(int arr[], int arrSize) {
    if (arrSize <= 1)
        return true;
    return (arr[arrSize - 1] > arr[arrSize - 2]) && isSorted(arr, arrSize - 1);
}