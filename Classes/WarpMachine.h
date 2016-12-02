//
//  WarpMachine.h
//  Gabari
//
//  Created by Furukawa on 2016/12/02.
//
//

#ifndef __Gabari__WarpMachine__
#define __Gabari__WarpMachine__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "FCommon.h"
//#include "Actor.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;
using namespace FGeneral;

class WarpMachine : public Sprite
{
public:
    static WarpMachine *create(int trans);
    virtual bool init(int trans);
    void update(float delta);
    
    void warp();
    bool warpCheck();
    
    Sprite *_uyo;
    
    int _transition;
    bool _warped;
};

#endif /* defined(__Gabari__WarpMachine__) */
