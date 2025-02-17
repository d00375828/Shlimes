#ifndef ENVELOPE_H
#define ENVELOPE_H

#include <string>
#include <iostream>
#include "AudioTrack.h"



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