#include "instrument_designer_aux.h"
#include <iostream>
#include <memory>
#include "menu_test_aux.h"
#include "Instrument.h"
#include "audio_track_creator_aux.h"
#include "ADEnvelope.h"
#include "ADSREnvelope.h"
#include "wav_file_creator_aux.h"
#include "WaveformFactory.h"
#include "EnvelopeFactory.h"

// Forward declarations
void configure_audio_track_and_wav_file(ApplicationData& app_data);
void save_wav_file(ApplicationData& app_data);

void listWaveformsUI(ApplicationData& app_data) {
    auto& out = app_data.getOutputStream();
    auto& waveforms = app_data.getWaveforms();
    
    for (const auto& pair : waveforms) {
        const auto& name = pair.first;
        const auto& waveform = pair.second;
        out << name << " : " << waveform->getName() << " " 
            << waveform->getTypeName() << " " << waveform->getAmplitude() << "\n";
    }
}

void addWaveformUI(ApplicationData& app_data) {
    auto& out = app_data.getOutputStream();
    auto& waveforms = app_data.getWaveforms();

    std::string name = app_data.getString("Waveform name: ");
    std::string type = app_data.getString("Waveform type: ");
    double amplitude = app_data.getDouble("Amplitude: ");

    auto waveform = WaveformFactory::create(type, name);
    if (!waveform) {
        out << "Unable to create a waveform of type '" << type << "'.\n";
        return;
    }

    waveform->setAmplitude(amplitude);
    waveforms.addWaveform(name, std::move(waveform));
}

void editWaveformUI(ApplicationData& app_data) {
    auto& out = app_data.getOutputStream();
    auto& waveforms = app_data.getWaveforms();

    std::string name = app_data.getString("Waveform name: ");
    auto waveform = waveforms.getWaveform(name);
    
    if (!waveform) {
        out << "Unable to find a waveform with name '" << name << "'.\n";
        return;
    }

    out << "Amplitude(" << waveform->getAmplitude() << "): ";
    double amplitude = app_data.getDouble("");
    waveform->setAmplitude(amplitude);
}

void listEnvelopesUI(ApplicationData& app_data) {
    auto& out = app_data.getOutputStream();
    auto& envelopes = app_data.getEnvelopes();
    
    for (const auto& pair : envelopes) {
        const auto& name = pair.first;
        const auto& envelope = pair.second;
        out << name << " : " << envelope->getName() << " " 
            << envelope->getTypeName() << " " << envelope->getMaximumAmplitude() << "\n";
    }
}

void addEnvelopeUI(ApplicationData& app_data) {
    auto& out = app_data.getOutputStream();
    auto& envelopes = app_data.getEnvelopes();

    std::string name = app_data.getString("Envelope name: ");
    std::string type = app_data.getString("Envelope type: ");
    double maxAmplitude = app_data.getDouble("Maximum amplitude: ");

    std::shared_ptr<Envelope> envelope;
    
    if (type == "AD") {
        double attack = app_data.getDouble("Attack seconds: ");
        envelope = std::make_shared<ADEnvelope>(name, maxAmplitude, attack);
    } else if (type == "ADSR") {
        double attack = app_data.getDouble("Attack seconds: ");
        double decay = app_data.getDouble("Decay seconds: ");
        double sustain = app_data.getDouble("Sustain amplitude: ");
        double release = app_data.getDouble("Release seconds: ");
        envelope = std::make_shared<ADSREnvelope>(name, maxAmplitude, attack, decay, sustain, release);
    } else {
        out << "Unable to create an envelope of type '" << type << "'.\n";
        return;
    }

    envelopes.addEnvelope(name, std::move(envelope));
}

void editEnvelopeUI(ApplicationData& app_data) {
    auto& out = app_data.getOutputStream();
    auto& envelopes = app_data.getEnvelopes();

    std::string name = app_data.getString("Envelope name: ");
    auto envelope = envelopes.getEnvelope(name);
    
    if (!envelope) {
        out << "Unable to find an envelope with name '" << name << "'.\n";
        return;
    }

    out << "Maximum amplitude(" << envelope->getMaximumAmplitude() << "): ";
    double maxAmplitude = app_data.getDouble("");
    
    std::string typeName = envelope->getTypeName();
    std::shared_ptr<Envelope> newEnvelope;
    
    if (typeName == "AD") {
        auto adEnvelope = std::dynamic_pointer_cast<ADEnvelope>(envelope);
        if (adEnvelope) {
            out << "Attack seconds(" << adEnvelope->getAttackSeconds() << "): ";
            double attack = app_data.getDouble("");
            newEnvelope = std::make_shared<ADEnvelope>(name, maxAmplitude, attack);
        }
    } else if (typeName == "ADSR") {
        auto adsrEnvelope = std::dynamic_pointer_cast<ADSREnvelope>(envelope);
        if (adsrEnvelope) {
            out << "Attack seconds(" << adsrEnvelope->getAttackSeconds() << "): ";
            double attack = app_data.getDouble("");
            out << "Decay seconds(" << adsrEnvelope->getDecaySeconds() << "): ";
            double decay = app_data.getDouble("");
            out << "Sustain amplitude(" << adsrEnvelope->getSustainAmplitude() << "): ";
            double sustain = app_data.getDouble("");
            out << "Release seconds(" << adsrEnvelope->getReleaseSeconds() << "): ";
            double release = app_data.getDouble("");
            
            newEnvelope = std::make_shared<ADSREnvelope>(name, maxAmplitude, attack, decay, sustain, release);
        }
    }
    
    if (newEnvelope) {
        envelopes.addEnvelope(name, std::move(newEnvelope));
    }
}

