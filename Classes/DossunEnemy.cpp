//
//  DossunEnemy.cpp
//  Gabari
//
//  Created by 蔵元隼人 on 2016/09/29.
//
//

#include "DossunEnemy.h"

DossunEnemy *DossunEnemy::create(int no)
{
    DossunEnemy *pRet = new DossunEnemy();
    
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

bool DossunEnemy::init(int no)
{
    if(!EnemyActor::init(no)) return false;
    
    cnt = 0;
    fall = false;
    
    
    this->scheduleUpdate();
    
    return true;
}

void DossunEnemy::update(float delta)
{
    //EnemyActor::update(delta);
    
    
    
    state();
    if(cnt == 0)
    {
        move();
    }
    
    if(!_isDestroy)
    {
        if(_force.y > 0.0f)
        {
            _move.x = _data.speed *(isFlipX()? -1:1);
            fall = false;
        }
        else
        {
            _move.y = _data.speed * -5;
            _move.x = 0;
            _force.x = 0;
            if(cnt == 0 && fall == false)
            {
                
                cnt = 60;
                fall = true;
                
            }
            
        }
    }
    
    //actor->updateから拝借
    if(!_isDestroy && _hp <= 0)
    {
        destroy();
    }
    
    if(_hp > 0)
    {
        // ダメージ食らったら赤くするだろう？
        if(_hp != _preHp) setColor(Color3B(200, 100, 100));
        else setColor(Color3B::WHITE);
    }
    
    _preHp = _hp;
    
    if(cnt > 0)
    {
        cnt--;
    }
}

void DossunEnemy::yukaHit()
{
    if(_isLanding == false)
    {
        cnt = 60;
    }
    
    _isLanding = true;
    
    if(!_isDestroy && _isLanding && cnt ==0)
    {
        _jumpPow = Actor::JUMP_POW_MAX;
    }
}

void DossunEnemy::kabeHit()
{

    setFlippedX(!isFlippedX());
    _force.x *= -1;
}



