#ifndef ENVELOPEFACTORY_H
#define ENVELOPEFACTORY_H

#include <string>
#include <vector>
#include <memory>
#include "Envelope.h"

class EnvelopeFactory {
public:
    // Enumeration for envelope types
    enum EnvelopeId {
        EN_AD,
        EN_ADSR,
        EN_ERROR
    };

    // Vector of envelope names
    static const std::vector<std::string> EnvelopeName;

    // Factory methods
    static std::unique_ptr<Envelope> create(EnvelopeId id, const std::string& name);
    static std::unique_ptr<Envelope> create(const std::string& id, const std::string& name);
    
    // Helper methods
    static EnvelopeId stringToEnvelopeId(const std::string& id);
    static bool validStringId(const std::string& id);

    virtual ~EnvelopeFactory() = default;
};

#endif
