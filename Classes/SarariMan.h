//
//  SarariMan.h
//  Lost
//
//  Created by Furukawa on 2015/11/10.
//
//

#ifndef __Lost__SarariMan__
#define __Lost__SarariMan__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "EnemyActor.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class SarariMan : public EnemyActor
{
public:
    
    static SarariMan *create(int no);
    bool init(int no) override;
    void update(float delta) override;
    
    void kabeHit() override;
    void destroy() override;
    void destroyEffect() override;
};

#endif /* defined(__Lost__SarariMan__) */
