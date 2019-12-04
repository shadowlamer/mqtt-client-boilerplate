/**
 * @file ActionListener.h
 * @brief Заголовочный файл для класса ActionListener.
 * @author Vadim Cherenev
 * @date 20.02.2019
 * @copyright MIT License
 */

#ifndef MQTT_CLIENT_ACTIONLISTENER_H
#define MQTT_CLIENT_ACTIONLISTENER_H

#include <Serializable.h>

/**
 * @class ActionListener ActionListener.h
 * @brief Абстрактный класс получателя сообщений MQTT.
 */
class ActionListener {
public:

/**
 * @brief Вызывается при получении сообщения.
 * @param s нагрузка сообщения, передаваемая в метод
 */
    virtual void processAction(Serializable* s) = 0;
};

#endif //MQTT_CLIENT_ACTIONLISTENER_H
