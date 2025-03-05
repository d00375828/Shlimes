#include "SquareWaveform.h"

SquareWaveform::SquareWaveform(const std::string& name)
    : Waveform(name, "square") {
}

SquareWaveform::~SquareWaveform() {
}

double SquareWaveform::generateOneSample(const double frequency, 
                                       const int sample_number, 
                                       const double samples_per_second) const {
    double cycle_position = computeSampleCyclePosition(frequency, sample_number, samples_per_second);
    return (cycle_position < 0.5) ? mAmplitude : -mAmplitude;
}
