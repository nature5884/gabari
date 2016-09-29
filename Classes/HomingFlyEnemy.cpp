//
//  HomingFlyEnemy.cpp
//  Gabari
//
//  Created by 蔵元隼人 on 2016/09/28.
//
//

#include "HomingFlyEnemy.h"
#include "ActorController.h"

HomingFlyEnemy *HomingFlyEnemy::create(int no)
{
    HomingFlyEnemy *pRet = new HomingFlyEnemy();
    
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

bool HomingFlyEnemy::init(int no)
{
    if(!EnemyActor::init(no))
    {
        return false;
    }
    
    
    this->scheduleUpdate();
    return true;
}

void HomingFlyEnemy::update(float delta)
{
    EnemyActor::update(delta);
}


void HomingFlyEnemy::homing()
{
    auto actorCon = ActorController::getInstance();
    if(actorCon->_targetActor->getName() != "gabari") return;
    
    Vec2 targetPos = actorCon->_targetActor->getPosition();
    
    Vec2 toTargetVec = this->getPosition() - targetPos;
    toTargetVec.normalize();
    
    
    
    float rot = acos(Vec2::dot());
    
    
//    // 内積から角度差を出す
//    // 内積は移動方向と自分とターゲット間のベクトル
//    float rot = acos(Vec2::dot(moveDir,vecMy_Target));
//    
//    // 細かい角度は無視する感じで
//    if(rot > 0.003f)
//    {
//        
//        float rotMax = 0.001f * (180.0f / M_PI);
//        if(rot>rotMax)// 最大角度を超えていたら
//        {
//            
//            rot = rotMax;//固定
//        }
//        // 回転方向を外積から求める
//        float ccw = moveDir.x * vecMy_Target.y - moveDir.y * vecMy_Target.x;
//        if(ccw < 0)
//        {
//            rot = -rot;
//        }
//        
//        Vec2 vec = moveDir; //コピる
//        // moveDirを回転させて進行方向変換
//        moveDir.x = (float)(vec.x * cos(rot) - vec.y *sin(rot));
//        moveDir.y = (float)(vec.x * sin(rot) + vec.y * cos(rot));
//        
//        moveDir.normalize();
//    }
//    
//    // 最終的なmoveDirで移動。
//    misairu->setPosition(misairu->getPosition() + moveDir*moveSpeed);
//    
    
    
    
    
    
}
    
    
    
    
    
    
    
    
    
    













