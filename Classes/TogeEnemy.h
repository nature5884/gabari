//
//  TogeEnemy.h
//  Gabari
//
//  Created by 小林俊太郎 on 2016/10/07.
//
//

#ifndef TOGE_ENEMY_H
#define TOGE_ENEMY_H

#include <stdio.h>
#include "EnemyActor.h"

class TogeEnemy : public EnemyActor
{
public:
	static TogeEnemy *create(int no);
	bool init(int no);
	void update(float delta);
	
};

#endif 
