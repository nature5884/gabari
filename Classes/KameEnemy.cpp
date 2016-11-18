//
//  KameEnemy.cpp
//  Gabari
//
//  Created by 小林俊太郎 on 2016/10/07.
//
//

#include "KameEnemy.h"

KameEnemy *KameEnemy::create(int no)
{
	KameEnemy *pRet = new KameEnemy();

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

bool KameEnemy::init(int no)
{
	if (!EnemyActor::init(no))
	{
		return false;
	}

	_hp  = _recoverHp = 10000;

	this->scheduleUpdate();
	return true;
}

void KameEnemy::regAnim()
{
	animationRegist("stand", 1, 100);
	animationRegist("walk", 2, 0.5);
	animationRegist("attack", 5, 0.5);
	//animationRegist("damage", 1, 600);
}

void KameEnemy::update(float delta)
{
	if (!_isDestroy)
	{
		_move.x = _data.speed * (isFlippedX() ? -1 : 1);
	}

	EnemyActor::update(delta);

	if (_hp < 10000)
	{
		_data.speed = 0;
		_state = STAND;
	}
}

void KameEnemy::kabeHit()
{
	setFlippedX(!isFlippedX());
	_force.x *= -1;
}
