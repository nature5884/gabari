//
//  MassuguToriEnemy.hpp
//  Gabari
//
//  Created by 蔵元隼人 on 2016/10/27.
//
//

#ifndef MassuguToriEnemy_hpp
#define MassuguToriEnemy_hpp

#include <stdio.h>
#include "EnemyActor.h"

class MassuguToriEnemy : public EnemyActor
{
public:
    static MassuguToriEnemy *create(int no);
    bool init(int no);
    void update(float delta);
    
private:
    void flyMove();
    void regAnim() override;
    
};


#endif /* MassuguToriEnemy_hpp */
