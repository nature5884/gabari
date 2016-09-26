//
//  CustomFollow.cpp
//  OreTobe
//
//  Created by Furukawa on 2014/12/27.
//
//

#include "CustomFollow.h"
#include "MultiResolution.h"
#include "MapManager.h"

CustomFollow* CustomFollow::create(Node* followNode)
{
    return create(followNode, visibleCenter, Vec2(10, 10));
}

CustomFollow* CustomFollow::create(Node* followNode, Vec2 screenPos)
{
    return create(followNode, screenPos, Vec2(10, 10));
}

CustomFollow* CustomFollow::create(Node* followNode, Vec2 screenPos, Vec2 weight)
{
    
    CustomFollow *follow = new CustomFollow();
    if (follow && follow->initWithTarget(followNode, Rect::ZERO) && follow->init(screenPos, weight))
    {
        follow->autorelease();
        return follow;
    }
    CC_SAFE_DELETE(follow);
    return nullptr;
}

bool CustomFollow::init(cocos2d::Vec2 screenPos, cocos2d::Vec2 weight)
{
    _screenPos = screenPos;
    _weight = weight;
    _stageSize = Size(1000,1000);
    
    return true;
}

void CustomFollow::step(float dt)
{
    CC_UNUSED_PARAM(dt);
    
    if(_boundarySet)
    {
        if(_boundaryFullyCovered)
            return;
        
        Vec2 tempPos = _screenPos - _followedNode->getPosition();
        
        _target->setPosition(Vec2(clampf(tempPos.x, _leftBoundary, _rightBoundary),
                                  clampf(tempPos.y, _bottomBoundary, _topBoundary)));
    }
    else
    {
        Vec2 move = (_screenPos - _followedNode->getPosition()) - _target->getPosition();
        
        move.x /= _weight.x;
        move.y /= _weight.y;
        
        Vec2 pos = _target->getPosition() + move;
        
//        pos = Vec2(floor(pos.x), floor(pos.y));
        
        _target->setPosition(pos);
        
        // ステージからカメラがはみ出ないようにする
        if(_target->getPositionX() > _origin.x) _target->setPositionX(_origin.x);
        if(_target->getPositionX() < -_stageSize.width + designResolutionSize.width + _origin.x)
            _target->setPositionX(-_stageSize.width + designResolutionSize.width + _origin.x);
        
        if(_target->getPositionY() > _origin.y) _target->setPositionY(_origin.y);
        if(_target->getPositionY() < -_stageSize.height + designResolutionSize.height - _origin.y)
            _target->setPositionY(-_stageSize.height + designResolutionSize.height - _origin.y);
        
        
    }
//    _target->setPosition(_target->getPosition() + _origin);
}