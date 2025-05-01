#ifndef WAV_WRITER_H
#define WAV_WRITER_H

#include <string>
#include "MusicalScore.h"
#include "WAVFile.h"

class WavWriter {
public:
    WavWriter();
    virtual ~WavWriter();
    
    void writeWavFromScore(const MusicalScore& score, const int samples_per_second, 
                           const int bits_per_sample, const std::string& wav_filename) const;
};

#endif // WAV_WRITER_H 