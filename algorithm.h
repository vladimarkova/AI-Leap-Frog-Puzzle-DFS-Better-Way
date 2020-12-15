#include <iostream>
using namespace std;

const int MAX_NUMBER_OF_FROGS = 100;
const int MAX_ALL_PLACES = 2 * MAX_NUMBER_OF_FROGS + 1;
const int MAX_CHILDREN = 4;

int number_of_frogs;

struct State {
    char configuration[MAX_ALL_PLACES];
    void make_start() {
        for (int i = 0; i < number_of_frogs; i++) {
            configuration[i] = 'L';
        }
        configuration[number_of_frogs] = '*';
        for (int i = number_of_frogs + 1; i < 2 * number_of_frogs + 1; i++) {
            configuration[i] = 'R';
        }
    }
    void generate_children() const {

    }
    bool is_goal() const {
        for (int i = 0; i < number_of_frogs / 2; i++) {
            if (configuration[i] != 'R') {
                return false;
            }
        }
        if (configuration[number_of_frogs / 2] != '_') {
            return false;
        }
        for (int i = (number_of_frogs / 2) + 1; i < number_of_frogs; i++) {
            if (configuration[i] != 'L') {
                return false;
            }
        }
        return true;
    }
    void print_state() const {
        for (int i = 0; i < 2 * number_of_frogs + 1; i++) {
            cout << configuration[i];
        }
        cout << endl << endl;
    }
};

State children_states[MAX_CHILDREN];

void read() {
    cout << "Enter number of frogs (should be a number less than or equal to " << MAX_NUMBER_OF_FROGS << "): " << endl << endl;
    cin >> number_of_frogs;
    while(number_of_frogs < 2 || number_of_frogs > MAX_NUMBER_OF_FROGS) {
        cout << "Enter valid number of forgs: " << endl << endl;
        cin >> number_of_frogs;
    }
}

void isolated_tests() {
    State initial_state;
    initial_state.make_start();
    cout << "Is goal state? " << boolalpha << initial_state.is_goal() << endl<< endl;
    initial_state.print_state();
}

void play() {
    isolated_tests();
}