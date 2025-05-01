#include "Instrumentarium.h"

Instrumentarium::Instrumentarium() {}

Instrumentarium::~Instrumentarium() {}

void Instrumentarium::addInstrument(const std::string& name, std::shared_ptr<Instrument> instrument) {
    mInstrument[name] = instrument;
}

std::shared_ptr<Instrument> Instrumentarium::getInstrument(const std::string& name) {
    if (mInstrument.find(name) == mInstrument.end()) {
        return nullptr;
    }
    return mInstrument[name];
}

Instrumentarium::iterator Instrumentarium::begin() {
    return mInstrument.begin();
}

Instrumentarium::const_iterator Instrumentarium::begin() const {
    return mInstrument.begin();
}

Instrumentarium::iterator Instrumentarium::end() {
    return mInstrument.end();
}

Instrumentarium::const_iterator Instrumentarium::end() const {
    return mInstrument.end();
}
