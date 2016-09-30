//
//  SarariMan.cpp
//  Lost
//
//  Created by Furukawa on 2015/11/10.
//
//

#include "SarariMan.h"
#include "EffectAnimation.h"

SarariMan *SarariMan::create(int no)
{
    SarariMan *pRet = new SarariMan();
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

bool SarariMan::init(int no)
{
    if(!EnemyActor::init(no)) return false;
    
    scheduleUpdate();
    return true;
}

void SarariMan::update(float delta)
{
    if(!_isDestroy)
    {
        _move.x = _data.speed * (isFlippedX()?-1:1);
    }
    
    EnemyActor::update(delta);
}

void SarariMan::kabeHit()
{
//    log("kabe");
    
    setFlippedX(!isFlippedX());
    _force.x *= -1;
    
    if(_isLanding)
    {
        _jumpPow = Actor::JUMP_POW_MAX;
    }
}

void SarariMan::destroy()
{
    if(_isDestroy) return;
    _isDestroy = true;
    
    stopAllActions();
    runAction(Sequence::create(DelayTime::create(1),
                               CallFunc::create([=]()
                                                {
                                                    EffectAnimation *eff = EffectAnimation::create("image/effect/bon/", 2, 0.06);
                                                    eff->setPosition(getPosition() + Vec2(0, getBoundingBox().size.height/2));
                                                    eff->setRotation(90 * (rand()%3));
                                                    getParent()->addChild(eff);
                                                    
                                                    this->removeFromParent();
                                                    
                                                }),
                               NULL));
    _force.y = 5;
    
    setColor(Color3B::WHITE);
    setTexture(_data.file + "death/0.png");
}

void SarariMan::destroyEffect()
{
    EffectAnimation *eff = EffectAnimation::create("image/effect/bon/", 2, 0.06);
    eff->setPosition(getPosition() + Vec2(0, getBoundingBox().size.height/2));
    eff->setRotation(90 * (rand()%3));
    getParent()->addChild(eff);
}









