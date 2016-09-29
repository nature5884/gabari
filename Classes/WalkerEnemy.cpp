//
//  WalkerEnemy.cpp
//  Gabari
//
//  Created by 蔵元隼人 on 2016/09/28.
//
//

#include "WalkerEnemy.h"

WalkerEnemy *WalkerEnemy::create(int no)
{
    WalkerEnemy *pRet = new WalkerEnemy();
    
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

bool WalkerEnemy::init(int no)
{
    if(!EnemyActor::init(no))
    {
        return false;
    }
    
    this->scheduleUpdate();
    
    return true;
}

void WalkerEnemy::update(float delta)
{
    EnemyActor::update(delta);
    
    if(!_isDestroy)
    {
        _move.x = _data.speed *(isFlipX()? -1:1);
    }
}

void WalkerEnemy::kabeHit()
{
    setFlippedX(!isFlippedX());
    _force.x *= -1;
    
    if(_isLanding)
    {
        _jumpPow = Actor::JUMP_POW_MAX;
    }
}









