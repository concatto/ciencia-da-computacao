#include <iostream>
#include <vector>
#include "finiteautomaton.h"

int main(int argc, char *argv[])
{
    FiniteAutomaton<char> automaton;
    automaton.addTransition(0, {1, 4}, 'a');
    automaton.addTransition(1, 2, 'n');
    automaton.addTransition(2, 3, 'd');
    automaton.addTransition(4, 5, 'n');
    automaton.addTransition(5, 6, 'y');
    automaton.setFinalStates({3, 6});

//    for (const std::vector<char>& word : automaton.capture("asdfgabcabcdeaababc")) {
//        std::string s(word.begin(), word.end());
//        std::cout << s << "\n";
//    }

    std::cout << automaton.recognize(std::string("any")) << "\n";

    return 0;
}
