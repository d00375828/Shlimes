#ifndef SINEWAVEFORM_H
#define SINEWAVEFORM_H

#include "Waveform.h"
#include <cmath>

class SineWaveform : public Waveform {
    public:
        SineWaveform(const std::string& name);
        virtual ~SineWaveform();

        virtual double generateOneSample(const double frequency, 
                                       const int sample_number, 
                                       const double samples_per_second) const override;
};

#endif