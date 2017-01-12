//
//  LogoREnemy.cpp
//  Gabari
//
//  Created by Kobayashi on 2016/10/07.
//
//

#include "LogoREnemy.h"

LogoREnemy *LogoREnemy::create(int no)
{
	LogoREnemy *pRet = new LogoREnemy();

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

bool LogoREnemy::init(int no)
{
	if (!EnemyActor::init(no))
	{
		return false;
	}

	_isKinematic = true;

	this->scheduleUpdate();
	return true;
}

void LogoREnemy::regAnim()
{
	animationRegist("stand", 1, 100);
}

void LogoREnemy::update(float delta)
{
	EnemyActor::update(delta);
}