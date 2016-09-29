//
//  Actor.h
//  Lost
//
//  Created by Furukawa on 2015/11/08.
//
//

#ifndef __Lost__Actor__
#define __Lost__Actor__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MultiResolution.h"
#include "FCommon.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;
using namespace FGeneral;

class Actor : public Sprite
{
public:
    struct ActorData
    {
        int no;
        string name;
        string file;
        vector<string> action;
        float speed;
        int hp;
    };
    
    enum ActorKind
    {
        PLAYER,
        NPC,
        ENEMY,
        ITEM,
    };
    
    enum ActorState
    {
        STAND,
        WALK,
        JUMP,
        ATTACK,
    };
    
    static const int JUMP_POW_MAX;      // ジャンプしたときに与えるチカラ
    static const int JUMP_BOOST_MAX;    // ジャンプふんばるチカラ
    static const float GRAVITY;
    
    ActorData _data;
    Vec2 _move;             // キャラにかけたい力
    Vec2 _force;            // キャラにかかっている力
    float _jumpPow;         // ジャンプのチカラ（現在の）
    int _jumpBoost;         // ジャンプふんばり力
    bool _isLanding;        // 着地してるか
    bool _isAttack;         // 攻撃中か
    int _hp;                // HP
    int _preHp;             // 1フレーム前のhp
    bool _isDestroy;          // 消滅したか
    
    int _attackPow;         // 攻撃力
    
    Vec2 _prePos;
    Vec2 _pos;              // ポジション
    Vec2 _movedVec;
    
    Vec2 _forceLimit;
    
    ActorState _state;      // ジャンプ中かとかそういう状態（アニメーションに使う）
    ActorState _preState;   // １フレーム前の_state
    
    ActorKind _kind;
    
    static Actor *create(int no);
    virtual bool init(int no);
    virtual void update(float delta);
    
    int hitCheck();    // マップとの当たり判定
    int hitCheckFromPoint();    // マップとの当たり判定（ポジションver)
    Actor *hitCheckActor();
    Actor *hitCheckActorFromPoint();
    
    void merikomiBack();
    
    void move();    // 座標の移動と当たり判定の処理（移動、ジャンプ等）
    virtual void state();   // アニメーションを状態で推移する
    
    virtual void attack();  // 攻撃する
    virtual void destroy(); // 消滅
    virtual void destroyEffect();   // 消滅時のエフェクト
    virtual void damage(Actor *target);  // 他のアクターに当たったとき
    virtual void damageEffect();         // ダメージエフェクト
    
    virtual void kabeHit();     // 壁にあたったとき
    virtual void yukaHit();     // 床にあたったとき
    virtual void tenjoHit();    // 天井にあたったとき
    
    virtual void regAnim();     // アニメーション登録するところ
    void animationRegist(string actionName, int frameNum, float delay);     // アニメーション登録
    bool isActionEnable(string actionName);
    
};

#endif /* defined(__Lost__Actor__) */
