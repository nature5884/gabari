//
//  GoriraBossEnemy.cpp
//  Gabari
//
//  Created by 蔵元隼人 on 2016/12/01.
//
//

#include "GoriraBossEnemy.h"

GoriraBossEnemy* GoriraBossEnemy::create(int no)
{
    GoriraBossEnemy *pRet = new GoriraBossEnemy();
    
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

bool GoriraBossEnemy::init(int no)
{
    if(!BossActor::init(no))
    {
        return false;
    }
    
    
    
    return true;
}

void GoriraBossEnemy::update(float delta)
{
    
}
