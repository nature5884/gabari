//
//  FCommon.h
//  WAU
//
//  Created by Furukawa on 2016/02/05.
//
//
#pragma execution_character_set("utf-8")

#ifndef __WAU__FCommon__
#define __WAU__FCommon__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;
using namespace extension;

namespace FGeneral
{
    class FCommon
    {
    public:
        static bool containsWorldPoint(Node *node, Vec2 pos);
        static cocos2d::Rect getWorldHitBox(Node *node);
        static Vec2 getWorldPos(Node *node);
        static float getAngle(Node *nodeA, Node *nodeB);
        static float getAngle(Vec2 A, Vec2 B, Vec2 C);
        static float getRand();
        static int getRand(int min, int max);
        static Sprite *createColorSprite(Color3B col);
        static Sprite *createBlack();
    };
    
    enum FDirection
    {
        DIR_UP,
        DIR_RIGHT,
        DIR_DOWN,
        DIR_LEFT,
        DIR_NONE,
    };
}


#endif /* defined(__WAU__FCommon__) */
