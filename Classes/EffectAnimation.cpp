//
//  EffectAnimation.cpp
//  Lost
//
//  Created by Furukawa on 2015/11/09.
//
//

#include "EffectAnimation.h"
#include "AnimationManager.h"

EffectAnimation *EffectAnimation::create(string file, int frameNum, float delay)
{
    EffectAnimation *pRet = new EffectAnimation();
    if(pRet && pRet->init(file, frameNum, delay))
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

bool EffectAnimation::init(string file, int frameNum, float delay)
{
    if ( !Sprite::init() ) return false;
    
    initWithFile(file + "0.png");
    
    AnimationManager::addAnimationCache(file, file, frameNum, delay);
    
    runAction(Sequence::create(AnimationManager::createRepeat(file, 1),
                               CallFunc::create([=]()
                                                {
                                                    this->removeFromParent();
                                                }),
                               NULL));
    
    scheduleUpdate();
    return true;
}

void EffectAnimation::update(float delta)
{
    
}