//
//  LogoREnemy.h
//  Gabari
//
//  Created by Kobayashi on 2016/10/07.
//
//

#ifndef LOGO_R_ENEMY_H
#define LOGO_R_ENEMY_H

#include <stdio.h>
#include "EnemyActor.h"

class LogoREnemy : public EnemyActor
{
public:
	static LogoREnemy *create(int no);
	bool init(int no);
	void regAnim() override;
	void update(float delta);

};

#endif 
