#include "difference_aux.h"
#include <iostream>

int difference(ApplicationData& /* app_data */) {
    double a, b;
    
    std::cout << "Minuend? ";
    std::cin >> a;
    
    std::cout << "Subtrahend? ";
    std::cin >> b;

    double c = a - b;
    
    std::cout << "Difference " << c << std::endl;

    if (c > 0) {
        return 2;
    } else if (c < 0) {
        return 1;
    } else {
        return 0;
    }
}
