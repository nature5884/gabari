//
//  LogoBEnemy.cpp
//  Gabari
//
//  Created by Kobayashi on 2016/10/07.
//
//

#include "LogoBEnemy.h"

LogoBEnemy *LogoBEnemy::create(int no)
{
	LogoBEnemy *pRet = new LogoBEnemy();

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

bool LogoBEnemy::init(int no)
{
	if (!EnemyActor::init(no))
	{
		return false;
	}

	_isKinematic = true;

	this->scheduleUpdate();
	return true;
}

void LogoBEnemy::regAnim()
{
	animationRegist("stand", 1, 100);
}

void LogoBEnemy::update(float delta)
{
	EnemyActor::update(delta);
}