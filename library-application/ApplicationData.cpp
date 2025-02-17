
#include "ApplicationData.h"

// Constructor
ApplicationData::ApplicationData(std::istream& input_stream, std::ostream& output_stream)
    : mInputStream(input_stream), mOutputStream(output_stream), mWAVFile(1,8) {
        mAudioTrack = AudioTrack();
        doubleRegisters = std::vector<double>(5, 0.0);
        mChannels = std::vector<AudioTrack>();
    }

int ApplicationData::getInteger(const std::string& prompt) {
    promptUser(prompt);
    int value;
    mInputStream >> value;
    return value;
}

double ApplicationData::getDouble(const std::string& prompt) {
    promptUser(prompt);
    double value;
    mInputStream >> value;
    return value;
}

std::string ApplicationData::getString(const std::string& prompt) {
    promptUser(prompt);
    std::string value;
    mInputStream >> value;
    return value;
}

double ApplicationData::getDoubleRegister(const unsigned int position) const {
    if (position >= doubleRegisters.size()) {
        return -INFINITY;
    }
    return doubleRegisters[position];
}

void ApplicationData::setDoubleRegister(const unsigned int position, const double value) {
    if (position >= doubleRegisters.size()) {
        return;
    }
    doubleRegisters[position] = value;
}

// Output a prompt to the user
void ApplicationData::promptUser(const std::string& prompt) {
    mOutputStream << prompt;
}

// Access the input stream
std::istream& ApplicationData::getInputStream() {
    return mInputStream;
}

// Access the output stream
std::ostream& ApplicationData::getOutputStream() {
    return mOutputStream;
}

// Get a reference to the AudioTrack
AudioTrack& ApplicationData::getAudioTrack() {
    return mAudioTrack;
}

// Get a const reference to the AudioTrack
const AudioTrack& ApplicationData::getAudioTrack() const {
    return mAudioTrack;
}

// Get a reference to the WAVFile
WAVFile& ApplicationData::getWAVFile() {
    return mWAVFile;
}

// Get a const reference to the WAVFile
const WAVFile& ApplicationData::getWAVFile() const {
    return mWAVFile;
}

// Get a reference to the channels vector
std::vector<AudioTrack>& ApplicationData::getChannels() {
    return mChannels;
}

// Get a const reference to the channels vector
const std::vector<AudioTrack>& ApplicationData::getChannels() const {
    return mChannels;
}
