//
//  HassyaDaiEnemy.hpp
//  Gabari
//
//  Created by 蔵元隼人 on 2016/10/28.
//
//

#ifndef HassyaDaiEnemy_hpp
#define HassyaDaiEnemy_hpp

#include <stdio.h>
#include "EnemyActor.h"

class HassyaDaiEnemy : public EnemyActor
{
public:
    static HassyaDaiEnemy *create(int no);
    bool init(int no);
    void update(float delta);
    
    bool _isAppHoming;
    int _appMax;
    int _timeReset;
private:
    int _timer;
    Vector<EnemyActor*> _appEnemies;
    
    void appToriEnemy();
    
};

#endif /* HassyaDaiEnemy_hpp */
