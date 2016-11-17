//
//  UsagiEnemy.hpp
//  Gabari
//
//  Created by 蔵元隼人 on 2016/10/21.
//
//

#ifndef UsagiEnemy_hpp
#define UsagiEnemy_hpp

#include <stdio.h>
#include "EnemyActor.h"

class UsagiEnemy : public EnemyActor
{
public:
    static UsagiEnemy *create(int no);
    bool init(int no) override;
    void update(float delta) override;
    
private:
    int _waitCnt;
    int _WAITMAX;
    
    void regAnim() override;
    void kabeHit() override;
    void yukaHit() override;
};



#endif /* UsagiEnemy_hpp */
