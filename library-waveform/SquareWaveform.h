#ifndef SQUAREWAVEFORM_H
#define SQUAREWAVEFORM_H

#include "Waveform.h"

class SquareWaveform : public Waveform {
    public:
        SquareWaveform(const std::string& name);
        virtual ~SquareWaveform();

        virtual double generateOneSample(const double frequency, 
                                       const int sample_number, 
                                       const double samples_per_second) const override;
};

#endif
