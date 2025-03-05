#include "waveform_test_aux.h"
#include "wav_file_creator_aux.h"
#include "SineWaveform.h"
#include "SquareWaveform.h"
#include <iostream>
#include <memory>


void fill_audio_track_with_waveform(ApplicationData& app_data) {
    std::string style = app_data.getString("Waveform style: ");
    double amplitude = app_data.getDouble("Amplitude: ");
    double frequency = app_data.getDouble("Frequency: ");

    AudioTrack& track = app_data.getAudioTrack();

    std::unique_ptr<Waveform> waveform;

    if (style == "sine") {
        waveform = std::make_unique<SineWaveform>("sine");
    } else if (style == "square") {
        waveform = std::make_unique<SquareWaveform>("square");
    } else {
        app_data.getOutputStream() << "Waveform style '" << style << "' is not known.\n";
        return;
    }

    waveform->setAmplitude(amplitude);
    waveform->generateSamples(frequency, 
                             track.getSeconds(),
                             track.getSamplesPerSecond(),
                             track);
}

void fill_channels_with_waveforms(ApplicationData& app_data) {
    app_data.getChannels().resize(2);
    
    // Fill left channel
    app_data.getOutputStream() << "Left Channel\n";
    fill_audio_track_with_waveform(app_data);
    app_data.getChannels()[0] = app_data.getAudioTrack();
    
    // Fill right channel
    app_data.getOutputStream() << "Right Channel\n";
    fill_audio_track_with_waveform(app_data);
    app_data.getChannels()[1] = app_data.getAudioTrack();
}

int waveform_test(ApplicationData& app_data) {
    configure_audio_track_and_wav_file(app_data);
    fill_channels_with_waveforms(app_data);
    save_wav_file(app_data);
    return 0;
}
