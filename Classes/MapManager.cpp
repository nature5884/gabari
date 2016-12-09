//
//  MapManager.cpp
//  Lost
//
//  Created by Furukawa on 2015/11/08.
//
//

#include "MapManager.h"
#include "MapDataLoader.h"
#include "GameController.h"
#include "CustomFollow.h"

MapManager *MapManager::_instance = NULL;

MapManager *MapManager::getInstance()
{
    if(!_instance)
    {
        _instance = MapManager::create();
    }
    
    return _instance;
}

MapManager *MapManager::create()
{
    MapManager *pRet = new MapManager();
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

bool MapManager::init()
{
    if ( !Layer::init() ) return false;
    
    
//    setPosition(Vec2(-3, -3));
    
    scheduleUpdate();
    return true;
}

void MapManager::update(float delta)
{
    
}

void MapManager::transitionMap(int mapNo)
{
    setPositionX(0);
    getParent()->setPositionX(0);
    getParent()->setPositionY(GameController::getInstance()->getUIHeight());
    
    removeAllChildren();
    _actorManager->removeAllChildren();
    _mapData.mapData.clear();
    _mapData.chipFileName.clear();
    _mapData.tileData.clear();
    _mapData.constValue.clear();
    
    char fileName[128];
    sprintf(fileName, "map/%d.txt", mapNo);
    
    _mapData = MapDataLoader::getInstance()->getMapData(fileName);
    
    for(int y=_mapData.mapHeight-1; y>=0; y--)
    {
        for(int x=0; x<_mapData.mapWidth; x++)
        {
            int gridSize = _mapData.gridSize;
            Vec2 index = Vec2(x, y);
            Vec2 pos = Vec2(x * (gridSize),
                            (_mapData.mapHeight-1 - y) * gridSize);
            
            int d = _mapData.mapData[index];
            
            if(_mapData.chipFileName[d] == "start")
            {
                auto actor = _actorManager->createActor(d, pos);
                _actorManager->_actorController->_targetActor = actor;
                
                follow(actor);
            }
            else if(_mapData.chipFileName[d] == "actor")
            {
                _actorManager->createActor(d, pos);
            }
            
            else if(_mapData.chipFileName[d].find("warp/") != string::npos)
            {
                int trans;
                sscanf(_mapData.chipFileName[d].c_str(), "warp/%d", &trans);
                
                _actorManager->createWarpMachine(trans, pos);
            }
            else if(d != 0)
            {
                log("debug : %s",_mapData.chipFileName[_mapData.mapData[index]].c_str());
                Sprite *chip = Sprite::create(_mapData.chipFileName[_mapData.mapData[index]]);
                chip->getTexture()->setAliasTexParameters();
                chip->setPosition(pos);
                chip->setAnchorPoint(Vec2(0.5, 0));
                addChild(chip);
                
                if(d == 1)
                {
                    _mapData.tileData[index] = chip;
//                    chip->setAnchorPoint(Vec2(0, 0));
					chip->setLocalZOrder(1);
                }
                
                if(d != 1)
                {
                    chip->setPosition(chip->getPosition() + Vec2(0, 0));
					
                }
            }
        }
    }
}

void MapManager::follow(cocos2d::Node *target)
{
    if(getParent() == NULL) CC_ASSERT("parent is null. follow　できへんよ");
    
    getParent()->stopAllActions();
    
    CustomFollow *follow = CustomFollow::create(_actorManager->_actorController->_targetActor,
                                                Vec2(designResolutionSize.width * 0.5, designResolutionSize.height*0.66),
                                                Vec2(5,5));
    
    follow->_stageSize = Size(_mapData.mapWidth * _mapData.gridSize,
                              _mapData.mapHeight * _mapData.gridSize);
    follow->_origin = getParent()->getPosition();
    getParent()->runAction(follow);
}







































