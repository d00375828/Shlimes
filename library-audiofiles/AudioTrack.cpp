#include "AudioTrack.h"

// Default constructor initializes data members to zero
AudioTrack::AudioTrack() : samplesPerSecond(0), seconds(0.0), values() {}

// Getter for samplesPerSecond
int AudioTrack::getSamplesPerSecond() const {
    return samplesPerSecond;
}

// Getter for seconds
double AudioTrack::getSeconds() const {
    return seconds;
}

// Returns the size of the values vector
unsigned int AudioTrack::getSize() const {
    return values.size();
}

// Setter for samplesPerSecond
void AudioTrack::setSamplesPerSecond(const int newSamplesPerSecond) {
    if (newSamplesPerSecond < 1) {
        return; // Do nothing if the value is less than 1
    }
    samplesPerSecond = newSamplesPerSecond;
    resizeValues();
}

// Setter for seconds
void AudioTrack::setSeconds(const double newSeconds) {
    if (newSeconds <= 0.0) {
        return; // Do nothing if the value is less than or equal to 0
    }
    seconds = newSeconds;
    resizeValues();
}

// Sets both samplesPerSecond and seconds, then resizes values
void AudioTrack::setSize(const int newSamplesPerSecond, const double newSeconds) {
    if (newSamplesPerSecond < 1 || newSeconds <= 0.0) {
        return; // Do nothing if either value is invalid
    }
    samplesPerSecond = newSamplesPerSecond;
    seconds = newSeconds;
    resizeValues();
}

// Checks if the index is valid for the values vector
bool AudioTrack::indexValid(const unsigned int index) const {
    return index < values.size();
}

// Gets the value at a specific index, or -INFINITY if the index is invalid
double AudioTrack::getValue(const unsigned int index) const {
    if (!indexValid(index)) {
        return -INFINITY;
    }
    return values[index];
}

// Sets the value at a specific index, does nothing if the index is invalid
void AudioTrack::setValue(const unsigned int index, const double value) {
    if (indexValid(index)) {
        values[index] = value;
    }
}

// Protected method to resize the values vector
void AudioTrack::resizeValues() {
    if (samplesPerSecond > 0 && seconds > 0) {
        values.clear();
        values.resize(static_cast<unsigned int>(samplesPerSecond * seconds), 0.0);
    }
}
