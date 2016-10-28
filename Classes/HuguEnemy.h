//
//  HuguEnemy.h
//  Gabari
//
//  Created by ¬—Ñr‘¾˜Y on 2016/10/07.
//
//

#ifndef HUGU_ENEMY_H
#define HUGU_ENEMY_H

#include <stdio.h>
#include "EnemyActor.h"

class HuguEnemy : public EnemyActor
{
public:

	int _swellDistance;


	static HuguEnemy *create(int no);
	bool init(int no);
	void update(float delta);
	void regAnim() override;

	void swell();


};

#endif 
