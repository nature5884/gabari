//
//  ItemActor.cpp
//  Lost
//
//  Created by Furukawa on 2015/11/13.
//
//

#include "ItemActor.h"

ItemActor *ItemActor::create(int no)
{
    ItemActor *pRet = new ItemActor();
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

bool ItemActor::init(int no)
{
    if ( !Actor::init(no) ) return false;
    
    _kind = ITEM;
    
    scheduleUpdate();
    return true;
}

void ItemActor::update(float delta)
{
    Actor::update(delta);
    
    _force.y = 3;
}

void ItemActor::state()
{
    
}

void ItemActor::damage(Actor *actor)
{
    
}

void ItemActor::destroyEffect()
{
    Sprite *heart = Sprite::createWithTexture(getTexture());
    heart->setPosition(getPosition() + Vec2(0, getBoundingBox().size.height/2));
    getParent()->addChild(heart);
    
    heart->runAction(Sequence::create(Spawn::create(JumpBy::create(0.3, Vec2::ZERO, 10, 1),//EaseBackOut::create(MoveBy::create(0.6, Vec2(0, 10))),
                                                    FadeOut::create(0.3),
                                                    NULL),
                                      CallFunc::create([=]()
                                                       {
                                                           heart->removeFromParent();
                                                       }),
                                      NULL));
}










