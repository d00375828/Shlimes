#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <vector>
#include <cmath>
#include <string>
#include "AudioTrack.h"

// Global constant for ScoreReader
const std::string AMPLITUDE = "AMPLITUDE";

class Waveform {

protected:
    std::string mWaveFormName;
    std::string mWaveFormType;
    double mAmplitude;

public:
    Waveform(const std::string& name, const std::string& type_name);
    virtual ~Waveform();

    // getters
    const std::string& getName() const;
    const std::string& getTypeName() const;
    double getAmplitude() const;

    // setters
    void setName(const std::string& name);
    void setTypeName(const std::string& type_name);
    void setAmplitude(const double amplitude);

    double computeSampleAngle(const double frequency, const double sample_number, const int samples_per_second) const;
    double computeSampleCyclePosition(const double frequency, const double sample_number, const int samples_per_second) const;
    virtual void generateSamples(const double frequency, const double seconds, const int samples_per_second, AudioTrack& track) const;

    virtual double generateOneSample(const double frequency, const int sample_number, const double samples_per_second) const = 0;

};

#endif