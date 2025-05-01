#include "ADSREnvelope.h"


ADSREnvelope::ADSREnvelope(const std::string& name, const std::string& type_name)
    : Envelope(name, type_name),
    mAttack(0.0), mDecay(0.0), mSustain(0.5), mRelease(0.0) {}

ADSREnvelope::ADSREnvelope(const std::string& name, const std::string& type_name, const double maximum_amplitude, const double attack_seconds, const double decay_seconds, const double sustain_amplitude, const double release_seconds)
    : Envelope(name, type_name, maximum_amplitude),
    mAttack(attack_seconds), mDecay(decay_seconds), mSustain(sustain_amplitude), mRelease(release_seconds) {}

ADSREnvelope::ADSREnvelope(const std::string& name)
    : Envelope(name, "ADSR"),
    mAttack(0.0), mDecay(0.0), mSustain(0.5), mRelease(0.0) {}

ADSREnvelope::ADSREnvelope(const std::string& name, const double maximum_amplitude, const double attack_seconds, const double decay_seconds, const double sustain_amplitude, const double release_seconds)
    : Envelope(name, "ADSR", maximum_amplitude),
    mAttack(attack_seconds), mDecay(decay_seconds), mSustain(sustain_amplitude), mRelease(release_seconds) {}

ADSREnvelope::~ADSREnvelope() {}

double ADSREnvelope::getAttackSeconds() const {
    return mAttack;
}

double ADSREnvelope::getDecaySeconds() const {
    return mDecay;
}

double ADSREnvelope::getReleaseSeconds() const {
    return mRelease;
}

double ADSREnvelope::getSustainAmplitude() const {
    return mSustain;
}

void ADSREnvelope::setAttackSeconds(const double attack_seconds) {
    if (attack_seconds > 0.0) {
    mAttack = attack_seconds;
    }
}

void ADSREnvelope::setDecaySeconds(const double decay_seconds) {
    if (decay_seconds > 0.0) {
    mDecay = decay_seconds;
    }
}


void ADSREnvelope::setSustainAmplitude(const double sustain_amplitude) {
    if (sustain_amplitude > 0.0) {
    mSustain = sustain_amplitude;
    }
}

void ADSREnvelope::setReleaseSeconds(const double release_seconds) {
    if (release_seconds > 0.0) {
    mRelease = release_seconds;
    }
}


void ADSREnvelope::generateAmplitudes(const double seconds, const int samples_per_second, AudioTrack& track) const {
    int total_samples = (seconds * samples_per_second);

    if (total_samples < (mAttack + mDecay + mRelease) * samples_per_second) {
    return;
}

    track.setSize(samples_per_second, seconds);

    int attack_end = (mAttack * samples_per_second);
    int decay_end = (mAttack + mDecay) * samples_per_second;

    unsigned int release_end = track.getSize();
    unsigned int release_start = (seconds - mRelease) * samples_per_second;

    assignAttackAmplitudes(0, attack_end, track, 0.0, getMaximumAmplitude());

    assignDecayAmplitudes(attack_end, decay_end, track, getMaximumAmplitude(), mSustain);

    assignSustainAmplitudes(decay_end, release_start, track, mSustain);

    assignReleaseAmplitudes(release_start, release_end, track, mSustain);
}

void ADSREnvelope::assignAttackAmplitudes(const int begin, const int end, AudioTrack& track, const double a0, const double a1) const {
    for (int i = begin; i < end; i++) {
        double num = ((a1 - a0) * (i - begin)) / (end - begin) + a0;
        track.setValue(i, num);
    }

    for (std::size_t i = static_cast<std::size_t>(end); i < track.getSize(); i++) {
        double num = a1;
        track.setValue(i, num);
    }
}


void ADSREnvelope::assignDecayAmplitudes(const int begin, const int end, AudioTrack& track, const double a0, const double a1) const {
    for (int i = begin; i < end; ++i) {
        double num = ((a1 - a0) * (i - begin)) / (end - begin) + a0;
        track.setValue(i, num);
    }
}

void ADSREnvelope::assignSustainAmplitudes(const int begin, const int end, AudioTrack& track, const double a0) const {
    for (int i = begin; i < end; i++) {
        double num = a0;
        track.setValue(i, num);
    }
}

void ADSREnvelope::assignReleaseAmplitudes(const int begin, const int end, AudioTrack& track, const double a0) const {
    for (int i = begin; i < end; i++) {
        double num = a0 - (i - begin) * (a0/(end-begin));
        track.setValue(i, num);
    }
}