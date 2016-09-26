//
//  UISpriteButton.h
//  FPaint
//
//  Created by Furukawa on 2015/05/04.
//
//
#pragma execution_character_set("utf-8")

#ifndef __FPaint__UISpriteButton__
#define __FPaint__UISpriteButton__

#include "cocos2d.h"

using namespace cocos2d;
//using namespace CocosDenshion;
using namespace std;

class UISpriteButton : public Sprite
{
public:
    UISpriteButton();
    ~UISpriteButton();
    
    static UISpriteButton *create();
    static UISpriteButton *create(function<void()> pushed);
    static UISpriteButton *create(function<void()> pushed, function<void()> released);
    static UISpriteButton *create(string fileName);
    static UISpriteButton *create(string neutral, string pushed ,string mark);
    static UISpriteButton *create(string fileName, function<void()> pushed);
    static UISpriteButton *create(string fileName, function<void()> pushed, function<void()> released);
    
    virtual bool init();
    virtual bool init(function<void()> pushed);
    virtual bool init(function<void()> pushed, function<void()> released);
    virtual bool init(string fileName);
    virtual bool init(string neutral, string pushed ,string mark);
    virtual bool init(string fileName, function<void()> pushed);
    virtual bool init(string fileName, function<void()> pushed, function<void()> released);
    
    void setBaseScale(float scale);
    void update(float delta);
    
    void setKey(EventKeyboard::KeyCode keyCode);
    
    void buttonPushed();
    void buttonReleased();
    
    function<void ()> _pushed;
    function<void ()> _released;
    
    float _baseScale;
    
    bool _isPushedFrame;
    bool _isReleasedFrame;
    
    bool _isPushed;
    bool _isPushOnly;
    bool _isEnable;
    bool _isEnablePushAction;
    
    int _pushCount;
    
    Sprite *_markSp;
    
    Texture2D *_neutralTex;
    Texture2D *_pushedTex;
    
    EventKeyboard::KeyCode _key;
    
    virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchEnded(Touch *touch, Event *event);
    virtual void onTouchMoved(Touch *touch, Event *event);
    

    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
};

#endif /* defined(__FPaint__UISpriteButton__) */
