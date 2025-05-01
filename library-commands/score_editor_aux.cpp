#include "score_editor_aux.h"
#include "menu_test_aux.h"
#include "WaveformFactory.h"
#include "EnvelopeFactory.h"
#include "ADEnvelope.h"
#include "ADSREnvelope.h"
#include "ScoreReader.h"
#include "ScoreWriter.h"
#include "WavWriter.h"
#include "StaffNote.h"
#include <memory>
#include <iostream>
#include <fstream>

void listScoreWaveformsUI(ApplicationData& app) {
    auto& out = app.getOutputStream();
    auto& waveforms = app.getScore().getWaveforms();
    
    for (const auto& pair : waveforms) {
        const auto& name = pair.first;
        const auto& waveform = pair.second;
        out << name << " : " << waveform->getName() << " " 
            << waveform->getTypeName() << " " << waveform->getAmplitude() << "\n";
    }
}

void addScoreWaveformUI(ApplicationData& app) {
    auto& out = app.getOutputStream();
    auto& waveforms = app.getScore().getWaveforms();

    std::string name = app.getString("Waveform name: ");
    std::string type = app.getString("Waveform type: ");
    
    // Check if the waveform type is valid before asking for amplitude
    if (!WaveformFactory::validStringId(type)) {
        out << "Unable to create a waveform of type '" << type << "'.\n";
        return;
    }
    
    double amplitude = app.getDouble("Amplitude: ");

    auto waveform = WaveformFactory::create(type, name);
    if (!waveform) {
        out << "Unable to create a waveform of type '" << type << "'.\n";
        return;
    }

    waveform->setAmplitude(amplitude);
    std::shared_ptr<Waveform> shared_waveform(std::move(waveform));
    waveforms.addWaveform(name, shared_waveform);
}

void editScoreWaveformUI(ApplicationData& app) {
    auto& out = app.getOutputStream();
    auto& waveforms = app.getScore().getWaveforms();

    std::string name = app.getString("Waveform name: ");
    auto waveform = waveforms.getWaveform(name);
    
    if (!waveform) {
        out << "Unable to find a waveform with name '" << name << "'.\n";
        return;
    }

    out << "Amplitude(" << waveform->getAmplitude() << "): ";
    double amplitude = app.getDouble("");
    waveform->setAmplitude(amplitude);
}

void listScoreEnvelopesUI(ApplicationData& app) {
    auto& out = app.getOutputStream();
    auto& envelopes = app.getScore().getEnvelopes();
    
    for (const auto& pair : envelopes) {
        const auto& name = pair.first;
        const auto& envelope = pair.second;
        out << name << " : " << envelope->getName() << " " 
            << envelope->getTypeName() << " " << envelope->getMaximumAmplitude() << "\n";
    }
}

void addScoreEnvelopeUI(ApplicationData& app) {
    auto& out = app.getOutputStream();
    auto& envelopes = app.getScore().getEnvelopes();

    std::string name = app.getString("Envelope name: ");
    std::string type = app.getString("Envelope type: ");
    
    std::shared_ptr<Envelope> envelope;
    
    if (type == "AD" || type == "ADSR") {
        double maxAmplitude = app.getDouble("Maximum amplitude: ");
        
        if (type == "AD") {
            double attackSeconds = app.getDouble("Attack seconds: ");
            
            envelope = std::make_shared<ADEnvelope>(name, maxAmplitude, attackSeconds);
        } else { // type is ADSR
            double attackSeconds = app.getDouble("Attack seconds: ");
            double decaySeconds = app.getDouble("Decay seconds: ");
            double sustainAmplitude = app.getDouble("Sustain amplitude: ");
            double releaseSeconds = app.getDouble("Release seconds: ");
            
            envelope = std::make_shared<ADSREnvelope>(name, maxAmplitude, attackSeconds, 
                                                      decaySeconds, sustainAmplitude, releaseSeconds);
        }
        
        envelopes.addEnvelope(name, envelope);
    } else {
        out << "Unable to create an envelope of type '" << type << "'.\n";
        return;
    }
}

