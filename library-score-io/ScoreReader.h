#ifndef SCORE_READER_H
#define SCORE_READER_H

#include <iostream>
#include <fstream>
#include <memory>
#include "Waveform.h"
#include "Envelope.h"
#include "Instrument.h"
#include "MusicalScore.h"
#include "ADEnvelope.h"
#include "ADSREnvelope.h"
#include "SquareWaveform.h"
#include "SineWaveform.h"
#include "SawtoothWaveform.h"
#include "TriangleWaveform.h"
#include "TimeSignature.h"
#include "MusicalStaff.h"

class ScoreReader {
public:
    ScoreReader();
    virtual ~ScoreReader();
    
    void readScore(std::istream& input_stream, MusicalScore& score) const;
    std::shared_ptr<Waveform> readWaveform(std::istream& input_stream, MusicalScore& score) const;
    std::shared_ptr<Envelope> readEnvelope(std::istream& input_stream, MusicalScore& score) const;
    std::shared_ptr<Instrument> readInstrument(std::istream& input_stream, MusicalScore& score) const;
    void readStaff(std::istream& is, MusicalScore& score, MusicalStaff& staff) const;
};

#endif // SCORE_READER_H
