#ifndef TRIANGLEWAVEFORM_H
#define TRIANGLEWAVEFORM_H

#include "Waveform.h"

class TriangleWaveform : public Waveform {
public:
    TriangleWaveform(const std::string& name);
    virtual ~TriangleWaveform();
    
    double generateOneSample(const double frequency, const int sample_number, const double samples_per_second) const override;
};

#endif
