#include "WavWriter.h"
#include <iostream>
#include <vector>

WavWriter::WavWriter() {
    // Empty constructor
}

WavWriter::~WavWriter() {
    // Empty destructor
}

void WavWriter::writeWavFromScore(const MusicalScore& score, 
                                const int samples_per_second, 
                                const int bits_per_sample, 
                                const std::string& wav_filename) const {
    // Render score into channels
    std::vector<AudioTrack> channels;
    score.renderWavChannels(samples_per_second, channels);
    
    // Create WAV file with the correct parameters
    WAVFile wavFile(samples_per_second, bits_per_sample);
    
    // If we have channels, set the number of channels in the WAV file
    if (!channels.empty()) {
        wavFile.setNumberOfChannels(channels.size());
    }
    
    // Write channels to WAV file
    wavFile.writeFile(wav_filename, channels);
} 