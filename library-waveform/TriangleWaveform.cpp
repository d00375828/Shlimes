#include "TriangleWaveform.h"

TriangleWaveform::TriangleWaveform(const std::string& name)
    : Waveform(name, "triangle") {
}

TriangleWaveform::~TriangleWaveform() {
}

double TriangleWaveform::generateOneSample(const double frequency, const int sample_number, const double samples_per_second) const {
    double cycle_position = computeSampleCyclePosition(frequency, sample_number, samples_per_second);
    double value = 0.0;
    
    if (cycle_position < 0.25) {
        value = (4.0 * (cycle_position - 0.0) + 0.0) * mAmplitude;
    } else if (cycle_position < 0.75) {
        value = (-4.0 * (cycle_position - 0.25) + 1.0) * mAmplitude;
    } else {
        value = (4.0 * (cycle_position - 0.75) - 1.0) * mAmplitude;
    }
    
    return value;
}
