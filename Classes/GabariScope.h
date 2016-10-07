//
//  GabariScope.h
//  Gabari
//
//  Created by Furukawa on 2016/09/29.
//
//

#ifndef __Gabari__GabariScope__
#define __Gabari__GabariScope__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "FCommon.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;
using namespace FGeneral;

class GabariScope : public Node
{
public:
    static GabariScope *create();
    virtual bool init();
    void update(float delta);
    
    void drawScope(int r);
    void drawScope(int r, float rota);
    void drawArrow(int r, int size);
    
    void rotateScope(float r);
    
    DrawNode *_circle;
    DrawNode *_arrow;
    
    DrawNode *_debug;
    
};

#endif /* defined(__Gabari__GabariScope__) */
