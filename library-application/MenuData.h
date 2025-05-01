#ifndef MENUDATA_H
#define MENUDATA_H

#include <map>
#include <string>
#include <iostream>
#include "ActionFunctionData.h"


// Forward declaration
class ActionFunctionData;

class MenuData {
protected:
    bool actionExistsAux(const std::string& name) const;
    const std::string actionPrefix(const std::string& name) const;

public:
    MenuData();
    void addAction(const ActionFunctionData& function);
    bool actionExists(const std::string& name) const;
    const ActionFunctionData& getAction(const std::string& name);
    void printActionHelp(std::ostream& out) const;

private:
    std::map<std::string, ActionFunctionData> actions;
};

#endif
