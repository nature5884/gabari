//
//  GameLayer.cpp
//  Lost
//
//  Created by Furukawa on 2015/11/08.
//
//

#include "GameLayer.h"
#include "GameController.h"
#include "CustomFollow.h"

GameLayer *GameLayer::create()
{
    GameLayer *pRet = new GameLayer();
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

bool GameLayer::init()
{
    if ( !Layer::init() ) return false;
    
    _running = true;
    
    auto gameCont = GameController::getInstance();
    
    setPosition(Vec2(4, gameCont->getUIHeight() - 3));
    
    _actorManager = ActorManager::getInstance();
    addChild(_actorManager, 1);
    
    _mapManager = MapManager::getInstance();
    addChild(_mapManager);
    _mapManager->_actorManager = _actorManager;
    
    _mapManager->transitionMap(0);
    
    
    
    
    
    
    scheduleUpdate();
    return true;
}

void GameLayer::update(float delta)
{
    
}

void GameLayer::pauseWorld()
{
    for(auto child : getChildren())
    {
        child->pause();
    }
    
    for(auto child : _mapManager->getChildren())
    {
        child->pause();
    }
    for(auto child : _actorManager->getChildren())
    {
        child->pause();
    }
}

void GameLayer::resumeWorld()
{
    for(auto child : getChildren())
    {
        child->resume();
    }
    
    for(auto child : _mapManager->getChildren())
    {
        child->resume();
    }
    for(auto child : _actorManager->getChildren())
    {
        child->resume();
    }
}






