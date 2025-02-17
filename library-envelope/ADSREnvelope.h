#ifndef ADSRENVELOPE_H
#define ADSRENVELOPE_H

#include "Envelope.h"


class ADSREnvelope : public Envelope {
    public:
        ADSREnvelope(const std::string& name, const std::string& type_name);
        ADSREnvelope(const std::string& name, const std::string& type_name, const double maximum_amplitude, const double attack_seconds, const double decay_seconds, const double sustain_amplitude, const double release_seconds);
        ADSREnvelope(const std::string& name);
        ADSREnvelope(const std::string& name, const double maximum_amplitude, const double attack_seconds, const double decay_seconds, const double sustain_amplitude, const double release_seconds);

        virtual ~ADSREnvelope();

        // getters
        double getAttackSeconds() const;
        double getDecaySeconds() const;
        double getSustainAmplitude() const;
        double getReleaseSeconds() const;

        // setters
        void setAttackSeconds(const double attack_seconds);
        void setDecaySeconds(const double decay_seconds);
        void setSustainAmplitude(const double sustain_amplitude);
        void setReleaseSeconds(const double release_seconds);

        virtual void generateAmplitudes(const double seconds, const int samples_per_second, AudioTrack& track) const;
        void assignAttackAmplitudes(const int begin, const int end, AudioTrack& track, const double a0, const double a1) const;
        void assignDecayAmplitudes(const int begin, const int end, AudioTrack& track, const double a0, const double a1) const;
        void assignSustainAmplitudes(const int begin, const int end, AudioTrack& track, const double a0) const;
        void assignReleaseAmplitudes(const int begin, const int end, AudioTrack& track, const double a0, const double a1) const;

    private:
        double mAttack;
        double mDecay;
        double mSustain;
        double mRelease;

};
#endif