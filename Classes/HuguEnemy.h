//
//  HuguEnemy.h
//  Gabari
//
//  Created by 小林俊太郎 on 2016/10/07.
//
//

#ifndef HUGU_ENEMY_H
#define HUGU_ENEMY_H

#include <stdio.h>
#include "EnemyActor.h"

class HuguEnemy : public EnemyActor
{
public:

	static HuguEnemy *create(int no);
	bool init(int no);
	void update(float delta);
	void regAnim() override;
	void swell();
    
    int _swellDistance;


};

#endif 
