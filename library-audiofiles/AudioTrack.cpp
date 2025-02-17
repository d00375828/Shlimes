#include "AudioTrack.h"
#include <iostream>


// Constructor
AudioTrack::AudioTrack() : samples_per_second(0), seconds(0.0), values() {}


// Getters
int AudioTrack::getSamplesPerSecond() const {
    return samples_per_second;
}

double AudioTrack::getSeconds() const {
    return seconds;
}

unsigned int AudioTrack::getSize() const {
    return values.size();
}

// Setters

void AudioTrack::setSamplesPerSecond(const int new_samples_per_second) {
    if (new_samples_per_second < 1) return;
    samples_per_second = new_samples_per_second;
    resizeValues();
}

void AudioTrack::setSeconds(const double new_seconds) {
    if (new_seconds <= 0) return;
    seconds = new_seconds;
    resizeValues();
}

void AudioTrack::setSize(const int new_samples_per_second, const double new_seconds) {
    if (new_samples_per_second < 1 || new_seconds <= 0) {
        std::cout << "Invalid setSize inputs: samples_per_second=" << new_samples_per_second
                  << ", seconds=" << new_seconds << std::endl;
        return;
    }
    samples_per_second = new_samples_per_second;
    seconds = new_seconds;
    resizeValues();  // Resize the vector
}




// Validation and access
bool AudioTrack::indexValid(const unsigned int index) const {
    return index < values.size();
}

double AudioTrack::getValue(const unsigned int index) const {
    if (!indexValid(index)) return -INFINITY;
    return values[index];
}

void AudioTrack::setValue(const unsigned int index, const double value) {
    if (!indexValid(index)) return;
    values[index] = value;
}

void AudioTrack::resizeValues() {
    unsigned int new_size = static_cast<unsigned int>(samples_per_second * seconds);
    values.assign(new_size, 0.0);  // Fully clear and reinitialize to 0.0
}



