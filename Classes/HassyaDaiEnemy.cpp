//
//  HassyaDaiEnemy.cpp
//  Gabari
//
//  Created by 蔵元隼人 on 2016/10/28.
//
//

#include "HassyaDaiEnemy.h"
#include "ActorManager.h"

#include "HomingToriEnemy.h"
#include "MassuguToriEnemy.h"


HassyaDaiEnemy *HassyaDaiEnemy::create(int no)
{
    HassyaDaiEnemy *pRet = new HassyaDaiEnemy();
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

bool HassyaDaiEnemy::init(int no)
{
    if(!EnemyActor::init(no))
    {
        return false;
    }
    
    
    _isAppHoming = true;
    _appMax = 4;
    _timeReset = 120;
    
    this->scheduleUpdate();
    
    return true;
}

void HassyaDaiEnemy::update(float delta)
{
    EnemyActor::update(delta);
    
    if(_timer ==0 && _appEnemies.size() < _appMax)
    {
        appToriEnemy();
    }
    
    if(_timer > 0)
    {
        _timer--;
    }
}


void HassyaDaiEnemy::appToriEnemy()
{
    EnemyActor *toriRobo;
    
    //鳥ロボの番号わかったらいれよ？
    if(_isAppHoming)
    {
        toriRobo = HomingToriEnemy::create(104);
    }
    else
    {
        toriRobo = MassuguToriEnemy::create(104);
    }
    toriRobo->setPosition(this->getPosition());
    toriRobo->_pos = this->getPosition();
    toriRobo->setFlippedX(this->isFlipX());
    ActorManager::getInstance()->addChild(toriRobo);
    
    _appEnemies.pushBack(toriRobo);
    
    _timer = _timeReset;
}




















