#ifndef ADENVELOPE_H
#define ADENVELOPE_H

#include "ADSREnvelope.h"

class ADEnvelope : public ADSREnvelope {
public:

    ADEnvelope(const std::string& name);


    ADEnvelope(const std::string& name, const double maximum_amplitude, const double attack_seconds);

    virtual ~ADEnvelope(); 


    virtual void generateAmplitudes(const double seconds, const int samples_per_second, AudioTrack& track) const override;
};

#endif
