//
//  EventDataLoader.h
//  Lost
//
//  Created by Furukawa on 2015/11/12.
//
//

#ifndef __Lost__EventDataLoader__
#define __Lost__EventDataLoader__

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class EventDataLoader
{
public:
    vector<string> _lineList;
    
    static EventDataLoader *_instance;
    static EventDataLoader *getInstance();
    
    void loadDataFromFile(string fileName);
    string getLine(unsigned int index);
    vector<string> getLineList(string strData);
    
};

#endif /* defined(__Lost__EventDataLoader__) */