void editScoreEnvelopeUI(ApplicationData& app) {
    auto& out = app.getOutputStream();
    auto& envelopes = app.getScore().getEnvelopes();

    std::string name = app.getString("Envelope name: ");
    auto envelope = envelopes.getEnvelope(name);
    
    if (!envelope) {
        out << "Unable to find an envelope with name '" << name << "'.\n";
        return;
    }
    
    std::string type = envelope->getTypeName();
    
    out << "Maximum amplitude(" << envelope->getMaximumAmplitude() << "): ";
    double maxAmplitude = app.getDouble("");
    
    if (type == "ADSR") {
        auto adsr = std::dynamic_pointer_cast<ADSREnvelope>(envelope);
        if (!adsr) {
            out << "Error: Unable to cast to ADSR envelope.\n";
            return;
        }
        
        out << "Attack seconds(" << adsr->getAttackSeconds() << "): ";
        double attackSeconds = app.getDouble("");
        
        out << "Decay seconds(" << adsr->getDecaySeconds() << "): ";
        double decaySeconds = app.getDouble("");
        
        out << "Sustain amplitude(" << adsr->getSustainAmplitude() << "): ";
        double sustainAmplitude = app.getDouble("");
        
        out << "Release seconds(" << adsr->getReleaseSeconds() << "): ";
        double releaseSeconds = app.getDouble("");
        
        // Create a new envelope with the updated values
        auto newEnvelope = std::make_shared<ADSREnvelope>(name, maxAmplitude, attackSeconds, 
                                                        decaySeconds, sustainAmplitude, releaseSeconds);
        
        // Replace the old envelope
        envelopes.addEnvelope(name, newEnvelope);
    } else if (type == "AD") {
        auto ad = std::dynamic_pointer_cast<ADEnvelope>(envelope);
        if (!ad) {
            out << "Error: Unable to cast to AD envelope.\n";
            return;
        }
        
        out << "Attack seconds(" << ad->getAttackSeconds() << "): ";
        double attackSeconds = app.getDouble("");
        
        // Create a new envelope with the updated values
        auto newEnvelope = std::make_shared<ADEnvelope>(name, maxAmplitude, attackSeconds);
        
        // Replace the old envelope
        envelopes.addEnvelope(name, newEnvelope);
    } else {
        out << "Unsupported envelope type: " << type << "\n";
    }
}

void listScoreInstrumentsUI(ApplicationData& app) {
    auto& out = app.getOutputStream();
    auto& instrumentarium = app.getScore().getInstrumentarium();
    
    for (const auto& pair : instrumentarium) {
        const auto& name = pair.first;
        const auto& instrument = pair.second;
        
        // Format: "ins1 : ins1 : SineWaveObjectName ADSREnvelopeObjectName1"
        out << name << " : " << name << " : ";
        
        if (instrument->getWaveform()) {
            out << instrument->getWaveform()->getName() << " ";
        } else {
            out << "none ";
        }
        
        if (instrument->getEnvelope()) {
            out << instrument->getEnvelope()->getName();
        } else {
            out << "none";
        }
        
        out << "\n";
    }
}

void addScoreInstrumentUI(ApplicationData& app) {
    auto& out = app.getOutputStream();
    auto& instrumentarium = app.getScore().getInstrumentarium();
    auto& score = app.getScore();

    std::string name = app.getString("Instrument name: ");
    std::string waveformName = app.getString("Waveform name: ");
    std::string envelopeName = app.getString("Envelope name: ");
    
    // Check if waveform exists
    auto waveform = score.getWaveforms().getWaveform(waveformName);
    if (!waveform) {
        out << "Unable to find a waveform with name '" << waveformName << "'.\n";
        return;
    }
    
    // Check if envelope exists
    auto envelope = score.getEnvelopes().getEnvelope(envelopeName);
    if (!envelope) {
        out << "Unable to find an envelope with name '" << envelopeName << "'.\n";
        return;
    }
    
    // Create and add the instrument
    auto instrument = std::make_shared<Instrument>(name, waveform, envelope);
    instrumentarium.addInstrument(name, instrument);
}

void editScoreInstrumentUI(ApplicationData& app) {
    auto& out = app.getOutputStream();
    auto& instrumentarium = app.getScore().getInstrumentarium();
    auto& score = app.getScore();

    std::string name = app.getString("Instrument name: ");
    auto instrument = instrumentarium.getInstrument(name);
    
    if (!instrument) {
        out << "Unable to find an instrument with name '" << name << "'.\n";
        return;
    }
    
    std::string waveformName = app.getString("Waveform name: ");
    std::string envelopeName = app.getString("Envelope name: ");
    
    // Check if waveform exists
    auto waveform = score.getWaveforms().getWaveform(waveformName);
    if (!waveform) {
        out << "Unable to find a waveform with name '" << waveformName << "'.\n";
        return;
    }
    
    // Check if envelope exists
    auto envelope = score.getEnvelopes().getEnvelope(envelopeName);
    if (!envelope) {
        out << "Unable to find an envelope with name '" << envelopeName << "'.\n";
        return;
    }
    
    // Update the instrument
    instrument->setWaveform(waveform);
    instrument->setEnvelope(envelope);
}

