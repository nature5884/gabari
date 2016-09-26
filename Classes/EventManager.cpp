//
//  EventManager.cpp
//  Lost
//
//  Created by Furukawa on 2015/11/12.
//
//

#include "EventManager.h"
#include "TalkEventLayer.h"
#include "MapManager.h"

EventManager *EventManager::_instance;

EventManager *EventManager::getInstance()
{
    if(!_instance)
    {
        _instance = new EventManager();
    }
    
    return _instance;
}

void EventManager::init(int eventNo)
{
    _eventDataLoader = EventDataLoader::getInstance();
    
    char fileName[256];
    sprintf(fileName, "event/%d.txt", eventNo);
    _eventDataLoader->loadDataFromFile(fileName);
    
    _index = 0;
    _eventState = TALK;
    
    _isChoosed = false;
    _chooseAnswer = false;
}

void EventManager::update()
{
    auto gameCtrl = GameController::getInstance();
    auto talk = TalkEventLayer::getInstance();
    
    
    if(_eventState == TALK)
    {
        if(talk->_isAppeared && !talk->_talkLabel->getRunning() && gameCtrl->maruReleased())
        {
            if(_eventDataLoader->_lineList.size() > _index)
            {
                run();
            }
            else
            {
                talk->disappear();
            }
        }
        else if(talk->_isAppeared && gameCtrl->maruReleased())
        {
            talk->_talkLabel->endRunString();
        }
    }
    else if(_eventState == CHOOSE)
    {
        if(gameCtrl->maruReleased() || gameCtrl->batsuReleased())
        {
            if(gameCtrl->maruReleased()) _chooseAnswer = true;
            else _chooseAnswer = false;
            
            if(_chooseAnswer)
            {
                init(_jumpNo[0]);
            }
            else
            {
                init(_jumpNo[1]);
            }
            
            talk->chooseEnd();
            
            run();
        }
    }
    
    
}

void EventManager::run()
{
    run(_index);
    _index ++;
}

void EventManager::run(int index)
{
    string script = _eventDataLoader->getLine(index);
    
    auto talk = TalkEventLayer::getInstance();
    
//    puts(script.c_str());
    
    if(script[0] == '@')
    {
        string methodName;
        string argStr;
        bool isName = true;
        
        // コマンド名を抽出
        for(char c : script)
        {
            if(c == '@') continue;
            
            if(c == '\t')
            {
                isName = false;
                continue;
            }
            
            if(isName) methodName += c;
            else argStr += c;
        }
        
        // , で句切られたStringの値を切り分けてvectorに
        vector<string> args = getStringList(argStr);
        
        // 選択肢コマンド
        if(methodName == "choose")
        {
            _eventState = CHOOSE;
            _isChoosed = false;
            
            _jumpNo[0] = stoi(args[2]);
            _jumpNo[1] = stoi(args[3]);
            
            talk->choose(args[0], args[1]);
        }
        
        // マップチェンジコマンド
        if(methodName == "map")
        {
            talk->disappear();
            
            int mapNo = stoi(args[0]);
            
            auto mapMgr = MapManager::getInstance();
            float duration = 0.3;
            talk->fadeIn(duration);
            mapMgr->runAction(Sequence::create(DelayTime::create(duration),
                                               CallFunc::create([=]()
                                                                {
                                                                    mapMgr->transitionMap(mapNo);
                                                                    talk->fadeOut(duration);
                                                                }),
                                               NULL));
        }
    }
    else
    {
        talk->_isAppeared = false;
        talk->appear();
        
        string talkStr;
        
        // セリフはそのまま出力するかっていえばそうでもない。
        for(auto c : script)
        {
            // 省く文字
            if(c == ' ') continue;
            
            // ＆は、改行だけど行間稼ぐために２回改行する
            if(c == '&')
            {
                c = '\n';
                talkStr += '\n';
            }
            
            talkStr += c;
        }
        
        _eventState = TALK;
        
        talk->talk(talkStr);
    }
}

vector<string> EventManager::getStringList(string str)
{
    vector<string> list;
    string buf;
    
    for(char c : str)
    {
        if( c == ',' )
        {
            if(buf.size() > 0) list.push_back(buf);
            buf.clear();
            continue;
        }
        
        buf += c;
    }
    
    if(buf.size() > 0) list.push_back(buf);
    
    return list;
}



























