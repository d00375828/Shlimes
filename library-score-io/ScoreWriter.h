#ifndef SCORE_WRITER_H
#define SCORE_WRITER_H

#include <iostream>
#include <fstream>
#include "Waveform.h"
#include "Envelope.h"
#include "Instrument.h"
#include "MusicalScore.h"
#include "MusicalStaff.h"
#include "Note.h"
#include "StaffNote.h"

class ScoreWriter {
public:
    ScoreWriter();
    virtual ~ScoreWriter();
    
    void writeScore(std::ostream& output_stream, const MusicalScore& score) const;
    void writeWaveform(std::ostream& output_stream, const MusicalScore& score, const Waveform& waveform) const;
    void writeEnvelope(std::ostream& output_stream, const MusicalScore& score, const Envelope& envelope) const;
    void writeInstrument(std::ostream& output_stream, const MusicalScore& score, const Instrument& instrument) const;
    
    // Staff-related methods
    void writeStaff(std::ostream& os, const MusicalScore& score, const MusicalStaff& staff) const;
    void writeStaffNote(std::ostream& os, const MusicalScore& score, const StaffNote& staff_note) const;
    std::string getDurationLetter(const double duration) const;
    std::string formatNote(const Note& note) const;
};

#endif // SCORE_WRITER_H 