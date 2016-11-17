//
//  UsagiEnemy.cpp
//  Gabari
//
//  Created by 蔵元隼人 on 2016/10/21.
//
//

#include "UsagiEnemy.h"

UsagiEnemy *UsagiEnemy::create(int no)
{
    UsagiEnemy *pRet = new UsagiEnemy();
    if(!pRet && pRet->init(no))
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

bool UsagiEnemy::init(int no)
{
    if(!EnemyActor::init(no))
    {
        return false;
    }
    
    _waitCnt = 0;
    _WAITMAX = 120;
    
    
    this->scheduleUpdate();
    return true;
}
void UsagiEnemy::regAnim()
{
    animationRegist("jump", 2, 0.1);
}

void UsagiEnemy::update(float delta)
{
    EnemyActor::update(delta);
    
    log("%f,%f",this->getPositionX(),this->getPositionY());
    
    // when _waitCnt is 0 to Jump
    if(!_isDestroy)
    {
        if(_isLanding)
        {
            if(_waitCnt == 0)
            {
                _jumpPow = Actor::JUMP_POW_MAX;
            }
        }
        if(_jumpPow > 0 || !_isLanding)// Moving only Jumpping
        {
            _move.x = _data.speed *(isFlipX()? -1:1);
        }
        // _waitCnt cntDown
        if(_waitCnt > 0)
        {
            _waitCnt--;
        }
    }
}

void UsagiEnemy::kabeHit()
{
    setFlippedX(!isFlippedX());
    _force.x *= -1;
}

void UsagiEnemy::yukaHit()
{
    if(!_isLanding)
    {
        _waitCnt = _WAITMAX;
    }
    Actor::yukaHit(); //isLanding is true this Point
}


















