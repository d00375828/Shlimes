#ifndef AUDIOTRACK_H
#define AUDIOTRACK_H

#include <vector>
#include <cmath>

class AudioTrack {

protected:
    int samples_per_second;
    double seconds;
    std::vector<double> values;

    void resizeValues();


public:

    // Constructor
    AudioTrack();

    // Getters
    int getSamplesPerSecond() const;
    double getSeconds() const;
    unsigned int getSize() const;


    // Setters
    void setSamplesPerSecond(const int samples_per_second);
    void setSeconds(const double seconds);
    void setSize(const int samples_per_second, const double seconds);

    // Validation and access
    bool indexValid(const unsigned int index) const;
    double getValue(const unsigned int index) const;
    void setValue(const unsigned int index, const double value);

};

#endif