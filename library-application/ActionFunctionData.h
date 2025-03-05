#ifndef ACTIONFUNCTIONDATA_H
#define ACTIONFUNCTIONDATA_H

#include <string>

// Forward declaration
class ApplicationData;

class ActionFunctionData {

public:
    // Function pointer type definition
    typedef void (*ActionFunctionType)(ApplicationData&);

    // Constructors
    ActionFunctionData();
    ActionFunctionData(const std::string& name, 
                      const ActionFunctionType& function, 
                      const std::string& description);
    ActionFunctionData(const std::string& name, 
                      const ActionFunctionType& function, 
                      const std::string& description, 
                      const int prefix_length);

    // Getters
    const std::string& getName() const;
    ActionFunctionType getFunction() const;
    const std::string& getDescription() const;
    int getPrefixLength() const;

    // Setters
    void setName(const std::string& name);
    void setFunction(ActionFunctionType function);
    void setDescription(const std::string& description);
    void setPrefixLength(const int length);

private:
    std::string name;
    ActionFunctionType function;
    std::string description;
    int prefix_length;
};

#endif
