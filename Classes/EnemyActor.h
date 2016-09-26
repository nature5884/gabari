//
//  EnemyActor.h
//  Lost
//
//  Created by Furukawa on 2015/11/12.
//
//

#ifndef __Lost__EnemyActor__
#define __Lost__EnemyActor__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "Actor.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class EnemyActor : public Actor
{
public:
    static EnemyActor *create(int no);
    virtual bool init(int no) override;
    void update(float delta) override;
    
    void damage(Actor *actor) override;
    void damage();
};

#endif /* defined(__Lost__EnemyActor__) */
