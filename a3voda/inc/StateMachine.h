//
// Created by sl on 19.02.2019.
//

#ifndef MQTT_CLIENT_STATEMACHINE_H
#define MQTT_CLIENT_STATEMACHINE_H

#include <ActionListener.h>
#include <chrono>
using namespace std::chrono;

class StateMachine {
private:
    long timer = 0;
    int state = 0;
public:
    void go(int newState, int interval = 0);
    int getState();
    bool isState(int state);
    virtual void loop() = 0;
    bool expired();
    void refreshInterval();
};

#endif //MQTT_CLIENT_STATEMACHINE_H
