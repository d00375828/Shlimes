#include "SineWaveform.h"

SineWaveform::SineWaveform(const std::string& name)
    : Waveform(name, "sine") {
}

SineWaveform::~SineWaveform() {}

double SineWaveform::generateOneSample(const double frequency, 
                                     const int sample_number, 
                                     const double samples_per_second) const {
    double angle = computeSampleAngle(frequency, sample_number, samples_per_second);
    return mAmplitude * std::sin(angle);
}