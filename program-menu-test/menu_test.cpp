#include "ApplicationData.h"
#include "menu_test_aux.h"

int main() {
    ApplicationData app_data(std::cin, std::cout);
    return menu_test(app_data);
} 