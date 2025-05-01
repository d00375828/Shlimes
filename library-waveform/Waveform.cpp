#include "Waveform.h"
#include "AudioTrack.h"
#include <iostream>
#include <string>



Waveform::Waveform(const std::string& name, const std::string& type_name)
    : mWaveFormName(name),
    mWaveFormType(type_name),
    mAmplitude(1.0) {}


Waveform::~Waveform() {}

const std::string& Waveform::getName() const {
    return mWaveFormName;
}

const std::string& Waveform::getTypeName() const {
    return mWaveFormType;
}

double Waveform::getAmplitude() const{
    return mAmplitude;
}

void Waveform::setName(const std::string& name) {
    mWaveFormName = name;
}

void Waveform::setTypeName(const std::string& type_name) {
    mWaveFormType = type_name;
}

void Waveform::setAmplitude(const double amplitude) {
    if (amplitude >= 0 && amplitude <= 1.0) {
        mAmplitude = amplitude;
    }
}

double Waveform::computeSampleAngle(const double frequency, const double sample_number, const int samples_per_second) const {
    const double two_pi = 6.283185307179586476925286766559;
    double angle = two_pi * sample_number * frequency / samples_per_second;
    return angle;
}

double Waveform::computeSampleCyclePosition(const double frequency, const double sample_number, const int samples_per_second) const {
    const double two_pi = 6.283185307179586476925286766559;
    double angle = computeSampleAngle(frequency, sample_number, samples_per_second);

    double wrapped_angle = std::fmod(angle, two_pi);

    return wrapped_angle / two_pi;
}

void Waveform::generateSamples(const double frequency, const double seconds, const int samples_per_second, AudioTrack& track) const {
    track.setSize(samples_per_second, seconds);
    
    for (unsigned int sample_number = 0; sample_number < track.getSize(); ++sample_number) {
        double sample_value = generateOneSample(frequency, sample_number, samples_per_second);
        track.setValue(sample_number, sample_value);
    }
}


