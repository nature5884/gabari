//
//  GameLayer.h
//  Lost
//
//  Created by Furukawa on 2015/11/08.
//
//

#ifndef __Lost__GameLayer__
#define __Lost__GameLayer__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "MapManager.h"
#include "ActorManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class GameLayer : public Layer
{
public:
    
    MapManager *_mapManager;
    ActorManager *_actorManager;
    
    static GameLayer *create();
    virtual bool init();
    void update(float delta);
    
    void pauseWorld();
    void resumeWorld();
};

#endif /* defined(__Lost__GameLayer__) */
