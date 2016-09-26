//
//  FDotLayer.cpp
//  Gabari
//
//  Created by Furukawa on 2016/09/14.
//
//

#include "FDotLayer.h"


FDotLayer *FDotLayer::create()
{
    FDotLayer *pRet = new FDotLayer();
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

bool FDotLayer::init()
{
    if ( !FLayer::init() ) return false;
    
    
    _render = RenderTexture::create(designResolutionSize.width,
                                    designResolutionSize.height,
                                    Texture2D::PixelFormat::RGBA8888, 0);
    _render->setName("render");
    _render->setPosition(visibleCenter);
    _render->setVisible(true);
    Node::addChild(_render, INT_MAX);
    
    scheduleUpdate();
    return true;
}

void FDotLayer::update(float delta)
{
    
    _render->beginWithClear(0, 0, 0, 255);

//    visit();
    for(auto child : _children)
    {
        if(child->getName() == "render") continue;
        child->visit();
    }
    
    _render->end();
}

void FDotLayer::addChild(cocos2d::Node *node)
{
    addChild(node, 0);
    
//    _children.pushBack(node);
    
//    node->resume();
//    Node::addChild(node);
}

void FDotLayer::addChild(cocos2d::Node *node, int zorder)
{

    _children.pushBack(node);
    
    sortNodes(_children);
    node->_running = true;
}

















