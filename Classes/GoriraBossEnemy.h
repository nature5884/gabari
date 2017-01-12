//
//  GoriraBossEnemy.hpp
//  Gabari
//
//  Created by 蔵元隼人 on 2016/12/01.
//
//

#ifndef GoriraBossEnemy_hpp
#define GoriraBossEnemy_hpp

#include <stdio.h>
#include "BossActor.h"

class GoriraBossEnemy : public BossActor
{
public:
    static GoriraBossEnemy* create(int no);
    bool init(int no);
    void update(float delta);
    
protected:
};

#endif /* GoriraBossEnemy_hpp */
