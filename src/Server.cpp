#include <Server.h>

bool _help_requested = false;

int ServerApp::main(const vector<string> &)
{
    if (_help_requested)
        return Application::EXIT_OK;

    cerr << "Server started" << endl;

    TaskManager tm;
    try {
        tm.start(new MQTTTask());
    } catch (int e) {
        cerr << e << endl;
    }
    waitForTerminationRequest();

    tm.cancelAll();
    tm.joinAll();

    return Application::EXIT_OK;
}
