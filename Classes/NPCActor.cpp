//
//  NPCActor.cpp
//  Lost
//
//  Created by Furukawa on 2015/11/12.
//
//

#include "NPCActor.h"
#include "ActorController.h"
#include "EventManager.h"

NPCActor *NPCActor::create(int no)
{
    NPCActor *pRet = new NPCActor();
    if(pRet && pRet->init(no))
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

bool NPCActor::init(int no)
{
    if ( !Actor::init(no) ) return false;
    
    _isTalked = false;
    
    _kind = NPC;
    
    scheduleUpdate();
    return true;
}

void NPCActor::update(float delta)
{
    Actor::update(delta);
    
    // イベント発生後、キャラが離れたらフラグ折る。
    if(_isTalked)
    {
        auto actorCtrl = ActorController::getInstance();
        auto actor = actorCtrl->_targetActor;
        
        if(actor && !actor->getBoundingBox().intersectsRect(getBoundingBox()))
        {
            _isTalked = false;
        }
    }
}

void NPCActor::damage(Actor *actor)
{
    auto actorCtrl = ActorController::getInstance();
    
    // 操作中のキャラがぶつかった場合、イベント発生させる
    if(actorCtrl->_targetActor == actor)
    {
        if(_isTalked) return;
        _isTalked = true;
        
        if(getPositionX() > actor->getPositionX()) setFlippedX(false);
        else setFlippedX(true);
        
        actor->_force = Vec2::ZERO;
        
        event();
    }
}

void NPCActor::event()
{
    auto eventMgr = EventManager::getInstance();
    eventMgr->init(0);
    eventMgr->run();
    
}








