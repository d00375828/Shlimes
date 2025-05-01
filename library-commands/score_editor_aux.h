#ifndef SCORE_EDITOR_AUX_H
#define SCORE_EDITOR_AUX_H

#include "ApplicationData.h"

// Waveform management functions for the score editor
void listScoreWaveformsUI(ApplicationData& app);
void addScoreWaveformUI(ApplicationData& app);
void editScoreWaveformUI(ApplicationData& app);

// Envelope management functions for the score editor
void listScoreEnvelopesUI(ApplicationData& app);
void addScoreEnvelopeUI(ApplicationData& app);
void editScoreEnvelopeUI(ApplicationData& app);

// Instrument management functions for the score editor
void listScoreInstrumentsUI(ApplicationData& app);
void addScoreInstrumentUI(ApplicationData& app);
void editScoreInstrumentUI(ApplicationData& app);
void buildScoreInstrumentFromWaveformAndEnvelopePair(ApplicationData& app, std::shared_ptr<Waveform> w, std::shared_ptr<Envelope> e);
void buildScoreAllPossibleInstrumentsUI(ApplicationData& app);

// Time signature and tempo management functions
void setScoreTimeSignatureUI(ApplicationData& app);
void setScoreTempoUI(ApplicationData& app);

// Staff management functions
void setStaffInstrumentUI(ApplicationData& app);
void listScoreStavesUI(ApplicationData& app);
void addStaffUI(ApplicationData& app);
void removeStaffUI(ApplicationData& app);
void showStaffUI(ApplicationData& app);
void addStaffNoteUI(ApplicationData& app);
void addStaffNoteRunUI(ApplicationData& app);
void renderScoreUI(ApplicationData& app);

// File operations
void readScoreUI(ApplicationData& app);
void writeScoreUI(ApplicationData& app);

// Program setup and control functions
int register_score_editor_commands(ApplicationData& app_data);
int score_editor(ApplicationData& app_data);

#endif // SCORE_EDITOR_AUX_H
