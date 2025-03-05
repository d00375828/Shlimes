#include "Envelopes.h"

Envelopes::Envelopes() {}

Envelopes::~Envelopes() {}

void Envelopes::addEnvelope(const std::string& name, std::shared_ptr<Envelope> envelope) {
    mEnvelope[name] = envelope;
}

std::shared_ptr<Envelope> Envelopes::getEnvelope(const std::string& name) {
    if (mEnvelope.find(name) == mEnvelope.end()) {
        return nullptr;
    }
    return mEnvelope[name];
}

Envelopes::iterator Envelopes::begin() {
    return mEnvelope.begin();
}

Envelopes::const_iterator Envelopes::begin() const {
    return mEnvelope.begin();
}

Envelopes::iterator Envelopes::end() {
    return mEnvelope.end();
}

Envelopes::const_iterator Envelopes::end() const {
    return mEnvelope.end();
}
