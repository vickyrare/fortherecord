#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <thread>

#include "timer.h"

using namespace std;

enum STATE {
    STARTUP,
    PAUSED,
    RUNNING,
    NEW_ENTRY,
    QUIT
};

bool isFibonacci(int num)
{
    double X1 = 5 * pow(num, 2) + 4;
    double X2 = 5 * pow(num, 2) - 4;

    long X1_sqrt = (long) sqrt(X1);
    long X2_sqrt = (long) sqrt(X2);

    return (X1_sqrt * X1_sqrt == X1) || (X2_sqrt * X2_sqrt == X2);
}

STATE state = STARTUP;
std::map<int, int> dataTable;
Timer timer;
int number;

void insertDatatable(int number) {
    if (dataTable.find(number) == dataTable.end())
    {
        // new entry
        dataTable.insert(std::pair<int, int>(number, 1));
    }
    else
        {
        // update existing entry
        dataTable[number] = dataTable[number] + 1;
    }
}

void takeNumberInput(string message)
{
    cout << message.c_str() << endl;
    cin >> number;
    if (isFibonacci(number))
    {
        cout << "FIB!" << endl;
    }
}

void printDatatable()
{
    std::vector<pair<int,int>> vec;

    // copy key-value pairs from the map to the vector
    std::copy(dataTable.begin(), dataTable.end(), std::back_inserter<vector<pair<int,int>>>(vec));

    // sort the vector by decreasing order of its pair's second value (value)
    // if second value are equal, order by the pair's first value (key)
    sort(vec.begin(), vec.end(),
     [](const pair<int,int>& l, const pair<int,int>& r)
     {
         if (l.second != r.second)
         {
             return l.second > r.second;
         }

         return l.first < r.first;
     });

    bool first = true;
    for (auto const &pair: vec)
    {
        if (first)
        {
            cout << pair.first << ":" << pair.second;
            first = false;
        }
        else
        {
            cout << ", " << pair.first << ":" << pair.second;
        }
    }
    cout << endl;
}

void processInput()
{
    char input;
    while(state != QUIT)
    {
        if (state == RUNNING)
        {
            cin >> input;
        }
        switch (input)
        {
            case 'N':
                timer.pause();
                state = NEW_ENTRY;
                takeNumberInput("Please enter the new number: ");
                insertDatatable(number);
                timer.start();
                state = RUNNING;
                break;
            case 'P':
                timer.pause();
                state = PAUSED;
                cin >> input;
                switch (input) {
                    case 'N':
                    case 'Q':
                    case 'R':
                        state = RUNNING;
                        timer.start();
                        break;
                }
                break;
            case 'Q':
                state = QUIT;
                printDatatable();
                cout << "See you next time!" << endl;
                break;
            case 'R':
                state = RUNNING;
                break;
            case 'A':
                printDatatable();
                break;
        }
    }
}

int main()
{
    int period;
    cout << "Please enter the output period: ";
    cin >> period;
    takeNumberInput("Please enter the first number: ");
    insertDatatable(number);
    state = RUNNING;
    timer.start();
    thread inputThread(processInput);
    inputThread.detach();
    while(state != QUIT) {
        while (timer.elapsedSeconds() < period && state != QUIT)
        {
        }
        if (state != QUIT)
        {
            printDatatable();
        }
        timer.stop();
        timer.start();
    }
    return 0;
}
