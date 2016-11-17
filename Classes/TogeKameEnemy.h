//
//  TogeKameEnemy.h
//  Gabari
//
//  Created by 小林俊太郎 on 2016/10/28.
//
//

#ifndef TOGE_KAME_ENEMY_H
#define TOGE_KAME_ENEMY_H

#include <stdio.h>
#include "EnemyActor.h"

class TogeKameEnemy : public EnemyActor
{
public:

	static TogeKameEnemy *create(int no);
	bool init(int no);
	void update(float delta);
	void regAnim() override;
	void kabeHit() override;

	void damage();

};

#endif 
