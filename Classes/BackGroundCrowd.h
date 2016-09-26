//
//  BackGroundCrowd.h
//  Lost
//
//  Created by Furukawa on 2015/11/09.
//
//

#ifndef __Lost__BackGroundCrowd__
#define __Lost__BackGroundCrowd__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class BackGroundCrowd : public Sprite
{
public:
    static BackGroundCrowd *create();
    virtual bool init();
    void update(float delta);
    
    float _speed;
    
    void replace();
};

#endif /* defined(__Lost__BackGroundCrowd__) */
