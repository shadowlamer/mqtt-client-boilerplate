#include <MQTTTask.h>

#include <iostream>

MQTTTask::MQTTTask():
        Task("MQTTTask"),
        mqttWrapper(MQTT_CLIENT_ID, MQTT_HOST, MQTT_PORT, {
            LOCAL_REQUEST_TOPIC,
            LOCAL_PROCESS_TOPIC
        }),
        paymentSystem(mqttWrapper)
{
    mqttWrapper.subscribeAction(paymentSystem);
    mqttWrapper.connect();
}


void MQTTTask::runTask() {
    mosqpp::lib_init();
    try {
        while (!sleep(200)) {}
    } catch (exception& e) {
        cerr << e.what() << endl;
        Poco::Process::requestTermination(Poco::Process::id());
    }
}
