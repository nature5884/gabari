//
//  FLabelButton.h
//  Tokuten
//
//  Created by Furukawa on 2016/09/06.
//
//

#ifndef __Tokuten__FLabelButton__
#define __Tokuten__FLabelButton__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "FCommon.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;
using namespace FGeneral;

class FLabelButton : public Scale9Sprite
{
public:
    static FLabelButton *create(string text, function<void()> func);
    virtual bool init(string text, function<void()> func);
    void update(float delta);
    
    void changeImage(string fileName);
    
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
    
    
    Label *_label;
    bool _isPushed;
    
    function<void()> _func;
    
    EventListenerTouchOneByOne *_touchListener;
};

#endif /* defined(__Tokuten__FLabelButton__) */
