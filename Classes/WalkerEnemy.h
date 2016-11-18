//
//  WalkerEnemy.hpp
//  Gabari
//
//  Created by 蔵元隼人 on 2016/09/28.
//
//

#ifndef WalkerEnemy_hpp
#define WalkerEnemy_hpp

#include <stdio.h>
#include "EnemyActor.h"


class WalkerEnemy : public EnemyActor
{
public:
    static WalkerEnemy *create(int no);
    bool init(int no);
    void update(float delta);
    
    void kabeHit() override;
    
private:
    
};

#endif /* WalkerEnemy_hpp */
