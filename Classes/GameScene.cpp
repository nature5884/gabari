//
//  GameScene.cpp
//  Lost
//
//  Created by Furukawa on 2015/11/08.
//
//

#include "GameScene.h"
#include "BackGroundCrowd.h"
#include "EventManager.h"
#include "MapManager.h"
#include "FDotLayer.h"

#include "ResultBoard.h"

Scene *GameScene::createScene()
{
    auto scene = Scene::create();
    scene->addChild(GameScene::create());
    return scene;
}

GameScene *GameScene::create()
{
    GameScene *pRet = new GameScene();
    if(pRet && pRet->init())
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

bool GameScene::init()
{
    if ( !Layer::init() ) return false;
    
    _running = true;
    
    Sprite *back = Sprite::create();
    back->setTextureRect(Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
    back->setColor(Color3B(214, 212, 198));
    back->setAnchorPoint(Vec2::ZERO);
    addChild(back);
    
    
    for(int i=0; i<3; i++)
    {
        BackGroundCrowd *kumo = BackGroundCrowd::create();
        kumo->_running = true;
        addChild(kumo);
    }
    
    
    _controller = GameController::getInstance();
    _controller->_running = true;

	back->setPositionY(-_controller->getUIHeight());
    
    Sprite *biru = Sprite::create("image/back/labo.png");
    biru->setAnchorPoint(Vec2::ZERO);
    biru->setPosition(Vec2(0,0));
    addChild(biru);
    
    _gameLayer = GameLayer::create();
    addChild(_gameLayer);
    
    addChild(_controller, 100);
    
    // トークのアレ
    _talkEventLayer = TalkEventLayer::getInstance();
    addChild(_talkEventLayer);
    _talkEventLayer->_gameLayer = _gameLayer;
    
    scheduleUpdate();
    
    
    ///////debug
//    ResultBoard *hoge = ResultBoard::create(0);
//    this->addChild(hoge);
//    hoge->setZOrder(10000);
//    
    
    return true;
    
    
}

void GameScene::update(float delta)
{
//    FDotLayer::update(delta);
    
    _controller->update(delta);
    _gameLayer->update(delta);
    _talkEventLayer->update(delta);
    
    EventManager::getInstance()->update();
}




