<<<<<<< HEAD
#ifndef AUDIO_TRACK_H
#define AUDIO_TRACK_H
=======
#ifndef AUDIOTRACK_H
#define AUDIOTRACK_H
>>>>>>> b63ca74 (curts quads or burts?)

#include <vector>
#include <cmath>

class AudioTrack {
<<<<<<< HEAD
private:
    int samplesPerSecond;          // Sampling rate of the audio data
    double seconds;                // Duration of the audio data in seconds
    std::vector<double> values;    // Sequence of samples

protected:
    /**
     * Resizes the `values` vector based on `samplesPerSecond` and `seconds`.
     * The new size will be `samplesPerSecond * seconds`, and all elements will be initialized to 0.
     */
    void resizeValues();

public:
    // Default constructor initializes data members to zero
    AudioTrack();

    // Getter for samplesPerSecond
    int getSamplesPerSecond() const;

    // Getter for seconds
    double getSeconds() const;

    // Returns the size of the values vector
    unsigned int getSize() const;

    // Setter for samplesPerSecond
    void setSamplesPerSecond(const int samplesPerSecond);

    // Setter for seconds
    void setSeconds(const double seconds);

    // Sets both samplesPerSecond and seconds, then resizes values
    void setSize(const int samplesPerSecond, const double seconds);

    // Checks if the index is valid for the values vector
    bool indexValid(const unsigned int index) const;

    // Gets the value at a specific index, or -INFINITY if the index is invalid
    double getValue(const unsigned int index) const;

    // Sets the value at a specific index, does nothing if the index is invalid
    void setValue(const unsigned int index, const double value);
};

#endif // AUDIO_TRACK_H
=======

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
>>>>>>> b63ca74 (curts quads or burts?)
