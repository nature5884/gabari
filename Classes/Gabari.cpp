//
//  Gabari.cpp
//  Gabari
//
//  Created by Furukawa on 2016/09/22.
//
//

#include "Gabari.h"

const int Gabari::MUTEKI_FRAME = 60;
const int Gabari::ROTATION_SPEED = 2;
const int Gabari::ATTACK_SPEED = 2;

Gabari *Gabari::create(int no)
{
    Gabari *pRet = new Gabari();
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

bool Gabari::init(int no)
{
    if ( !Actor::init(no) ) return false;
    
    _atkMode = ATK_NONE;
    _preIsAttackPushed = false;
    _isAttackPushed = false;
    
    scheduleUpdate();
    return true;
}

void Gabari::update(float delta)
{
    _preIsAttackPushed = _isAttackPushed;
    
    if(_atkMode == ATK_NONE)
    {
        Actor::update(delta);
    }
    else
    {
        if(_atkMode == ATK_STANDBY)
        {
            attackStandby();
        }
        
        else if(_atkMode == ATK_NOW)
        {
            attackNow();
        }
        
        else if(_atkMode == ATK_AFTER)
        {
            attackAfter();
        }
    }
    
    _isAttackPushed = false;
}

void Gabari::damage(Actor *actor)
{
    if(actor->_kind != ENEMY)
    {
        return;
    }
    
    if(_isMuteki) return;
    
    _mutekiCount = 0;
    _isMuteki = true;
    
    _hp --;
    
    damageEffect();
}

void Gabari::attack()
{
    _isAttackPushed = true;
    
    // ボタンを押している間ずっと連続で呼ばれてしまうので、
    // ボタンの切り替わりだけを見る
    bool firstInput = (_preIsAttackPushed != _isAttackPushed);
    
    if(firstInput)
    {
        if(_atkMode == ATK_NONE) _atkMode = ATK_STANDBY;
        else if(_atkMode == ATK_STANDBY)
        {
            _force = Vec2::ZERO;
            _isAttack = true;
            _atkMode = ATK_NOW;
        }
    }
}

void Gabari::regAnim()
{
    animationRegist("stand", 1, 100);
    animationRegist("walk", 5, 0.1);
    animationRegist("jump", 1, 100);
    animationRegist("attack", 1, 0.1);
}



void Gabari::attackStandby()
{
    int dir = (isFlippedX() ? -1 : 1);
    
    setRotation(getRotation() - ROTATION_SPEED * dir);
    
    if(getRotation() > 360) setRotation(getRotation() - 360);
    if(getRotation() < 0) setRotation(getRotation() + 360);
}

void Gabari::attackNow()
{
    int dir = (isFlippedX() ? -1 : 1);
    float rota = getRotation() - 180 * dir;
    if(rota > 360) rota -= 360;
    else if(rota < 0) rota += 360;
//    while(!hitCheck())
    {
        setPosition(getPosition() + Vec2(sin(rota/180.0*M_PI),
                                         cos(rota/180.0*M_PI)) * ATTACK_SPEED);
    }
    
    if(hitCheck())
    {
        _jumpPow = 0;
        _atkMode = ATK_AFTER;
//        _isAttack = false;
    }
    
}

void Gabari::attackAfter()
{
    _atkMode = ATK_NONE;
    setRotation(0);
}























