#ifndef FINITEAUTOMATON_H
#define FINITEAUTOMATON_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <algorithm>

using State = int;

/**
 * A class that simulates a Nondeterministic Finite State Automaton.
 * The automaton can be in zero or many states at any time.
 * If left unspecified, the initial state is assumed to be {0}.
 * Does not accept epsilon-moves.
 */
template <class Input>
class FiniteAutomaton
{        
public:
    using StateSet = std::unordered_set<State>;
    using TransitionTable = std::unordered_map<State, std::unordered_map<Input, StateSet>>;

    FiniteAutomaton() {

    }

    void addTransition(State current, State next, const Input& input) {
        addTransition(current, StateSet{next}, input);
    }

    template <class Container>
    void addTransition(State current, State next, const Container& inputs) {
        for (const Input& input : inputs) {
            addTransition(current, next, input);
        }
    }

    void addTransition(State current, const StateSet& nextStates, const Input& input) {
        table[current][input] = nextStates;
    }

    template <class Container>
    void addTransition(State current, const StateSet& nextStates, const Container& inputs) {
        for (const Input& input : inputs) {
            addTransition(current, nextStates, input);
        }
    }

    void rewind() {
        currentStates = {initialState};
    }

    void setFinalStates(const StateSet& finalStates) {
        this->finalStates = finalStates;
    }

    bool advance(const Input& input) {
        StateSet nextStates;

        for (State s : currentStates) {
            if (transitionExists(s, input)) {
                const StateSet& states = table[s][input];
                nextStates.insert(states.begin(), states.end());
            }
        }

        currentStates = nextStates;
        return !nextStates.empty();
    }

    bool transitionExists(State state, const Input& input) const {
        typename TransitionTable::const_iterator it = table.find(state);
        if (it != table.end()) {
            return it->second.find(input) != it->second.end();
        }

        return false;
    }

    bool isAccepting() const {
        return std::any_of(currentStates.begin(), currentStates.end(), [&](State s) {
            return isAccepting(s);
        });
    }

    bool isAccepting(State state) const {
        return finalStates.find(state) != finalStates.end();
    }

    void setInitialState(State initialState) {
        this->initialState = initialState;
    }

    template <class InputIterator>
    bool recognize(InputIterator first, InputIterator last) {
        rewind();

        for (; first != last; ++first) {
            const Input& symbol = *first;

            if (!advance(symbol)) {
                return false;
            }
        }
        return isAccepting();
    }

    template <class InputIterator>
    std::vector<std::vector<Input>> capture(InputIterator first, InputIterator last) {
        std::vector<std::vector<Input>> captured;
        std::vector<Input> current;

        rewind();

        for (; first != last; ++first) {
            const Input& symbol = *first;

            if (!advance(symbol)) {
                if (!current.empty()) {
                    if (isAccepting()) {
                        captured.push_back(current);
                    }

                    current.clear();
                    //Try the symbol again.
                    --first;
                }

                rewind();
            } else {
                current.push_back(symbol);
            }
        }

        return captured;
    }

    template <class Container>
    bool recognize(const Container& container) {
        return recognize(std::begin(container), std::end(container));
    }

    template <class Container>
    std::vector<std::vector<Input>> capture(const Container& container) {
        return capture(std::begin(container), std::end(container));
    }

    StateSet getCurrentState() const {
        return currentStates;
    }

private:
    TransitionTable table;
    State initialState = 0;
    StateSet currentStates;
    std::unordered_set<State> finalStates;
};



#endif // FINITEAUTOMATON_H
