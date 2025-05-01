#include "wav_file_creator_aux.h"
#include "ApplicationData.h"
#include <memory>



void configure_audio_track_and_wav_file(ApplicationData& app_data) {
    // Prompt user for input
    int samples_per_second = app_data.getInteger("Samples/Second: ");
    double seconds = app_data.getDouble("Seconds: ");
    int bits_per_sample = app_data.getInteger("Bits/Sample[8,16,24,32]: ");

    app_data.getWAVFile().setSamplesPerSecond(samples_per_second);
    app_data.getWAVFile().setBitsPerSample(bits_per_sample);
    app_data.getAudioTrack().setSamplesPerSecond(samples_per_second);
    app_data.getAudioTrack().setSeconds(seconds);
}

void fill_channels(ApplicationData& app_data) {
    // Resize channels to have two tracks (left and right)
    app_data.getChannels().resize(2);

    // Fill each channel
    for (int i = 0; i < 2; ++i) {
        std::string channel_name = (i == 0) ? "Left Channel" : "Right Channel";
        app_data.getOutputStream() << channel_name << std::endl;
        fill_audio_track (app_data);
        app_data.getChannels()[i] = app_data.getAudioTrack();
    }
}

void save_wav_file(ApplicationData& app_data) {
    std::string filename = app_data.getString("WAV filename: ");
    app_data.getWAVFile().writeFile(filename, app_data.getChannels());
}

int wav_file_creator(ApplicationData& app_data) {
    configure_audio_track_and_wav_file(app_data);

    // Validate that configuration was successful
    if (app_data.getAudioTrack().getSize() > 0) {
        fill_channels(app_data);
        save_wav_file(app_data);
        return app_data.getAudioTrack().getSize();
    } else {
        app_data.getOutputStream() << "Positive values expected for samples per second and seconds.\n";
        return 0;
    }
}

void configure_audio_track(ApplicationData& app_data) {
    // Get user input
    int samples_per_second = app_data.getInteger("Samples/Second: ");
    double seconds = app_data.getDouble("Seconds: ");

    // Configure the track
    AudioTrack& track = app_data.getAudioTrack();
    if (samples_per_second > 0 && seconds > 0) {
        track.setSize(samples_per_second, seconds);
    }
}
