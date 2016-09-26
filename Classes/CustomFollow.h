//
//  CustomFollow.h
//  OreTobe
//
//  Created by Furukawa on 2014/12/27.
//
//

#ifndef __OreTobe__CustomFollow__
#define __OreTobe__CustomFollow__

#include <stdio.h>
#include "cocos2d.h"
#include "MapManager.h"

using namespace cocos2d;

class CustomFollow : public Follow {
    
    
public:
    
    static CustomFollow* create(Node *followedNode);
    static CustomFollow* create(Node *followedNode, Vec2 screenPos);
    static CustomFollow* create(Node *followedNode, Vec2 screenPos, Vec2 weight);
    
    bool init(Vec2 screenPos, Vec2 weight);
    void step(float dt);
    
    Vec2 _origin;
    Size _stageSize;
    
    
private:
    
    Vec2 _screenPos;
    Vec2 _weight;
    
};

#endif /* defined(__OreTobe__CustomFollow__) */
