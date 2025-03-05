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
    values.resize(0,0.0);
    values.assign(samples_per_second * seconds, 0.0);
}


AudioTrack AudioTrack::operator*(const AudioTrack& rhs) const {
    if (this->samples_per_second != rhs.getSamplesPerSecond() || seconds != rhs.getSeconds()) {
        return AudioTrack();  // Return empty track if incompatible
    }
    AudioTrack newTrack;
    newTrack.setSize(this->samples_per_second, this->seconds);
    
    for (std::size_t i = 0; i < this->values.size(); ++i) {
        double num = this->values[i] * rhs.getValue(i);
        newTrack.setValue(i, num);
    } 
    return newTrack;
}


