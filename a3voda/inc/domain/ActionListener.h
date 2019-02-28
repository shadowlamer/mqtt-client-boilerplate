//
// Created by sl on 20.02.2019.
//

#ifndef MQTT_CLIENT_ACTIONLISTENER_H
#define MQTT_CLIENT_ACTIONLISTENER_H

#include <domain/Serializable.h>

class ActionListener {
public:
    virtual void processAction(Serializable* s) = 0;
};

#endif //MQTT_CLIENT_ACTIONLISTENER_H
