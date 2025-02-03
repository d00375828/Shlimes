#ifndef _WAVFILE_H_
#define _WAVFILE_H_

#include <string>
#include <vector>
#include <fstream>
#include "AudioTrack.h"

class WAVFile {
public:
    WAVFile(int samples_per_second, int bits_per_sample);

    int getSamplesPerSecond() const;
    int getBitsPerSample() const;

    void setSamplesPerSecond(const int samples_per_second);
    void setBitsPerSample(const int bits_per_sample);
    void writeFile(const std::string& filename, const std::vector<AudioTrack>& tracks);
    void writeFile(std::ostream& output_stream, const std::vector<AudioTrack>& tracks);

protected:
    void open(const std::string& filename, std::ofstream& output_stream);
    void writeRIFFHeader(std::ostream& output_stream);
    void writeFMTSubchunk(std::ostream& output_stream);
    void writeDataSubchunkHeader(std::ostream& output_stream);
    void writeOneTrackData(std::ostream& output_stream, const double track_data, int maximum_amplitude, int bytes_per_sample);
    void writeTracks(std::ostream& output_stream, const std::vector<AudioTrack>& tracks);
    void writeSizes(std::ostream& output_stream);
    void close(std::ofstream& output_stream);

private:
    int samples_per_second_;
    int bits_per_sample_;
    unsigned int mDataSubchunkPosition;
};

#endif /* _WAVFILE_H_ */