void listInstrumentsUI(ApplicationData& app_data) {
    auto& out = app_data.getOutputStream();
    auto& instruments = app_data.getInstrumentarium();
    
    for (const auto& pair : instruments) {
        const auto& name = pair.first;
        const auto& instrument = pair.second;
        out << name << " : " << instrument->getWaveform()->getName() << " " 
            << instrument->getEnvelope()->getName() << "\n";
    }
}

void addInstrumentUI(ApplicationData& app_data) {
    auto& out = app_data.getOutputStream();
    auto& instruments = app_data.getInstrumentarium();
    
    std::string name = app_data.getString("Instrument name: ");
    std::string waveform_name = app_data.getString("Waveform name: ");
    std::string envelope_name = app_data.getString("Envelope name: ");
    
    auto waveform = app_data.getWaveforms().getWaveform(waveform_name);
    if (!waveform) {
        out << waveform_name << " does not name a waveform in this application.\n";
        return;
    }
    
    auto envelope = app_data.getEnvelopes().getEnvelope(envelope_name);
    if (!envelope) {
        out << envelope_name << " does not name an envelope in this application.\n";
        return;
    }
    
    // Create instrument using default constructor and then set properties
    auto instrument = std::make_shared<Instrument>();
    instrument->setName(name);
    instrument->setWaveform(waveform);
    instrument->setEnvelope(envelope);
    
    instruments.addInstrument(name, std::move(instrument));
}

void editInstrumentUI(ApplicationData& app_data) {
    auto& out = app_data.getOutputStream();
    auto& instruments = app_data.getInstrumentarium();
    
    std::string name = app_data.getString("Instrument name: ");
    std::string waveform_name = app_data.getString("Waveform name: ");
    std::string envelope_name = app_data.getString("Envelope name: ");
    
    auto instrument = instruments.getInstrument(name);
    
    if (!instrument) {
        out << name << " does not name an instrument in this application.\n";
        return;
    }
    
    auto waveform = app_data.getWaveforms().getWaveform(waveform_name);
    if (!waveform) {
        out << waveform_name << " does not name a waveform in this application.\n";
        return;
    }
    
    auto envelope = app_data.getEnvelopes().getEnvelope(envelope_name);
    if (!envelope) {
        out << envelope_name << " does not name an envelope in this application.\n";
        return;
    }
    
    instrument->setWaveform(waveform);
    instrument->setEnvelope(envelope);
}

void put_frequency_in_register(ApplicationData& app_data) {
    double frequency = app_data.getDouble("Frequency: ");
    app_data.setDoubleRegister(0, frequency);
}

void recordInstrumentNoteUI(ApplicationData& app_data) {
    auto& out = app_data.getOutputStream();
    auto& instruments = app_data.getInstrumentarium();
    
    std::string name = app_data.getString("Instrument name: ");
    auto instrument = instruments.getInstrument(name);
    
    if (!instrument) {
        out << name << " does not name an instrument in this application.\n";
        return;
    }
    
    put_frequency_in_register(app_data);
    
    // Generate samples directly
    double frequency = app_data.getDoubleRegister(0);
    instrument->generateSamples(frequency,
                              app_data.getAudioTrack().getSeconds(),
                              app_data.getAudioTrack().getSamplesPerSecond(),
                              app_data.getAudioTrack());
    
    auto& channels = app_data.getChannels();
    channels.resize(2);
    channels[0] = app_data.getAudioTrack();
    channels[1] = app_data.getAudioTrack();
    
    std::string filename = app_data.getString("WAV filename: ");
    app_data.getWAVFile().writeFile(filename, channels);
}

int register_instrument_designer_commands(ApplicationData& app_data) {
    register_menu_test_commands(app_data);
    
    app_data.addAction(ActionFunctionData("list-waveforms", listWaveformsUI, 
        "List waveforms in the inventory."));
    app_data.addAction(ActionFunctionData("add-waveform", addWaveformUI, 
        "Add waveform to the inventory."));
    app_data.addAction(ActionFunctionData("edit-waveform", editWaveformUI, 
        "Edit waveform in the inventory."));
    
    app_data.addAction(ActionFunctionData("list-envelopes", listEnvelopesUI, 
        "List envelopes in the inventory."));
    app_data.addAction(ActionFunctionData("add-envelope", addEnvelopeUI, 
        "Add envelope to the inventory."));
    app_data.addAction(ActionFunctionData("edit-envelope", editEnvelopeUI, 
        "Edit envelope in the inventory."));
    
    app_data.addAction(ActionFunctionData("list-instruments", listInstrumentsUI, 
        "List instruments in the inventory."));
    app_data.addAction(ActionFunctionData("add-instrument", addInstrumentUI, 
        "Add instrument to the inventory."));
    app_data.addAction(ActionFunctionData("edit-instrument", editInstrumentUI, 
        "Edit instrument in the inventory."));
    
    app_data.addAction(ActionFunctionData("record-instrument-note", recordInstrumentNoteUI, 
        "Record a note for an instrument to a WAV file."));
    
    app_data.addAction(ActionFunctionData("configure-audio-track-and-wav-file", configure_audio_track_and_wav_file, 
        "Configure meta data for the audio track and WAV file."));
    
    return 0;
}

int instrument_designer(ApplicationData& app_data) {
    register_instrument_designer_commands(app_data);
    app_data.mainLoop();
    return 0;
} 