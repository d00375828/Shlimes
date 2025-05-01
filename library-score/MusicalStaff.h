#ifndef MUSICAL_STAFF_H
#define MUSICAL_STAFF_H

#include <string>
#include <vector>
#include <memory>
#include "Instrument.h"
#include "StaffNote.h"
#include "TimeSignature.h"
#include "AudioTrack.h"

class MusicalStaff {
protected:
    std::string mName;
    std::shared_ptr<Instrument> mInstrument;
    std::vector<StaffNote> mNotes;

public:
    // Constructors and destructor
    MusicalStaff(); // defaults to empty name, nullptr for Instrument, and no notes
    MusicalStaff(std::shared_ptr<Instrument> instrument); // empty name and no notes, parameter used to initialize Instrument
    MusicalStaff(const std::string& name, std::shared_ptr<Instrument> instrument); // no notes, parameters initialize name and Instrument
    MusicalStaff(const MusicalStaff& src); // copy all data members from src
    virtual ~MusicalStaff(); // Required, needs empty block of code
    
    // Assignment operator
    MusicalStaff& operator=(const MusicalStaff& rhs) = default;
    
    // Conversion to string
    virtual std::string toString() const; // Format is "name_of_staff name_of_instrument"
    
    // Accessors
    const std::string& getName() const;
    std::shared_ptr<Instrument> getInstrument();
    std::shared_ptr<const Instrument> getInstrument() const;
    const std::vector<StaffNote>& getNotes() const;
    
    // Mutators
    void setName(const std::string& name);
    void setInstrument(std::shared_ptr<Instrument> instrument);
    void addNote(const StaffNote& note);
    
    // Staff rendering
    double getDurationInWholeNotes() const; // Computes the end of the last note to finish, in whole notes
    void render(const TimeSignature& time_signature, const double tempo, const int samples_per_second, AudioTrack& track) const;
};

// Stream operator
std::ostream& operator<<(std::ostream& output_stream, const MusicalStaff& staff);

#endif // MUSICAL_STAFF_H 