#ifndef INSTRUMENTARIUM_H
#define INSTRUMENTARIUM_H

#include <string>
#include <map>
#include "Instrument.h"

class Instrumentarium {
public:
    typedef std::map<std::string, std::shared_ptr<Instrument>>::iterator iterator;
    typedef std::map<std::string, std::shared_ptr<Instrument>>::const_iterator const_iterator;

    Instrumentarium();
    virtual ~Instrumentarium();

    void addInstrument(const std::string& name, std::shared_ptr<Instrument> instrument);
    std::shared_ptr<Instrument> getInstrument(const std::string& name);
    
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

protected:
    std::map<std::string, std::shared_ptr<Instrument>> mInstrument;
};

#endif
