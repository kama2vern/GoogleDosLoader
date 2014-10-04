//
//  ModuleLocator.cpp
//  DiverDark
//
//  Created by S_Wyvern on 2014/08/23.
//
//

#include "ModuleLocator.h"

ModuleLocator* ModuleLocator::instance;

void ModuleLocator::registerModule(std::string key, BaseModule *module)
{
    modules.insert(std::make_pair(key, module));
}