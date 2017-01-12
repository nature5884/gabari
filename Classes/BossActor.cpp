//
//  BossActor.cpp
//  Gabari
//
//  Created by 蔵元隼人 on 2016/11/24.
//
//

#include "BossActor.h"
#include "ActorDataLoader.h"

BossActor* BossActor::create(int no)
{
    BossActor *pRet = new BossActor();
    
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

bool BossActor::init(int no)
{
    if(!Node::init())
    {
        return false;
    }
    
    _data = ActorDataLoader::getInstance()->getActorDataFromNo(no);
    
    return true;
    
}

void BossActor::update(float delta)
{
    
}

void BossActor::createParts(int noMin, int noMax)
{
    for(int i = noMin; i < noMax+1; i++)
    {
        EnemyActor *parts = new EnemyActor();
        
        addChild(parts);
        parts->init(i);
        parts->autorelease();
        
        pushParts(parts);
    }
}

void BossActor::pushParts(EnemyActor *parts)
{
    _bossParts.pushBack(parts);
}

Vector<EnemyActor*>& BossActor::getBossParts()
{
    return _bossParts;
}










