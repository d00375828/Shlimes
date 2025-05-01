#include "MusicalStaff.h"
#include <algorithm>

// Default constructor
MusicalStaff::MusicalStaff() 
    : mName(""), mInstrument(nullptr), mNotes() {
}

// Constructor with instrument
MusicalStaff::MusicalStaff(std::shared_ptr<Instrument> instrument)
    : mName(""), mInstrument(instrument), mNotes() {
}

// Constructor with name and instrument
MusicalStaff::MusicalStaff(const std::string& name, std::shared_ptr<Instrument> instrument)
    : mName(name), mInstrument(instrument), mNotes() {
}

// Copy constructor
MusicalStaff::MusicalStaff(const MusicalStaff& src)
    : mName(src.mName), mInstrument(src.mInstrument), mNotes(src.mNotes) {
}

// Destructor
MusicalStaff::~MusicalStaff() {
    // Empty implementation
}

// String representation
std::string MusicalStaff::toString() const {
    std::string instrument_name = "";
    if (mInstrument) {
        instrument_name = mInstrument->getName();
    }
    return mName + " " + instrument_name;
}

// Accessors
const std::string& MusicalStaff::getName() const {
    return mName;
}

std::shared_ptr<Instrument> MusicalStaff::getInstrument() {
    return mInstrument;
}

std::shared_ptr<const Instrument> MusicalStaff::getInstrument() const {
    return mInstrument;
}

const std::vector<StaffNote>& MusicalStaff::getNotes() const {
    return mNotes;
}

// Mutators
void MusicalStaff::setName(const std::string& name) {
    mName = name;
}

void MusicalStaff::setInstrument(std::shared_ptr<Instrument> instrument) {
    mInstrument = instrument;
}

void MusicalStaff::addNote(const StaffNote& note) {
    mNotes.push_back(note);
}

// Rendering
double MusicalStaff::getDurationInWholeNotes() const {
    double max_end = 0.0;
    
    for (const auto& note : mNotes) {
        double note_end = note.getStart() + note.getNote().getDuration();
        if (note_end > max_end) {
            max_end = note_end;
        }
    }
    
    return max_end;
}

void MusicalStaff::render(const TimeSignature& time_signature, const double tempo, 
                         const int samples_per_second, AudioTrack& track) const {
    if (!mInstrument) {
        return;
    }
    
    // Calculate seconds per whole note
    double seconds_per_whole_note = time_signature.getBeatValue() * 60.0 / tempo;
    
    // Configure the track
    track.setSamplesPerSecond(samples_per_second);
    track.setSeconds(getDurationInWholeNotes() * seconds_per_whole_note);
    
    // Render each note
    for (const auto& staff_note : mNotes) {
        // Get note properties
        double frequency = staff_note.getNote().getFrequency();
        double duration_in_whole_notes = staff_note.getNote().getDuration();
        double start_in_whole_notes = staff_note.getStart();
        
        // Convert duration from whole notes to seconds
        double duration_in_seconds = duration_in_whole_notes * seconds_per_whole_note;
        
        // Create a temporary track for this note
        AudioTrack temp_track;
        temp_track.setSamplesPerSecond(samples_per_second);
        temp_track.setSeconds(duration_in_seconds);
        
        // Generate samples for this note
        mInstrument->generateSamples(frequency, duration_in_seconds, samples_per_second, temp_track);
        
        // Add this note to the main track at the appropriate time
        double start_time_in_seconds = start_in_whole_notes * seconds_per_whole_note;
        track.addAt(temp_track, start_time_in_seconds);
    }
}

// Free function
std::ostream& operator<<(std::ostream& output_stream, const MusicalStaff& staff) {
    output_stream << staff.toString();
    return output_stream;
} 