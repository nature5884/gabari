//
//  DossunEnemy.hpp
//  Gabari
//
//  Created by 蔵元隼人 on 2016/09/29.
//
//

#ifndef DossunEnemy_hpp
#define DossunEnemy_hpp

#include <stdio.h>
#include "EnemyActor.h"

class DossunEnemy : public EnemyActor
{
public:
    static DossunEnemy *create(int no);
    bool init(int no);
    void update(float delta);
    
    int cnt;
    bool fall;
    
    
    void kabeHit() override;
    void yukaHit() override;
};

#endif /* DossunEnemy_hpp */
