#include "instrument_test_aux.h"
#include "SineWaveform.h"
#include "SquareWaveform.h"
#include "ADSREnvelope.h"
#include "ADEnvelope.h"
#include "wav_file_creator_aux.h"

std::shared_ptr<Waveform> choose_waveform(ApplicationData& app_data) {
    std::string style = app_data.getString("Waveform style: ");
    
    if (style == "sine") {
        return std::make_shared<SineWaveform>("");
    } else if (style == "square") {
        return std::make_shared<SquareWaveform>("");
    } else {
        app_data.getOutputStream() << "Waveform style '" << style << "' is not known.\n";
        return nullptr;
    }
}

std::shared_ptr<Envelope> choose_envelope(ApplicationData& app_data) {
    std::string style = app_data.getString("Envelope style: ");
    double max_amplitude = app_data.getDouble("Maximum amplitude: ");
    
    if (style == "ADSR") {
        double attack = app_data.getDouble("Attack seconds: ");
        double decay = app_data.getDouble("Decay seconds: ");
        double release = app_data.getDouble("Release seconds: ");
        double sustain = app_data.getDouble("Sustain amplitude: ");
        return std::make_shared<ADSREnvelope>("", max_amplitude, attack, decay, sustain, release);
    } else if (style == "AD") {
        double attack = app_data.getDouble("Attack seconds: ");
        return std::make_shared<ADEnvelope>("", max_amplitude, attack);
    } else {
        app_data.getOutputStream() << "Envelope style '" << style << "' is not known.\n";
        return nullptr;
    }
}

std::shared_ptr<Instrument> create_instrument(ApplicationData& app_data) {
    auto waveform = choose_waveform(app_data);
    auto envelope = choose_envelope(app_data);
    return std::make_shared<Instrument>("", waveform, envelope);
}

void fill_audio_track_from_instrument(ApplicationData& app_data, 
                                    std::shared_ptr<Instrument> instrument_ptr) {
    double frequency = app_data.getDoubleRegister(0);
    if (instrument_ptr) {
        instrument_ptr->generateSamples(frequency,
                                      app_data.getAudioTrack().getSeconds(),
                                      app_data.getAudioTrack().getSamplesPerSecond(),
                                      app_data.getAudioTrack());
    }
}

int instrument_test(ApplicationData& app_data) {
    configure_audio_track_and_wav_file(app_data);
    
    auto instrument = create_instrument(app_data);
    
    app_data.setDoubleRegister(0, app_data.getDouble("Frequency: "));
    
    fill_audio_track_from_instrument(app_data, instrument);
    
    // Get reference to channels vector and set up stereo
    std::vector<AudioTrack>& tracks = app_data.getChannels();
    tracks.resize(2);
    tracks[0] = app_data.getAudioTrack();
    tracks[1] = app_data.getAudioTrack();
    
    save_wav_file(app_data);
    
    return 0;
}
