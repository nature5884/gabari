//
//  MapManager.h
//  Lost
//
//  Created by Furukawa on 2015/11/08.
//
//

#ifndef __Lost__MapManager__
#define __Lost__MapManager__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "ActorManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class MapManager : public Layer
{
public:
    
    struct MapData
    {
        int mapWidth;
        int mapHeight;
        int gridSize;
        map<Vec2, int> mapData;
        map<int, string> chipFileName;
        map<string, int> constValue;
        map<Vec2, Sprite*> tileData;
    };
    
    Sprite *_black;
    
    MapData _mapData;
    ActorManager *_actorManager;
    
    static MapManager *_instance;
    static MapManager *getInstance();
    static MapManager *create();
    virtual bool init();
    void update(float delta);
    
    void transitionMap(int mapNo);
    
    void follow(Node *target);
};

#endif /* defined(__Lost__MapManager__) */
