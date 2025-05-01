#include "Note.h"
#include "Frequency.h"
#include <sstream>
#include <algorithm>

// Global constant for flat note names
static const std::vector<std::string> g_names_flat = {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"};

// Constructors
Note::Note() : mName(""), mDuration(0.0) {
}

Note::Note(const std::string& full_note) : mName(""), mDuration(0.0) {
    set(full_note);
}

Note::Note(const std::string& name, const double& duration) : mName(""), mDuration(0.0) {
    setName(name);
    setDuration(duration);
}

Note::Note(const std::string& name, const std::string& duration_str) : mName(""), mDuration(0.0) {
    setName(name);
    setDuration(duration_str);
}

// Getters
const std::string& Note::getName() const {
    return mName;
}

const double& Note::getDuration() const {
    return mDuration;
}

double Note::getFrequency() const {
    return Frequency::getFrequency(mName);
}

// Setters
void Note::setName(const std::string& name) {
    // Verify the name is valid by checking if it has a frequency
    if (Frequency::getFrequency(name) > 0.0) {
        mName = name;
    }
}

void Note::setDuration(const double duration) {
    if (duration > 0.0) {
        mDuration = duration;
    }
}

void Note::setDuration(const std::string& duration_str) {
    if (duration_str.empty()) {
        return;
    }
    
    char first_char = duration_str[0];
    double base_duration = 0.0;
    
    // Get base duration from the first character
    switch (first_char) {
        case 'w': base_duration = WHOLE_NOTE; break;
        case 'h': base_duration = HALF_NOTE; break;
        case 'q': base_duration = QUARTER_NOTE; break;
        case 'e': base_duration = EIGHTH_NOTE; break;
        case 's': base_duration = SIXTEENTH_NOTE; break;
        default: return; // Invalid duration character
    }
    
    // Check for modifiers
    if (duration_str.length() == 2) {
        char modifier = duration_str[1];
        if (modifier == '.') {
            // Dotted note - 1.5 times the duration
            base_duration *= 1.5;
        } else if (modifier == 't') {
            // Triplet - 1/3 of the duration
            base_duration /= 3.0;
        } else {
            // Invalid modifier
            return;
        }
    } else if (duration_str.length() > 2) {
        // Invalid duration string (too long)
        return;
    }
    
    mDuration = base_duration;
}

void Note::set(const std::string& full_note) {
    std::string name, duration;
    splitString(full_note, name, duration);
    
    setName(name);
    setDuration(duration);
}

// Helper method
void Note::splitString(const std::string& full_note, std::string& name, std::string& duration) {
    if (full_note.empty()) {
        name = "";
        duration = "";
        return;
    }
    
    // Determine duration length (1 or 2 chars)
    size_t duration_length = 1;
    if (full_note.length() > 1) {
        char second_char = full_note[1];
        if (second_char == '.' || second_char == 't') {
            duration_length = 2;
        }
    }
    
    // Split the string
    if (full_note.length() <= duration_length) {
        duration = full_note;
        name = "";
    } else {
        duration = full_note.substr(0, duration_length);
        name = full_note.substr(duration_length);
    }
}

// Operator overload for output
std::ostream& operator<<(std::ostream& output_stream, const Note& note) {
    output_stream << note.getDuration() << " " << note.getName() << "(" << note.getFrequency() << ")";
    return output_stream;
}

// New methods for note run functionality
std::string Note::keyName() const {
    // Find the last non-digit character
    size_t last_non_digit = mName.find_last_not_of("0123456789");
    if (last_non_digit == std::string::npos) {
        return "";
    }
    return mName.substr(0, last_non_digit + 1);
}

int Note::octaveNumber() const {
    // Find the first digit
    size_t first_digit = mName.find_first_of("0123456789");
    if (first_digit == std::string::npos) {
        return -1;
    }
    
    std::string octave_str = mName.substr(first_digit);
    std::stringstream ss(octave_str);
    int octave;
    ss >> octave;
    return octave;
}

unsigned int Note::findKeyPositionFlat() const {
    std::string key = keyName();
    auto it = std::find(g_names_flat.begin(), g_names_flat.end(), key);
    if (it == g_names_flat.end()) {
        return g_names_flat.size() + 1;
    }
    return std::distance(g_names_flat.begin(), it);
}

std::string Note::relativeNoteNameFlat(unsigned int semitones) const {
    unsigned int current_pos = findKeyPositionFlat();
    if (current_pos >= g_names_flat.size()) {
        return "";
    }
    
    int octave = octaveNumber();
    if (octave < 0) {
        return "";
    }
    
    // Calculate new position and octave
    unsigned int new_pos = (current_pos + semitones) % g_names_flat.size();
    int octave_increase = (current_pos + semitones) / g_names_flat.size();
    octave += octave_increase;
    
    // Create the new note name
    std::stringstream ss;
    ss << g_names_flat[new_pos] << octave;
    return ss.str();
} 