#include "ADEnvelope.h"

ADEnvelope::ADEnvelope(const std::string& name)
    : ADSREnvelope(name, "AD", 1.0, 0.0, 0.0, 0.0, 0.0) {}

ADEnvelope::ADEnvelope(const std::string& name, const double maximum_amplitude, const double attack_seconds)
    : ADSREnvelope(name, "AD", maximum_amplitude, attack_seconds, 0.0, 0.0, 0.0) {}

ADEnvelope::~ADEnvelope() {}  

void ADEnvelope::generateAmplitudes(const double seconds, const int samples_per_second, AudioTrack& track) const {
    if (seconds < getAttackSeconds()) {
        return;
    }
    track.setSize(samples_per_second, seconds);


    int attack_samples = (getAttackSeconds() * samples_per_second);
    int decay_samples = (seconds*samples_per_second);

    assignAttackAmplitudes(0, attack_samples, track, 0.0, getMaximumAmplitude());
    assignDecayAmplitudes(attack_samples, decay_samples, track, getMaximumAmplitude(), 0.0);
}
