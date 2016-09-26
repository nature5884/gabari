//
//  TalkEventLayer.cpp
//  Lost
//
//  Created by Furukawa on 2015/11/12.
//
//

#include "TalkEventLayer.h"
#include "GameController.h"

TalkEventLayer *TalkEventLayer::_instance;

TalkEventLayer *TalkEventLayer::getInstance()
{
    if(!_instance)
    {
        _instance = TalkEventLayer::create();
    }
    
    return _instance;
}

TalkEventLayer *TalkEventLayer::create()
{
    TalkEventLayer *pRet = new TalkEventLayer();
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

bool TalkEventLayer::init()
{
    if ( !Layer::init() ) return false;
    
    _black = Sprite::create();
    _black->setTextureRect(Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
    _black->setAnchorPoint(Vec2::ZERO);
    _black->setOpacity(0);
    _black->setColor(Color3B::BLACK);
    addChild(_black);
    
    _talkLabel = TalkLabel::create("", "fonts/misaki_gothic.ttf", 8);
//    _talkLabel->setAnchorPoint(Vec2(0, 1));
    _talkLabel->setPosition(Vec2(designResolutionSize.width * 0.5, designResolutionSize.height * 0.7));
    addChild(_talkLabel);
    
    _isAppeared = false;
    
    
    // 選択肢に使うLabel
    _chooseLabelA = Label::createWithTTF("", "fonts/misaki_gothic.ttf", 8);
    _chooseLabelB = Label::createWithTTF("", "fonts/misaki_gothic.ttf", 8);
    _chooseLabelA->setPosition(Vec2(designResolutionSize.width * 0.4, designResolutionSize.height * 0.5));
    _chooseLabelB->setPosition(Vec2(designResolutionSize.width * 0.4, designResolutionSize.height * 0.4));
    _chooseLabelA->setAnchorPoint(Vec2(0, 0.5));
    _chooseLabelB->setAnchorPoint(Vec2(0, 0.5));
    addChild(_chooseLabelA);
    addChild(_chooseLabelB);
    
    
    
    scheduleUpdate();
    return true;
}

void TalkEventLayer::update(float delta)
{
    
}


void TalkEventLayer::talk(string serif)
{
    appear();
    
    runAction(Sequence::create(DelayTime::create(0.5),
                               CallFunc::create([=]()
                                                {
                                                    _isAppeared = true;
                                                    _talkLabel->startRunString(serif, 0.03);
                                                }),
                               NULL));
}

void TalkEventLayer::choose(string ansA, string ansB)
{
    _chooseLabelA->setString("◯　" + ansA);
    _chooseLabelB->setString("Ｘ　" + ansB);
}

void TalkEventLayer::chooseEnd()
{
    _chooseLabelA->setString("");
    _chooseLabelB->setString("");
}

void TalkEventLayer::appear()
{
    _black->runAction(FadeTo::create(0.2, 255 * 0.8));
    _talkLabel->setString("");
    _talkLabel->setOpacity(255);
    
    _gameLayer->pauseWorld();
}


void TalkEventLayer::disappear()
{
    _isAppeared = false;
    _black->runAction(FadeOut::create(0.2));
    _talkLabel->endRunString();
    _talkLabel->setOpacity(0);
    
    _gameLayer->resumeWorld();
    
    
}

void TalkEventLayer::fadeOut(float duration)
{
    _black->runAction(FadeOut::create(duration));
}

void TalkEventLayer::fadeIn(float duration)
{
    _black->runAction(FadeIn::create(duration));
}








