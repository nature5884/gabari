//
//  LogoGEnemy.cpp
//  Gabari
//
//  Created by Kobayashi on 2016/10/07.
//
//

#include "LogoGEnemy.h"

LogoGEnemy *LogoGEnemy::create(int no)
{
	LogoGEnemy *pRet = new LogoGEnemy();

	if (pRet && pRet->init(no))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool LogoGEnemy::init(int no)
{
	if (!EnemyActor::init(no))
	{
		return false;
	}

	//_isKinematic = true;


	//this->Repeat::create(Sequence::create(runAction(JumpBy::create(0.5f, this->getPosition(), 10, 10)),NULL));

	this->scheduleUpdate();
	return true;
}

void LogoGEnemy::regAnim()
{
	animationRegist("stand", 1, 100);
}

void LogoGEnemy::update(float delta)
{
	EnemyActor::update(delta);
}