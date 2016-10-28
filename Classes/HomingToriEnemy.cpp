//
//  HomingToriEnemy.cpp
//  Gabari
//
//  Created by 蔵元隼人 on 2016/10/28.
//
//

#include "HomingToriEnemy.h"
#include "ActorController.h"

HomingToriEnemy *HomingToriEnemy::create(int no)
{
    HomingToriEnemy *pRet = new HomingToriEnemy();
    
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

bool HomingToriEnemy::init(int no)
{
    if(!EnemyActor::init(no))
    {
        return false;
    }
    
    _isKinematic = true;
    
    _moveVec.x = (isFlipX()? -1:1);
    _moveVec.y = 0;
    
    this->scheduleUpdate();
    return true;
}

void HomingToriEnemy::update(float delta)
{
    EnemyActor::update(delta);
    homingMove();
    merikomiBack();
    
}

void HomingToriEnemy::homingMove()
{
    //ぶっちゃけトラッキングでも良い感
    
    
    auto actorCon = ActorController::getInstance();
    if(actorCon->_targetActor->getName() != "gabari") return;
    
    Vec2 targetPos = actorCon->_targetActor->getPosition();
    
    Vec2 toTargetVec = this->getPosition() - targetPos;
    toTargetVec.normalize();
    
    float rot = acos(Vec2::dot(_movedVec,toTargetVec));
    // ターゲットに対して自分の向いてる方向と角度を出してその差分緩やかに回転するよ
    if(rot > 0.003f)
    {
        float rotMax = 0.001f * (180.0f / M_PI);
        
        if(rot > rotMax) rot = rotMax;
        
        float ccw = _moveVec.x * toTargetVec.y + _moveVec.y * toTargetVec.x;
        if(ccw < 0) rot = -rot;
        
        Vec2 vec = _moveVec;
        
        _moveVec.x = vec.x * cos(rot) - vec.y * sin(rot);
        _moveVec.y = vec.x * sin(rot) + vec.y * cos(rot);
        
        // え？なんでYだけ反転する？？？−１かけちゃう・・・・・
        _moveVec.normalize();
        _moveVec = _data.speed * _moveVec;
        
        // 回転する角度でローテーション変更
        this->setRotation(this->getRotation() + rot * (180/M_PI));

    }
    
    _pos.x += _moveVec.x;
    _pos.y -= _moveVec.y;
}

























