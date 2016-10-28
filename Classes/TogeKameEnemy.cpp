//
//  TogeKameEnemy.cpp
//  Gabari
//
//  Created by ¬—Ñr‘¾˜Y on 2016/10/28.
//
//

#include "TogeKameEnemy.h"

TogeKameEnemy *TogeKameEnemy::create(int no)
{
	TogeKameEnemy *pRet = new TogeKameEnemy();

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

bool TogeKameEnemy::init(int no)
{
	if (!EnemyActor::init(no))
	{
		return false;
	}

	_hp = 10000;

	this->scheduleUpdate();
	return true;
}

void TogeKameEnemy::regAnim()
{
	animationRegist("stand", 1, 100);
	animationRegist("walk", 2, 0.5);
	animationRegist("attack", 5, 0.5);
}

void TogeKameEnemy::update(float delta)
{
	if (!_isDestroy)
	{
		_move.x = _data.speed * (isFlippedX() ? -1 : 1);
	}

	EnemyActor::update(delta);
}

void TogeKameEnemy::kabeHit()
{
	setFlippedX(!isFlippedX());
	_force.x *= -1;
}

void TogeKameEnemy::damage()
{
	_hp = 10000;
}