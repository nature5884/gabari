//
//  EventDataLoader.cpp
//  Lost
//
//  Created by Furukawa on 2015/11/12.
//
//

#include "EventDataLoader.h"

EventDataLoader *EventDataLoader::_instance;

EventDataLoader *EventDataLoader::getInstance()
{
    if(!_instance)
    {
        _instance = new EventDataLoader();
    }
    
    return _instance;
}

void EventDataLoader::loadDataFromFile(string fileName)
{
    _lineList = getLineList(FileUtils::getInstance()->getStringFromFile(fileName));
}

string EventDataLoader::getLine(unsigned int index)
{
    if(_lineList.size()  <= index)
    {
        return _lineList[0];
    }
    
    return _lineList[index];
}

vector<string> EventDataLoader::getLineList(string strData)
{
    vector<string> line;
    
    string str;
    
    for(char c : strData)
    {
        // こいついらんねん
        if(c == '\r') continue;
        
        // なんか文字はいってて、改行か終了コードきたら次の行いく
        if(c == '\n' || c == '\0')
        {
            if(str.size() > 0)
            {
                if(!(str[0] == '/' && str[1] == '/'))
                {
                    line.push_back(str);
                }
                str.clear();
            }
            
            continue;
        }
        
        str.push_back(c);
    }
    
//    for(string s : line)
//    {
//        puts(s.c_str());
//    }
//    puts("");
    
    return line;
}

