#ifndef ENVELOPE_H
#define ENVELOPE_H

#include <string>
#include <iostream>
#include "AudioTrack.h"

// Constants for property names
const std::string MAXIMUM_AMPLITUDE = "MAXIMUM-AMPLITUDE";
const std::string ATTACK_SECONDS = "ATTACK-SECONDS";
const std::string DECAY_SECONDS = "DECAY-SECONDS";
const std::string SUSTAIN_AMPLITUDE = "SUSTAIN-AMPLITUDE";
const std::string RELEASE_SECONDS = "RELEASE-SECONDS";

class Envelope {
    public:
        Envelope(const std::string& name, const std::string& type_name);
        Envelope(const std::string& name, const std::string& type_name, const double amplitude);
        virtual ~Envelope();

        virtual void generateAmplitudes(const double seconds, const int samples_per_second, AudioTrack& track) const = 0;

        // Getters
        const std::string& getName() const;
        const std::string& getTypeName() const;
        double getMaximumAmplitude() const;

        // setters
        void setName(const std::string& name);
        void setTypeName(const std::string& type_name);
        void setMaximumAmplitude(const double amplitude);
    private:
        std::string mName;
        std::string mTypeName;
        double mMaximumAmplitude;

};


#endif