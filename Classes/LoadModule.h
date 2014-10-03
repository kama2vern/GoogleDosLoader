//
//  LoadModule.h
//  DiverDark
//
//  Created by S_Wyvern on 2014/08/30.
//
//

#ifndef __DiverDark__LoadModule__
#define __DiverDark__LoadModule__

#include <iostream>
#include <map>

#include "json11.hpp"
#include "BaseModule.h"

class LoadModule : public BaseModule
{
public:
    LoadModule();
    void initializeLoadUrlList();
    
    bool isFinishedLoad();
    inline unsigned int getLoadCounter() {
        return load_counter;
    }
    
    json11::Json getMasterData(std::string key);
    
private:
    unsigned int load_counter;
    std::map<std::string, std::string> load_url_list;
    
    std::map<std::string, json11::Json> master_data;
};

#endif /* defined(__DiverDark__LoadModule__) */
