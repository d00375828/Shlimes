<<<<<<< HEAD
#ifndef _APPLICATIONDATA_H_
#define _APPLICATIONDATA_H_

#include <iostream>
#include <string>
#include <map>
#include <vector>
=======
#ifndef APPLICATIONDATA_H
#define APPLICATIONDATA_H

#include <iostream>
#include <vector>
#include <string>
>>>>>>> b63ca74 (curts quads or burts?)
#include "AudioTrack.h"
#include "WAVFile.h"

class ApplicationData {
public:
<<<<<<< HEAD
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
=======
    ApplicationData(std::istream& input_stream, std::ostream& output_stream);

    int getInteger(const std::string& prompt);
    double getDouble(const std::string& prompt);
    double getDoubleRegister(const unsigned int position) const;
    void setDoubleRegister(const unsigned int position, const double value);
    std::string getString(const std::string& prompt);
    void promptUser(const std::string& prompt);

    std::istream& getInputStream();
    std::ostream& getOutputStream();

    AudioTrack& getAudioTrack();
    const AudioTrack& getAudioTrack() const;
    WAVFile& getWAVFile();
    const WAVFile& getWAVFile() const;
    std::vector<AudioTrack>& getChannels();
    const std::vector<AudioTrack>& getChannels() const;

private:
    std::istream& mInputStream;
    std::ostream& mOutputStream;
    std::vector<double> doubleRegisters;
    AudioTrack mAudioTrack;
    WAVFile mWAVFile;
    std::vector<AudioTrack> mChannels;
};

#endif // APPLICATIONDATA_H
>>>>>>> b63ca74 (curts quads or burts?)
