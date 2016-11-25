//
//  KameEnemy.h
//  Gabari
//
//  Created by 小林俊太郎 on 2016/10/21.
//
//

#ifndef KAME_ENEMY_H
#define KAME_ENEMY_H

#include <stdio.h>
#include "EnemyActor.h"

class KameEnemy : public EnemyActor
{
public:

	int _recoverHp;
	int _recoverTime;
	static const int _recoverCompleteTime;

	static KameEnemy *create(int no);
	bool init(int no);
	void update(float delta);
	void regAnim() override;
	void kabeHit() override;

	//void damage();
	
};

#endif 
