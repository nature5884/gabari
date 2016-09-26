//
//  MapDataLoader.h
//  Lost
//
//  Created by Furukawa on 2015/11/08.
//
//

#ifndef __Lost__MapDataLoader__
#define __Lost__MapDataLoader__

#include "cocos2d.h"
#include "MapManager.h"

using namespace cocos2d;
using namespace std;

class MapDataLoader
{
public:
    
    struct NameAndInt
    {
        string name;
        int value;
    };
    
    struct StringAndString
    {
        string strA;
        string strB;
    };
    
    MapManager::MapData _mapData;
    
    static MapDataLoader *_instance;
    static MapDataLoader *getInstance();
    
    vector<string> getLineList(string strData);
    MapManager::MapData getMapData(string fileName);
    
    StringAndString getStringAndString(string str);
    
    map<Vec2, int> getMapArrayFromString(string str, int w, int h);
};

#endif /* defined(__Lost__MapDataLoader__) */
