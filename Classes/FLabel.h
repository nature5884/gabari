//
//  FLabel.h
//
//  Created by Furukawa on 2014/10/28.
//
//
#pragma execution_character_set("utf-8")

#ifndef __FLabel__
#define __FLabel__

#include <stdio.h>
#include "cocos2d.h"
#include "MultiResolution.h"
#include "SimpleAudioEngine.h"
#include "FCommon.h"

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;
using namespace FGeneral;

class FLabel: public cocos2d::Label
{
public:
    bool init(string str, string fontFile, int fontSize);
    static FLabel *create(string str, string fontFile, int fontSize);
    void update(float delta);
    
    void startRunString(string text, float dt);
    void endRunString();
    
    bool getRunning(){return running;};
    
    void setSE(string fileName);
    
    float delayTime;
    
    static const int STRING_LINE_MAX;
    
    string talkingChar;
    
private:
    
    int frameCnt;
    string baseString;
    int tempDelayTime;
    
    int lineCount;
    
    bool running;
    bool cansel;
    
    string _seFileName;
    
    void runString();
    
protected:
    
    
};

#endif /* defined(__TextScript1__Label__) */
