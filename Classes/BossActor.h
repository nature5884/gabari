//
//  BossActor.hpp
//  Gabari
//
//  Created by 蔵元隼人 on 2016/11/24.
//
//

#ifndef BossActor_hpp
#define BossActor_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "EnemyActor.h"
#include "Actor.h"
USING_NS_CC;

class BossActor : public EnemyActor
{
public:
    static BossActor* create(int no);
    virtual bool init(int no);
    virtual void update(float delta);
    
    
    void createParts(int noMin, int noMax);
    void pushParts(EnemyActor *parts);
    Vector<EnemyActor*>& getBossParts();
    
protected:
    Vector<EnemyActor*> _bossParts;

    
};

#endif /* BossActor_hpp */
