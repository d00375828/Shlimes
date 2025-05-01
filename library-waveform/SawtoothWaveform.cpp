#include "SawtoothWaveform.h"

SawtoothWaveform::SawtoothWaveform(const std::string& name)
    : Waveform(name, "sawtooth") {
}

SawtoothWaveform::~SawtoothWaveform() {
}

double SawtoothWaveform::generateOneSample(const double frequency, const int sample_number, const double samples_per_second) const {
    double cycle_position = computeSampleCyclePosition(frequency, sample_number, samples_per_second);
    double maximum_amplitude = getAmplitude();
    
    if (cycle_position < 0.5) {
        return 2 * cycle_position * maximum_amplitude;
    } else {
        return (2 * (cycle_position - 0.5) - 1.0) * maximum_amplitude;
    }
}
