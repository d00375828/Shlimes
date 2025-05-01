#include "TimeSignature.h"

// Default constructor - 4/4 time signature
TimeSignature::TimeSignature() 
    : mBeatsPerBar(4), mBeatValue(4) {
}

// Parameterized constructor
TimeSignature::TimeSignature(const int beats_per_bar, const int beat_value) 
    : mBeatsPerBar(4), mBeatValue(4) {
    setBeatsPerBar(beats_per_bar);
    setBeatValue(beat_value);
}

// Accessors
int TimeSignature::getBeatsPerBar() const {
    return mBeatsPerBar;
}

int TimeSignature::getBeatValue() const {
    return mBeatValue;
}

// Mutators
void TimeSignature::setBeatsPerBar(const int beats_per_bar) {
    if (beats_per_bar >= 1) {
        mBeatsPerBar = beats_per_bar;
    }
}

void TimeSignature::setBeatValue(const int beat_value) {
    if (beat_value >= 1) {
        mBeatValue = beat_value;
    }
} 