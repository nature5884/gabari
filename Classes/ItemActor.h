//
//  ItemActor.h
//  Lost
//
//  Created by Furukawa on 2015/11/13.
//
//

#ifndef __Lost__ItemActor__
#define __Lost__ItemActor__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "Actor.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class ItemActor : public Actor
{
public:
    static ItemActor *create(int no);
    virtual bool init(int no) override;
    void update(float delta) override;
    
    void state() override;
    void damage(Actor *actor) override;
    
    void destroyEffect() override;
};

#endif /* defined(__Lost__ItemActor__) */
