//
//  GabariScope.cpp
//  Gabari
//
//  Created by Furukawa on 2016/09/29.
//
//

#include "GabariScope.h"

GabariScope *GabariScope::create()
{
    GabariScope *pRet = new GabariScope();
    if(pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool GabariScope::init()
{
    if ( !Node::init() ) return false;
    
    _running = true;
    
    _circle = DrawNode::create();
    _circle->_running = true;
    _circle->setOpacity(255 * 0.5);
    addChild(_circle);
    
    _arrow = DrawNode::create();
    _arrow->_running = true;
    _arrow->setRotation(90);
    addChild(_arrow);
    
    
    _debug = DrawNode::create();
    _debug->_running = true;
    addChild(_debug);
    
    scheduleUpdate();
    return true;
}

void GabariScope::update(float delta)
{
    _circle->clear();
    _arrow->clear();
    
    drawScope(50);
    drawScope(50 * 0.5);
//    drawScope(50 * 0.6, -_arrow->getRotation());
//    drawScope(50 * 0.7, _arrow->getRotation());
    drawArrow(50, 6);
    drawArrow(50 * 0.5, 3);
}

void GabariScope::rotateScope(float r)
{
    _arrow->setRotation(r + 90);
}


void GabariScope::drawScope(int r)
{
    drawScope(r, 0);
}

void GabariScope::drawScope(int r, float rota)
{
    Color4F meterColor = Color4F(Color4B(255, 255, 255, _circle->getOpacity() * (getOpacity()/255.0f)));
    
    vector<Vec2> verts;
    int vertsCount = 50;
    
    rota = rota / 180 * M_PI;
    
    for(int i=0; i<vertsCount; i++)
    {
        
        Vec2 p = Vec2(cos(2*M_PI / vertsCount * i + rota), sin(2*M_PI / vertsCount * i + rota)) * r;
        verts.push_back(p);
        
        Vec2 origin = (i%5 == 0) ? p * 0.75 : p * 0.9;
        _circle->drawLine(origin, p, meterColor);
    }
    
    _circle->drawPolygon(&verts[0], vertsCount, Color4F(0,0,0,0), 0.5, meterColor);
    
}

void GabariScope::drawArrow(int r, int size)
{
    
    vector<Vec2> arrowVerts;
    int arrowSize = size;
    
    Color4F arrowColor = Color4F(Color4B(255, 96, 109, _arrow->getOpacity() * (getOpacity()/255.0f)));
    
    for(int i=0; i<3; i++)
    {
        Vec2 p = Vec2(cos(2*M_PI / 3 * i), sin(2*M_PI / 3 * i)) * arrowSize;
        arrowVerts.push_back(p + Vec2(r - arrowSize/2, 0));
    }
    
    _arrow->drawPolygon(&arrowVerts[0], arrowVerts.size(), arrowColor, 0, Color4F(0,0,0,0));
//    _arrow->drawLine(Vec2(r * 0.5, 0), Vec2(r, 0), arrowColor);
}










