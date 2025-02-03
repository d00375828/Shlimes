#include "WAVFile.h"
#include "endian_io.h"

#include <fstream>
#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace little_endian_io;

WAVFile::WAVFile(int samples_per_second, int bits_per_sample)
    : samples_per_second_(0), bits_per_sample_(0), mDataSubchunkPosition(0) {
    setSamplesPerSecond(samples_per_second);
    setBitsPerSample(bits_per_sample);
}

int WAVFile::getSamplesPerSecond() const {
    return samples_per_second_;
}

int WAVFile::getBitsPerSample() const {
    return bits_per_sample_;
}

void WAVFile::setSamplesPerSecond(const int samples_per_second) {
    if (samples_per_second > 0) {
        samples_per_second_ = samples_per_second;
    }
}

void WAVFile::setBitsPerSample(const int bits_per_sample) {
    if (bits_per_sample == 8 || bits_per_sample == 16 || bits_per_sample == 24 || bits_per_sample == 32) {
        bits_per_sample_ = bits_per_sample;
    }
}

void WAVFile::writeFile(const std::string& filename, const std::vector<AudioTrack>& tracks) {
    std::ofstream output_stream;
    open(filename, output_stream);
    writeFile(output_stream, tracks);
    close(output_stream);
}

void WAVFile::writeFile(std::ostream& output_stream, const std::vector<AudioTrack>& tracks) {
    mDataSubchunkPosition = 0;
    writeRIFFHeader(output_stream);
    writeFMTSubchunk(output_stream);
    writeDataSubchunkHeader(output_stream);
    writeTracks(output_stream, tracks);
    writeSizes(output_stream);
}

/*This is where the second Assignment starts 
Everything failing is below this line*/

void WAVFile::open(const std::string& filename, std::ofstream& output_stream) {
    output_stream.open(filename, std::ios::binary);
    if (!output_stream.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
}

void WAVFile::writeRIFFHeader(std::ostream& output_stream) {
    output_stream.write("RIFF", 4);
    write_4_bytes(output_stream, 0);
    output_stream.write("WAVE", 4);
}

void WAVFile::writeFMTSubchunk(std::ostream& output_stream) {
    output_stream.write("fmt ", 4);
    write_4_bytes(output_stream, 16);
    write_2_bytes(output_stream, 1);
    write_2_bytes(output_stream, 2);
    write_4_bytes(output_stream, samples_per_second_);
    int byte_rate = samples_per_second_ * 2 * bits_per_sample_ / 8;
    write_4_bytes(output_stream, byte_rate);
    write_2_bytes(output_stream, 2 * (bits_per_sample_ / 8 ));
    write_2_bytes(output_stream, bits_per_sample_);
}

void WAVFile::writeDataSubchunkHeader(std::ostream& output_stream) {
    output_stream.write("data", 4);
    mDataSubchunkPosition = output_stream.tellp();
    little_endian_io::write_4_bytes(output_stream, 0);
}

/*Pretty sure it is this method and the one under it that are broke and need to be rewrittin*/
void WAVFile::writeOneTrackData(std::ostream& output_stream, const double track_data, int maximum_amplitude, int bytes_per_sample) {
    int value = static_cast<int>(track_data * maximum_amplitude);
    little_endian_io::write_word(output_stream, value, bytes_per_sample);
}


void WAVFile::writeTracks(std::ostream& output_stream, const std::vector<AudioTrack>& tracks) {
    if (tracks.size() != 2 || tracks[0].getSize() != tracks[1].getSize()) {
        return; }

        int bytes_per_sample = bits_per_sample_ / 8;
        int maximum_amplitude = (1 << (bits_per_sample_ - 1)) -1;

        const auto& left_channel = tracks[0];
        const auto& right_channel = tracks[1];

        for (unsigned int i = 0; i < left_channel.getSize(); i++) {
            writeOneTrackData(output_stream, left_channel.getValue(i), maximum_amplitude, bytes_per_sample);
            writeOneTrackData(output_stream, right_channel.getValue(i), maximum_amplitude, bytes_per_sample);

        }
    }

void WAVFile::writeSizes(std::ostream& output_stream) {
    std::streampos end_pos = output_stream.tellp();
    std::streamsize file_size = end_pos;
    output_stream.seekp(4);
    write_4_bytes(output_stream, file_size - 8);
    output_stream.seekp(mDataSubchunkPosition);
    write_4_bytes(output_stream, file_size - mDataSubchunkPosition - 4);
}

void WAVFile::close(std::ofstream& output_stream) {
    if (output_stream.is_open()) {
        output_stream.close();
    }
}
