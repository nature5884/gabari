//
//  TogeEnemy.cpp
//  Gabari
//
//  Created by Kobayashi on 2016/10/07.
//
//

#include "TogeEnemy.h"

TogeEnemy *TogeEnemy::create(int no)
{
	TogeEnemy *pRet = new TogeEnemy();

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

bool TogeEnemy::init(int no)
{
	if (!EnemyActor::init(no))
	{
		return false;
	}

	_isKinematic = true;

	this->scheduleUpdate();
	return true;
}

void TogeEnemy::regAnim()
{
	animationRegist("stand", 1, 100);
}

void TogeEnemy::update(float delta)
{
	EnemyActor::update(delta);
}