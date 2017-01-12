//
//  ActorManager.h
//  Lost
//
//  Created by Furukawa on 2015/11/08.
//
//

#ifndef __Lost__ActorManager__
#define __Lost__ActorManager__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "Actor.h"
#include "ActorDataLoader.h"
#include "ActorController.h"
#include "WarpMachine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class ActorManager : public Layer
{
public:
    
    ActorDataLoader *_actorDataLodaer;
    ActorController *_actorController;
    
    static ActorManager *_instance;
    static ActorManager *getInstance();
    static ActorManager *create();
    virtual bool init();
    void update(float delta);
    
    Actor *createActor(int no, Vec2 pos);
    WarpMachine *createWarpMachine(int trans, Vec2 pos);
    void damageCheck();
};

#endif /* defined(__Lost__ActorManager__) */
