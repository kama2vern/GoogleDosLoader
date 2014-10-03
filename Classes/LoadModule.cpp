//
//  LoadModule.cpp
//  DiverDark
//
//  Created by S_Wyvern on 2014/08/30.
//
//

#include <cocos2d.h>
#include <network/HttpClient.h>

#include "LoadModule.h"

USING_NS_CC;
using namespace network;

LoadModule::LoadModule() :
BaseModule()
{
    this->initializeLoadUrlList();
    
    auto it = load_url_list.begin();
    for (;it != load_url_list.end(); ++it) {
        auto key = it->first;
        auto url = it->second;
        
        HttpRequest* request = new HttpRequest();
        request->setUrl(url.c_str());
        request->setRequestType(HttpRequest::Type::GET);
        request->setResponseCallback([=](HttpClient* client, HttpResponse* response) {
            if (!response) {
                return ;
            }
            
            std::string err;
            std::string responseString(response->getResponseData()->begin(), response->getResponseData()->end());
            auto jsonData = json11::Json::parse(responseString, err);
            
            CCLOG("%s", jsonData.dump().c_str());
            
            std::string key = response->getHttpRequest()->getTag();
            this->master_data.insert(std::make_pair(key, jsonData));
            this->load_counter -= 1;
        });
        
        request->setTag(key.c_str());
        HttpClient::getInstance()->send(request);
        request->release();
    }
}

void LoadModule::initializeLoadUrlList()
{
    load_url_list.insert(std::make_pair("enemy","https://script.google.com/macros/s/AKfycbwyEe85VVRb80hgOhRVEjvtbMoZwB35DIza_iLVa1wOhldNUgM0/exec"));
    load_url_list.insert(std::make_pair("command","https://script.google.com/macros/s/AKfycbwP_FQSt1ugWEfQFVbwfAJS1_OZ0dJtHokgQdmMimPA7Sblt5o/exec"));
    load_url_list.insert(std::make_pair("story", "https://script.google.com/macros/s/AKfycbylr1GnxZx0HqJriZXwUJBd0PZPAn9ApcAWQznKllpCZVCWLVc/exec"));
    
    load_counter = load_url_list.size();
}

bool LoadModule::isFinishedLoad()
{
    return (load_counter == 0);
}

json11::Json LoadModule::getMasterData(std::string key)
{
    auto it = master_data.find(key);
    if (it == master_data.end()) {
        throw "master data not found";
    }
    return it->second;
}