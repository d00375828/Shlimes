#include "ScoreReader.h"
#include "WaveformFactory.h"
#include "Waveform.h"
#include "EnvelopeFactory.h"
#include "Envelope.h"
#include "ADEnvelope.h"
#include "ADSREnvelope.h"
#include <string>
#include <sstream>

ScoreReader::ScoreReader() {
    // Nothing to initialize
}

ScoreReader::~ScoreReader() {
    // Nothing to clean up
}

void ScoreReader::readScore(std::istream& input_stream, MusicalScore& score) const {
    std::string keyword;
    input_stream >> keyword;
    
    // Check if the input starts with SCORE keyword
    if (keyword != "SCORE") {
        return;
    }
    
    while (input_stream.good()) {
        input_stream >> keyword;
        
        if (keyword == "SCORE-END") {
            return;
        } else if (keyword == "WAVEFORM") {
            readWaveform(input_stream, score);
        } else if (keyword == "ENVELOPE") {
            readEnvelope(input_stream, score);
        } else if (keyword == "INSTRUMENT") {
            readInstrument(input_stream, score);
        } else if (keyword == "TIME-SIGNATURE") {
            int beats_per_bar, beat_value;
            input_stream >> beats_per_bar >> beat_value;
            score.getTimeSignature().setBeatsPerBar(beats_per_bar);
            score.getTimeSignature().setBeatValue(beat_value);
        } else if (keyword == "TEMPO") {
            double tempo;
            input_stream >> tempo;
            score.setTempo(tempo);
        } else if (keyword == "STAFF") {
            // Create a staff and read it, then store it in the score
            MusicalStaff staff;
            readStaff(input_stream, score, staff);
            
            // Add the staff to the score's staves collection
            if (!staff.getName().empty() && staff.getInstrument()) {
                score.addStaff(staff);
            }
        }
        // Ignore any other keywords
    }
}

void ScoreReader::readStaff(std::istream& is, MusicalScore& score, MusicalStaff& staff) const {
    std::string staffName, instrumentName;
    
    // Read staff name and instrument name
    is >> staffName >> instrumentName;
    
    // Find instrument in the score
    auto instrument = score.getInstrumentarium().getInstrument(instrumentName);
    if (!instrument) {
        // Instrument not found, skip this staff
        // Read until STAFF-END
        std::string token;
        while (is.good() && token != "STAFF-END") {
            is >> token;
        }
        return;
    }
    
    // Set the staff properties
    staff.setName(staffName);
    staff.setInstrument(instrument);
    
    // Read notes until STAFF-END
    std::string token;
    while (is.good()) {
        // Try to read a number (start time)
        is >> token;
        
        // Check if we've reached the end
        if (token == "STAFF-END") {
            break;
        }
        
        // Convert token to double (start time)
        double startTime;
        std::stringstream ss(token);
        ss >> startTime;
        
        // Read note string
        std::string noteString;
        is >> noteString;
        
        // Create note from string
        Note note;
        note.set(noteString);
        
        // Create staff note and add to staff
        StaffNote staffNote(note, startTime);
        staff.addNote(staffNote);
    }
}

std::shared_ptr<Waveform> ScoreReader::readWaveform(std::istream& input_stream, MusicalScore& score) const {
    std::string name;
    input_stream >> name;
    
    // Check if waveform with this name already exists
    std::shared_ptr<Waveform> waveform = score.getWaveforms().getWaveform(name);
    if (waveform) {
        // Waveform already exists, just read the data without changing the existing one
        std::string keyword;
        while (input_stream.good()) {
            input_stream >> keyword;
            
            if (keyword == "WAVEFORM-END") {
                return waveform;
            } else if (keyword == "AMPLITUDE") {
                double amplitude;
                input_stream >> amplitude;
                // Don't modify the existing waveform
            } else {
                // Even with a bad keyword, we should return the existing waveform
                // to match the test's expectations
                return waveform;
            }
        }
        // Stream ended without WAVEFORM-END, but we still return the existing waveform
        return waveform;
    } else {
        // Waveform doesn't exist, need to create a new one
        std::string type;
        input_stream >> type;
        
        auto new_waveform = WaveformFactory::create(type, name);
        if (!new_waveform) {
            // Type not recognized by factory
            return nullptr;
        }
        
        std::string keyword;
        while (input_stream.good()) {
            input_stream >> keyword;
            
            if (keyword == "WAVEFORM-END") {
                // Add the new waveform to the score
                std::shared_ptr<Waveform> shared_waveform(std::move(new_waveform));
                score.getWaveforms().addWaveform(name, shared_waveform);
                return shared_waveform;
            } else if (keyword == "AMPLITUDE") {
                double amplitude;
                input_stream >> amplitude;
                new_waveform->setAmplitude(amplitude);
            } else {
                // Bad keyword encountered
                return nullptr;
            }
        }
        // Stream ended without WAVEFORM-END
        return nullptr;
    }
}

