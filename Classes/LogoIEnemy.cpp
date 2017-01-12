//
//  LogoIEnemy.cpp
//  Gabari
//
//  Created by Kobayashi on 2016/10/07.
//
//

#include "LogoIEnemy.h"

LogoIEnemy *LogoIEnemy::create(int no)
{
	LogoIEnemy *pRet = new LogoIEnemy();

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

bool LogoIEnemy::init(int no)
{
	if (!EnemyActor::init(no))
	{
		return false;
	}

	_isKinematic = true;

	this->scheduleUpdate();
	return true;
}

void LogoIEnemy::regAnim()
{
	animationRegist("stand", 1, 100);
}

void LogoIEnemy::update(float delta)
{
	EnemyActor::update(delta);
}