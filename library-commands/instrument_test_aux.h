#ifndef INSTRUMENT_TEST_AUX_H
#define INSTRUMENT_TEST_AUX_H

#include "ApplicationData.h"
#include "Instrument.h"
#include <memory>

// Choose waveform based on user input
std::shared_ptr<Waveform> choose_waveform(ApplicationData& app_data);

// Choose and configure envelope based on user input
std::shared_ptr<Envelope> choose_envelope(ApplicationData& app_data);

// Create instrument from user-selected components
std::shared_ptr<Instrument> create_instrument(ApplicationData& app_data);

// Fill audio track with instrument samples
void fill_audio_track_from_instrument(ApplicationData& app_data, 
                                    std::shared_ptr<Instrument> instrument_ptr);

// Main test function
int instrument_test(ApplicationData& app_data);

#endif
