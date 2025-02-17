#include "difference_aux.h"
#include "ApplicationData.h"
#include <iostream>

int main() {
    ApplicationData app_data(std::cin, std::cout);
    return difference(app_data);
}