#include "ApplicationData.h"
#include "envelope_test_aux.h"

int main() {
    ApplicationData app_data(std::cin, std::cout);
    return envelope_test(app_data);
}
