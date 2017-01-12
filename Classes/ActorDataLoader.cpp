//
//  ActorDataLoader.cpp
//  ActorsDataLoader
//
//  Created by Furukawa on 2015/07/01.
//  Copyright (c) 2015年 Furukawa. All rights reserved.
//

#include "ActorDataLoader.h"

ActorDataLoader *ActorDataLoader::instance = NULL;

ActorDataLoader *ActorDataLoader::getInstance()
{
    if(!instance) instance = new ActorDataLoader();
    
    return instance;
}


ActorDataLoader::ActorDataLoader()
{
    _actData = getActorDataFromFileName("actor/data.txt");
}

ActorDataLoader::~ActorDataLoader()
{
    delete [] instance;
}

vector<Actor::ActorData> ActorDataLoader::getActorData()
{
    return _actData;
}


int ActorDataLoader::getActorNoFromName(string name)
{
    for(auto act : _actData)
    {
        if(act.name == name) return act.no;
    }
    
    return -1;
}

Actor::ActorData ActorDataLoader::getActorDataFromNo(int n)
{
    for(auto act : _actData)
    {
        if(act.no == n) return act;
    }
    
    return _actData[0];
}

void ActorDataLoader::disp(vector<vector<string> > data)
{
    for(auto list : data)
    {
        for(auto str : list)
        {
            for(auto c : str)
            {
                printf("%c", c);
            }
            printf("\t");
        }
        printf("\n");
    }
    
}

vector<vector<vector<string>>> ActorDataLoader::getDataFromFile(string fileName)
{
    // 一度ファイルの中身をstringに全コピーする
    string data = FileUtils::getInstance()->getStringFromFile(fileName);
    
    int count = 0;
    int dataIndex = 0;
    int itemIndex = 0;
    bool isCommentLine = false;
    string str = "";
    
    vector<string> temp;
    vector<vector<string>> tsvData;
    vector<vector<vector<string>>> dataList;
    
    
    while (count < data.size())
    {
        // 「//」でコメント
        if(data.size() > count + 1 &&
           data[count] == '/' && data[count+1] == '/') isCommentLine = true;
        
        // 改行きたらコメントおわり
        if(isCommentLine)
        {
            if(data[count] == '\n') isCommentLine = false;
        }
        
        // タブで次項
        else if(data[count] == '\t')
        {
            if(str != "")
            {
                temp.push_back(str);
                str = "";
                itemIndex ++;
            }
        }
        
        // 改行で次の行
        else if(data[count] == '\n')
        {
            // データのくぎり
            if(str == "end")
            {
                dataList.push_back(tsvData);
                tsvData.clear();
                temp.clear();
                itemIndex = 0;
                dataIndex ++;
                str = "";
            }
            else if(temp.size() > 0)
            {
                temp.push_back(str);
                tsvData.push_back(temp);
                temp.clear();
                itemIndex = 0;
                dataIndex ++;
                str = "";
            }
        }
        
        else if(data[count] == '\r')
        {
            // 読み飛ばす
        }
        
        else
        {
            str.push_back(data[count]);
        }
        
        count++;
    }
    
    return dataList;
}

vector<Actor::ActorData> ActorDataLoader::getActorDataFromFileName(string fileName)
{
    vector<Actor::ActorData> actData;
    
    auto dataList = getDataFromFile(fileName);
    
    
    for(auto tsvData : dataList)
    {
        Actor::ActorData act;
        for(auto data : tsvData)
        {
            if(data.size() < 2) continue;
            
            auto head = data[0];
            
            if(head == "no") act.no = stoi(data[1]);
            else if(head == "name") act.name = data[1];
            else if(head == "image") act.file = data[1];
            else if(head == "speed") act.speed = stof(data[1]);
            else if(head == "action") act.action = getStringList(data[1]);
            else if(head == "hp") act.hp = stoi(data[1]);
        }
        
        actData.push_back(act);
    }
    
    return actData;
}

vector<string> ActorDataLoader::getStringList(string data)
{
    vector<string> strList;
    
    int count = 0;
    string str = "";
    while(count < data.size())
    {
        if(data[count] == ',' || data.size() == count+1)
        {
            if(data.size() == count+1) str += data[count];
            
            strList.push_back(str);
            str = "";
        }
        else
        {
            str += data[count];
        }
        
        count ++;
    }
    
    
    return strList;
}

map<string, int> ActorDataLoader::getMapList(string data)
{
    map<string, int> mapData;
    
    int count = 0;
    bool isKey = true;
    string key = "";
    string str = "";
    int dataIndex = 0;
    
    while(count < data.size())
    {
        if(data[count] == ':' || data[count] == '\t' || data.size() == count+1)
        {
            if(isKey)
            {
                key = str;
                isKey = false;
            }
            else
            {
                mapData[key] = stoi(str);
                dataIndex ++;
                isKey = true;
            }
            str = "";
        }
        else
        {
            str += data[count];
        }
        
        count ++;
    }
    
    return mapData;
}
































