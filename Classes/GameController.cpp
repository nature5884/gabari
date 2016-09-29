//
//  GameController.cpp
//  Lost
//
//  Created by Furukawa on 2015/11/08.
//
//

#include "GameController.h"

GameController *GameController::_instance;
GameController *GameController::getInstance()
{
    if(!_instance)
    {
        _instance = GameController::create();
    }
    
    return _instance;
}

GameController *GameController::create()
{
    GameController *pRet = new GameController();
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

bool GameController::init()
{
    if ( !Layer::init() ) return false;
    
//    Label *test = Label::createWithTTF("hello", "fonts/arial.ttf", 10);
//    test->setPosition(visibleCenter);
//    addChild(test);
    
    _running = true;
    
    _uiBaseSp = Sprite::create("image/ui/ui_base.png");
    _uiBaseSp->setAnchorPoint(Vec2::ZERO);
    _uiBaseSp->setPosition(Vec2::ZERO);
    _uiBaseSp->setTextureRect(Rect(0, 0, designResolutionSize.width, _uiBaseSp->getBoundingBox().size.height));
    _uiBaseSp->getTexture()->setAliasTexParameters();
    addChild(_uiBaseSp);
    
    // ボタン生成
    string fileName[] =
    {
        "image/ui/button/left.png",
        "image/ui/button/right.png",
        "image/ui/button/batsu.png",
        "image/ui/button/maru.png",
    };
    float buttonPosY = _uiBaseSp->getBoundingBox().size.height/2;
    Vec2 pos[] =
    {
        Vec2(designResolutionSize.width * 0.1, buttonPosY),
        Vec2(designResolutionSize.width * 0.25, buttonPosY),
        Vec2(designResolutionSize.width * 0.75, buttonPosY),
        Vec2(designResolutionSize.width * 0.9, buttonPosY),
    };
    EventKeyboard::KeyCode keyCode[] =
    {
        EventKeyboard::KeyCode::KEY_LEFT_ARROW,
        EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
        EventKeyboard::KeyCode::KEY_X,
        EventKeyboard::KeyCode::KEY_C,
    };
    
    int index = 0;
    _leftButton = initButton(fileName[index], pos[index], keyCode[index]); index++;
    _rightButton = initButton(fileName[index], pos[index], keyCode[index]); index++;
    _batsuButton = initButton(fileName[index], pos[index], keyCode[index]); index++;
    _maruButton = initButton(fileName[index], pos[index], keyCode[index]); index++;
    
    scheduleUpdate();
    return true;
}

UISpriteButton *GameController::initButton(string mark, Vec2 pos, EventKeyboard::KeyCode keyCode)
{
    UISpriteButton *button = createButton(mark);
    button->setPosition(pos);
    button->setKey(keyCode);
    addChild(button);
    
    return button;
}

void GameController::update(float delta)
{
    
}

UISpriteButton *GameController::createButton(string mark)
{
    UISpriteButton *button = UISpriteButton::create("image/ui/button/0.png",
                                                    "image/ui/button/1.png",
                                                    mark);
    button->_neutralTex->setAliasTexParameters();
    button->_pushedTex->setAliasTexParameters();
    button->_markSp->getTexture()->setAliasTexParameters();
    
    return button;
}

bool GameController::maru()
{
    return _maruButton->_isPushed;
}

bool GameController::batsu()
{
    return _batsuButton->_isPushed;
}

bool GameController::right()
{
    return _rightButton->_isPushed;
}

bool GameController::left()
{
    return _leftButton->_isPushed;
}

bool GameController::maru(int pushedFrame)
{
    return (_maruButton->_isPushed && _maruButton->_pushCount <= pushedFrame);
}

bool GameController::batsu(int pushedFrame)
{
    return (_batsuButton->_isPushed && _batsuButton->_pushCount <= pushedFrame);
}

bool GameController::right(int pushedFrame)
{
    return (_rightButton->_isPushed && _rightButton->_pushCount <= pushedFrame);
}

bool GameController::left(int pushedFrame)
{
    return (_leftButton->_isPushed && _leftButton->_pushCount <= pushedFrame);
}

float GameController::getUIHeight()
{
    return _uiBaseSp->getBoundingBox().size.height;
}

int GameController::getMaruPushCount()
{
    return _maruButton->_pushCount;
}

int GameController::getBatsuPushCount()
{
    return _batsuButton->_pushCount;
}

int GameController::getRightPushCount()
{
    return _rightButton->_pushCount;
}

int GameController::getLeftPushCount()
{
    return _leftButton->_pushCount;
}

bool GameController::maruReleased()
{
    return _maruButton->_isReleasedFrame;
}

bool GameController::batsuReleased()
{
    return _batsuButton->_isReleasedFrame;
}

bool GameController::leftReleased()
{
    return _leftButton->_isReleasedFrame;
}

bool GameController::rightReleased()
{
    return _rightButton->_isReleasedFrame;
}






