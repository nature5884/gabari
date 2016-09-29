//
//  FCommon.cpp
//  WAU
//
//  Created by Furukawa on 2016/02/05.
//
//
#pragma execution_character_set("utf-8")

#include "FCommon.h"

using namespace FGeneral;

bool FCommon::containsWorldPoint(cocos2d::Node *node, cocos2d::Vec2 pos)
{
    return getWorldHitBox(node).containsPoint(pos);
}

cocos2d::Rect FCommon::getWorldHitBox(cocos2d::Node *node)
{
//    Vec3 trans;
//    
//    node->getNodeToWorldTransform().getTranslation(&trans);
//    
//    return Rect(trans.x, trans.y, node->getBoundingBox().size.width, node->getBoundingBox().size.height);
//    
    Vec3 trans;
    Vec3 scale;
    node->getNodeToWorldTransform().getTranslation(&trans);
    node->getNodeToWorldTransform().getScale(&scale);
    auto hitBox = cocos2d::Rect(0,
                       0,
                       node->getContentSize().width * scale.x,
                       node->getContentSize().height * scale.y);
    
    Sprite *hitSprite = Sprite::create();
    hitSprite->setTextureRect(hitBox);
    hitSprite->setAnchorPoint(Vec2::ZERO);
    hitSprite->setRotation(node->getRotation());
    hitSprite->setPosition(Vec2(trans.x, trans.y));
    
    return hitSprite->getBoundingBox();
    
}

Vec2 FCommon::getWorldPos(cocos2d::Node *node)
{
    Vec3 trans;
    
    node->getNodeToWorldTransform().getTranslation(&trans);
    
    return Vec2(trans.x, trans.y);
}

float FCommon::getAngle(Node *nodeA, Node *nodeB)
{
    Vec2 start = getWorldPos(nodeA);
    Vec2 end = getWorldPos(nodeB);
    
    Vec2 angleVec = end - start;
    
    return angleVec.getAngle() * 180 / M_PI;
}

float FCommon::getAngle(cocos2d::Vec2 A, cocos2d::Vec2 B, cocos2d::Vec2 C)
{
    float angle = 0;
    
    Vec2 a = B - A;
    Vec2 b = B - C;
    
//    angle = a.getAngle(b);
    
    angle = acos( ( a.x*b.x + a.y*b.y ) / ( sqrtf(powf(a.x, 2) + powf(a.y, 2)) * sqrtf(powf(b.x, 2) + powf(b.y, 2)) ) );
    
    return angle;
}

int FCommon::getRand(int min, int max)
{
    // 被決定的な乱数生成器でシード生成器を生成
    std::random_device rnd;
    // メルセンヌ・ツイスタ 引数は初期シード値 ファンクタを渡す
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<int> rand100(min,max); // [0, 100]の一様乱数
    
    int r = rand100(mt);

    return r;
}

float FCommon::getRand()
{
//    int r = rand()%100;
//    
//    return r / 100.0f;
    
    
    return getRand(0, 100) / 100.0f;
}

Sprite *FCommon::createColorSprite(cocos2d::Color3B col)
{
    Sprite *black = Sprite::create();
    black->setTextureRect(cocos2d::Rect(0,0,designResolutionSize.width,designResolutionSize.height));
    black->setAnchorPoint(Vec2::ZERO);
    black->setColor(col);
    return black;
}

Sprite *FCommon::createBlack()
{
    return createColorSprite(Color3B::BLACK);
}

Rect FCommon::intersect(cocos2d::Rect a, cocos2d::Rect b)
{
    float sx = MAX(a.origin.x, b.origin.x);
    float sy = MAX(a.origin.y, b.origin.y);
    float ex = MIN(a.origin.x + a.size.width, b.origin.x + b.size.width);
    float ey = MIN(a.origin.y + a.size.height, b.origin.y + b.size.height);
    
    float w = ex - sx;
    float h = ey - sy;
    if (w > 0 && h > 0) {
        return Rect(sx, sy, w, h);
    }
    return Rect(0, 0, 0, 0); // 重なっていない
}






















