//
//  TalkEventLayer.h
//  Lost
//
//  Created by Furukawa on 2015/11/12.
//
//

#ifndef __Lost__TalkEventLayer__
#define __Lost__TalkEventLayer__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "TalkLabel.h"
#include "GameLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class TalkEventLayer : public Layer
{
public:
    
    Sprite *_black;
    TalkLabel *_talkLabel;
    bool _isAppeared;
    
    Label *_chooseLabelA;
    Label *_chooseLabelB;
    
    GameLayer *_gameLayer;
    
    static TalkEventLayer *_instance;
    static TalkEventLayer *getInstance();
    static TalkEventLayer *create();
    virtual bool init();
    void update(float delta);
    
    void talk(string serif);
    void choose(string ansA, string ansB);
    void chooseEnd();
    
    void appear();
    void disappear();
    
    void fadeOut(float duration);
    void fadeIn(float duration);
};

#endif /* defined(__Lost__TalkEventLayer__) */
