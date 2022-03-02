#include <iostream>
using namespace std;

bool isPalindrome(string str);

int main() {
    string str;

    cout << "Please enter a word: ";
    cin >> str;

    if (isPalindrome(str)) {
        cout << str << " is a palindrome" << endl;
    } else {
        cout << str << " is not a palindrome" << endl;
    }

    return 0;
}

bool isPalindrome(string str) {
    int p1 = 0, p2 = str.length() - 1;

    while (p1 != p2) {
        if (str[p1] != str[p2]) {
            return false;
        }
        p1++;
        p2--;
    }
    return true;
}