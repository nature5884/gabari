//
//  NPCActor.h
//  Lost
//
//  Created by Furukawa on 2015/11/12.
//
//

#ifndef __Lost__NPCActor__
#define __Lost__NPCActor__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "Actor.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class NPCActor : public Actor
{
public:
    bool _isTalked;
    
    static NPCActor *create(int no);
    virtual bool init(int no) override;
    void update(float delta) override;
    
    virtual void damage(Actor *actor) override;
    virtual void event();
};

#endif /* defined(__Lost__NPCActor__) */
