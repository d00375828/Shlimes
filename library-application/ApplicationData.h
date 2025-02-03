#ifndef _APPLICATIONDATA_H_
#define _APPLICATIONDATA_H_

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "AudioTrack.h"
#include "WAVFile.h"

class ApplicationData {
public:
  ApplicationData(std::istream& input_stream, std::ostream& output_stream);

  int getInteger(const std::string& prompt);
  double getDouble(const std::string& prompt);
  std::string getString(const std::string& prompt);
  void promptUser(const std::string& prompt);

  std::istream& getInputStream();
  std::ostream& getOutputStream();

  AudioTrack audiotrack;

  AudioTrack& getAudioTrack();

  const AudioTrack& getAudioTrack() const;

  double getDoubleRegister(const unsigned int position) const;
  void setDoubleRegister(const unsigned int position, const double value);

  WAVFile& getWAVFile();
  const WAVFile& getWAVFile() const;

  std::vector<AudioTrack>& getChannels();
  const std::vector<AudioTrack>& getChannels() const;
protected:
  std::istream& mInputStream;
  std::ostream& mOutputStream;

private:
std::vector<double> doubleRegisters;
WAVFile wavFile;
std::vector<AudioTrack> channels;
};

#endif /* _APPLICATIONDATA_H_ */
