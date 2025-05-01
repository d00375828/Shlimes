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

void AudioTrack::addAt(const AudioTrack& other_track, double offset_seconds) {
    // Check if this track is properly initialized
    if (samples_per_second <= 0 || seconds <= 0.0) {
        return;
    }
    
    // Check if the other track is properly initialized
    if (other_track.getSamplesPerSecond() <= 0 || other_track.getSeconds() <= 0.0) {
        return;
    }
    
    // Make sure both tracks have the same sample rate
    if (samples_per_second != other_track.getSamplesPerSecond()) {
        std::cout << "Cannot add tracks with different sample rates" << std::endl;
        return;
    }
    
    // Calculate start index in this track based on offset
    size_t start_index = static_cast<size_t>(offset_seconds * samples_per_second);
    
    // Skip if start index is beyond the end of this track
    if (start_index >= values.size()) {
        return;
    }
    
    // Calculate how many samples we can add
    unsigned int samples_to_add = other_track.getSize();
    unsigned int available_samples = values.size() - start_index;
    unsigned int samples_to_copy = std::min(samples_to_add, available_samples);
    
    // Add samples from other track to this track
    for (unsigned int i = 0; i < samples_to_copy; ++i) {
        values[start_index + i] += other_track.getValue(i);
    }
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


