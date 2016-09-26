//
//  ActorController.h
//  Lost
//
//  Created by Furukawa on 2015/11/08.
//
//

#ifndef __Lost__ActorController__
#define __Lost__ActorController__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "Actor.h"
#include "GameController.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class ActorController
{
public:
    
    Actor *_targetActor;
    GameController *_gameController;
    
    ActorController();
    ~ActorController();
    
    static ActorController *_instance;
    static ActorController *getInstance();
    
    virtual bool init();
    void update(float delta);
};

#endif /* defined(__Lost__ActorController__) */
