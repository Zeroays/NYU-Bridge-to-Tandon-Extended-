#include <iostream>
using namespace std;

void printTriangle(int n);
void printOppositeTriangles(int n);
void printRuler(int n);

int main() {
    int triangleHeight;

    cout << "Enter a value to print triangle: ";
    cin >> triangleHeight;

    // printTriangle(triangleHeight);
    // printOppositeTriangles(triangleHeight);
    printRuler(triangleHeight);

    return 0;
}

void printTriangle(int n) {
    if (n <= 0) 
        return ;
    printTriangle(n - 1);
    for (int i = 0; i < n; i++) {
        cout << "*";   
    }
    cout << endl;
}

void printOppositeTriangles(int n) {
    if (n <= 0) 
        return ;
    for (int i = 0; i < n; i++) {
        cout << "*";   
    }
    cout << endl;
    printOppositeTriangles(n - 1);
    for (int i = 0; i < n; i++) {
        cout << "*";   
    }
    cout << endl;
}

void printRuler(int n) {
    if (n <= 0) 
        return ;

    printRuler(n - 1);
    for (int i = 0; i < n; i++) {
        cout << "-";   
    }
    cout << endl;  
    printRuler(n - 1);
}