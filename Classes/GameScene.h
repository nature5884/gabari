//
//  GameScene.h
//  Lost
//
//  Created by Furukawa on 2015/11/08.
//
//

#ifndef __Lost__GameScene__
#define __Lost__GameScene__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "GameController.h"
#include "GameLayer.h"
#include "TalkEventLayer.h"
#include "FCommon.h"
#include "FDotLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class GameScene : public FDotLayer
{
public:
    static Scene *createScene();
    static GameScene *create();
    virtual bool init();
    void update(float delta);
    
    GameController *_controller;
    GameLayer *_gameLayer;
    
    TalkEventLayer *_talkEventLayer;
    
};

#endif /* defined(__Lost__GameScene__) */
