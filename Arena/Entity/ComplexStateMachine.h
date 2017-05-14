#ifndef COMPLEXSTATEMACHINE_H
#define COMPLEXSTATEMACHINE_H

#include <algorithm>
#include <functional>
#include <list>
#include <map>
#include <string>

using State = const std::string;
#define STATE(stateName) \
    State stateName##State{#stateName};

using StateList = std::list<std::remove_const<State>::type>;
static const StateList EMPTY_COMPLEX_STATE{};

using StateFunction = std::function<void()>;
static const StateFunction DO_NOTHING{[](){}};
#define METHOD_FUNCTION(methodName) \
    std::bind(&methodName, this)
//    [&](){methodName();}

class ComplexStateMachine;

class StateBuilder
{
public:
    StateBuilder(ComplexStateMachine& stateMachine, const State& state);

    StateBuilder& setStateFunction(StateFunction function);
    StateBuilder& setStateRequirements(const StateList& requirements);
    StateBuilder& setStateIncompatibilities(const StateList& incompatibilities);

private:
    ComplexStateMachine& _stateMachine;
    const State _state;
};

class ComplexStateMachine
{
public:
    using ComplexState = StateList;

    const ComplexState& complexState() const;

    void activateState(const State& state);
    void deactivateState(const State& state);

    bool isStateActive(const State& state);

    const StateFunction& stateFunction(const State& state);
    void setStateFunction(const State& state, StateFunction function);
    void callStateFunction(const State& state);
    void callComplexStateFunctions();

    const StateList& stateRequirements(const State& state);
    void setStateRequirements(const State& state, const StateList& requirements);

    const StateList& stateIncompatibilities(const State& state);
    void setStateIncompatibilities(const State& state, const StateList& incompatibilities);

    StateBuilder stateBuilder(const State& state);

private:
    ComplexState _complexState;
    std::map<State, StateFunction> _stateFunctions;
    std::map<State, std::list<std::remove_const<State>::type>> _stateRequirements;
    std::map<State, std::list<std::remove_const<State>::type>> _stateIncompatibilities;
};

#endif // COMPLEXSTATEMACHINE_H
