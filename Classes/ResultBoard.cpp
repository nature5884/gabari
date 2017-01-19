//
//  ResultBoard.cpp
//  Gabari
//
//  Created by 蔵元隼人 on 2017/01/12.
//
//

#include "ResultBoard.h"


ResultBoard* ResultBoard::create(int score)
{
    ResultBoard *pRet = new ResultBoard();
    
    if(pRet && pRet->init(score))
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

bool ResultBoard::init(int score)
{
    if(!Node::init())
    {
        return false;
    }
    
    _score = score;
    
   
    setupBoard();
    
    this->setPosition(designResolutionSize.width/2,designResolutionSize.height * 1.5f);
    
    this->runAction(Sequence::create(
                                     EaseBounceOut::create(MoveTo::create(1.0f, designResolutionSize/2)),
                                     CallFunc::create([=](){frontLb->startRunString("こんかいのスコア", 0.1f);}),
                                     NULL
                                     )
                    );
    
    
    this->scheduleUpdate();
    
    return true;
}

void ResultBoard::update(float delta)
{
    if(frontLb->getRunFinish() && !scoreLb->getRunning() && !scoreLb->getRunFinish())
    {
        char str[36];
        sprintf(str, "%d",_score);
        
        scoreLb->startRunString(str, 0.05f);
    }
}

void ResultBoard::setupBoard()
{
    _backBoard = Scale9Sprite::create("image/ui/waku.png", Rect(0, 0, 12, 12), Rect(4,4,4,4));
    _backBoard->setContentSize(Size(160, 120));
    _backBoard->setPosition(0,0);
    this->addChild(_backBoard);
    
    makeScoreText();
    
    
    
}

void ResultBoard::makeScoreText()
{
    Vec2 startPos;
    startPos.x = -_backBoard->getContentSize().width / 2.6f;
    startPos.y = _backBoard->getContentSize().height / 4.0f;
    
    
    frontLb = TalkLabel::create("", "fonts/misaki_gothic.ttf", 15);
    frontLb->setAnchorPoint(Vec2(0.0f, 0.5f));
    frontLb->setPosition(startPos);
    this->addChild(frontLb);
    
    int fontSize = 30;
    
    scoreLb = TalkLabel::create("", "fonts/misaki_gothic.ttf", fontSize);
    this->addChild(scoreLb);
    scoreLb->setPositionY(startPos.y - 30.0f - fontSize/2);
    
    
 }
