void setScoreTimeSignatureUI(ApplicationData& app) {
    auto& score = app.getScore();
    
    int beatsPerBar = app.getInteger("Beats per bar: ");
    int beatValue = app.getInteger("Beat value: ");
    
    score.getTimeSignature().setBeatsPerBar(beatsPerBar);
    score.getTimeSignature().setBeatValue(beatValue);
}

void setScoreTempoUI(ApplicationData& app) {
    auto& score = app.getScore();
    
    double tempo = app.getDouble("Beats per minute: ");
    score.setTempo(tempo);
}

void readScoreUI(ApplicationData& app) {
    auto& out = app.getOutputStream();
    std::string filename = app.getString("Filename: ");
    
    std::ifstream file(filename);
    if (!file) {
        out << "Unable to open file '" << filename << "'.\n";
        return;
    }
    
    ScoreReader reader;
    reader.readScore(file, app.getScore());
    
    file.close();
}

void writeScoreUI(ApplicationData& app) {
    auto& out = app.getOutputStream();
    
    std::string filename = app.getString("Filename: ");
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        out << "Unable to open file '" << filename << "' for writing.\n";
        return;
    }
    
    ScoreWriter writer;
    writer.writeScore(file, app.getScore());
    
    file.close();
}

// Staff management functions
void setStaffInstrumentUI(ApplicationData& app) {
    auto& out = app.getOutputStream();
    auto& score = app.getScore();
    
    std::string staffName = app.getString("Staff name: ");
    auto& staff = score.getStaff(staffName);
    
    if (staff.getName().empty()) {
        out << "Unable to find a staff with name '" << staffName << "'.\n";
        return;
    }
    
    std::string instrumentName = app.getString("Instrument name: ");
    auto instrument = score.getInstrumentarium().getInstrument(instrumentName);
    
    if (!instrument) {
        out << "Unable to find an instrument with name '" << instrumentName << "'.\n";
        return;
    }
    
    staff.setInstrument(instrument);
}

void listScoreStavesUI(ApplicationData& app) {
    auto& out = app.getOutputStream();
    auto& staves = app.getScore().getStaves();
    
    for (const auto& pair : staves) {
        const auto& staff = pair.second;
        out << staff.getName() << " ";
        
        if (staff.getInstrument()) {
            out << staff.getInstrument()->getName();
        } else {
            out << "none";
        }
        
        out << "\n";
    }
}

void addStaffUI(ApplicationData& app) {
    auto& out = app.getOutputStream();
    auto& score = app.getScore();
    
    std::string staffName = app.getString("Staff name: ");
    std::string instrumentName = app.getString("Instrument name: ");
    
    // Check if instrument exists
    auto instrument = score.getInstrumentarium().getInstrument(instrumentName);
    if (!instrument) {
        out << "Unable to find an instrument with name '" << instrumentName << "'.\n";
        return;
    }
    
    // Create and add the staff
    MusicalStaff staff(staffName, instrument);
    score.addStaff(staff);
}

void showStaffUI(ApplicationData& app) {
    auto& out = app.getOutputStream();
    auto& score = app.getScore();
    
    std::string staffName = app.getString("Staff name: ");
    const auto& staff = score.getStaff(staffName);
    
    if (staff.getName().empty()) {
        out << "Unable to find a staff with name '" << staffName << "'.\n";
        return;
    }
    
    // Display staff details
    out << staff.getName() << " ";
    
    if (staff.getInstrument()) {
        out << staff.getInstrument()->getName();
    } else {
        out << "none";
    }
    
    out << "\n";
    
    // Disable frequency display for UI output
    bool previous_show_frequency = StaffNote::getShowFrequency();
    StaffNote::setShowFrequency(false);
    
    // Display notes
    for (const auto& note : staff.getNotes()) {
        out << note << "\n";
    }
    
    // Restore previous setting
    StaffNote::setShowFrequency(previous_show_frequency);
    
    out << "\n";
}

