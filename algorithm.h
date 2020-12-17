#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
using namespace std;

/* #region Constants */
const int MAX_NUMBER_OF_FROGS = 100;
const int MAX_ALL_PLACES = 2 * MAX_NUMBER_OF_FROGS + 1;
const int CHILDREN_FROM_INNER_ES = 4;                          // ES <=> EMPTY SPACE
const int CHILDREN_FROM_OUTER_ES = CHILDREN_FROM_INNER_ES / 2; // ES <=> EMPTY SPACE
const int FOUND = 1;
const int MAX_PRINTING_SIZE = 14;
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
        for (int i = 0; i < number_of_frogs; i++)
        {
            if (configuration[i] != 'R')
            {
                return false;
            }
        }
        if (configuration[number_of_frogs] != '-')
        {
            return false;
        }
        for (int i = (number_of_frogs + 1); i < 2 * number_of_frogs + 1; i++)
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
        // else
        // {
        //     cout << "Error in empty spaces!" << endl
        //          << endl;
        // }
    }
    void left_frog_single_jump(int frog_index)
    {
        if (frog_index != (2 * number_of_frogs) && configuration[frog_index + 1] == '-')
        {
            configuration[frog_index + 1] = configuration[frog_index];
            configuration[frog_index] = '-';
        }
        // else
        // {
        //     cout << "Error in empty spaces!" << endl
        //          << endl;
        // }
    }
    void right_frog_double_jump(int frog_index)
    {
        if (frog_index > 1 && configuration[frog_index - 2] == '-')
        {
            configuration[frog_index - 2] = configuration[frog_index];
            configuration[frog_index] = '-';
        }
        // else
        // {
        //     cout << "Error in empty spaces!" << endl
        //          << endl;
        // }
    }
    void left_frog_double_jump(int frog_index)
    {
        if (frog_index < (2 * number_of_frogs - 2) && configuration[frog_index + 2] == '-')
        {
            configuration[frog_index + 2] = configuration[frog_index];
            configuration[frog_index] = '-';
        }
        // else
        // {
        //     cout << "Error in empty spaces!" << endl
        //          << endl;
        // }
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
    string code() const
    {
        string result;
        for (int i = 0; i < (2 * number_of_frogs + 1); i++)
        {
            result.push_back(configuration[i]);
        }
        return result;
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
    for (int i = 0; i < children.size(); i++)
    {
        children[i].print_state();
    }
    string encoded_configuration = initial_state.code();
    cout << "Encoded initial state: " << encoded_configuration << endl
         << endl;
    initial_state.configuration[0] = 'R';
    initial_state.configuration[1] = 'R';
    initial_state.configuration[2] = 'R';
    initial_state.configuration[3] = 'R';
    initial_state.configuration[4] = 'R';
    initial_state.configuration[5] = '-';
    initial_state.configuration[6] = 'L';
    initial_state.configuration[7] = 'L';
    initial_state.configuration[8] = 'L';
    initial_state.configuration[9] = 'L';
    initial_state.configuration[10] = 'L';
    initial_state.print_state();
    cout << "IS A GOAL STATE: " << boolalpha << initial_state.is_goal() << endl
         << endl;
}
/* #endregion */

/* #region dfs */
int dfs(const State &state, vector<string> &steps, unordered_set<string> &visited_codes)
{
    visited_codes.insert(state.code());
    if (state.is_goal())
    {
        cout << "GOAL" << endl
             << endl;
        return FOUND;
    }
    vector<State> children = state.generate_children();
    int temp = 0;
    if (children.size() != 0)
    {
        for (int i = 0; i < children.size(); i++)
        {
            if (!visited_codes.count(children[i].code()))
            {
                string encoded_child = children[i].code();
                steps.push_back(encoded_child);
                temp = dfs(children[i], steps, visited_codes);
                if (temp == FOUND)
                {
                    return FOUND;
                }
                steps.pop_back();
            }
        }
    }
    return temp;
}
/* #endregion */

/* #region Print */
void print_steps(const vector<string> &steps)
{
    for (int i = 0; i < steps.size(); i++)
    {
        cout << steps[i] << endl;
    }
    cout << endl;
}
/* #endregion */

/* #region Play */
vector<string> play()
{
    // isolated_tests();
    read();
    State initial_state;
    vector<string> steps;
    unordered_set<string> visited_codes;
    initial_state.make_start();
    int result_from_dfs = dfs(initial_state, steps, visited_codes);
    if (result_from_dfs == FOUND)
    {
        cout << "RESULT FROM dfs: "
             << "FOUND" << endl
             << endl;
    }
    else
    {
        cout << "RESULT FROM dfs: " << result_from_dfs << endl
             << endl;
    }
    if (result_from_dfs == FOUND)
    {
        steps.insert(steps.begin(), initial_state.code());
        cout << "STEPS TO SOLUTION AS FOLLOWING: " << endl
             << endl;
        cout << "NUMBER OF STEPS (including the initial state and final state): " << steps.size() << endl
             << endl;
        if (number_of_frogs <= MAX_PRINTING_SIZE)
        {
            print_steps(steps);
        }
        else
        {
            cout << "WE PRINT THE STEPS ONLY IF NUMBER OF FROGS (SINGLE SIDE) IS LESS THAN OR EQUAL TO " << MAX_PRINTING_SIZE << endl
                 << endl;
        }
        return steps;
    }
    cout << endl
         << endl;
    cout << "UNREACHED SOLUTION" << endl
         << endl;
    return {"UNREACHED SOLUTION"};
}
/* #endregion */