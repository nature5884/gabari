//
//  LogoAEnemy.h
//  Gabari
//
//  Created by Kobayashi on 2016/10/07.
//
//

#ifndef LOGO_A_ENEMY_H
#define LOGO_A_ENEMY_H

#include <stdio.h>
#include "EnemyActor.h"

class LogoAEnemy : public EnemyActor
{
public:
	static LogoAEnemy *create(int no);
	bool init(int no);
	void regAnim() override;
	void update(float delta);

};

#endif 
