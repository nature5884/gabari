//
//  Gabari.h
//  Gabari
//
//  Created by Furukawa on 2016/09/22.
//
//

#ifndef __Gabari__Gabari__
#define __Gabari__Gabari__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "FCommon.h"
#include "Actor.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;
using namespace FGeneral;

class Gabari : public Actor
{
public:
    
    enum AttackMode
    {
        ATK_NONE,
        ATK_STANDBY,
        ATK_NOW,
        ATK_AFTER,
    };
    
    static Gabari *create(int no);
    virtual bool init(int no);
    void update(float delta);
    
    void attack();
    void damage(Actor *actor);
    
    void regAnim();
    
    void attackStandby();
    void attackNow();
    void attackAfter();
    
    static const int MUTEKI_FRAME;
    static const int ROTATION_SPEED;
    static const float ATTACK_SPEED;
    
    Actor *_targetActor;
    
    bool _isMuteki;
    int _mutekiCount;
    
    AttackMode _atkMode;
    bool _isAttackPushed;
    bool _preIsAttackPushed;
};

#endif /* defined(__Gabari__Gabari__) */
