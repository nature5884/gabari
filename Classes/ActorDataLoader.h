//
//  ActorDataLoader.h
//  ActorsDataLoader
//
//  Created by Furukawa on 2015/07/01.
//  Copyright (c) 2015年 Furukawa. All rights reserved.
//

#ifndef __ActorsDataLoader__ActorDataLoader__
#define __ActorsDataLoader__ActorDataLoader__

#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include "Actor.h"

using namespace std;

class ActorDataLoader
{
public:
    
    static ActorDataLoader *instance;
    static ActorDataLoader *getInstance();
    
    ActorDataLoader();
    ~ActorDataLoader();
    
    vector<Actor::ActorData> getActorDataFromFileName(string fileName);
    vector<Actor::ActorData> getActorData();
    int getActorNoFromName(string name);
    Actor::ActorData getActorDataFromNo(int n);
    
private:
    
    vector<Actor::ActorData> _actData;
    
    void disp(vector<vector<string>> data);
    vector<vector<vector<string>>> getDataFromFile(string fileName);
    vector<string> getStringList(string data);
    map<string, int> getMapList(string data);
    
};

#endif /* defined(__ActorsDataLoader__ActorDataLoader__) */
