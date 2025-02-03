#include "ApplicationData.h"
#include <string>
#include <iostream>
#include <cmath>

ApplicationData::ApplicationData(std::istream& input_stream, std::ostream& output_stream) 
  : mInputStream(input_stream), mOutputStream(output_stream), wavFile(1,8) {
    audiotrack = AudioTrack();
    doubleRegisters = std::vector<double>(5, 0.0);
    channels = std::vector<AudioTrack>();
}

int ApplicationData::getInteger(const std::string& prompt) {
  int value;{}
  promptUser(prompt);
  mInputStream >> value;
  return value;
}

double ApplicationData::getDouble(const std::string& prompt) {
  double value;{}
  promptUser(prompt);
  mInputStream >> value;
  return value;
}

std::string ApplicationData::getString(const std::string& prompt) {
  std::string value;
  promptUser(prompt);
  mInputStream >> value;
  return value;
}

void ApplicationData::promptUser(const std::string& prompt) {
  mOutputStream << prompt;
}

std::istream& ApplicationData::getInputStream() {
  return mInputStream;
}
std::ostream& ApplicationData::getOutputStream() {
  return mOutputStream;
}

AudioTrack& ApplicationData::getAudioTrack() {
  return audiotrack;
}

const AudioTrack& ApplicationData::getAudioTrack() const{
  return audiotrack;
}
double ApplicationData::getDoubleRegister(const unsigned int position) const {
  if (position < doubleRegisters.size()) {
    return doubleRegisters[position];
  }
  return -INFINITY; 
}

void ApplicationData::setDoubleRegister(const unsigned int position, const double value) {
  if (position < doubleRegisters.size()) {
    doubleRegisters[position] = value; 
  }
}

WAVFile& ApplicationData::getWAVFile() {
  return wavFile;
}

const WAVFile& ApplicationData::getWAVFile() const {
  return wavFile;
}

std::vector<AudioTrack>& ApplicationData::getChannels() {
  return channels;
}

const std::vector<AudioTrack>& ApplicationData::getChannels() const {
  return channels;
}