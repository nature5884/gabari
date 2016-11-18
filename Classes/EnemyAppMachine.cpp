//
//  EnemyAppMachine.cpp
//  Gabari
//
//  Created by 蔵元隼人 on 2016/10/07.
//
//

#include "EnemyAppMachine.h"
#include "ActorManager.h"
#include "SarariMan.h"

EnemyAppMachine *EnemyAppMachine::create(int no)
{
    EnemyAppMachine *pRet = new EnemyAppMachine();
    
    if(!pRet && pRet->init(no))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return pRet;
    }
}

bool EnemyAppMachine::init(int no)
{
    if(!EnemyActor::init(no))
    {
        return false;
    }
    
    
    this->scheduleUpdate();
    return true;
}

void EnemyAppMachine::update(float delta)
{
    
    if(appTiming == 0)
    {
        appear(0);
    }
    if(appTiming > 0) appTiming--;
}

void EnemyAppMachine::appear(int no)
{
    
    auto mgr = ActorManager::getInstance();
    
    Actor *actor;
    
    actor = SarariMan::create(104);
    mgr -> addChild(actor);
    
}






