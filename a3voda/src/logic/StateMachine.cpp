/**
 * @file StateMachine.cpp
 * @brief Реализация класса StateMachine.
 * @author Vadim Cherenev
 * @date 19.02.2019
 * @copyright MIT License
 */


#include <StateMachine.h>

long savedTime;

/**
 * @return Текущее время в миллисекундах с начала эпохи
 */
long now() {
    milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    return ms.count();
}

/**
 * @brief Изменить состояние конечного автомата.
 * Метод можно переопределить для выполнения действий, связанных со сменой состояния.
 * @param newState Новое состояние
 * @param interval Новое значение таймера, если необходимо
 */
void StateMachine::go(int newState, int interval) {
    timer = interval;
    state = newState;
    savedTime = now();
}

/**
 * @brief Цикл обработки событий.
 * Метод нужно переопределить для выполнения действий, связанных с текущим состоянием.
 * Метод нужно периодически вызывать для выполнения действий, связанных с текущим состоянием.
 */
void StateMachine::loop() {}

/**
 * @brief Проверяет истек ли взведенный таймер
 * @return true, если таймер истек
 */
bool StateMachine::expired() {
    long passed = now() - savedTime;
    return passed > timer;
}

/**
 * @return Текущее состояние конечного автомата.
 */
int StateMachine::getState() {
    return state;
}

/**
 * @brief Проверяет, находится ли автомат в заданном состоянии.
 * @param requestedState Состояние для проверки
 * @return true, если автомат находится в заданном состоянии.
 */
bool StateMachine::isState(int requestedState) {
    return state == requestedState;
}
