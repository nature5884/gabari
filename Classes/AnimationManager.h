//
//  AnimationManager.h
//  TextScript1
//
//  Created by Furukawa on 2014/11/20.
//
//

#ifndef __TextScript1__AnimationManager__
#define __TextScript1__AnimationManager__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class AnimationManager
{
public:
    
    static void addAnimationCache(string path, string cacheName, int frameNum, float delay);
    static Repeat* createRepeat(string cacheName, unsigned int time);
    static RepeatForever* createRepeatForever(string cacheName);
    
    
private:
    
};


#endif /* defined(__TextScript1__AnimationManager__) */
