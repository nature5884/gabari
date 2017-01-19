//
//  Label.h
//  TextScript1
//
//  Created by Furukawa on 2014/10/28.
//
//

#ifndef __TextScript1__Label__
#define __TextScript1__Label__

#include <stdio.h>
#include "cocos2d.h"
#include "MultiResolution.h"

using namespace std;
using namespace cocos2d;

class TalkLabel: public cocos2d::Label
{
public:
    static TalkLabel *create(string str, string fontFile, int fontSize);
    bool init(string str, string fontFile, int fontSize);
    void update(float delta);
    
    void startRunString(string text, float dt);
    void endRunString();
    
    bool getRunning(){return running;};
    bool getRunFinish(){return runFinish;};
    
    static const int STRING_LINE_MAX;
    
private:
    
    int frameCnt;
    string baseString;
    float delayTime;
    int tempDelayTime;
    
    int lineCount;
    
    bool running;
    bool runFinish;
    bool cansel;
    
    void runString();
    
protected:
    
    
};

#endif /* defined(__TextScript1__Label__) */
