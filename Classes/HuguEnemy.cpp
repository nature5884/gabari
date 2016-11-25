//
//  HuguEnemy.cpp
//  Gabari
//
//  Created by 小林俊太郎 on 2016/10/07.
//
//

#include "HuguEnemy.h"
#include "ActorController.h"

HuguEnemy *HuguEnemy::create(int no)
{
	HuguEnemy *pRet = new HuguEnemy();

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

bool HuguEnemy::init(int no)
{
	if (!EnemyActor::init(no))
	{
		return false;
	}

	//_isKinematic = true;

	// 近づいたら膨らむ距離
	_swellDistance = 28;

	this->scheduleUpdate();
	return true;
}

void HuguEnemy::regAnim()
{
	animationRegist("stand",1,100);
	animationRegist("attack", 1, 100);
}

void HuguEnemy::update(float delta)
{
	swell();
	EnemyActor::update(delta);
}

void HuguEnemy::swell()
{
	auto actorCon = ActorController::getInstance();
	if (actorCon->_targetActor->getName() != "gabari") return;


	Vec2 distanceVec = Vec2(abs(getPositionX() - actorCon->_targetActor->getPositionX()), abs(getPositionY() - actorCon->_targetActor->getPositionY()));

	float distance = sqrt(pow(distanceVec.x, 2) + pow(distanceVec.y, 2));

	if (abs(distance) <= _swellDistance)
	{
		//膨らむ
		_isAttack = true;
	}
	else
	{
		_isAttack = false;
	}
}
