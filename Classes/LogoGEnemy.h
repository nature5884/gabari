//
//  LogoGEnemy.h
//  Gabari
//
//  Created by Kobayashi on 2016/10/07.
//
//

#ifndef LOGO_G_ENEMY_H
#define LOGO_G_ENEMY_H

#include <stdio.h>
#include "EnemyActor.h"

class LogoGEnemy : public EnemyActor
{
public:
	static LogoGEnemy *create(int no);
	bool init(int no);
	void regAnim() override;
	void update(float delta);

};

#endif 
