//
//  Gabari.cpp
//  Gabari
//
//  Created by Furukawa on 2016/09/22.
//
//

#include "Gabari.h"
#include "GameController.h"

const int Gabari::MUTEKI_FRAME = 60;
const int Gabari::ROTATION_SPEED = 4;
const float Gabari::ATTACK_SPEED = 2;

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
    
    _isMuteki = false;
    _mutekiCount = 0;
    
    _attackPow = 5;
    
    _targetActor = NULL;
    
    scheduleUpdate();
    return true;
}

void Gabari::update(float delta)
{
    _preIsAttackPushed = _isAttackPushed;
    
    if(_atkMode == ATK_NONE)
    {
        Actor::update(delta);
        
        if(getRotation() != 0)
        {
            setRotation(getRotation() * 0.6);
        }
    }
    else
    {
        _isAttack = true;
        
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
        
        state();
        
        // アクターに刺さっていたら、移動量足す
        if(_targetActor)
        {
            _pos += _targetActor->_movedVec;
            setPosition(_pos);
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
    
    if(firstInput && !_isLanding)
    {
        if(_atkMode == ATK_NONE)
        {
            _atkMode = ATK_STANDBY;
            
            Vec2 anchorVec = Vec2(0.5, 0.8) - getAnchorPoint();
            setAnchorPoint(Vec2(0.5, 0.8));
            
            Vec2 size = getBoundingBox().size;
            
            size.x *= anchorVec.x;
            size.y *= anchorVec.y;
            
            setPosition(getPosition() + size);
        }
        else if(_atkMode == ATK_STANDBY)
        {
            _force = Vec2::ZERO;
            _atkMode = ATK_NOW;
            
            
            Vec2 anchorVec = Vec2(0.5, 0) - Vec2(0.5, 0.8);
            setAnchorPoint(Vec2(0.5, 0));
            
            Vec2 size = getBoundingBox().size;
            
            size.x *= anchorVec.x;
            size.y *= anchorVec.y;
            
            setPosition(getPosition() + size);
        }
    }
}

void Gabari::regAnim()
{
    animationRegist("stand", 1, 100);
    animationRegist("walk", 5, 0.1);
    animationRegist("jump", 1, 100);
    animationRegist("attack", 1, 100);
}



void Gabari::attackStandby()
{
    int dir = (isFlippedX() ? -1 : 1);
    
//    int dir = 0;
//    
//    auto gameCtrl = GameController::getInstance();
//    if(gameCtrl->left())
//    {
//        dir = 1;
//    }
//    if(gameCtrl->right())
//    {
//        dir = -1;
//    }
    
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
    
    int hanteiCount = 0;
    int zanzoCount = 1;
    
    Actor *hitAct;
    
    while(hitCheck() == -1)
    {
        _pos = (getPosition() + Vec2(sin(rota/180.0*M_PI),
                                     cos(rota/180.0*M_PI)) * ATTACK_SPEED);
        setPosition(_pos);
        
        if(hanteiCount % 5 == 0)
        {
            Sprite *zanzo = Sprite::createWithTexture(getTexture());
            zanzo->_running = true;
            zanzo->setRotation(getRotation());
            zanzo->setAnchorPoint(getAnchorPoint());
            zanzo->setFlippedX(isFlippedX());
            zanzo->setPosition(_pos);
            getParent()->addChild(zanzo);
            
            float duration = 0.04 * zanzoCount;
            zanzo->runAction(Sequence::create(Spawn::create(EaseBackOut::create(ScaleBy::create(duration, 1.5)),
                                                            FadeOut::create(duration),
                                                            NULL),
                                              RemoveSelf::create(),
                                              NULL));
            zanzoCount ++;
        }
        
        hanteiCount ++;
        
        hitAct = hitCheckActorFromPoint();
        if(hitAct != NULL)
        {
            break;
        }
    }
    
    if(hitAct)
    {
        hitAct->damage(this);
        _targetActor = hitAct;
    }
    
    if(hitCheck() != -1 || hitAct)
    {
        _jumpPow = 0;
        _atkMode = ATK_AFTER;
    }
    
}

void Gabari::attackAfter()
{
    auto gameCtrl = GameController::getInstance();
    
    if(gameCtrl->maru(1) || gameCtrl->right(1) || gameCtrl->left(1))
    {
        _targetActor = NULL;
        _isAttack = false;
        _atkMode = ATK_NONE;
        if(getRotation() > 180) setRotation(getRotation() - 360);
        
        
        if(gameCtrl->maru(1))
        {
            _jumpPow = Actor::JUMP_POW_MAX;
        }
        else
        {
            
        }
    }
    
}























