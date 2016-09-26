//
//  FDotLayer.h
//  Gabari
//
//  Created by Furukawa on 2016/09/14.
//
//

#ifndef __Gabari__FDotLayer__
#define __Gabari__FDotLayer__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "FCommon.h"
#include "FLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;
using namespace FGeneral;

class FDotLayer : public FLayer
{
public:
    
    static FDotLayer *create();
    virtual bool init();
    virtual void update(float delta);
    
    void addChild(Node *node);
    void addChild(Node *node, int zorder);
    
    Vector<Node*> _children;
    
    RenderTexture *_render;
};

#endif /* defined(__Gabari__FDotLayer__) */
