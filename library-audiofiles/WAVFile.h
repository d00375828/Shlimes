<<<<<<< HEAD
#ifndef _WAVFILE_H_
#define _WAVFILE_H_

#include <string>
#include <vector>
#include <fstream>
=======
#ifndef WAVFILE_H_
#define WAVFILE_H_

#include <iostream>
#include <string>
#include <vector>
>>>>>>> b63ca74 (curts quads or burts?)
#include "AudioTrack.h"

class WAVFile {
public:
<<<<<<< HEAD
    WAVFile(int samples_per_second, int bits_per_sample);

    int getSamplesPerSecond() const;
    int getBitsPerSample() const;

    void setSamplesPerSecond(const int samples_per_second);
    void setBitsPerSample(const int bits_per_sample);
    void writeFile(const std::string& filename, const std::vector<AudioTrack>& tracks);
    void writeFile(std::ostream& output_stream, const std::vector<AudioTrack>& tracks);

protected:
=======
    // Constructor
    WAVFile(int samples_per_second, int bits_per_sample);

    // Getters
    int getSamplesPerSecond() const;
    int getBitsPerSample() const;

    // Setters
    void setSamplesPerSecond(const int samples_per_second);
    void setBitsPerSample(const int bits_per_sample);

    // Public Methods
    void writeFile(const std::string& filename, const std::vector<AudioTrack>& tracks);
    void writeFile(std::ostream& output_stream, const std::vector<AudioTrack>& tracks);

    // Configure the associated AudioTrack
    void configureAudioTrack(double seconds);

    int getNumberOfChannels() const;
    void setNumberOfChannels(const int number_of_channels);

protected:
    // Protected Methods
>>>>>>> b63ca74 (curts quads or burts?)
    void open(const std::string& filename, std::ofstream& output_stream);
    void writeRIFFHeader(std::ostream& output_stream);
    void writeFMTSubchunk(std::ostream& output_stream);
    void writeDataSubchunkHeader(std::ostream& output_stream);
    void writeOneTrackData(std::ostream& output_stream, const double track_data, int maximum_amplitude, int bytes_per_sample);
    void writeTracks(std::ostream& output_stream, const std::vector<AudioTrack>& tracks);
    void writeSizes(std::ostream& output_stream);
    void close(std::ofstream& output_stream);

private:
<<<<<<< HEAD
    int samples_per_second_;
    int bits_per_sample_;
    unsigned int mDataSubchunkPosition;
};

#endif /* _WAVFILE_H_ */
=======
    // Private Data Members
    int mSamplesPerSecond;
    int mBitsPerSample;
    AudioTrack mAudioTrack; 
    unsigned int mDataSubchunkPosition;
    int mNumberOfChannels;
};

#endif
>>>>>>> b63ca74 (curts quads or burts?)
