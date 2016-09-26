//
//  MapDataLoader.cpp
//  Lost
//
//  Created by Furukawa on 2015/11/08.
//
//

#include "MapDataLoader.h"

MapDataLoader *MapDataLoader::_instance;

MapDataLoader *MapDataLoader::getInstance()
{
    if(!_instance)
    {
        _instance = new MapDataLoader();
    }
    
    return _instance;
}

MapManager::MapData MapDataLoader::getMapData(string fileName)
{
    MapManager::MapData data;
    
    string strData = FileUtils::getInstance()->getStringFromFile(fileName);
    
    vector<string> line = getLineList(strData);
    string mapDataStr;
    
    for(string s : line)
    {
        // コメントとばす
        if(s.size() >= 2 && s[0] == '/' && s[1] == '/') continue;
        
        // 定数や、参照するファイルネームが書かれた行
        if(s[0] == '@' || s[0] == '#')
        {
            StringAndString buf = getStringAndString(s);
            
            if(s[0] == '@')
            {
                data.constValue[buf.strA] = stoi(buf.strB);
            }
            else if(s[0] == '#')
            {
                data.chipFileName[stoi(buf.strA)] = buf.strB;
            }
            
            continue;
        }
        
        // それ以外はmapdataだと思う
        else
        {
            mapDataStr += s;
        }
    }
    
    data.mapWidth = data.constValue["mapWidth"];
    data.mapHeight = data.constValue["mapHeight"];
    data.gridSize = data.constValue["gridSize"];
    
    data.mapData = getMapArrayFromString(mapDataStr,
                                         data.constValue["mapWidth"],
                                         data.constValue["mapHeight"]);
//    Vec2 pos = Vec2::ZERO;
//    for(int y=0; y<data.constValue["mapHeight"]; y++)
//    {
//        for(int x=0; x<data.constValue["mapWidth"]; x++)
//        {
//            pos = Vec2(x, y);
//            printf("%d ", data.mapData[pos]);
//        }
//        puts("");
//    }
    
    return data;
}

map<Vec2, int> MapDataLoader::getMapArrayFromString(string str, int w, int h)
{
    map<Vec2, int> data;
    
    string s;
    int value;
    
    Vec2 pos = Vec2::ZERO;
    
    for(char c : str)
    {
        if(c == ',')
        {
//            printf("%s ", s.c_str());
            value = stoi(s);
            data[pos] = value;
            s.clear();
            
            pos.x ++;
            if(pos.x == w)
            {
                pos.x = 0;
                pos.y ++;
            }
            
            continue;
        }
        
        s.push_back(c);
    }
    
    return data;
}

vector<string> MapDataLoader::getLineList(string strData)
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
                line.push_back(str);
                str.clear();
            }
            
            continue;
        }
        
        str.push_back(c);
    }
    
    for(string s : line)
    {
        puts(s.c_str());
    }
    puts("");
    
    return line;
}

MapDataLoader::StringAndString MapDataLoader::getStringAndString(string str)
{
    StringAndString buf;
    bool next = false;
    
    string strA;
    string strB;
    
    for(char c : str)
    {
        if(c == '@' || c == '#') continue;
        if(c == '\t')
        {
            next = true;
            continue;
        }
        
        if(!next)
        {
            strA.push_back(c);
        }
        else
        {
            strB.push_back(c);
        }
    }
    
    buf.strA = strA;
    buf.strB = strB;
    
    return buf;
}













