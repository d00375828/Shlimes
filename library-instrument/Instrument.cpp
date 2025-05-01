#include "Instrument.h"

// Constructors and destructor
Instrument::Instrument() 
    : name(""), waveform(nullptr), envelope(nullptr) {}

Instrument::Instrument(const std::string& name, 
                     std::shared_ptr<Waveform> waveform, 
                     std::shared_ptr<Envelope> envelope)
    : name(name), waveform(waveform), envelope(envelope) {}

Instrument::~Instrument() {}

// Getters
const std::string& Instrument::getName() const {
    return name;
}

std::shared_ptr<Waveform> Instrument::getWaveform() const {
    return waveform;
}

std::shared_ptr<Envelope> Instrument::getEnvelope() const {
    return envelope;
}

// Setters
void Instrument::setName(const std::string& new_name) {
    name = new_name;
}

void Instrument::setWaveform(std::shared_ptr<Waveform> new_waveform) {
    waveform = new_waveform;
}

void Instrument::setEnvelope(std::shared_ptr<Envelope> new_envelope) {
    envelope = new_envelope;
}

// Sample generation
void Instrument::generateSamples(const double frequency, 
                               const double seconds, 
                               const int samples_per_second, 
                               AudioTrack& track) const {
    // Create temporary tracks for waveform and envelope
    AudioTrack waveform_track;
    AudioTrack envelope_track;
    
    // Set size for both tracks
    waveform_track.setSize(samples_per_second, seconds);
    envelope_track.setSize(samples_per_second, seconds);
    
    // Generate samples for both components
    if (waveform && envelope) {
        waveform->generateSamples(frequency, seconds, samples_per_second, waveform_track);
        envelope->generateAmplitudes(seconds, samples_per_second, envelope_track);
        
        // Multiply the tracks together to get final result
        track = waveform_track * envelope_track;
    }
}
