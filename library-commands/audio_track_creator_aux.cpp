#include "audio_track_creator_aux.h"
#include <string>
#include <iostream>
#include <cmath> // For std::sin

void rampup_fill_audio_track(ApplicationData& app_data) {
    AudioTrack& track = app_data.getAudioTrack();
    unsigned int size = track.getSize();
    for (unsigned int i = 0; i < size; ++i) {
        track.setValue(i, static_cast<double>(i) / (size - 1));
    }
}

void rampdown_fill_audio_track(ApplicationData& app_data) {
    AudioTrack& track = app_data.getAudioTrack();
    unsigned int size = track.getSize();
    for (unsigned int i = 0; i < size; ++i) {
        track.setValue(i, 1.0 - static_cast<double>(i) / (size - 1));
    }
}

void sine_fill_audio_track(ApplicationData& app_data) {
    AudioTrack& track = app_data.getAudioTrack();
    double frequency = app_data.getDoubleRegister(0);
    unsigned int samples_per_second = track.getSamplesPerSecond();
    unsigned int size = track.getSize();

    for (unsigned int i = 0; i < size; ++i) {
        double angle = (6.28 * i * frequency) / samples_per_second;
        track.setValue(i, std::sin(angle));
    }
}

void sawtooth_fill_audio_track(ApplicationData& app_data) {
    AudioTrack& track = app_data.getAudioTrack();
    double frequency = app_data.getDoubleRegister(0);
    unsigned int samples_per_second = track.getSamplesPerSecond();
    unsigned int size = track.getSize();

    for (unsigned int i = 0; i < size; ++i) {
        unsigned int cycle_size = static_cast<unsigned int>(samples_per_second / frequency);
        unsigned int j = i % cycle_size;
        double amplitude = -1.0 + (2.0 * j) / (cycle_size - 1);
        track.setValue(i, amplitude);
    }
}

void display_audio_track(ApplicationData& app_data) {
    AudioTrack& track = app_data.getAudioTrack();
    unsigned int size = track.getSize();
    app_data.getOutputStream() << "\nsample_number,amplitude\n";
    for (unsigned int i = 0; i < size; ++i) {
        app_data.getOutputStream() << i << "," << track.getValue(i) << "\n";
    }
}

void fill_audio_track(ApplicationData& app_data) {
    std::string fill_style = app_data.getString("Fill style: ");
    if (fill_style == "rampup") {
        rampup_fill_audio_track(app_data);
    } else if (fill_style == "rampdown") {
        rampdown_fill_audio_track(app_data);
    } else if (fill_style == "sine") {
        double frequency = app_data.getDouble("Frequency: ");
        if (frequency > 0.0) {
            app_data.setDoubleRegister(0, frequency);
            sine_fill_audio_track(app_data);
        } else {
            app_data.getOutputStream() << "Frequency must be positive.\n";
        }
    } else if (fill_style == "sawtooth") {
        double frequency = app_data.getDouble("Frequency: ");
        if (frequency > 0.0) {
            app_data.setDoubleRegister(0, frequency);
            sawtooth_fill_audio_track(app_data);
        } else {
            app_data.getOutputStream() << "Frequency must be positive.\n";
        }
    } else {
        app_data.getOutputStream() << "Fill style '" << fill_style << "' is not allowed." << std::endl;
    }
}

int audio_track_creator(ApplicationData& app_data) {
    int samples_per_second = app_data.getInteger("Samples/Second: ");
    double seconds = app_data.getDouble("Seconds: ");

    if (samples_per_second > 0 && seconds > 0.0) {
        app_data.getAudioTrack().setSize(samples_per_second, seconds);
        fill_audio_track(app_data);
        display_audio_track(app_data);
        return app_data.getAudioTrack().getSize();
    } else {
        app_data.getOutputStream() << "Positive values expected for samples per second and seconds." << std::endl;
        return 0;
    }
}
