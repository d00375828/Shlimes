#ifndef WAVEFORMS_H
#define WAVEFORMS_H

#include <string>
#include <map>
#include "Waveform.h"
#include "memory"

class Waveforms {
public:

    typedef std::map<std::string, std::shared_ptr<Waveform>>::iterator iterator;
    typedef std::map<std::string, std::shared_ptr<Waveform>>::const_iterator const_iterator;

    Waveforms();
    virtual ~Waveforms();

    void addWaveform(const std::string& name, std::shared_ptr<Waveform> waveform);
    
    std::shared_ptr<Waveform> getWaveform(const std::string& name);
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;



protected:
    std::map<std::string, std::shared_ptr<Waveform>> mWaveform;

};

#endif
