#include "multi_track_creator_aux.h"
#include "audio_track_creator_aux.h" 
#include "ApplicationData.h"
#include "WAVFile.h"
#include "AudioTrack.h"
#include "wav_file_creator_aux.h"
#include <iostream>
#include <vector>


void multi_track_configure_audio_track_and_wav_file(ApplicationData& app_data) {
    configure_audio_track_and_wav_file(app_data);
    int number_of_channels = app_data.getInteger("Number of channels: ");
    if (number_of_channels < 1) {
        std::cerr << "Error: Number of channels must be at least 1." << std::endl;
        return;
    }
    WAVFile& wav_file = app_data.getWAVFile();
    wav_file.setNumberOfChannels(number_of_channels);
}

void multi_track_fill_channels(ApplicationData& app_data) {
    WAVFile& wav_file = app_data.getWAVFile();
    int number_of_channels = wav_file.getNumberOfChannels();
    std::vector<AudioTrack> tracks;
    
    for (int i = 0; i < number_of_channels; ++i) {
        std::cout << "Channel " << (i + 1) << std::endl;
        fill_audio_track(app_data);
        tracks.push_back(app_data.getAudioTrack());
    }
    
    app_data.getChannels() = tracks;
}

int multi_track_creator(ApplicationData& app_data) {
    multi_track_configure_audio_track_and_wav_file(app_data);
    multi_track_fill_channels(app_data);
    WAVFile& wav_file = app_data.getWAVFile();
    std::string filename = app_data.getString("Output filename: ");
    wav_file.writeFile(filename, app_data.getChannels());
    return 0;
}
