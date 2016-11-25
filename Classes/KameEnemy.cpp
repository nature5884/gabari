//
//  KameEnemy.cpp
//  Gabari
//
//  Created by 小林俊太郎 on 2016/10/07.
//
//

#include "KameEnemy.h"

const int KameEnemy::_recoverCompleteTime = 300;

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
	_recoverTime = 0;

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
	if (_isDestroy)
	{
		return;
	}

	if (!_isDestroy && _hp >= 10000)
	{
		_move.x = _data.speed * (isFlippedX() ? -1 : 1);
	}
	else if (_hp < 10000)
	{
		_move.x = 0;
		_recoverTime++;

		// 復帰までの時間
		if (_recoverTime >= _recoverCompleteTime)
		{
			_hp = 10000;
			_recoverTime = 0;
		}
	}

	EnemyActor::update(delta);
}

void KameEnemy::kabeHit()
{
	setFlippedX(!isFlippedX());
	_force.x *= -1;
}