void addStaffNoteUI(ApplicationData& app) {
    auto& out = app.getOutputStream();
    auto& score = app.getScore();
    
    std::string staffName = app.getString("Staff name: ");
    auto& staff = score.getStaff(staffName);
    
    if (staff.getName().empty()) {
        out << "Unable to find a staff with name '" << staffName << "'.\n";
        return;
    }
    
    double start = app.getDouble("Start: ");
    std::string duration = app.getString("Duration: ");
    std::string noteName = app.getString("Note: ");
    
    // Create the note
    Note note;
    note.setName(noteName);
    
    // Set the duration based on the input
    if (duration == "w") {
        note.setDuration(1.0); // Whole note
    } else if (duration == "h") {
        note.setDuration(0.5); // Half note
    } else if (duration == "q") {
        note.setDuration(0.25); // Quarter note
    } else if (duration == "e") {
        note.setDuration(0.125); // Eighth note
    } else if (duration == "s") {
        note.setDuration(0.0625); // Sixteenth note
    } else {
        out << "Invalid duration: '" << duration << "'. Expected w, h, q, e, or s.\n";
        return;
    }
    
    // Create and add the staff note
    StaffNote staffNote(note, start);
    staff.addNote(staffNote);
}

void addStaffNoteRunUI(ApplicationData& app) {
    auto& out = app.getOutputStream();
    auto& score = app.getScore();
    
    std::string staffName = app.getString("Staff name: ");
    auto& staff = score.getStaff(staffName);
    
    if (staff.getName().empty()) {
        out << "Unable to find a staff with name '" << staffName << "'.\n";
        return;
    }
    
    double start = app.getDouble("Start: ");
    std::string duration = app.getString("Duration: ");
    std::string firstNoteName = app.getString("First note: ");
    
    // Create the first note
    Note firstNote;
    firstNote.setName(firstNoteName);
    
    // Set the duration based on the input
    if (duration == "w") {
        firstNote.setDuration(1.0); // Whole note
    } else if (duration == "h") {
        firstNote.setDuration(0.5); // Half note
    } else if (duration == "q") {
        firstNote.setDuration(0.25); // Quarter note
    } else if (duration == "e") {
        firstNote.setDuration(0.125); // Eighth note
    } else if (duration == "s") {
        firstNote.setDuration(0.0625); // Sixteenth note
    } else {
        out << "Invalid duration: '" << duration << "'. Expected w, h, q, e, or s.\n";
        return;
    }
    
    // Create the second note (4 semitones above)
    Note secondNote;
    secondNote.setName(firstNote.relativeNoteNameFlat(4));
    secondNote.setDuration(firstNote.getDuration());
    
    // Create the third note (7 semitones above)
    Note thirdNote;
    thirdNote.setName(firstNote.relativeNoteNameFlat(7));
    thirdNote.setDuration(firstNote.getDuration());
    
    // Add the notes to the staff with appropriate start times
    StaffNote staffNote1(firstNote, start);
    StaffNote staffNote2(secondNote, start + firstNote.getDuration());
    StaffNote staffNote3(thirdNote, start + 2 * firstNote.getDuration());
    
    staff.addNote(staffNote1);
    staff.addNote(staffNote2);
    staff.addNote(staffNote3);
}

void renderScoreUI(ApplicationData& app) {
    auto& score = app.getScore();
    
    std::string filename = app.getString("Filename: ");
    int samplesPerSecond = app.getInteger("Samples per second: ");
    int bitsPerSample = app.getInteger("Bits per sample: ");
    
    // Create WAV writer and write the score to a WAV file
    WavWriter writer;
    writer.writeWavFromScore(score, samplesPerSecond, bitsPerSample, filename);
}

void buildScoreInstrumentFromWaveformAndEnvelopePair(ApplicationData& app, std::shared_ptr<Waveform> w, std::shared_ptr<Envelope> e) {
    auto& instrumentarium = app.getScore().getInstrumentarium();
    
    // Create instrument name by concatenating waveform and envelope names with a slash
    std::string instrumentName = w->getName() + "/" + e->getName();
    
    // Create and add the instrument
    auto instrument = std::make_shared<Instrument>(instrumentName, w, e);
    instrumentarium.addInstrument(instrumentName, instrument);
}