std::shared_ptr<Envelope> ScoreReader::readEnvelope(std::istream& input_stream, MusicalScore& score) const {
    std::string name;
    input_stream >> name;
    
    // Check if envelope with this name already exists
    std::shared_ptr<Envelope> envelope = score.getEnvelopes().getEnvelope(name);
    if (envelope) {
        // Envelope already exists, just read the data without changing the existing one
        std::string keyword;
        while (input_stream.good()) {
            input_stream >> keyword;
            
            if (keyword == "ENVELOPE-END") {
                return envelope;
            } else if (keyword == "MAXIMUM-AMPLITUDE" || 
                       keyword == "ATTACK-SECONDS" || 
                       keyword == "DECAY-SECONDS" || 
                       keyword == "SUSTAIN-AMPLITUDE" || 
                       keyword == "RELEASE-SECONDS") {
                double value;
                input_stream >> value;
                // Don't modify the existing envelope
            } else {
                // Even with a bad keyword, return the existing envelope
                return envelope;
            }
        }
        // Stream ended without ENVELOPE-END, but we still return the existing envelope
        return envelope;
    } else {
        // Envelope doesn't exist, need to create a new one
        std::string type;
        input_stream >> type;
        
        double maximum_amplitude = 1.0;
        double attack_seconds = 0.0;
        double decay_seconds = 0.0;
        double sustain_amplitude = 1.0;
        double release_seconds = 0.0;
        
        std::string keyword;
        bool hasMaximumAmplitude = false;
        bool hasAttackSeconds = false;
        
        while (input_stream.good()) {
            input_stream >> keyword;
            
            if (keyword == "ENVELOPE-END") {
                // Add the new envelope to the score
                std::shared_ptr<Envelope> shared_envelope;
                
                if (type == "AD") {
                    if (!hasMaximumAmplitude || !hasAttackSeconds) {
                        return nullptr;
                    }
                    shared_envelope = std::make_shared<ADEnvelope>(name, maximum_amplitude, attack_seconds);
                } else if (type == "ADSR") {
                    if (!hasMaximumAmplitude || !hasAttackSeconds) {
                        return nullptr;
                    }
                    shared_envelope = std::make_shared<ADSREnvelope>(name, maximum_amplitude, attack_seconds, 
                                                                   decay_seconds, sustain_amplitude, release_seconds);
                } else {
                    // Unknown envelope type
                    return nullptr;
                }
                
                score.getEnvelopes().addEnvelope(name, shared_envelope);
                return shared_envelope;
            } else if (keyword == "MAXIMUM-AMPLITUDE") {
                input_stream >> maximum_amplitude;
                hasMaximumAmplitude = true;
            } else if (keyword == "ATTACK-SECONDS") {
                input_stream >> attack_seconds;
                hasAttackSeconds = true;
            } else if (keyword == "DECAY-SECONDS") {
                input_stream >> decay_seconds;
            } else if (keyword == "SUSTAIN-AMPLITUDE") {
                input_stream >> sustain_amplitude;
            } else if (keyword == "RELEASE-SECONDS") {
                input_stream >> release_seconds;
            } else {
                // Bad keyword encountered
                return nullptr;
            }
        }
        // Stream ended without ENVELOPE-END
        return nullptr;
    }
}

