//
//  ActorController.cpp
//  Lost
//
//  Created by Furukawa on 2015/11/08.
//
//

#include "ActorController.h"

ActorController *ActorController::_instance;

ActorController *ActorController::getInstance()
{
    if(!_instance)
    {
        _instance = new ActorController();
    }
    
    return _instance;
}

ActorController::ActorController()
{
    init();
}

ActorController::~ActorController()
{
    
}

bool ActorController::init()
{
    _targetActor = NULL;
    
    _gameController = GameController::getInstance();
    
    return true;
}

void ActorController::update(float delta)
{
if(!_targetActor || _targetActor->_isDestroy) return;
    
    float speed = _targetActor->_data.speed;
    
    // ボタン押している間
    if(_gameController->right())
    {
        _targetActor->_move.x = speed;
    }
    
    if(_gameController->left())
    {
        _targetActor->_move.x = -speed;
    }
    
    if(_gameController->batsu())
    {
        _targetActor->attack();
    }
    
    if(_gameController->maru(1))
    {
        if(_targetActor->_isLanding)
        {
            _targetActor->_jumpPow = Actor::JUMP_POW_MAX;
        }
    }
    
    if(_gameController->maru())
    {
        if(!_targetActor->_isLanding && _targetActor->_jumpBoost > 0)
        {
            _targetActor->_jumpBoost --;
            _targetActor->_jumpPow += 0.5 * sin((float(_targetActor->_jumpBoost) / Actor::JUMP_BOOST_MAX));
            
        }
    }
}









