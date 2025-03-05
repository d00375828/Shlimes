#include "EnvelopeFactory.h"
#include "ADEnvelope.h"
#include "ADSREnvelope.h"
#include <algorithm>

// Initialize static member
const std::vector<std::string> EnvelopeFactory::EnvelopeName = {"AD", "ADSR", "error"};

std::unique_ptr<Envelope> EnvelopeFactory::create(EnvelopeId id, const std::string& name) {
    switch (id) {
        case EN_AD:
            return std::make_unique<ADEnvelope>(name);
        case EN_ADSR:
            return std::make_unique<ADSREnvelope>(name);
        default:
            return nullptr;
    }
}

std::unique_ptr<Envelope> EnvelopeFactory::create(const std::string& id, const std::string& name) {
    return create(stringToEnvelopeId(id), name);
}

EnvelopeFactory::EnvelopeId EnvelopeFactory::stringToEnvelopeId(const std::string& id) {
    if (id == "AD") return EN_AD;
    if (id == "ADSR") return EN_ADSR;
    return EN_ERROR;
}

bool EnvelopeFactory::validStringId(const std::string& id) {
    return std::find(EnvelopeName.begin(), EnvelopeName.end(), id) != EnvelopeName.end();
}
