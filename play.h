#include <iostream>
#include <ratio>
#include <chrono>
#include "algorithm.h"
using namespace std;

void game_test() {
    char response = '1';
    while (response != '0') {
        read();

        using namespace std::chrono;
        high_resolution_clock::time_point t1 = high_resolution_clock::now();  

        play();

        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double, std::milli> time_span = t2 - t1; 
        cout << "Time in miliseconds for execution was: " << time_span.count() << " milliseconds." << endl;    

        // print();

        cout << "Enter 1 to start a new game or 0 to stop: " << endl << endl; 

        cin >> response;

        if (response == '0') {
            cout << "GAME FINFISHED!" << endl << endl;
        } 
        else {
            cout << "NEW GAME STARTED!" << endl << endl;
        }
    }
}