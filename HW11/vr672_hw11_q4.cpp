#include <iostream>
using namespace std;

int min(int x, int y);
int jumpIt(int arr[], int arrSize, int start);

int main() {
    const int JUMP_BOARD_SIZE = 6;
    int jumpItBoard[JUMP_BOARD_SIZE] = {0, 3, 80, 6, 57, 10};

    const int JUMP_BOARD_SIZE_2 = 3;
    int jumpItBoard2[JUMP_BOARD_SIZE_2] = {0, 3, 80};

    const int JUMP_BOARD_SIZE_3 = 4;
    int jumpItBoard3[JUMP_BOARD_SIZE_3] = {0, 3, 80, 6};

    cout << jumpIt(jumpItBoard, JUMP_BOARD_SIZE, 0) << endl;
    cout << jumpIt(jumpItBoard2, JUMP_BOARD_SIZE_2, 0) << endl;
    cout << jumpIt(jumpItBoard3, JUMP_BOARD_SIZE_3, 0) << endl;

    return 0;
}

int min(int x, int y) {
    if (x < y) 
        return x;
    return y;
}

int jumpIt(int arr[], int arrSize, int start) {
    if (start >= arrSize - 1)
        return arr[arrSize - 1];
    return min(arr[start] + jumpIt(arr, arrSize, start + 1), arr[start] + jumpIt(arr, arrSize, start + 2));
}