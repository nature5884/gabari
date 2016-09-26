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
    
    _kind = PLAYER;
    
    _hp = _data.hp;
    _preHp = _hp;
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
    move();
    
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
    
    // あたったんだよ
    bool isHitX = false;
    bool isHitY = false;
    
    setPositionX(getPositionX() + _force.x);
    
    // めり込んでたらちょっとずつもどす。
    float offsetX = 0.1 * (_force.x > 0 ? -1 : 1);
    if(_force.x == 0) offsetX = 0.1 * (isFlippedX()?1:-1);
    
    while(hitCheck())
    {
        if(_force.x == 0) break;
        setPositionX(getPositionX() + offsetX);
        
        isHitX = true;
    }
    
    if(isHitX)
    {
        kabeHit();
    }
    
    // 同じくY
    setPositionY(getPositionY() + _force.y);
    auto hitVec = hitCheckReturnVec2();
    _isLanding = false;
    
    float offsetY = 0.1 * (_force.y > 0 ? -1 : 1);
    while(hitCheck())
    {
        if(_force.y == 0) break;
        setPositionY(getPositionY() + offsetY);
        isHitY = true;
    }
    
    if(isHitY)
    {
        if(hitVec.y < 0)
        {
            yukaHit();
            _isLanding = true;
        }
        else if(hitVec.y > 0)
        {
            tenjoHit();
            _jumpBoost = 0;
        }
    }
    
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

bool Actor::hitCheck()
{
    MapManager *mapManager = MapManager::getInstance();
    
    int gridSize = mapManager->_mapData.gridSize;
    Vec2 index = Vec2((int)(getPositionX() / gridSize), mapManager->_mapData.mapHeight-1 - (int)(getPositionY() / gridSize));
    
    int search = 1;
    
    for(int y = -search; y <= search; y++)
    {
        for(int x = -search; x <= search; x++)
        {
            Sprite *tile = mapManager->_mapData.tileData[index + Vec2(x,y)];
            if(tile == NULL)
                continue;
            
            Rect box = getBoundingBox();
            box.origin.x += box.size.width * 0.35;
            box.size.width = box.size.width * 0.3;
            box.origin.y += 2;
            
            if(box.intersectsRect(tile->getBoundingBox()))
            {
                return true;
            }
        }
    }
    
    
    return false;
}

Vec2 Actor::hitCheckReturnVec2()
{
    MapManager *mapManager = MapManager::getInstance();
    
    int gridSize = mapManager->_mapData.gridSize;
    Vec2 index = Vec2((int)(getPositionX() / gridSize), mapManager->_mapData.mapHeight-1 - (int)(getPositionY() / gridSize));
    
    int search = 1;
    
    for(int y = -search; y <= search; y++)
    {
        for(int x = -search; x <= search; x++)
        {
            Sprite *tile = mapManager->_mapData.tileData[index + Vec2(x,y)];
            if(tile == NULL)
                continue;
            
            Rect box = getBoundingBox();
            box.origin.x += box.size.width * 0.35;
            box.size.width = box.size.width * 0.3;
            box.origin.y += 2;
            
            if(box.intersectsRect(tile->getBoundingBox()))
            {
                return tile->getPosition() - getPosition();
            }
        }
    }
    
    
    return Vec2::ZERO;
    
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
    _hp --;
    
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
    
}

void Actor::tenjoHit()
{
    
}

bool Actor::isActionEnable(string actionName)
{
    for(auto act : _data.action)
    {
        if(act == actionName) return true;
    }
    
    return false;
}






















