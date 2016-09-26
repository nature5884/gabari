//
//  EventManager.h
//  Lost
//
//  Created by Furukawa on 2015/11/12.
//
//

#ifndef __Lost__EventManager__
#define __Lost__EventManager__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "EventDataLoader.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class EventManager
{
public:
    
    enum EventState
    {
        TALK,
        CHOOSE,
    };
    
    EventState _eventState;
    
    int _index;
    EventDataLoader *_eventDataLoader;
    
    bool _isChoosed;
    bool _chooseAnswer;
    int _jumpNo[2];
    
    static EventManager *_instance;
    static EventManager *getInstance();
    
    void init(int eventNo);
    void update();
    
    void run();
    void run(int index);
    
    vector<string> getStringList(string str);
    
};

#endif /* defined(__Lost__EventManager__) */
