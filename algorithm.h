#include <iostream>
#include <vector>
using namespace std;

/* #region Constants */
const int MAX_NUMBER_OF_FROGS = 100;
const int MAX_ALL_PLACES = 2 * MAX_NUMBER_OF_FROGS + 1;
const int CHILDREN_FROM_INNER_ES = 4;                          // ES <=> EMPTY SPACE
const int CHILDREN_FROM_OUTER_ES = CHILDREN_FROM_INNER_ES / 2; // ES <=> EMPTY SPACE
/* #endregion */

/* #region Variables */
int number_of_frogs;
/* #endregion */

/* #region State (with all functions) */
struct State
{
    char configuration[MAX_ALL_PLACES];
    void make_start()
    {
        for (int i = 0; i < number_of_frogs; i++)
        {
            configuration[i] = 'L';
        }
        configuration[number_of_frogs] = '-';
        for (int i = number_of_frogs + 1; i < 2 * number_of_frogs + 1; i++)
        {
            configuration[i] = 'R';
        }
    }
    vector<State> generate_children() const
    {
        int iterations = 0;
        if (empty_space_outer())
        {
            iterations = CHILDREN_FROM_OUTER_ES;
            for (int i = 0; i < iterations; i++)
            {
            }
        }
        else
        {
            iterations = CHILDREN_FROM_INNER_ES;
        }

        return {};
    }
    bool is_goal() const
    {
        for (int i = 0; i < number_of_frogs / 2; i++)
        {
            if (configuration[i] != 'R')
            {
                return false;
            }
        }
        if (configuration[number_of_frogs / 2] != '_')
        {
            return false;
        }
        for (int i = (number_of_frogs / 2) + 1; i < number_of_frogs; i++)
        {
            if (configuration[i] != 'L')
            {
                return false;
            }
        }
        return true;
    }
    void print_state() const
    {
        for (int i = 0; i < 2 * number_of_frogs + 1; i++)
        {
            cout << configuration[i];
        }
        cout << endl
             << endl;
    }
    bool empty_space_outer() const
    {
        return (configuration[0] == '-' || configuration[2 * number_of_frogs] == '-');
    }
    bool empty_space_inner() const
    {
        return !empty_space_outer();
    }
    void right_frog_single_jump(int frog_index)
    {
        if (frog_index != 0 && configuration[frog_index - 1] == '-')
        {
            configuration[frog_index - 1] = configuration[frog_index];
            configuration[frog_index] = '-';
        }
        else
        {
            cout << "Error in empty spaces!" << endl
                 << endl;
        }
    }
    void left_frog_single_jump(int frog_index)
    {
        if (frog_index != (2 * number_of_frogs) && configuration[frog_index + 1] == '-')
        {
            configuration[frog_index + 1] = configuration[frog_index];
            configuration[frog_index] = '-';
        }
        else
        {
            cout << "Error in empty spaces!" << endl
                 << endl;
        }
    }
    void right_frog_double_jump(int frog_index)
    {
        if (frog_index > 1 && configuration[frog_index - 2] == '-')
        {
            configuration[frog_index - 2] = configuration[frog_index];
            configuration[frog_index] = '-';
        }
        else
        {
            cout << "Error in empty spaces!" << endl
                 << endl;
        }
    }
    void left_frog_double_jump(int frog_index)
    {
        if (frog_index < (2 * number_of_frogs - 2) && configuration[frog_index + 2] == '-')
        {
            configuration[frog_index + 2] = configuration[frog_index];
            configuration[frog_index] = '-';
        }
        else
        {
            cout << "Error in empty spaces!" << endl
                 << endl;
        }
    }
};

/* #endregion */

/* #region Read */
void read()
{
    cout << "Enter number of frogs (should be a number less than or equal to " << MAX_NUMBER_OF_FROGS << "): " << endl
         << endl;
    cin >> number_of_frogs;
    while (number_of_frogs < 2 || number_of_frogs > MAX_NUMBER_OF_FROGS)
    {
        cout << "Enter valid number of forgs: " << endl
             << endl;
        cin >> number_of_frogs;
    }
}
/* #endregion */

/* #region Isolated Tests */
void isolated_tests()
{
    State initial_state;
    initial_state.make_start();
    cout << "Is goal state? " << boolalpha << initial_state.is_goal() << endl
         << endl;
    initial_state.print_state();
    cout << "Is empty space inner? " << boolalpha << initial_state.empty_space_inner() << endl
         << endl;
    // initial_state.right_frog_single_jump(4);
    // initial_state.print_state();
    // initial_state.left_frog_single_jump(2);
    // initial_state.print_state();
    // initial_state.right_frog_double_jump(5);
    // initial_state.print_state();
    initial_state.left_frog_double_jump(1);
    initial_state.print_state();
}

/* #endregion */

/* #region Play */
void play() {
    isolated_tests();
}
/* #endregion */