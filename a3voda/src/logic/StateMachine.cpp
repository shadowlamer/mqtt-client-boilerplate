//
// Created by sl on 19.02.2019.
//

#include <StateMachine.h>

long savedTime;

long now() {
    milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    return ms.count();
}

void StateMachine::go(int newState, int interval) {
//    cerr << "Going to: " << newState << endl;
    timer = interval;
    state = newState;
    savedTime = now();
}

void StateMachine::loop() {}

bool StateMachine::expired() {
    long passed = now() - savedTime;
    return passed > timer;
}

int StateMachine::getState() {
    return state;
}

bool StateMachine::isState(int requestedState) {
    return state == requestedState;
}

void StateMachine::refreshInterval() {
    savedTime = now();
}
