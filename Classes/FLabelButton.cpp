//
//  FLabelButton.cpp
//  Tokuten
//
//  Created by Furukawa on 2016/09/06.
//
//
#pragma execution_character_set("utf-8")

#include "FLabelButton.h"

FLabelButton *FLabelButton::create(string text, function<void()> func)
{
    FLabelButton *pRet = new FLabelButton();
    if(pRet && pRet->init(text, func))
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

bool FLabelButton::init(string text, function<void()> func)
{
    if ( !Scale9Sprite::init() ) return false;
    
    
    // タッチ
    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan = CC_CALLBACK_2(FLabelButton::onTouchBegan, this);
    _touchListener->onTouchMoved = CC_CALLBACK_2(FLabelButton::onTouchMoved, this);
    _touchListener->onTouchEnded = CC_CALLBACK_2(FLabelButton::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);
    _touchListener->setSwallowTouches(true);
    
    
    
    initWithFile("image/button_sikaku0.png");
    
    _label = Label::createWithTTF(text, "fonts/yamafont.ttf", 50);
    _label->setColor(Color3B(68, 53, 50));
    addChild(_label);
    
    auto size = _label->getBoundingBox().size;
    
    setContentSize(Size(size.width + 100, size.height + 100));
    _label->setPosition(getBoundingBox().size/2);
    
    _isPushed = false;
    
    _func = func;
    
    setCascadeOpacityEnabled(true);
    
    scheduleUpdate();
    return true;
}

void FLabelButton::update(float delta)
{
    
}

bool FLabelButton::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(getOpacity() == 0) return false;
    
    if(FCommon::containsWorldPoint(this, touch->getLocation()))
    {
        changeImage("image/button_sikaku1.png");
        
        _isPushed = true;
        
        return true;
    }
    
    return false;
}

void FLabelButton::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
}

void FLabelButton::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    changeImage("image/button_sikaku0.png");
    
    if(FCommon::containsWorldPoint(this, touch->getLocation()))
    {
        if(_isPushed)
        {
            _func();
        }
    }
    
    _isPushed = false;
}

void FLabelButton::changeImage(string fileName)
{
    initWithFile(fileName);
    
    auto size = _label->getBoundingBox().size;
    
    setContentSize(Size(size.width + 100, size.height + 100));
    _label->setPosition(getBoundingBox().size/2);

}





















