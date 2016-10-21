//
//  EnemyAppMachine.hpp
//  Gabari
//
//  Created by 蔵元隼人 on 2016/10/07.
//
//

#ifndef EnemyAppMachine_hpp
#define EnemyAppMachine_hpp

#include <stdio.h>
#include "EnemyActor.h"

class EnemyAppMachine : public EnemyActor
{
public:
    static EnemyAppMachine *create(int no);
    bool init(int no);
    void update(float delta);
    
    
private:
    int childCnt;
    int appTiming;
    vector<EnemyActor*> childlen;
    
    void appear(int no);
    
    
    
};

#endif /* EnemyAppMachine_hpp */
