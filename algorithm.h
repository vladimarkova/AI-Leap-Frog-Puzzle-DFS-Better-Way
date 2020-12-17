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
    int get_empty_space_index() const
    {
        for (int i = 0; i < (2 * number_of_frogs + 1); i++)
        {
            if (configuration[i] == '-')
            {
                return i;
            }
        }
        return 0;
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
    vector<State> generate_children() const
    {
        vector<State> children_generated;
        int rightmost_index = 2 * number_of_frogs;
        if (empty_space_outer()) // leftmost space = '-' or rightmost space = '-'
        {
            if (configuration[0] == '-')
            {
                if (configuration[1] == 'R')
                {
                    State child1 = *this;
                    child1.right_frog_single_jump(1);
                    children_generated.push_back(child1);
                }
                if (configuration[2] == 'R')
                {
                    State child2 = *this;
                    child2.right_frog_double_jump(2);
                    children_generated.push_back(child2);
                }
            }
            if (configuration[rightmost_index] == '-')
            {
                if (configuration[rightmost_index - 1] == 'L')
                {
                    State child1 = *this;
                    child1.left_frog_single_jump(rightmost_index - 1);
                    children_generated.push_back(child1);
                }
                if (configuration[rightmost_index - 2] == 'L')
                {
                    State child2 = *this;
                    child2.left_frog_double_jump(rightmost_index - 2);
                    children_generated.push_back(child2);
                }
            }
        }
        else // empty space = '-' is inner
        {
            int empty_space_index = get_empty_space_index();
            if (configuration[empty_space_index - 1] == 'L')
            {
                State child1 = *this;
                child1.left_frog_single_jump(empty_space_index - 1);
                children_generated.push_back(child1);
            }
            if (configuration[empty_space_index - 2] == 'L')
            {
                State child2 = *this;
                child2.left_frog_double_jump(empty_space_index - 2);
                children_generated.push_back(child2);
            }
            if (configuration[empty_space_index + 1] == 'R')
            {
                State child3 = *this;
                child3.right_frog_single_jump(empty_space_index + 1);
                children_generated.push_back(child3);
            }
            if (configuration[empty_space_index + 2] == 'R')
            {
                State child4 = *this;
                child4.right_frog_double_jump(empty_space_index + 2);
                children_generated.push_back(child4);
            }
        }
        return children_generated;
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
    /* #region Jumps */
    // initial_state.right_frog_single_jump(4);
    // initial_state.print_state();
    // initial_state.left_frog_single_jump(2);
    // initial_state.print_state();
    // initial_state.right_frog_double_jump(5);
    // initial_state.print_state();
    // initial_state.left_frog_double_jump(1);
    // initial_state.print_state();
    /* #endregion */
    vector<State> children = initial_state.generate_children();
    for (int i = 0; i < children.size(); i++) {
        children[i].print_state();
    }
    /* #region Generate children */
    cout << "First child children: " << endl << endl;
    vector<State> children_of_first_child = children[0].generate_children();
    for (int i = 0; i < children_of_first_child.size(); i++) {
        children_of_first_child[i].print_state();
    }
    vector<State> children_third_generation = children_of_first_child[1].generate_children();
    cout << "Third generation: " << endl << endl;
    for (int i = 0; i < children_third_generation.size(); i++) {
        children_third_generation[i].print_state();
    }
    /* #endregion */
}

/* #endregion */

/* #region Play */
void play()
{
    isolated_tests();
}
/* #endregion */