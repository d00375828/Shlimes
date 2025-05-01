#include "StaffNote.h"

// Initialize the static member
thread_local bool StaffNote::mShowFrequency = true;

// Constructors
StaffNote::StaffNote() : mNote(), mStart(0.0) {
}

StaffNote::StaffNote(const Note& note, const double start) : mNote(note), mStart(0.0) {
    setStart(start);
}

// Accessors
Note& StaffNote::getNote() {
    return mNote;
}

const Note& StaffNote::getNote() const {
    return mNote;
}

double StaffNote::getStart() const {
    return mStart;
}

// Mutators
void StaffNote::setStart(const double start) {
    if (start >= 0.0) {
        mStart = start;
    }
}

// Frequency display control
void StaffNote::setShowFrequency(bool show) {
    mShowFrequency = show;
}

bool StaffNote::getShowFrequency() {
    return mShowFrequency;
}

// Stream operator
std::ostream& operator<<(std::ostream& os, const StaffNote& staff_note) {
    os << staff_note.getStart() << " " 
       << staff_note.getNote().getDuration() << " " 
       << staff_note.getNote().getName();
    
    // Add frequency information in parentheses if enabled
    if (StaffNote::getShowFrequency()) {
        if (!staff_note.getNote().getName().empty()) {
            os << "(" << staff_note.getNote().getFrequency() << ")";
        } else {
            os << "(0)";  // Special case for empty note name
        }
    }
    
    return os;
}