//
//  MassuguToriEnemy.cpp
//  Gabari
//
//  Created by 蔵元隼人 on 2016/10/27.
//
//

#include "MassuguToriEnemy.h"


MassuguToriEnemy *MassuguToriEnemy::create(int no)
{
    MassuguToriEnemy *pRet = new MassuguToriEnemy();
    
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

bool MassuguToriEnemy::init(int no)
{
    if(!EnemyActor::init(no))
    {
        return false;
    }
    
    _isKinematic = true;
    
    
    this->scheduleUpdate();
    return true;
}
void MassuguToriEnemy::regAnim()
{
    animationRegist("stand", 1, 0.1f);
}

void MassuguToriEnemy::update(float delta)
{
    _prePos = _pos;

    EnemyActor::update(delta);
    flyMove();
    merikomiBack();
    _movedVec = _pos - _prePos;

}

void MassuguToriEnemy::flyMove()
{
    _pos.x += _data.speed *(isFlipX()? -1:1);
}













