#ifndef ENVELOPES_H
#define ENVELOPES_H

#include <string>
#include <map>
#include "Envelope.h"
#include "memory"

class Envelopes {
public:
    typedef std::map<std::string, std::shared_ptr<Envelope>>::iterator iterator;
    typedef std::map<std::string, std::shared_ptr<Envelope>>::const_iterator const_iterator;

    Envelopes();
    virtual ~Envelopes();

    void addEnvelope(const std::string& name, std::shared_ptr<Envelope> envelope);
    std::shared_ptr<Envelope> getEnvelope(const std::string& name);
    
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

protected:
    std::map<std::string, std::shared_ptr<Envelope>> mEnvelope;
};

#endif
