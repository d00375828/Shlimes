#include "WaveformFactory.h"
#include "SineWaveform.h"
#include "SquareWaveform.h"
#include <algorithm>

// Initialize static member
const std::vector<std::string> WaveformFactory::WaveformName = {"sine", "square", "error"};

std::unique_ptr<Waveform> WaveformFactory::create(WaveformId id, const std::string& name) {
    switch (id) {
        case WF_SINE:
            return std::make_unique<SineWaveform>(name);
        case WF_SQUARE:
            return std::make_unique<SquareWaveform>(name);
        default:
            return nullptr;
    }
}

std::unique_ptr<Waveform> WaveformFactory::create(const std::string& id, const std::string& name) {
    return create(stringToWaveformId(id), name);
}

WaveformFactory::WaveformId WaveformFactory::stringToWaveformId(const std::string& id) {
    if (id == "sine") return WF_SINE;
    if (id == "square") return WF_SQUARE;
    return WF_ERROR;
}

bool WaveformFactory::validStringId(const std::string& id) {
    return std::find(WaveformName.begin(), WaveformName.end(), id) != WaveformName.end();
}
