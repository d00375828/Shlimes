#include "WAVFile.h"
#include "endian_io.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Constructor
WAVFile::WAVFile(int samples_per_second, int bits_per_sample)
    : mSamplesPerSecond(0), mBitsPerSample(0), mNumberOfChannels(2) { // Default to 2 channels
    setSamplesPerSecond(samples_per_second);
    setBitsPerSample(bits_per_sample);
}

// Getter for samples per second
int WAVFile::getSamplesPerSecond() const {
    return mSamplesPerSecond;
}

// Getter for bits per sample
int WAVFile::getBitsPerSample() const {
    return mBitsPerSample;
}

// Setter for samples per second
void WAVFile::setSamplesPerSecond(const int samples_per_second) {
    if (samples_per_second >= 1) {
        mSamplesPerSecond = samples_per_second;
        mAudioTrack.setSamplesPerSecond(samples_per_second); // Update AudioTrack
    }
}

// Setter for bits per sample
void WAVFile::setBitsPerSample(const int bits_per_sample) {
    if (bits_per_sample % 8 == 0 && bits_per_sample >= 8 && bits_per_sample <= 32) {
        mBitsPerSample = bits_per_sample;
    }
}

// Configure the associated AudioTrack
void WAVFile::configureAudioTrack(double seconds) {
    if (seconds > 0) {
        mAudioTrack.setSeconds(seconds);
    }
}

// Open File
void WAVFile::open(const std::string& filename, std::ofstream& output_stream) {
    output_stream.open(filename, std::ios::binary);
}


// Write RIFF Header
void WAVFile::writeRIFFHeader(std::ostream& output_stream) {
    output_stream.write("RIFF", 4);
    little_endian_io::write_4_bytes(output_stream, 0); // Placeholder for chunk size
    output_stream.write("WAVE", 4);
}

// Write FMT Subchunk
void WAVFile::writeFMTSubchunk(std::ostream& output_stream) {
    output_stream.write("fmt ", 4);
    little_endian_io::write_4_bytes(output_stream, 16); // Subchunk1Size
    little_endian_io::write_2_bytes(output_stream, 1);  // AudioFormat (PCM)
    little_endian_io::write_2_bytes(output_stream, mNumberOfChannels);  // NumChannels from data member
    little_endian_io::write_4_bytes(output_stream, mSamplesPerSecond); // SampleRate
    int byte_rate = mSamplesPerSecond * mNumberOfChannels * (mBitsPerSample / 8);
    little_endian_io::write_4_bytes(output_stream, byte_rate); // ByteRate
    int block_align = mNumberOfChannels * (mBitsPerSample / 8);
    little_endian_io::write_2_bytes(output_stream, block_align); // BlockAlign
    little_endian_io::write_2_bytes(output_stream, mBitsPerSample); // BitsPerSample
}

// Write Data Subchunk Header
void WAVFile::writeDataSubchunkHeader(std::ostream& output_stream) {
    output_stream.write("data", 4);
    mDataSubchunkPosition = static_cast<unsigned int>(output_stream.tellp());
    little_endian_io::write_4_bytes(output_stream, 0); // Placeholder for Subchunk2Size
}

// Write One Track Data
void WAVFile::writeOneTrackData(std::ostream& output_stream, const double track_data, int maximum_amplitude, int bytes_per_sample) {
    int value = static_cast<int>(track_data * maximum_amplitude);
    little_endian_io::write_word(output_stream, value, bytes_per_sample);
}

// Write Tracks
// void WAVFile::writeTracks(std::ostream& output_stream, const std::vector<AudioTrack>& tracks) {
//     if (tracks.size() != 2 || tracks[0].getSize() != tracks[1].getSize()) {
//         return; // Only handle stereo tracks with equal size
//     }

//     int bytes_per_sample = mBitsPerSample / 8;
//     int maximum_amplitude = (1 << (mBitsPerSample - 1)) - 1;

//     const auto& left_channel = tracks[0];
//     const auto& right_channel = tracks[1];

//     for (unsigned int i = 0; i < left_channel.getSize(); ++i) {
//         writeOneTrackData(output_stream, left_channel.getValue(i), maximum_amplitude, bytes_per_sample);
//         writeOneTrackData(output_stream, right_channel.getValue(i), maximum_amplitude, bytes_per_sample);
//     }
// }

void WAVFile::writeTracks(std::ostream& output_stream, const std::vector<AudioTrack>& tracks) {
    if (tracks.size() != static_cast<size_t>(mNumberOfChannels)) {
        std::cerr << "Error: Number of tracks does not match the number of channels." << std::endl;
        return;
    }

    unsigned int track_size = tracks[0].getSize();
    for (const auto& track : tracks) {
        if (track.getSize() != track_size) {
            std::cerr << "Error: All tracks must have the same size." << std::endl;
            return;
        }
    }

    int bytes_per_sample = mBitsPerSample / 8;
    int maximum_amplitude = (1 << (mBitsPerSample - 1)) - 1;

    for (unsigned int i = 0; i < track_size; ++i) {
        for (const auto& track : tracks) {
            writeOneTrackData(output_stream, track.getValue(i), maximum_amplitude, bytes_per_sample);
        }
    }
}

// Write Sizes
void WAVFile::writeSizes(std::ostream& output_stream) {
    std::streampos file_end = output_stream.tellp();
    int file_size = static_cast<int>(file_end);
    int data_subchunk_size = file_size - mDataSubchunkPosition - 4;

    // Update RIFF chunk size
    output_stream.seekp(4, std::ios::beg);
    little_endian_io::write_4_bytes(output_stream, file_size - 8);

    // Update Data Subchunk size
    output_stream.seekp(mDataSubchunkPosition, std::ios::beg);
    little_endian_io::write_4_bytes(output_stream, data_subchunk_size);
}

// Close File
void WAVFile::close(std::ofstream& output_stream) {
    if (output_stream.is_open()) {
        output_stream.close();
    }
}

// Write File (filename version)
void WAVFile::writeFile(const std::string& filename, const std::vector<AudioTrack>& tracks) {
    std::ofstream output_stream;
    open(filename, output_stream);
    writeFile(output_stream, tracks);
    close(output_stream);
}

// Write File (stream version)
void WAVFile::writeFile(std::ostream& output_stream, const std::vector<AudioTrack>& tracks) {
    mDataSubchunkPosition = 0;

    writeRIFFHeader(output_stream);
    writeFMTSubchunk(output_stream);
    writeDataSubchunkHeader(output_stream);
    writeTracks(output_stream, tracks);
    writeSizes(output_stream);
}


int WAVFile::getNumberOfChannels() const {
    return mNumberOfChannels;
}

void WAVFile::setNumberOfChannels(const int number_of_channels) {
    if (number_of_channels >= 1) {
        mNumberOfChannels = number_of_channels;
    } else {
        std::cerr << "Error: Number of channels must be at least 1.\n";
    }
}
