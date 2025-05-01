#include "MusicalScore.h"

// Default constructor
MusicalScore::MusicalScore() : mTempo(100.0) {
    // TimeSignature will be default constructed (4/4)
}

// Parameterized constructor
MusicalScore::MusicalScore(const TimeSignature& time_signature, const double tempo)
    : mTimeSignature(time_signature), mTempo(100.0) {
    setTempo(tempo);
}

// Accessors
Waveforms& MusicalScore::getWaveforms() {
    return mWaveforms;
}

const Waveforms& MusicalScore::getWaveforms() const {
    return mWaveforms;
}

Envelopes& MusicalScore::getEnvelopes() {
    return mEnvelopes;
}

const Envelopes& MusicalScore::getEnvelopes() const {
    return mEnvelopes;
}

Instrumentarium& MusicalScore::getInstrumentarium() {
    return mInstrumentarium;
}

const Instrumentarium& MusicalScore::getInstrumentarium() const {
    return mInstrumentarium;
}

// Time signature and tempo accessors
TimeSignature& MusicalScore::getTimeSignature() {
    return mTimeSignature;
}

const TimeSignature& MusicalScore::getTimeSignature() const {
    return mTimeSignature;
}

double MusicalScore::getTempo() const {
    return mTempo;
}

void MusicalScore::setTempo(const double tempo) {
    if (tempo > 0) {
        mTempo = tempo;
    }
}

// Staff-related methods
void MusicalScore::addStaff(const MusicalStaff& staff) {
    mStaves.addStaff(staff.getName(), staff);
}

MusicalStaff& MusicalScore::getStaff(const std::string& name) {
    return mStaves.getStaff(name);
}

const MusicalStaff& MusicalScore::getStaff(const std::string& name) const {
    return mStaves.getStaff(name);
}

MusicalStaves& MusicalScore::getStaves() {
    return mStaves;
}

const MusicalStaves& MusicalScore::getStaves() const {
    return mStaves;
}

// Rendering methods
void MusicalScore::renderStaff(const MusicalStaff& staff, const int samples_per_second, AudioTrack& track) const {
    staff.render(mTimeSignature, mTempo, samples_per_second, track);
}

void MusicalScore::renderStaves(const int samples_per_second, std::map<std::string, AudioTrack>& tracks) const {
    for (const auto& pair : mStaves) {
        AudioTrack track;
        renderStaff(pair.second, samples_per_second, track);
        tracks[pair.first] = track;
    }
}

void MusicalScore::renderWavChannels(const int samples_per_second, std::vector<AudioTrack>& channels) const {
    std::map<std::string, AudioTrack> tracks;
    renderStaves(samples_per_second, tracks);
    
    // Add all tracks to the channels vector
    for (const auto& pair : tracks) {
        channels.push_back(pair.second);
    }
} 