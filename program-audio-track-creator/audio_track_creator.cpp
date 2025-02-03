#include "audio_track_creator_aux.h"
#include <iostream>

int main() {
    ApplicationData app_data(std::cin, std::cout);
    return audio_track_creator(app_data);
}