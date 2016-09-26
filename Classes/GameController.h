//
//  GameController.h
//  Lost
//
//  Created by Furukawa on 2015/11/08.
//
//

#ifndef __Lost__GameController__
#define __Lost__GameController__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "UISpriteButton.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class GameController : public Layer
{
public:
    static GameController *_instance;
    
    static GameController *getInstance();
    static GameController *create();
    virtual bool init();
    void update(float delta);
    
    UISpriteButton *createButton(string mark);
    bool maru();
    bool batsu();
    bool right();
    bool left();
    
    bool maru(int pushedFrame);
    bool batsu(int pushedFrame);
    bool left(int pushedFrame);
    bool right(int pushedFrame);
    
    bool maruReleased();
    bool batsuReleased();
    bool leftReleased();
    bool rightReleased();
    
    int getMaruPushCount();
    int getBatsuPushCount();
    int getRightPushCount();
    int getLeftPushCount();
    
    float getUIHeight();
    
    
private:
    
    UISpriteButton *_leftButton;
    UISpriteButton *_rightButton;
    UISpriteButton *_maruButton;
    UISpriteButton *_batsuButton;
    
    Sprite *_uiBaseSp;
    
    UISpriteButton *initButton(string mark, Vec2 pos, EventKeyboard::KeyCode keyCode);
};

#endif /* defined(__Lost__GameController__) */
