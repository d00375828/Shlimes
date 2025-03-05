#include "ActionFunctionData.h"

// Default constructor
ActionFunctionData::ActionFunctionData()
    : name(""), function(nullptr), description(""), prefix_length(0) {}

// Constructor without prefix length
ActionFunctionData::ActionFunctionData(const std::string& name,
                                     const ActionFunctionType& function,
                                     const std::string& description)
    : name(name), function(function), description(description), prefix_length(0) {}

// Constructor with prefix length
ActionFunctionData::ActionFunctionData(const std::string& name,
                                     const ActionFunctionType& function,
                                     const std::string& description,
                                     const int prefix_length)
    : name(name), function(function), description(description), prefix_length(prefix_length) {}

// Getters
const std::string& ActionFunctionData::getName() const {
    return name;
}

ActionFunctionData::ActionFunctionType ActionFunctionData::getFunction() const {
    return function;
}

const std::string& ActionFunctionData::getDescription() const {
    return description;
}

int ActionFunctionData::getPrefixLength() const {
    return prefix_length;
}

// Setters
void ActionFunctionData::setName(const std::string& new_name) {
    name = new_name;
}

void ActionFunctionData::setFunction(ActionFunctionType new_function) {
    function = new_function;
}

void ActionFunctionData::setDescription(const std::string& new_description) {
    description = new_description;
}

void ActionFunctionData::setPrefixLength(const int length) {
    prefix_length = length;
}
