#include "Frequency.h"
#include <cmath>

// Initialize static members
double Frequency::trt = std::pow(2.0, 1.0 / 12.0); // 12th root of 2
std::map<std::string, double> Frequency::smFrequencies = Frequency::generateFrequencies();

// Get frequency for a note name
double Frequency::getFrequency(const std::string& note) {
    auto it = smFrequencies.find(note);
    if (it != smFrequencies.end()) {
        return it->second;
    }
    return 0.0;
}

// Calculate scaling factor for octaves and keys
double Frequency::computeFactor(const unsigned int& octaves, const unsigned int& keys) {
    return std::pow(2.0, octaves) * std::pow(trt, keys);
}

// Move frequency left (lower) by specified octaves and keys
double Frequency::moveLeft(const double& frequency, const unsigned int& octaves, const unsigned int& keys) {
    return frequency / computeFactor(octaves, keys);
}

// Move frequency right (higher) by specified octaves and keys
double Frequency::moveRight(const double& frequency, const unsigned int& octaves, const unsigned int& keys) {
    return frequency * computeFactor(octaves, keys);
}

// Generate map of all note frequencies
std::map<std::string, double> Frequency::generateFrequencies() {
    std::map<std::string, double> frequencies;
    
    // Standard frequency for A4 = 440 Hz
    double a4_frequency = 440.0;
    
    // Notes in one octave (including sharps and flats)
    std::string notes[] = {
        "C", "C#", "Db", "D", "D#", "Eb", "E", "F", "F#", "Gb", "G", "G#", "Ab", "A", "A#", "Bb", "B"
    };
    
    // Calculate C0 from A4
    // A4 is in octave 4, and is 9 semitones above C4
    // So C0 is 4 octaves and 9 semitones below A4
    double c0_frequency = moveLeft(a4_frequency, 4, 9);
    
    // Generate frequencies for notes C0 through B9
    for (unsigned int octave = 0; octave <= 9; octave++) {
        for (const std::string& note : notes) {
            std::string noteName = note + std::to_string(octave);
            
            // Calculate the frequency relative to C0
            // Sharps and flats share the same frequency
            int semitones = 0;
            if (note == "C") semitones = 0;
            else if (note == "C#" || note == "Db") semitones = 1;
            else if (note == "D") semitones = 2;
            else if (note == "D#" || note == "Eb") semitones = 3;
            else if (note == "E") semitones = 4;
            else if (note == "F") semitones = 5;
            else if (note == "F#" || note == "Gb") semitones = 6;
            else if (note == "G") semitones = 7;
            else if (note == "G#" || note == "Ab") semitones = 8;
            else if (note == "A") semitones = 9;
            else if (note == "A#" || note == "Bb") semitones = 10;
            else if (note == "B") semitones = 11;
            
            // Calculate frequency from C0
            double frequency = moveRight(c0_frequency, octave, semitones);
            frequencies[noteName] = frequency;
        }
    }
    
    return frequencies;
} 