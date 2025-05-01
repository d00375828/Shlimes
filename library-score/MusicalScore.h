#ifndef MUSICAL_SCORE_H
#define MUSICAL_SCORE_H

#include "Waveforms.h"
#include "Envelopes.h"
#include "Instrumentarium.h"
#include "TimeSignature.h"
#include "MusicalStaves.h"
#include "AudioTrack.h"
#include <map>
#include <vector>

class MusicalScore {
public:
    // Constructors
    MusicalScore();
    MusicalScore(const TimeSignature& time_signature, const double tempo);

    // Accessors
    Waveforms& getWaveforms();
    const Waveforms& getWaveforms() const;
    
    Envelopes& getEnvelopes();
    const Envelopes& getEnvelopes() const;
    
    Instrumentarium& getInstrumentarium();
    const Instrumentarium& getInstrumentarium() const;
    
    // Time signature and tempo accessors
    TimeSignature& getTimeSignature();
    const TimeSignature& getTimeSignature() const;
    double getTempo() const;
    void setTempo(const double tempo);
    
    // Staff-related methods
    void addStaff(const MusicalStaff& staff);
    MusicalStaff& getStaff(const std::string& name);
    const MusicalStaff& getStaff(const std::string& name) const;
    MusicalStaves& getStaves();
    const MusicalStaves& getStaves() const;
    
    // Rendering methods
    void renderStaff(const MusicalStaff& staff, const int samples_per_second, AudioTrack& track) const;
    void renderStaves(const int samples_per_second, std::map<std::string, AudioTrack>& tracks) const;
    void renderWavChannels(const int samples_per_second, std::vector<AudioTrack>& channels) const;

private:
    // Data members
    Waveforms mWaveforms;
    Envelopes mEnvelopes;
    Instrumentarium mInstrumentarium;
    MusicalStaves mStaves;
    TimeSignature mTimeSignature;
    double mTempo;
};

#endif // MUSICAL_SCORE_H 