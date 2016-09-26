//
//  BackGroundCrowd.cpp
//  Lost
//
//  Created by Furukawa on 2015/11/09.
//
//

#include "BackGroundCrowd.h"

BackGroundCrowd *BackGroundCrowd::create()
{
    BackGroundCrowd *pRet = new BackGroundCrowd();
    if(pRet && pRet->init())
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

bool BackGroundCrowd::init()
{
    if ( !Sprite::init() ) return false;
    
    replace();
    
    scheduleUpdate();
    return true;
}

void BackGroundCrowd::update(float delta)
{
    setPositionX(getPositionX() - _speed);
    
    if(getPositionX() < -getBoundingBox().size.width)
    {
        replace();
    }
}

void BackGroundCrowd::replace()
{
    char fileName[256];
    sprintf(fileName, "image/obj/kumo_%d.png", rand()%3);
    
    initWithFile(fileName);
    
    setOpacity(255 * 0.3);
    
    setAnchorPoint(Vec2::ZERO);
    setPosition(Vec2(designResolutionSize.width + designResolutionSize.width * (rand()%100/100.0f),
                     designResolutionSize.height * 0.5 + designResolutionSize.height * 0.5 * (rand()%100/100.0f)));
    
    _speed = 0.1 + rand()%50/100.0f;

}



