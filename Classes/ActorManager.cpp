//
//  ActorManager.cpp
//  Lost
//
//  Created by Furukawa on 2015/11/08.
//
//

#include "ActorManager.h"
#include "Gabari.h"
#include "SarariMan.h"

#include "UsagiEnemy.h"
#include "MassuguToriEnemy.h"
#include "HomingToriEnemy.h"
#include "HassyaDaiEnemy.h"

ActorManager *ActorManager::_instance = NULL;
ActorManager *ActorManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = ActorManager::create();
    }
    
    return _instance;
}

ActorManager *ActorManager::create()
{
    ActorManager *pRet = new ActorManager();
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

bool ActorManager::init()
{
    if ( !Layer::init() ) return false;
    
    _running = true;
    
    _actorDataLodaer = ActorDataLoader::getInstance();
    _actorController = ActorController::getInstance();
    
    scheduleUpdate();
    return true;
}

void ActorManager::update(float delta)
{
    _actorController->update(delta);
    
    // アクター同士の当たり判定。当っていたらdamage()呼ぶ。
//    damageCheck();
}

Actor *ActorManager::createActor(int no, Vec2 pos)
{
    Actor *actor;
    
    
    if(no == 999) actor = new Gabari();
    else if(no == 104) actor = new HassyaDaiEnemy();
    else actor = new Actor();
    
    addChild(actor);
    
    actor->init(no);
    actor->autorelease();
    
    actor->_pos = pos;
    actor->setPosition(pos);
    return actor;
}

void ActorManager::damageCheck()
{
    auto children = getChildren();
    
    for(auto childA : children)
    {
        // アクターにはなにかしら名前がついているはず
        if(childA->getName() == "") continue;
        
        Actor *actorA = (Actor*)childA;
        
        if(actorA->_isDestroy) continue;
        
        for(auto childB : children)
        {
            // アクターにはなにかしら名前がついているはず
            if(childB->getName() == "") continue;
            if(childA == childB) continue;
            
            Actor *actorB = (Actor*)childB;
            
            if(actorB->_isDestroy) continue;
            
            // 当たり判定
            if(actorA->getBoundingBox().intersectsRect(actorB->getBoundingBox()))
            {
                actorA->damage(actorB);
            }
        }
    }
}













