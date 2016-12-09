//
//  TitleScene.h
//  Gabari
//
//  Created by Kobayashi on 2016/12/09.
//
//

#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "GameController.h"
#include "GameLayer.h"
#include "TalkEventLayer.h"
#include "FCommon.h"
#include "FDotLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class TitleScene : public Layer
{
public:
	static Scene *createScene();
	static TitleScene *create();
	virtual bool init();
	void update(float delta);

	GameController *_controller;
	GameLayer *_gameLayer;

	TalkEventLayer *_talkEventLayer;

};

#endif TITLE_SCENE_H