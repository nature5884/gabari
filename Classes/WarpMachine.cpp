//
//  WarpMachine.cpp
//  Gabari
//
//  Created by Furukawa on 2016/12/02.
//
//

#include "WarpMachine.h"
#include "MapManager.h"
#include "ActorManager.h"
#include "GameController.h"
#include "Actor.h"

WarpMachine *WarpMachine::create(int trans)
{
    WarpMachine *pRet = new WarpMachine();
    if(pRet && pRet->init(trans))
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

bool WarpMachine::init(int trans)
{
    if ( !Sprite::initWithFile("image/obj/warp_dodai.png") ) return false;
//    if(!Spri::init(998)) return false;
    
    setAnchorPoint(Vec2(0.5, 0));
    auto size = getBoundingBox().size;
    
    _uyo = Sprite::create("image/obj/warp_uyouyo.png");
    _uyo->setPosition(Vec2(size.width/2, size.height));
    _uyo->setAnchorPoint(Vec2(0.5, 0));
    
    addChild(_uyo);
    
//    _isKinematic = false;
    _transition = trans;
    _warped = false;
    
    scheduleUpdate();
    return true;
}

void WarpMachine::update(float delta)
{
    float y =  _uyo->getTextureRect().origin.y + 0.5;
    if(y > _uyo->getTextureRect().size.height) y -= _uyo->getTextureRect().size.height;
    
    _uyo->setTextureRect(Rect(0,y,
                              _uyo->getTextureRect().size.width,
                              _uyo->getTextureRect().size.height));
    
    if(warpCheck())
    {
        warp();
    }
    
}

bool WarpMachine::warpCheck()
{
    auto gameCtrl = GameController::getInstance();
    auto gabari = ActorManager::getInstance()->_actorController->_targetActor;
    
    if(gameCtrl->maru(1) && FCommon::containsWorldPoint(this, FCommon::getWorldPos(gabari)))
    {
        return true;
    }
    
    return false;
}

void WarpMachine::warp()
{
    if(_warped) return;
    
    _warped = true;
    
//    auto gabari = ActorManager::getInstance()->_actorController->_targetActor;
    
    auto mapMng = MapManager::getInstance();
    mapMng->transitionMap(_transition);
}































