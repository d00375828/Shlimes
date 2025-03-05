#include "MenuData.h"
#include "ActionFunctionData.h"
#include <algorithm>

MenuData::MenuData() {}

void MenuData::addAction(const ActionFunctionData& function) {
    if (!actionExistsAux(function.getName())) {
        actions[function.getName()] = function;
    }
}

bool MenuData::actionExistsAux(const std::string& name) const {
    return actions.find(name) != actions.end();
}

const std::string MenuData::actionPrefix(const std::string& name) const {
    for (const auto& pair : actions) {
        const auto& action = pair.second;
        if (action.getPrefixLength() > 0 && 
            name.length() >= static_cast<std::size_t>(action.getPrefixLength()) &&
            pair.first.compare(0, action.getPrefixLength(), 
                             name, 0, action.getPrefixLength()) == 0) {
            return pair.first;
        }
    }
    return "";
}

bool MenuData::actionExists(const std::string& name) const {
    return actionExistsAux(name) || !actionPrefix(name).empty();
}

const ActionFunctionData& MenuData::getAction(const std::string& name) {
    static const ActionFunctionData default_action;
    
    if (actionExistsAux(name)) {
        return actions[name];
    }
    
    std::string prefix = actionPrefix(name);
    if (!prefix.empty()) {
        return actions[prefix];
    }
    
    return default_action;
}

void MenuData::printActionHelp(std::ostream& out) const {
    out << "Options are:\n";
    for (const auto& pair : actions) {
        const auto& action = pair.second;
        out << "  " << action.getName() << " - " << action.getDescription() << "\n";
    }
    out << "\n";
}

