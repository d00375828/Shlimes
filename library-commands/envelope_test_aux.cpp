#include "envelope_test_aux.h"
#include "ApplicationData.h"
#include "Envelope.h"
#include "ADEnvelope.h"
#include "ADSREnvelope.h"
#include "audio_track_creator_aux.h"
#include <memory>


void fill_audio_track_with_envelope(ApplicationData& app_data) {
    std::string envelope_style = app_data.getString("Envelope style: ");
    double max_amplitude = app_data.getDouble("Maximum amplitude: ");

    std::unique_ptr<Envelope> envelope;

    if (envelope_style == "ADSR") {
        double attack_seconds = app_data.getDouble("Attack seconds: ");
        double decay_seconds = app_data.getDouble("Decay seconds: ");
        double release_seconds = app_data.getDouble("Release seconds: ");
        double sustain_amplitude = app_data.getDouble("Sustain amplitude: ");

        
        envelope = std::make_unique<ADSREnvelope>("UserADSR", max_amplitude, attack_seconds, decay_seconds, sustain_amplitude, release_seconds);
    } else if (envelope_style == "AD") {
        double attack_seconds = app_data.getDouble("Attack seconds: ");

        envelope = std::make_unique<ADEnvelope>("UserAD", max_amplitude, attack_seconds);
    } else {
        app_data.getOutputStream() << "Envelope style '" << envelope_style << "' is not known.\n";
        return;
    }

    envelope->generateAmplitudes(app_data.getAudioTrack().getSeconds(), app_data.getAudioTrack().getSamplesPerSecond(), app_data.getAudioTrack());
}

int envelope_test(ApplicationData& app_data) {
    configure_audio_track(app_data);

    fill_audio_track_with_envelope(app_data);

    display_audio_track(app_data);
    return 0;
}