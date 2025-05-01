#ifndef FREQUENCY_H
#define FREQUENCY_H

#include <string>
#include <map>

class Frequency {
public:
    // Public methods
    static double getFrequency(const std::string& note);

protected:
    // Protected data members
    static double trt; // The twelfth root of two
    static std::map<std::string, double> smFrequencies; // Map from note names to frequencies
    
    // Protected methods
    static double computeFactor(const unsigned int& octaves, const unsigned int& keys);
    static double moveLeft(const double& frequency, const unsigned int& octaves, const unsigned int& keys);
    static double moveRight(const double& frequency, const unsigned int& octaves, const unsigned int& keys);
    static std::map<std::string, double> generateFrequencies();
};

#endif // FREQUENCY_H 