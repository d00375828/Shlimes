#include "Waveforms.h"

Waveforms::Waveforms() {}

Waveforms::~Waveforms() {}

void Waveforms::addWaveform(const std::string& name, std::shared_ptr<Waveform> waveform) {
    mWaveform[name] = waveform;
}
std::shared_ptr<Waveform> Waveforms::getWaveform(const std::string& name) {
    if (mWaveform.find(name) == mWaveform.end()) {
        return nullptr;
    }
    return mWaveform[name];
}

void Waveforms::removeWaveform(const std::string& name) {
    mWaveform.erase(name);
}

Waveforms::iterator Waveforms::begin() {
    return mWaveform.begin();
}

Waveforms::const_iterator Waveforms::begin() const {
    return mWaveform.begin();
}

Waveforms::iterator Waveforms::end() {
    return mWaveform.end();
}

Waveforms::const_iterator Waveforms::end() const {
    return mWaveform.end();
}



