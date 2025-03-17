#include <iostream>
#include "ApplicationData.h"
#include "instrument_designer_aux.h"

int main() {
    ApplicationData app_data(std::cin, std::cout);
    return instrument_designer(app_data);
}