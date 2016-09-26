//
//  UISpriteButton.cpp
//  FPaint
//
//  Created by Furukawa on 2015/05/04.
//
//
#pragma execution_character_set("utf-8")

#include "UISpriteButton.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "FCommon.h"

using namespace FGeneral;

UISpriteButton::UISpriteButton()
{
    
}

UISpriteButton::~UISpriteButton()
{
    if(_neutralTex) delete _neutralTex;
    if(_neutralTex) delete _pushedTex;
}

UISpriteButton *UISpriteButton::create()
{
    UISpriteButton *pRet = new UISpriteButton();
    if(pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

UISpriteButton *UISpriteButton::create(function<void()> pushed)
{
    auto pRet = create();
    pRet->_pushed = pushed;
    return pRet;
}
UISpriteButton *UISpriteButton::create(function<void()> pushed, function<void()> released)
{
    auto pRet = create();
    pRet->_pushed = pushed;
    pRet->_released = released;
    return pRet;
}
UISpriteButton *UISpriteButton::create(string fileName)
{
    UISpriteButton *pRet = new UISpriteButton();
    if(pRet && pRet->init(fileName))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

UISpriteButton *UISpriteButton::create(string neutral, string pushed ,string mark)
{
    UISpriteButton *pRet = new UISpriteButton();
    if(pRet && pRet->init(neutral, pushed, mark))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

UISpriteButton *UISpriteButton::create(string fileName, function<void()> pushed)
{
    auto pRet = create(fileName);
    pRet->_pushed = pushed;
    return pRet;
}
UISpriteButton *UISpriteButton::create(string fileName, function<void()> pushed, function<void()> released)
{
    auto pRet = create(fileName);
    pRet->_pushed = pushed;
    pRet->_released = released;
    return pRet;
}


bool UISpriteButton::init()
{
    if ( !Sprite::init() ) return false;
    
    
    // タッチ
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(UISpriteButton::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(UISpriteButton::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(UISpriteButton::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    touchListener->setSwallowTouches(true);
    
    
    // キーボード
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(UISpriteButton::onKeyPressed, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(UISpriteButton::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
    
    _isReleasedFrame = false;
    _isPushed = false;
    _isPushOnly = false;
    _baseScale = 1.0f;
    _isEnable = true;
    _isEnablePushAction = false;
    
    _neutralTex = NULL;
    _pushedTex = NULL;
    
    scheduleUpdate();
    
    
    return true;
}

bool UISpriteButton::init(function<void()> pushed)
{
    init();
    setTextureRect(cocos2d::Rect(0, 0, 100, 100));
    
    _pushed = pushed;
    
    return true;
}

bool UISpriteButton::init(function<void()> pushed, function<void()> released)
{
    init();
    setTextureRect(cocos2d::Rect(0, 0, 100, 100));
    
    _pushed = pushed;
    _released = released;
    
    return true;
}

bool UISpriteButton::init(string fileName)
{
    init();
    initWithFile(fileName);
    
    return true;
}

bool UISpriteButton::init(string neutral, string pushed ,string mark)
{
    init();
    
    Image *neutralImage = new Image();
    neutralImage->initWithImageFile(neutral);
    _neutralTex = new Texture2D();
    _neutralTex->initWithImage(neutralImage);
    
    Image *pushedImage = new Image();
    pushedImage->initWithImageFile(pushed);
    _pushedTex = new Texture2D();
    _pushedTex->initWithImage(pushedImage);
    
    initWithTexture(_neutralTex);
    
    _markSp = Sprite::create(mark);
    _markSp->setPosition(getBoundingBox().size/2);
    addChild(_markSp);
    
    return true;
}

bool UISpriteButton::init(string fileName, function<void()> pushed)
{
    init(fileName);
    _pushed = pushed;
    
    return true;
}

bool UISpriteButton::init(string fileName, function<void()> pushed, function<void()> released)
{
    init(fileName);
    _pushed = pushed;
    _released = released;
    
    return true;
}

void UISpriteButton::update(float delta)
{
    if(!_isPushed && _pushCount > 0) _isReleasedFrame = true;
    else _isReleasedFrame = false;
    
    if(_isPushed && _pushCount == 0) _isPushedFrame = true;
    else _isPushedFrame = false;
    
    if(_isPushed) _pushCount ++;
    else _pushCount = 0;
}

void UISpriteButton::setBaseScale(float scale)
{
    _baseScale = scale;
    setScale(_baseScale);
}

bool UISpriteButton::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(!_isEnable) return false;
    
    if(FCommon::containsWorldPoint(this, touch->getLocation()))
    {
        buttonPushed();
        return true;
    }
    else
    {
        return false;
    }
    
    return false;
}

void UISpriteButton::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
}

void UISpriteButton::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(!_isEnable) return;
    
    buttonReleased();
}

void UISpriteButton::setKey(EventKeyboard::KeyCode keyCode)
{
    _key = keyCode;
}

void UISpriteButton::buttonPushed()
{
    if(!_isEnable) return;
    
    if(_isEnablePushAction)
    {
        if(!_isPushOnly)
        {
            runAction(EaseOut::create(ScaleTo::create(0.07, 0.7 * _baseScale), 2));
        }
        else
        {
            auto act = EaseInOut::create(Sequence::create(ScaleTo::create(0.1, 0.7 * _baseScale),
                                                          ScaleTo::create(0.1, 1.0 * _baseScale),
                                                          NULL), 2);
            act->setTag(1);
            this->stopActionByTag(1);
            this->runAction(act);
        }
    }
    
    if(_pushedTex)
    {
        setTexture(_pushedTex);
        _markSp->setPosition(_markSp->getPosition() - cocos2d::Vec2(0, 2));
    }
    _isPushed = true;
    if(_pushed) _pushed();
}

void UISpriteButton::buttonReleased()
{
    if(!_isEnable) return;
    
//    if(_isPushed)
    {
        if(_isEnablePushAction)
        {
            if(!_isPushOnly)
            {
                //            SimpleAudioEngine::getInstance()->playEffect("se/peko.mp3");
                runAction(EaseOut::create(ScaleTo::create(0.07, 1.0 * _baseScale), 2));
            }
        }
        
        if(_neutralTex)
        {
            setTexture(_neutralTex);
            _markSp->setPosition(getBoundingBox().size/2);
        }
        
    }
    if(_isPushed)
    {
        _isPushed = false;
        if(_released) _released();
    }
}

void UISpriteButton::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
    if(keyCode == _key)
    {
        buttonPushed();
    }
}

void UISpriteButton::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if(keyCode == _key)
    {
        buttonReleased();
    }
}





