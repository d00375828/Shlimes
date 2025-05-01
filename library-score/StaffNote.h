#ifndef STAFF_NOTE_H
#define STAFF_NOTE_H

#include "Note.h"
#include <string>
#include <iostream>

class StaffNote {
protected:
    Note mNote;
    double mStart; // Number of whole notes since the beginning of the staff
    static thread_local bool mShowFrequency; // Thread-local flag to control frequency display

public:
    // Constructors
    StaffNote(); // defaults to default Note and 0.0 start
    StaffNote(const Note& note, const double start);
    
    // Accessors
    Note& getNote();
    const Note& getNote() const;
    double getStart() const;
    
    // Mutators
    void setStart(const double start);
    
    // Control frequency display in output
    static void setShowFrequency(bool show);
    static bool getShowFrequency();
};

// Stream operator
std::ostream& operator<<(std::ostream& os, const StaffNote& staff_note);

#endif // STAFF_NOTE_H 