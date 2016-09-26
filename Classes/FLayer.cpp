﻿//
//  FLayer.cpp
//  Collapse
//
//  Created by Furukawa on 2015/11/20.
//
//
#pragma execution_character_set("utf-8")

#include "FLayer.h"

FLayer *FLayer::create()
{
    FLayer *pRet = new FLayer();
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

bool FLayer::init()
{
    if ( !Layer::init() ) return false;
    
    // タッチ
    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan = CC_CALLBACK_2(FLayer::onTouchBegan, this);
    _touchListener->onTouchMoved = CC_CALLBACK_2(FLayer::onTouchMoved, this);
    _touchListener->onTouchEnded = CC_CALLBACK_2(FLayer::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);
    //    touchListener->setSwallowTouches(true);
    
    
    // キーボード
    auto keyListener = cocos2d::EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(FLayer::onKeyPressed, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(FLayer::onKeyReleased, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
    
    
    
    scheduleUpdate();
    return true;
}

void FLayer::update(float delta)
{
    
}


bool FLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
    _touchPos = touch->getLocation();
    
    return true;
}

void FLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    _touchPos = touch->getLocation();
    
}

void FLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    _touchPos = touch->getLocation();
    
}

void FLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event)
{
    
}

void FLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event)
{
    
}