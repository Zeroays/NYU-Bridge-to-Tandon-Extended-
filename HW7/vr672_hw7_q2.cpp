#include <iostream>
using namespace std;

void analyzeDividors(int num, int& outCountDivs, int& outSumDivs);
bool isPerfect(int num);

int main() {
    int num;
    
    cout << "Please provide a positive integer >= 2: ";
    cin >> num;

    cout << endl;
    cout << "***Perfect Numbers between 2 and " << num << "***" << endl;

    for (int i = 2; i < num; i++) {
        if (isPerfect(i)) {
            cout << i << endl;
        }
    }

    cout << endl << endl;

    cout << "***Pairs of Amicable Numbers between 2 and " << num << "***" << endl;
    for (int i = 2; i < num; i++) {
        int countDivs1, sumDivs1;
        int countDivs2, sumDivs2;

        analyzeDividors(i, countDivs1, sumDivs1);
        analyzeDividors(sumDivs1, countDivs1, sumDivs2);

        if (i == sumDivs2 && i < sumDivs1) {
            cout << i << ", " << sumDivs1 << endl;
        }
    }

    return 0;
}

void analyzeDividors(int num, int& outCountDivs, int& outSumDivs) {
    int countDivs = 0, sumDivs = 1;

    for (int i = 2; i * i < num; i++) {
        if (num % i == 0) {
            sumDivs += i;
            sumDivs += num / i;
            countDivs += 2;
        }
    }
    outCountDivs = countDivs;
    outSumDivs = sumDivs;
}

bool isPerfect(int num) {
    int countDivs, sumDivs;
    analyzeDividors(num, countDivs, sumDivs);
    return num == sumDivs;
}