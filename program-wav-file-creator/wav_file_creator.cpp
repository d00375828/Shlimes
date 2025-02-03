#include "ApplicationData.h"
#include "wav_file_creator_aux.h"

int main() {
    ApplicationData app_data(std::cin, std::cout);
    return wav_file_creator(app_data);
}
