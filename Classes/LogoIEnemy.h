//
//  LogoIEnemy.h
//  Gabari
//
//  Created by Kobayashi on 2016/10/07.
//
//

#ifndef LOGO_I_ENEMY_H
#define LOGO_I_ENEMY_H

#include <stdio.h>
#include "EnemyActor.h"

class LogoIEnemy : public EnemyActor
{
public:
	static LogoIEnemy *create(int no);
	bool init(int no);
	void regAnim() override;
	void update(float delta);

};

#endif 
