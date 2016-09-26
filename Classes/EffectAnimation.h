//
//  EffectAnimation.h
//  Lost
//
//  Created by Furukawa on 2015/11/09.
//
//

#ifndef __Lost__EffectAnimation__
#define __Lost__EffectAnimation__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class EffectAnimation : public Sprite
{
public:
    static EffectAnimation *create(string file, int frameNum, float delay);
    virtual bool init(string file, int frameNum, float delay);
    void update(float delta);
    
    
};

#endif /* defined(__Lost__EffectAnimation__) */
