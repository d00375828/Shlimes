#include "MusicalStaves.h"
#include <stdexcept>

// Initialize static member
MusicalStaff MusicalStaves::mStaticStaff;

// Constructors
MusicalStaves::MusicalStaves() : mStaves() {
}

MusicalStaves::~MusicalStaves() {
    // Nothing to clean up
}

// Methods required by the assignment
void MusicalStaves::addStaff(const std::string& name, const MusicalStaff& staff) {
    mStaves[name] = staff;
}

void MusicalStaves::removeStaff(const std::string& name) {
    mStaves.erase(name);
}

MusicalStaff& MusicalStaves::getStaff(const std::string& name) {
    if (contains(name)) {
        return mStaves.at(name);
    }
    return mStaticStaff;
}

const MusicalStaff& MusicalStaves::getStaff(const std::string& name) const {
    if (contains(name)) {
        return mStaves.at(name);
    }
    return mStaticStaff;
}

unsigned int MusicalStaves::size() const {
    return static_cast<unsigned int>(mStaves.size());
}

// Iteration support
MusicalStaves::iterator MusicalStaves::begin() {
    return mStaves.begin();
}

MusicalStaves::const_iterator MusicalStaves::begin() const {
    return mStaves.begin();
}

MusicalStaves::iterator MusicalStaves::end() {
    return mStaves.end();
}

MusicalStaves::const_iterator MusicalStaves::end() const {
    return mStaves.end();
}

// Existing methods for backward compatibility
bool MusicalStaves::contains(const std::string& name) const {
    return mStaves.find(name) != mStaves.end();
}

MusicalStaff& MusicalStaves::operator[](const std::string& name) {
    if (!contains(name)) {
        throw std::runtime_error("MusicalStaff not found: " + name);
    }
    return mStaves.at(name);
}

const MusicalStaff& MusicalStaves::operator[](const std::string& name) const {
    if (!contains(name)) {
        throw std::runtime_error("MusicalStaff not found: " + name);
    }
    return mStaves.at(name);
}

void MusicalStaves::add(const std::string& name, const MusicalStaff& staff) {
    addStaff(name, staff);
} 