#ifndef APPLICATIONDATA_H
#define APPLICATIONDATA_H

#include <iostream>
#include <vector>
#include <string>
#include "AudioTrack.h"
#include "WAVFile.h"
#include "MenuData.h"

class ApplicationData {
public:
    ApplicationData(std::istream& input_stream, std::ostream& output_stream);

    void addAction(const ActionFunctionData& action);
    void setDone(bool done);
    void printActionHelp();
    void clearToEOL();
    void takeAction(const std::string& choice);
    void mainLoop();

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
    
    bool mDone;
    MenuData mMenuData;
};

#endif // APPLICATIONDATA_H
