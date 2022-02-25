#include <iostream>
using namespace std;

int printMonthCalendar(int numOfDays, int startingDay);
bool isLeapYear(int year);
void printYearCalendar(int year, int startingDay);

int main() {
    int year, startingDay;

    cout << "Please enter the year: ";
    cin >> year;

    cout << "Please enter the starting day: ";
    cin >> startingDay;

    printYearCalendar(year, startingDay);

    return 0;
}

int printMonthCalendar(int numOfDays, int startingDay) {
    const int DAYS_IN_A_WEEK = 7;
    const string daysOfTheWeek = "Mon\tTue\tWed\tThr\tFri\tSat\tSun";

    int upperBound, lowerBound;

    int emptySpaces = 0;
    for (; emptySpaces < startingDay - 1; emptySpaces++) {
        cout << "\t";
    }
    int remaining = 0;
    for (; remaining <= DAYS_IN_A_WEEK - startingDay; remaining++) {
        cout << remaining + 1 << "\t";
    }

    cout << endl;


    lowerBound = remaining + 1;
    remaining++;
    upperBound = lowerBound + DAYS_IN_A_WEEK;

    for (; remaining <= numOfDays; remaining++) {
        if (lowerBound <= remaining && upperBound > remaining) {
            cout << remaining << "\t";
        } else {
            cout << endl;
            cout << remaining << "\t";
            lowerBound = upperBound;
            upperBound = lowerBound + DAYS_IN_A_WEEK;
        }
    }
    return numOfDays - lowerBound + 1;

}

bool isLeapYear(int year) {
    if (year % 4 == 0) {
        if (year % 100 != 0) {
            return true;
        } else {
            if (year % 400 == 0) {
                return true;
            }
            return false;
        }
    }
    return false;
}

void printYearCalendar(int year, int startingDay) {
    const int DAYS_IN_A_WEEK = 7;
    const int MONTHS_IN_A_YEAR = 12;

    const int FEBRUARY = 2;
    const int APRIL = 4;
    const int JUNE = 6;
    const int SEPTEMBER = 9;
    const int NOVEMBER = 11;

    for (int month = 1; month <= MONTHS_IN_A_YEAR; month++) {
        int endingDay;
        int daysInAMonth;

        switch (month) {
            case 1: cout << "January"; break;
            case 2: cout << "February"; break;
            case 3: cout << "March"; break;
            case 4: cout << "April"; break;
            case 5: cout << "May"; break;
            case 6: cout << "June"; break;
            case 7: cout << "July"; break;
            case 8: cout << "August"; break;
            case 9: cout << "September"; break;
            case 10: cout << "October"; break;
            case 11: cout << "November"; break;
            case 12: cout << "December"; break;
        }
        cout << " " << year << endl;

        if (month == APRIL || month == JUNE || month == SEPTEMBER || month == NOVEMBER) {
            daysInAMonth = 30;
        } else if (month == FEBRUARY) {
            if (isLeapYear(year)) {
                daysInAMonth = 29;
            } else {
                daysInAMonth = 28;
            }  
        } else {
            daysInAMonth = 31;
        }

        endingDay = printMonthCalendar(daysInAMonth, startingDay);
        startingDay = endingDay + 1;
        if (startingDay > DAYS_IN_A_WEEK) {
            startingDay = 1;
        }
        
        cout << endl << endl;
    }
    

}