#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <string>
#include <memory>
#include "Waveform.h"
#include "Envelope.h"
#include "AudioTrack.h"

class Instrument {
private:
    std::string name;
    std::shared_ptr<Waveform> waveform;
    std::shared_ptr<Envelope> envelope;

public:
    // Constructors and destructor
    Instrument();
    Instrument(const std::string& name, 
              std::shared_ptr<Waveform> waveform, 
              std::shared_ptr<Envelope> envelope);
    virtual ~Instrument();
    
    // Getters
    const std::string& getName() const;
    std::shared_ptr<Waveform> getWaveform() const;
    std::shared_ptr<Envelope> getEnvelope() const;
    
    // Setters
    void setName(const std::string& name);
    void setWaveform(std::shared_ptr<Waveform> waveform);
    void setEnvelope(std::shared_ptr<Envelope> envelope);
    
    // Sample generation
    void generateSamples(const double frequency, 
                        const double seconds, 
                        const int samples_per_second, 
                        AudioTrack& track) const;
};

#endif
