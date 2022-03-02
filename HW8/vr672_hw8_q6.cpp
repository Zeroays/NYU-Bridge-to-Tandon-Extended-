#include <iostream>
using namespace std;

bool isDigit(char digit);
bool hasNonDigit(string str);
void outputNewWord(string word);

int main() {
    string sentence;
    
    cout << "Please enter a line of text: " << endl;
    getline(cin, sentence);

    int currentWordIdx = 0;
    for (int i = 0; i <= sentence.length(); i++) {
        if (sentence[i] == ' ' || i == sentence.length()) {
            string word = sentence.substr(currentWordIdx, i - currentWordIdx);
            outputNewWord(word);
            currentWordIdx = i + 1;
        }
    }

    cout << endl;

    return 0;
}

bool isDigit(char digit) {
    return digit >= '0' && digit <= '9';
}

bool hasNonDigit(string str) {
    for (int i = 0; i < str.length(); i++) {
        if (!isDigit(str[i])) {
            return true;
        }
    }
    return false;
}

void outputNewWord(string word) {
    string newWord = "";

    if (hasNonDigit(word)) {
        cout << word << " ";
        return ;
    }

    for (int i = 0; i < word.length(); i++) {
        if (isDigit(word[i])) {
            newWord += "x";
        } else {
            newWord += word[i];
        }
    }
    cout << newWord << " ";
}

