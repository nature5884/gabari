//
//  HomingFlyEnemy.cpp
//  Gabari
//
//  Created by 蔵元隼人 on 2016/09/28.
//
//

#include "HomingFlyEnemy.h"
#include "ActorController.h"

HomingFlyEnemy *HomingFlyEnemy::create(int no)
{
    HomingFlyEnemy *pRet = new HomingFlyEnemy();
    
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

bool HomingFlyEnemy::init(int no)
{
    if(!EnemyActor::init(no))
    {
        return false;
    }
    
    
    
    this->scheduleUpdate();
    return true;
}

void HomingFlyEnemy::update(float delta)
{
    state();
    
    
    homing();
    this->setPosition(this->getPosition() + _move * _data.speed);
    
    
    
    
    
    
    
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
    //EnemyActor::update(delta);
}


void HomingFlyEnemy::homing()
{
    auto actorCon = ActorController::getInstance();
    if(actorCon->_targetActor->getName() != "gabari") return;
    
    Vec2 targetPos = actorCon->_targetActor->getPosition();
    
    Vec2 toTargetVec = this->getPosition() - targetPos;
    toTargetVec.normalize();
    
    float rot = acos(Vec2::dot(_movedVec,toTargetVec));
    
    if(rot > 0.003f)
    {
        float rotMax = 0.001f * (180.0f / M_PI);
        
        if(rot > rotMax) rot = rotMax;
        
        float ccw = _movedVec.x * toTargetVec.y + _movedVec.y * toTargetVec.x;
        if(ccw < 0) rot = -rot;
        
        Vec2 vec = _movedVec;
        
        _move.x = vec.x * cos(rot) - vec.y * sin(rot);
        _move.y = vec.x * sin(rot) + vec.y * cos(rot);
        
        _move = _data.speed * _move;
        
        _move.normalize();
        
    }
}

    
    
    
    
    
    
    
    













