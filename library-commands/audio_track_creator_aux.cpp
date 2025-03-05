#include "audio_track_creator_aux.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>

void rampup_fill_audio_track(ApplicationData& app_data) {
    AudioTrack& track = app_data.getAudioTrack();
    unsigned int size = track.getSize();
    double v1 = 0.0; // Start value
    double v2 = 1.0; // End value

    for (unsigned int i = 0; i < size; ++i) {
        double value = v1 + (v2 - v1) * static_cast<double>(i) / (size - 1);
        track.setValue(i, value);
    }
}

void rampdown_fill_audio_track(ApplicationData& app_data) {
    AudioTrack& track = app_data.getAudioTrack();
    unsigned int size = track.getSize();
    double v1 = 1.0; // Start value
    double v2 = 0.0; // End value

    for (unsigned int i = 0; i < size; ++i) {
        double value = v1 + (v2 - v1) * static_cast<double>(i) / (size - 1);
        track.setValue(i, value);
    }
}

void display_audio_track(ApplicationData& app_data) {
    const AudioTrack& track = app_data.getAudioTrack();
    std::ostream& out = app_data.getOutputStream();

    // Add a leading newline and header
    out << "\nsample_number,amplitude\n";  // Ensure the header includes a leading newline

    for (unsigned int i = 0; i < track.getSize(); ++i) {
        double value = track.getValue(i);

        out << i << ",";
        // Format floating-point values with exactly one decimal place
        out << value;
        out << "\n";  // Add newline after each sample
    }
}

void sine_fill_audio_track(ApplicationData& app_data) {
    AudioTrack& audio_track = app_data.getAudioTrack();
    unsigned int samples_per_second = audio_track.getSamplesPerSecond();
    unsigned int total_samples = audio_track.getSize();
    double frequency = app_data.getDoubleRegister(0);

        if (frequency <= 0.0) {
        throw std::invalid_argument("Frequency must be positive.");
    }

    for (unsigned int sample_number = 0; sample_number < total_samples; ++sample_number) {
        double angle = (6.28 * sample_number * frequency) / samples_per_second; // Compute angle
        double amplitude = std::sin(angle); // Compute sine wave value
        audio_track.setValue(sample_number, amplitude); // Store amplitude in the audio track
    }
}


void sawtooth_fill_audio_track(ApplicationData& app_data) {
    AudioTrack& audio_track = app_data.getAudioTrack();
    unsigned int samples_per_second = audio_track.getSamplesPerSecond();
    unsigned int total_samples = audio_track.getSize();
    double frequency = app_data.getDoubleRegister(0);

    if (frequency <= 0.0) {
        throw std::invalid_argument("Frequency must be positive.");
    }

    int cycle_size = samples_per_second / frequency; // Compute samples per cycle

    for (unsigned int sample_number = 0; sample_number < total_samples; ++sample_number) {
        // Use std::fmod for floating-point modulo operation
        double j = sample_number % cycle_size; // Position within the current cycle

        // Compute amplitude using the sawtooth formula
        double amplitude = -1.0 + (2.0 * j) / (cycle_size - 1);

        // Store amplitude in the audio track
        audio_track.setValue(sample_number, amplitude);
    }
}


void reverse_sawtooth_fill_audio_track(ApplicationData& app_data) {
    AudioTrack& audio_track = app_data.getAudioTrack();
    unsigned int samples_per_second = audio_track.getSamplesPerSecond();
    unsigned int total_samples = audio_track.getSize();
    double frequency = app_data.getDoubleRegister(0);

    if (frequency <= 0.0) {
        throw std::invalid_argument("Frequency must be positive.");
    }

    int cycle_size = samples_per_second / frequency; // Compute samples per cycle

    for (unsigned int sample_number = 0; sample_number < total_samples; ++sample_number) {
        // Use std::fmod for floating-point modulo operation
        double j = sample_number % cycle_size; // Position within the current cycle

        // Compute amplitude using the sawtooth formula
        double amplitude = 1.0 - (2.0 * j) / (cycle_size - 1);

        // Store amplitude in the audio track
        audio_track.setValue(sample_number, amplitude);
    }
}


// Fill the audio track based on user input, extended to include sine and sawtooth
void fill_audio_track(ApplicationData& app_data) {
    std::string style = app_data.getString("Fill style: ");

    if (style == "rampup") {
        rampup_fill_audio_track(app_data);
    } else if (style == "rampdown") {
        rampdown_fill_audio_track(app_data);
    } else if (style == "sine") {
        double frequency = app_data.getDouble("Frequency: ");
        app_data.setDoubleRegister(0, frequency); // Store frequency in register 0
        sine_fill_audio_track(app_data);
    } else if (style == "sawtooth") {
        double frequency = app_data.getDouble("Frequency: ");
        app_data.setDoubleRegister(0, frequency); // Store frequency in register 0
        sawtooth_fill_audio_track(app_data);
    } else if (style == "reverse-sawtooth") {
        double frequency = app_data.getDouble("Frequency: ");
        app_data.setDoubleRegister(0, frequency);
        reverse_sawtooth_fill_audio_track(app_data);
    }
    else {
        app_data.getOutputStream() << "Fill style '" << style << "' is not allowed.\n";
    }
}

int audio_track_creator(ApplicationData& app_data) {
    // Prompt for samples per second, seconds, and fill style on the same line
    app_data.getOutputStream() << "Samples/Second: "; // Single space after colon
    int samplesPerSecond = app_data.getInteger(""); // No additional prompt text

    app_data.getOutputStream() << "Seconds: "; // Single space after colon
    double seconds = app_data.getDouble(""); // No additional prompt text

    if (samplesPerSecond > 0 && seconds > 0) {
        app_data.getAudioTrack().setSize(samplesPerSecond, seconds);
        fill_audio_track(app_data);
        display_audio_track(app_data);
        return app_data.getAudioTrack().getSize();
    } else {
        app_data.getOutputStream() << "Positive values expected for samples per second and seconds.\n";
        return 0;
    }
}