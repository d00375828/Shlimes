#ifndef INSTRUMENT_DESIGNER_AUX_H
#define INSTRUMENT_DESIGNER_AUX_H

#include "ApplicationData.h"
#include "WaveformFactory.h"
#include "EnvelopeFactory.h"

// Waveform management functions
void listWaveformsUI(ApplicationData& app_data);
void addWaveformUI(ApplicationData& app_data);
void editWaveformUI(ApplicationData& app_data);

// Envelope management functions
void listEnvelopesUI(ApplicationData& app_data);
void addEnvelopeUI(ApplicationData& app_data);
void editEnvelopeUI(ApplicationData& app_data);

// Instrument management functions
void listInstrumentsUI(ApplicationData& app_data);
void addInstrumentUI(ApplicationData& app_data);
void editInstrumentUI(ApplicationData& app_data);

// Audio and recording functions
void put_frequency_in_register(ApplicationData& app_data);
void recordInstrumentNoteUI(ApplicationData& app_data);

// Program setup and control functions
int register_instrument_designer_commands(ApplicationData& app_data);
int instrument_designer(ApplicationData& app_data);

#endif // INSTRUMENT_DESIGNER_AUX_H
