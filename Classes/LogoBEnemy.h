//
//  LogoBEnemy.h
//  Gabari
//
//  Created by Kobayashi on 2016/10/07.
//
//

#ifndef LOGO_B_ENEMY_H
#define LOGO_B_ENEMY_H

#include <stdio.h>
#include "EnemyActor.h"

class LogoBEnemy : public EnemyActor
{
public:
	static LogoBEnemy *create(int no);
	bool init(int no);
	void regAnim() override;
	void update(float delta);

};

#endif 
