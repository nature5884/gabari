//
//  HomingToriEnemy.hpp
//  Gabari
//
//  Created by 蔵元隼人 on 2016/10/28.
//
//

#ifndef HomingToriEnemy_hpp
#define HomingToriEnemy_hpp

#include <stdio.h>
#include "EnemyActor.h"

class HomingToriEnemy : public EnemyActor
{
public:
    static HomingToriEnemy *create(int no);
    bool init(int no);
    void update(float delta);
    
private:
    Vec2 _moveVec;
    void homingMove();
    
    
};


#endif /* HomingToriEnemy_hpp */
