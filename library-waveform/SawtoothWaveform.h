#ifndef SAWTOOTHWAVEFORM_H
#define SAWTOOTHWAVEFORM_H

#include "Waveform.h"

class SawtoothWaveform : public Waveform {
public:
    SawtoothWaveform(const std::string& name);
    virtual ~SawtoothWaveform();
    
    double generateOneSample(const double frequency, const int sample_number, const double samples_per_second) const override;
};

#endif // SAWTOOTHWAVEFORM_H