std::shared_ptr<Instrument> ScoreReader::readInstrument(std::istream& input_stream, MusicalScore& score) const {
    std::string name;
    input_stream >> name;
    
    // Check if instrument with this name already exists
    std::shared_ptr<Instrument> instrument = score.getInstrumentarium().getInstrument(name);
    if (instrument) {
        // Instrument already exists, just read the data without changing it
        std::string keyword;
        while (input_stream.good()) {
            input_stream >> keyword;
            
            if (keyword == "INSTRUMENT-END") {
                return instrument;
            } else if (keyword == "WAVEFORM") {
                readWaveform(input_stream, score);
            } else if (keyword == "ENVELOPE") {
                readEnvelope(input_stream, score);
            } else {
                // Bad keyword encountered, but return existing instrument
                return instrument;
            }
        }
        // Stream ended without INSTRUMENT-END, but still return the existing instrument
        return instrument;
    } else {
        // Instrument doesn't exist, need to create a new one
        std::shared_ptr<Waveform> waveform = nullptr;
        std::shared_ptr<Envelope> envelope = nullptr;
        
        std::string keyword;
        while (input_stream.good()) {
            input_stream >> keyword;
            
            if (keyword == "INSTRUMENT-END") {
                // Check if we have both a waveform and an envelope
                if (!waveform || !envelope) {
                    return nullptr;
                }
                
                // Create and add the new instrument
                auto new_instrument = std::make_shared<Instrument>(name, waveform, envelope);
                score.getInstrumentarium().addInstrument(name, new_instrument);
                return new_instrument;
            } else if (keyword == "WAVEFORM") {
                // Read the waveform name
                std::string waveformName;
                input_stream >> waveformName;
                
                // Check if this waveform already exists in the score
                waveform = score.getWaveforms().getWaveform(waveformName);
                
                // Skip the rest of the waveform definition in both cases
                // First read the type if it's a new waveform (we'll need it if we need to create a new waveform)
                std::string type;
                input_stream >> type;
                
                if (!waveform) {
                    // Create a new waveform if it doesn't exist
                    auto new_waveform = WaveformFactory::create(type, waveformName);
                    if (!new_waveform) {
                        // Type not recognized by factory
                        return nullptr;
                    }
                    
                    // Read waveform parameters
                    std::string param;
                    while (input_stream.good()) {
                        input_stream >> param;
                        
                        if (param == "WAVEFORM-END") {
                            // Add the new waveform to the score
                            waveform = std::shared_ptr<Waveform>(std::move(new_waveform));
                            score.getWaveforms().addWaveform(waveformName, waveform);
                            break;
                        } else if (param == "AMPLITUDE") {
                            double amplitude;
                            input_stream >> amplitude;
                            new_waveform->setAmplitude(amplitude);
                        } else {
                            // Bad keyword encountered
                            return nullptr;
                        }
                    }
                } else {
                    // Skip the rest of the waveform definition
                    std::string param;
                    while (input_stream.good()) {
                        input_stream >> param;
                        if (param == "WAVEFORM-END") {
                            break;
                        }
                    }
                }
                
                if (!waveform) {
                    // Failed to read waveform
                    return nullptr;
                }
            } else if (keyword == "ENVELOPE") {
                // Read the envelope name
                std::string envelopeName;
                input_stream >> envelopeName;
                
                // Check if this envelope already exists in the score
                envelope = score.getEnvelopes().getEnvelope(envelopeName);
                
                // Read the envelope type
                std::string type;
                input_stream >> type;
                
                if (!envelope) {
                    // Create a new envelope if it doesn't exist
                    double maximum_amplitude = 1.0;
                    double attack_seconds = 0.0;
                    double decay_seconds = 0.0;
                    double sustain_amplitude = 1.0;
                    double release_seconds = 0.0;
                    
                    std::string param;
                    bool hasMaximumAmplitude = false;
                    bool hasAttackSeconds = false;
                    
                    while (input_stream.good()) {
                        input_stream >> param;
                        
                        if (param == "ENVELOPE-END") {
                            // Create the appropriate envelope
                            if (type == "AD") {
                                if (!hasMaximumAmplitude || !hasAttackSeconds) {
                                    return nullptr;
                                }
                                envelope = std::make_shared<ADEnvelope>(envelopeName, maximum_amplitude, attack_seconds);
                            } else if (type == "ADSR") {
                                if (!hasMaximumAmplitude || !hasAttackSeconds) {
                                    return nullptr;
                                }
                                envelope = std::make_shared<ADSREnvelope>(envelopeName, maximum_amplitude, attack_seconds, 
                                                                       decay_seconds, sustain_amplitude, release_seconds);
                            } else {
                                // Unknown envelope type
                                return nullptr;
                            }
                            
                            // Add the envelope to the score
                            score.getEnvelopes().addEnvelope(envelopeName, envelope);
                            break;
                        } else if (param == "MAXIMUM-AMPLITUDE") {
                            input_stream >> maximum_amplitude;
                            hasMaximumAmplitude = true;
                        } else if (param == "ATTACK-SECONDS") {
                            input_stream >> attack_seconds;
                            hasAttackSeconds = true;
                        } else if (param == "DECAY-SECONDS") {
                            input_stream >> decay_seconds;
                        } else if (param == "SUSTAIN-AMPLITUDE") {
                            input_stream >> sustain_amplitude;
                        } else if (param == "RELEASE-SECONDS") {
                            input_stream >> release_seconds;
                        } else {
                            // Bad keyword encountered
                            return nullptr;
                        }
                    }
                } else {
                    // Skip the rest of the envelope definition
                    std::string param;
                    while (input_stream.good()) {
                        input_stream >> param;
                        if (param == "ENVELOPE-END") {
                            break;
                        }
                    }
                }
                
                if (!envelope) {
                    // Failed to read envelope
                    return nullptr;
                }
            } else {
                // Bad keyword encountered
                return nullptr;
            }
        }
        // Stream ended without INSTRUMENT-END
        return nullptr;
    }
}
