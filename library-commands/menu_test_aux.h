#ifndef MENU_TEST_AUX_H
#define MENU_TEST_AUX_H

#include "ApplicationData.h"

// UI command functions
void menuUI(ApplicationData& app_data);
void commentUI(ApplicationData& app_data);
void echoUI(ApplicationData& app_data);
void quitUI(ApplicationData& app_data);

// Setup and main test functions
int register_menu_test_commands(ApplicationData& app_data);
int menu_test(ApplicationData& app_data);

#endif
