//
//  FFollow.h
//  OreTobe
//
//  Created by Furukawa on 2014/12/27.
//
//
#pragma execution_character_set("utf-8")

#ifndef __OreTobe__FFollow__
#define __OreTobe__FFollow__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class FFollow : public Follow {
    
    
public:
    
    static FFollow* create(Node *followedNode);
    static FFollow* create(Node *followedNode, Vec2 screenPos);
    static FFollow* create(Node *followedNode, Vec2 screenPos, Vec2 weight);
    
    bool init(Vec2 screenPos, Vec2 weight);
    void step(float dt);
    
    Vec2 _origin;
    cocos2d::Size _stageSize;
    
    
private:
    
    Vec2 _screenPos;
    Vec2 _weight;
    
};

#endif /* defined(__OreTobe__FFollow__) */
