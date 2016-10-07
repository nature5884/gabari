//
//  Actor.cpp
//  Lost
//
//  Created by Furukawa on 2015/11/08.
//
//

#include "Actor.h"
#include "ActorDataLoader.h"
#include "AnimationManager.h"
#include "MapManager.h"
#include "GameController.h"
#include "EffectAnimation.h"
#include "ActorManager.h"

const int Actor::JUMP_POW_MAX = 5;
const int Actor::JUMP_BOOST_MAX = 30;
const float Actor::GRAVITY = 2.0f;

Actor *Actor::create(int no)
{
    Actor *pRet = new Actor();
    if(pRet && pRet->init(no))
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

bool Actor::init(int no)
{
    _running = true;
    
    if ( !Sprite::init() ) return false;
    
    auto dataLoader = ActorDataLoader::getInstance();
    
    _data = dataLoader->getActorDataFromNo(no);
    
    setName(_data.name);
    initWithFile(_data.file + "stand/0.png");
    getTexture()->setAliasTexParameters();
    
    setAnchorPoint(Vec2(0.5, 0));
    
    regAnim();
    
    _move = Vec2::ZERO;
    _force = Vec2::ZERO;
    _isLanding = false;
    _state = STAND;
    _preState = WALK;
    _isAttack = false;
    _isDestroy = false;
    
    _forceLimit = Vec2(1.2f, GRAVITY);
//    _forceLimit = Vec2::ONE;
    
    _kind = PLAYER;
    
    _hp = _data.hp;
    _preHp = _hp;
    
    _attackPow = 1;
    
    _isKinematic = false;
    
    scheduleUpdate();
    
    return true;
}

void Actor::regAnim()
{
    animationRegist("stand", 1, 100);
    animationRegist("walk", 4, 0.1);
    animationRegist("jump", 1, 100);
    animationRegist("attack", 2, 0.1);
}

void Actor::animationRegist(string actionName, int frameNum, float delay)
{
    if(isActionEnable(actionName))
    {
        AnimationManager::addAnimationCache(_data.file + actionName + "/",
                                            _data.name + actionName,
                                            frameNum,
                                            delay);
    }
    else
    {
        printf("%s の %s は　登録できへんで\n", _data.name.c_str(), actionName.c_str());
    }
}

void Actor::update(float delta)
{
    state();
    if(!_isKinematic) move();
    
    
    
    
    if(!_isDestroy && _hp <= 0)
    {
        destroy();
    }
    
    if(_hp > 0)
    {
        // ダメージ食らったら赤くするだろう？
        if(_hp != _preHp) setColor(Color3B(200, 100, 100));
        else setColor(Color3B::WHITE);
    }
    
    _preHp = _hp;
}

void Actor::move()
{
    if(_move.x < 0) setFlippedX(true);
    if(_move.x > 0) setFlippedX(false);
    
    // ジャンプ
    if(_jumpPow > 0)
    {
        _move.y += (float)(_jumpPow) * 2;
        _jumpPow --;
    }
    
    // 重力
    _force.y = _force.y - GRAVITY/10.0f;
    
    // ジャンプ中だったら空中のｘ移動量を減少させる
    if(!_isLanding)
    {
        _move.x *= 0.56;
    }
    
    _force.x += _move.x;
    _force.y += _move.y;
    
    // 力かかりすぎて超スピードのなるのを防いでます。
    if(_force.x > _forceLimit.x) _force.x = _forceLimit.x;
    if(_force.x < -_forceLimit.x) _force.x = -_forceLimit.x;
    
    if(_force.y > _forceLimit.y) _force.y = _forceLimit.y;
    if(_force.y < -_forceLimit.y) _force.y = -_forceLimit.y;
    
    
//    printf("forcex %.3f forcey %.3f\n", _force.x, _force.y);
    
    if(abs(_force.x) < 0.05) _force.x = 0;
//    if(abs(_force.y) < 0.05) _force.y = 0;
    
    if(_isAttack) _force = Vec2::ZERO;
    
    
    _prePos = _pos;
    _pos += _force;
    
    merikomiBack();
    
    // 着地していてボタン押してなかったらjumpBoost回復する
    if(_isLanding && !GameController::getInstance()->maru())
    {
        _jumpBoost = JUMP_BOOST_MAX;
    }
    
    // 力をすこしずつ弱めて惰性にしてる（ちょっとだけ）
    if(_force.x != 0)
        _force.x += 0.12 * (_force.x > 0 ? -1 : 1) * (_isLanding ? 1 : 0.4);
    if(_force.y != 0)
        _force.y += 0.12 * (_force.y > 0 ? -1 : 1);
    
    _move = Vec2::ZERO;
    
    _movedVec = _pos - _prePos;
}

void Actor::merikomiBack()
{
    setPosition(Vec2((int)_pos.x, (int)_pos.y));
    
    int hit = 0;
    int hitCnt = 0;
    vector<bool> hitDir = {false,false,false,false};
    
    
    while ((hit = hitCheck()) != -1)
    {
        if(hit != -1)
        {
            hitDir[hit] = true;
            hitCnt ++;
        }
        
        if(hit == 0)
        {
            _pos.x -= 1;
        }
        if(hit == 1)
        {
            _pos.y -= 1;
        }
        if(hit == 2)
        {
            _pos.x += 1;
        }
        if(hit == 3)
        {
            _pos.y += 1;
        }
        
        setPosition(Vec2((int)_pos.x, (int)_pos.y));
        
        if(hitCnt > 60) break;
    }
    
    // 当たった方向
    if(hitDir[0])     // 左
    {
        kabeHit();
    }
    if(hitDir[1])     // 上
    {
        tenjoHit();
    }
    if(hitDir[2])     // 右
    {
        kabeHit();
    }
    if(hitDir[3])     // 下
    {
        yukaHit();
    }
    
    if(!hitDir[3])    // 当たってない
    {
        _isLanding = false;
    }
    
    if(getName() == "gabari")
    {
        for(int i=0; i<4; i++)
        {
            if(hitDir[i]) printf("%d", i);
        }
        printf("\n");
    }
}

void Actor::state()
{
    if(_isDestroy) return;
    
    
    // _state保存
    _preState = _state;
    
    // if　なのは、優先順位つけるため　あえてだからね！
    if(_move.x != 0)
    {
        _state = WALK;
    }
    else
    {
        _state = STAND;
    }
    
    if(!_isLanding)
    {
        _state = JUMP;
    }
    
    if(_isAttack)
    {
        _state = ATTACK;
    }
    
    if(_preState != _state)
    {
        stopAllActions();
        
//        printf("l");
        
        switch (_state) {
            case STAND:
                if(isActionEnable("stand"))
                {
                    runAction(AnimationManager::createRepeatForever(_data.name + "stand"));
                }
                break;
                
            case WALK:
                if(isActionEnable("walk"))
                {
                    runAction(AnimationManager::createRepeatForever(_data.name + "walk"));
                }
                break;
                
            case JUMP:
                if(isActionEnable("jump"))
                {
                    runAction(AnimationManager::createRepeat(_data.name + "jump", 1));
                }
                break;
                
            case ATTACK:
                if(isActionEnable("attack"))
                {
                    runAction(Sequence::create(AnimationManager::createRepeat(_data.name + "attack", 1),
                                            CallFunc::create([=]()
                                                             {
                                                                 _isAttack = false;
                                                                 _state = STAND;
                                                             }),
                                            NULL)); // 仮でwalkのアニメーションつかうわ
                }
                break;
                
            default:
                break;
        }
    }
    
}

void Actor::attack()
{
    
}

int Actor::hitCheck()
{
    MapManager *mapManager = MapManager::getInstance();
    
    auto box = getBoundingBox();
    Vec2 centerPos = Vec2(box.getMidX(), box.getMidY());
    
    int gridSize = mapManager->_mapData.gridSize;
    Vec2 index = Vec2((int)(centerPos.x / gridSize), mapManager->_mapData.mapHeight-1 - (int)(centerPos.y / gridSize));
    
    int search = 4;
    
    for(int y = search; y >= -search; y--)
    {
        for(int x = -search; x <= search; x++)
        {
            Sprite *tile = mapManager->_mapData.tileData[index + Vec2(x,y)];
            if(tile == NULL)
                continue;
            
//            box.origin.x += box.size.width * 0.35;
//            box.size.width = box.size.width * 0.8;
//            box.origin.y += 1;
            
            auto topTile = mapManager->_mapData.tileData[index + Vec2(x, y-1)];
            auto bottomTile = mapManager->_mapData.tileData[index + Vec2(x, y+1)];
            auto rightTile = mapManager->_mapData.tileData[index + Vec2(x+1, y)];
            auto leftTile = mapManager->_mapData.tileData[index + Vec2(x-1, y)];
            
            auto tileBox = tile->getBoundingBox();
            tileBox.size = Size(mapManager->_mapData.gridSize, mapManager->_mapData.gridSize);
            
            if(tileBox.intersectsRect(box))
            {
                Vec2 myPos = Vec2(box.getMidX(), box.getMidY());
                Vec2 tilePos = Vec2(tileBox.getMidX(), tileBox.getMidY());
                
                Vec2 vec = myPos - tilePos;
//                Vec2 vec = tilePos - myPos;
                
                float inAngle = vec.getAngle() * 180 / M_PI + 90;
                
                while(inAngle < 0) inAngle += 360;
                while(inAngle > 360) inAngle -= 360;
                
                // 右
                if(inAngle >= 45 && inAngle <= 135 && rightTile == NULL)
                {
                    return 2;
                }
                // 左
                else if(inAngle >= 225 && inAngle <= 315 && leftTile == NULL)
                {
                    return 0;
                }
                // 下
                else if(inAngle > 135 && inAngle < 225 && topTile == NULL)
                {
                    return 3;
                }
                // 上
                else if((inAngle > 315 || inAngle < 45) && bottomTile == NULL)
                {
                    return 1;
                }
            }
        }
    }
    
    
    return -1;
}

int Actor::hitCheckFromPoint()
{
    MapManager *mapManager = MapManager::getInstance();
    
    auto box = getBoundingBox();
    Vec2 centerPos = Vec2(box.getMidX(), box.getMidY());
    
    int gridSize = mapManager->_mapData.gridSize;
    Vec2 index = Vec2((int)(centerPos.x / gridSize), mapManager->_mapData.mapHeight-1 - (int)(centerPos.y / gridSize));
    
    int search = 4;
    
    for(int y = -search; y <= search; y++)
    {
        for(int x = -search; x <= search; x++)
        {
            Sprite *tile = mapManager->_mapData.tileData[index + Vec2(x,y)];
            if(tile == NULL)
                continue;
            
            auto tileBox = tile->getBoundingBox();
            tileBox.size = Size(mapManager->_mapData.gridSize, mapManager->_mapData.gridSize);
            
            if(tileBox.containsPoint(_pos))
            {
                Vec2 myPos = _pos;
                Vec2 tilePos = Vec2(tileBox.getMidX(), tileBox.getMidY());
                
                Vec2 vec = myPos - tilePos;
                
                float inAngle = vec.getAngle() * 180 / M_PI + 90;
                
                while(inAngle < 0) inAngle += 360;
                while(inAngle > 360) inAngle -= 360;
                
                // 右
                if(inAngle >= 45 && inAngle < 135)
                {
                    return 2;
                }
                // 下
                else if(inAngle >= 135 && inAngle < 225)
                {
                    return 3;
                }
                // 左
                else if(inAngle >= 225 && inAngle < 315)
                {
                    return 0;
                }
                // 上
                else
                {
                    return 1;
                }
            }
        }
    }
    
    return -1;
}

void Actor::destroy()
{
    if(_isDestroy) return;
    _isDestroy = true;
    
    destroyEffect();
    
    stopAllActions();
    removeFromParent();
}

void Actor::destroyEffect()
{
    EffectAnimation *eff = EffectAnimation::create("image/effect/bon/", 2, 0.06);
    eff->setPosition(getPosition() + Vec2(0, getBoundingBox().size.height/2));
    eff->setRotation(90 * (rand()%3));
    getParent()->addChild(eff);
}

void Actor::damage(Actor *target)
{
    _hp -= target->_attackPow;
    
    damageEffect();
}

void Actor::damageEffect()
{
    
}

void Actor::kabeHit()
{
    
}

void Actor::yukaHit()
{
    _isLanding = true;
    _jumpBoost = 0;
}

void Actor::tenjoHit()
{
    _jumpBoost = 0;
}

bool Actor::isActionEnable(string actionName)
{
    for(auto act : _data.action)
    {
        if(act == actionName) return true;
    }
    
    return false;
}

Actor *Actor::hitCheckActor()
{
    for(auto child : ActorManager::getInstance()->getChildren())
    {
        Actor *actor = (Actor*)child;
        
        if(actor->getName() == "") continue;
        if(actor == this) continue;
        if(actor->_isDestroy) continue;
        
        if(actor->getBoundingBox().intersectsRect(getBoundingBox()))
        {
            return actor;
        }
        
    }
    
    return NULL;
}

Actor *Actor::hitCheckActorFromPoint()
{
    for(auto child : ActorManager::getInstance()->getChildren())
    {
        Actor *actor = (Actor*)child;
        
        if(actor->getName() == "") continue;
        if(actor == this) continue;
        if(actor->_isDestroy) continue;
        if(actor->_hp == 0) continue;
        
        if(actor->getBoundingBox().containsPoint(getPosition()))
        {
            return actor;
        }
        
    }
    
    return NULL;
}





















