#include <iostream>
#include <cstdlib>
#include <memory>
#include <algorithm>
#include <vector>
#include <time.h> 


/*
Poniższy przykład maszyny Turinga zwiększa liczbę binarną o 1
*/
using namespace std;

enum Direction
{
    left = -1,
    right = 1
};

struct Rule {
    public:
        char inputSign;
        int inputState;
        char outputSign;
        int outputState;
        Direction dir;

};

void fullfillTape(vector<char> &tape, vector<char> dictionary, int numberOfSigns, char emptySign)
{
    srand (time(NULL));
    tape.push_back(emptySign);
    for(int i = 0; i < numberOfSigns; i++)
    {
        tape.push_back(dictionary[rand() % dictionary.size()]);
    }
    tape.push_back(emptySign);
}

void printTape(vector<char> tape)
{
    for(int i = 0; i < tape.size(); i++)
    {
        cout << tape[i];
    }
}

bool findRule(vector<Rule> rules, Rule &currentRule)
{
    bool ret = false;
    for(int i = 0; i < rules.size(); i++)
    {
        if(rules[i].inputSign == currentRule.inputSign && rules[i].inputState == currentRule.inputState)
        {
            currentRule.outputSign = rules[i].outputSign;
            currentRule.outputState = rules[i].outputState;
            currentRule.dir = rules[i].dir;
            ret = true;
        }
    }
    return ret;
}

void Process(vector<Rule> rules, vector<char> &tape, int beginningState)
{
    
    int iter = tape.size() - 2;
    Rule currentRule{tape[iter], beginningState, ' ', 0, Direction::left};
    while(findRule(rules, currentRule ))
    {
 
        tape[iter] = currentRule.outputSign;
        currentRule.inputState = currentRule.outputState;
        iter += currentRule.dir;
        currentRule.inputSign = tape[iter]; 
    }
    //return tape;
}

int main()
{
    vector<char> dictionary{'0','1'};
    vector<int> state{0, 1, 2};
    vector<char> tape;

    fullfillTape(tape, dictionary, 8, '?');

    vector<Rule> rules = {{dictionary[0], state[0], dictionary[1], state[2], Direction::left},
                         {dictionary[1], state[0], dictionary[0], state[1], Direction::left},
                         {dictionary[0], state[1], dictionary[1], state[2], Direction::left},
                         {dictionary[1], state[1], dictionary[0], state[1], Direction::left},
                         {'?', state[1], dictionary[1], state[2], Direction::left}};
                     
    cout<< "Losowa liczba binarna:"<<endl;
    printTape(tape);
    cout<< endl;
    Process(rules, tape, 0);
    cout<< endl;
    cout<< "Liczba binarna zwiekszona o 1:"<<endl;
    printTape(tape);
    return 0;
}

