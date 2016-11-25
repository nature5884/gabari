//
//  EnemyActor.cpp
//  Lost
//
//  Created by Furukawa on 2015/11/12.
//
//

#include "EnemyActor.h"
#include "ActorController.h"
#include "Gabari.h"

EnemyActor *EnemyActor::create(int no)
{
    EnemyActor *pRet = new EnemyActor();
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

bool EnemyActor::init(int no)
{
    if ( !Actor::init(no) ) return false;
    
    _kind = ENEMY;
    
    scheduleUpdate();
    return true;
}

void EnemyActor::update(float delta)
{
    Actor::update(delta);
    
    auto hitAct = hitCheckActor();
    
    if(hitAct && hitAct->_kind == PLAYER)
    {
        hitAct->damage(this);
    }
}

void EnemyActor::damage(Actor *actor)
{
   
    
    if(actor->_kind != PLAYER) return;
    
    // 主人公に当たった場合は、主人公に無敵時間が発生するのでHitを回避する
    auto actorCtrl = ActorController::getInstance();
    
    if(actor == actorCtrl->_targetActor)
    {
        if(actor->getName() == "gabari")
        {
            Gabari *hero = (Gabari*)actor;
            if(!hero->_isMuteki)
            {
                damage();
            }
            return;
        }
    }
    damage();
    
}

void EnemyActor::damage()
{
    _hp --;
    damageEffect();
}










