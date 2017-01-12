//
//  LogoAEnemy.cpp
//  Gabari
//
//  Created by Kobayashi on 2016/10/07.
//
//

#include "LogoAEnemy.h"

LogoAEnemy *LogoAEnemy::create(int no)
{
	LogoAEnemy *pRet = new LogoAEnemy();

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

bool LogoAEnemy::init(int no)
{
	if (!EnemyActor::init(no))
	{
		return false;
	}

	_isKinematic = true;

	this->scheduleUpdate();
	return true;
}

void LogoAEnemy::regAnim()
{
	animationRegist("stand", 1, 100);
}

void LogoAEnemy::update(float delta)
{
	EnemyActor::update(delta);
}