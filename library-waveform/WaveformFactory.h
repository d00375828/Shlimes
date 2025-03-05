#ifndef WAVEFORMFACTORY_H
#define WAVEFORMFACTORY_H

#include <string>
#include <vector>
#include <memory>
#include "Waveform.h"

class WaveformFactory {
public:
    // Enumeration for waveform types
    enum WaveformId {
        WF_SINE,
        WF_SQUARE,
        WF_ERROR
    };

    // Vector of waveform names
    static const std::vector<std::string> WaveformName;

    // Factory methods
    static std::unique_ptr<Waveform> create(WaveformId id, const std::string& name);
    static std::unique_ptr<Waveform> create(const std::string& id, const std::string& name);
    
    // Helper methods
    static WaveformId stringToWaveformId(const std::string& id);
    static bool validStringId(const std::string& id);

    virtual ~WaveformFactory() = default;
};

#endif
