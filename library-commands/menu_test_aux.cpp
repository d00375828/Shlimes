#include "menu_test_aux.h"
#include "ActionFunctionData.h"
#include <string>

void menuUI(ApplicationData& app_data) {
    app_data.printActionHelp();
    app_data.clearToEOL();
}

void commentUI(ApplicationData& app_data) {
    app_data.clearToEOL();
}

void echoUI(ApplicationData& app_data) {
    std::string line;
    std::getline(app_data.getInputStream(), line);
    app_data.getOutputStream() << line << "\n";
}

void quitUI(ApplicationData& app_data) {
    app_data.setDone(true);
}

int register_menu_test_commands(ApplicationData& app_data) {
    app_data.addAction(ActionFunctionData("#", &commentUI, "Skip to end of line (comment).", 1));
    app_data.addAction(ActionFunctionData("comment", &commentUI, "Skip to end of line (comment).", 1));
    app_data.addAction(ActionFunctionData("echo", &echoUI, "Echo back the arguments given.", 1));
    app_data.addAction(ActionFunctionData("help", &menuUI, "Display help message.", 1));
    app_data.addAction(ActionFunctionData("menu", &menuUI, "Display help message.", 1));
    app_data.addAction(ActionFunctionData("quit", &quitUI, "Terminate the program.", 1));
    return 0;
}

int menu_test(ApplicationData& app_data) {
    register_menu_test_commands(app_data);
    app_data.mainLoop();
    return 0;
}
