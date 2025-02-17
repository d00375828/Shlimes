#include "AudioTrack.h"
<<<<<<< HEAD

// Default constructor initializes data members to zero
AudioTrack::AudioTrack() : samplesPerSecond(0), seconds(0.0), values() {}

// Getter for samplesPerSecond
int AudioTrack::getSamplesPerSecond() const {
    return samplesPerSecond;
}

// Getter for seconds
=======
#include <iostream>


// Constructor
AudioTrack::AudioTrack() : samples_per_second(0), seconds(0.0), values() {}


// Getters
int AudioTrack::getSamplesPerSecond() const {
    return samples_per_second;
}

>>>>>>> b63ca74 (curts quads or burts?)
double AudioTrack::getSeconds() const {
    return seconds;
}

<<<<<<< HEAD
// Returns the size of the values vector
=======
>>>>>>> b63ca74 (curts quads or burts?)
unsigned int AudioTrack::getSize() const {
    return values.size();
}

<<<<<<< HEAD
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
=======
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
>>>>>>> b63ca74 (curts quads or burts?)
bool AudioTrack::indexValid(const unsigned int index) const {
    return index < values.size();
}

<<<<<<< HEAD
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
=======
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



>>>>>>> b63ca74 (curts quads or burts?)
