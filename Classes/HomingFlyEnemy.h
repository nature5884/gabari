//
//  HomingFlyEnemy.hpp
//  Gabari
//
//  Created by 蔵元隼人 on 2016/09/28.
//
//

#ifndef HomingFlyEnemy_hpp
#define HomingFlyEnemy_hpp

#include <stdio.h>
#include "EnemyActor.h"

class HomingFlyEnemy : public EnemyActor
{
public:
    static HomingFlyEnemy *create(int no);
    bool init(int no);
    void update(float delta);
    
    void homing();
    
    int cnt;
    
    
};

#endif /* HomingFlyEnemy_hpp */
