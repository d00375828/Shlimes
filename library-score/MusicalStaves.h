#ifndef MUSICAL_STAVES_H
#define MUSICAL_STAVES_H

#include <map>
#include <string>
#include "MusicalStaff.h"

class MusicalStaves {
protected:
    std::map<std::string, MusicalStaff> mStaves;
    static MusicalStaff mStaticStaff; // For returning when key doesn't exist

public:
    // Constructors
    MusicalStaves();
    virtual ~MusicalStaves();
    
    // Methods required by the assignment
    void addStaff(const std::string& name, const MusicalStaff& staff);
    void removeStaff(const std::string& name);
    MusicalStaff& getStaff(const std::string& name);
    const MusicalStaff& getStaff(const std::string& name) const;
    unsigned int size() const;
    
    // Iteration support
    typedef std::map<std::string, MusicalStaff>::iterator iterator;
    typedef std::map<std::string, MusicalStaff>::const_iterator const_iterator;
    
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    
    // Existing methods for backward compatibility
    bool contains(const std::string& name) const;
    MusicalStaff& operator[](const std::string& name);
    const MusicalStaff& operator[](const std::string& name) const;
    void add(const std::string& name, const MusicalStaff& staff);
};

#endif // MUSICAL_STAVES_H 