void buildScoreAllPossibleInstrumentsUI(ApplicationData& app) {
    auto& score = app.getScore();
    
    // Get all waveforms and envelopes
    const auto& waveforms = score.getWaveforms();
    const auto& envelopes = score.getEnvelopes();
    
    // Check if we have any waveforms or envelopes by trying to get the first element
    bool hasWaveforms = false;
    bool hasEnvelopes = false;
    
    // Check waveforms
    for (const auto& _ : waveforms) {
        (void)_; // Silence unused variable warning
        hasWaveforms = true;
        break;
    }
    
    // Check envelopes
    for (const auto& _ : envelopes) {
        (void)_; // Silence unused variable warning
        hasEnvelopes = true;
        break;
    }
    
    if (!hasWaveforms || !hasEnvelopes) {
        return;
    }
    
    // Create an instrument for each waveform/envelope pair
    for (const auto& waveformPair : waveforms) {
        for (const auto& envelopePair : envelopes) {
            buildScoreInstrumentFromWaveformAndEnvelopePair(app, waveformPair.second, envelopePair.second);
        }
    }
}

void removeStaffUI(ApplicationData& app) {
    auto& out = app.getOutputStream();
    auto& score = app.getScore();
    
    std::string staffName = app.getString("Staff name: ");
    auto& staff = score.getStaff(staffName);
    
    // Check if the staff exists by comparing names
    if (staff.getName() != staffName) {
        out << staffName << " does not name a staff in this application.\n";
        return;
    }
    
    // Remove the staff
    score.getStaves().removeStaff(staffName);
}

int register_score_editor_commands(ApplicationData& app_data) {
    register_menu_test_commands(app_data);
    
    // Waveform commands
    app_data.addAction(ActionFunctionData("score-list-waveforms", listScoreWaveformsUI, 
        "List waveforms in the score."));
    app_data.addAction(ActionFunctionData("score-add-waveform", addScoreWaveformUI, 
        "Add waveform to the score."));
    app_data.addAction(ActionFunctionData("score-edit-waveform", editScoreWaveformUI, 
        "Edit waveform in the score."));
    
    // Envelope commands
    app_data.addAction(ActionFunctionData("score-list-envelopes", listScoreEnvelopesUI, 
        "List envelopes in the score."));
    app_data.addAction(ActionFunctionData("score-add-envelope", addScoreEnvelopeUI, 
        "Add envelope to the score."));
    app_data.addAction(ActionFunctionData("score-edit-envelope", editScoreEnvelopeUI, 
        "Edit envelope in the score."));
    
    // Instrument commands
    app_data.addAction(ActionFunctionData("score-list-instruments", listScoreInstrumentsUI, 
        "List instruments in the score."));
    app_data.addAction(ActionFunctionData("score-add-instrument", addScoreInstrumentUI, 
        "Add instrument to the score."));
    app_data.addAction(ActionFunctionData("score-edit-instrument", editScoreInstrumentUI, 
        "Edit instrument in the score."));
    app_data.addAction(ActionFunctionData("score-build-all-instruments", buildScoreAllPossibleInstrumentsUI, 
        "Build an instrument for each waveform/envelope pair in the score."));
    
    // Time signature and tempo commands
    app_data.addAction(ActionFunctionData("score-set-time-signature", setScoreTimeSignatureUI, 
        "Edit the time signature of a score."));
    app_data.addAction(ActionFunctionData("score-set-tempo", setScoreTempoUI, 
        "Edit the tempo of a score."));
    
    // Staff commands
    app_data.addAction(ActionFunctionData("score-staff-set-instrument", setStaffInstrumentUI, 
        "Change instrument assigned to a staff in the score."));
    app_data.addAction(ActionFunctionData("score-list-staves", listScoreStavesUI, 
        "List staves in the score."));
    app_data.addAction(ActionFunctionData("score-add-staff", addStaffUI, 
        "Add a staff to the score."));
    app_data.addAction(ActionFunctionData("score-remove-staff", removeStaffUI, 
        "Remove a staff from the score."));
    app_data.addAction(ActionFunctionData("score-show-staff", showStaffUI, 
        "Display staff details."));
    app_data.addAction(ActionFunctionData("score-staff-add-note", addStaffNoteUI, 
        "Add a note to a staff."));
    app_data.addAction(ActionFunctionData("score-staff-add-note-run", addStaffNoteRunUI, 
        "Add a run of notes to a staff."));
    app_data.addAction(ActionFunctionData("score-render", renderScoreUI, 
        "Render score to wav file."));
    
    // File operations
    app_data.addAction(ActionFunctionData("score-read", readScoreUI, 
        "Read score from file."));
    app_data.addAction(ActionFunctionData("score-write", writeScoreUI, 
        "Write score to score file."));
    
    return 0;
}

int score_editor(ApplicationData& app_data) {
    register_score_editor_commands(app_data);
    app_data.mainLoop();
    return 0;
} 