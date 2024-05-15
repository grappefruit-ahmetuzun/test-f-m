//
//  Gameplayb2d.h
//  hiball
//
//  Created by Marek on 1/8/17.
//
//

#ifndef Gameplayb2d_h
#define Gameplayb2d_h

#include "SPPhysicsLayer.h"
#include "Game.h"
#include "Knife.h"
#include "Fruit.h"
#include "Patterns.h"
#include "HudLayer.h"
#include "Pattern.h"
#include "PathField.h"
#include "Mixer.h"
#include "Recipes.h"
#include "Coctail.h"
#include "FortuneWheelLayer.h"
#include "FlyingObject.h"

USING_NS_CC;

class GameplayDelegate{
public:

    virtual void gameplay_score_didchange   (int score){};
    virtual void gameplay_gameover          (float delay){};
    virtual void gameplay_slow_motion       (bool enable){};
    virtual void gameplay_miss_star         (){};
    virtual void gameplay_level_complete    (){};
    virtual void gameplay_coins_fly         (Vec2 point,FLYING_OBJECT_TYPE object_type,std::function<void()> on_end){};
    
};

class Gameplayb2d :
public SPPhysicsLayer
{
public:
    
    Gameplayb2d():
    _score(0),
    _delegate(nullptr),
    _wave(0),
    _gameOver(false),
    _gameStarted(false),
    _orderId(0),
    _knife_count(0),
    _fruits_in_pattern(0),
    _canSpawnPattern(false),
    _lifesCount(0),
    _canGiveAnotherKnife(false),
    _fruitsHitCount(0)
    {};
    ~Gameplayb2d(){
    }
    
    virtual bool init() override;
    CREATE_FUNC(Gameplayb2d);
    
    // Game Objects
    
    Knife * add_knife();
    Fruit * spawn_object(fruit_info info,Node *parent);
    void do_phase(float delay = 0);
    
    virtual void update                         (float dt) override;
    
    void collisionContactDidBegin(SPPhysicsSprite *sp1, SPPhysicsSprite *sp2, Point contactPoint, SPPhysicsContact contact) override;
    void collisionContactDidEnd(SPPhysicsSprite *sp1,SPPhysicsSprite *sp2,Point contactPoint, SPPhysicsContact contact) override;
    void collisionHandle(SPPhysicsSprite *sp1,SPPhysicsSprite *sp2, SPPhysicsContact contact, bool collision_begin, bool collision_end);
    virtual bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) override;
    
    // touches
    
    bool onTouchBegan(Touch *touch, Event *event) override;
    void onTouchMoved(Touch *touch, Event *event) override;
    void onTouchEnded(Touch *touch, Event *event) override;
    
    void gameplay_prepare();
    void gameplay_start();
    void game_continue_watched();
    void game_over(float delay);
    
    CC_SYNTHESIZE(int,                   _score,                Score);
    CC_SYNTHESIZE(int,                   _wave,                 Wave);
    CC_SYNTHESIZE(int,                   _orderId,              OrderId);
    CC_SYNTHESIZE(bool,                  _gameOver,             GameOver);
    CC_SYNTHESIZE(bool,                  _gameStarted,          GameStarted);
    CC_SYNTHESIZE(GameplayDelegate *,    _delegate,             Delegate);
    CC_SYNTHESIZE(int,                   _knife_count,          Knife_count);
    CC_SYNTHESIZE(int,                   _fruits_in_pattern,    Fruits_in_pattern);
    CC_SYNTHESIZE(int,                   _lifesCount,           LifesCount);
    CC_SYNTHESIZE(bool,                  _canSpawnPattern,      CanSpawnPattern);
    CC_SYNTHESIZE(bool,                  _canGiveAnotherKnife,  CanGiveAnotherKnife);
    CC_SYNTHESIZE(int,                   _fruitsHitCount,       FruitsHitCount);
    
    level_info current_level;

    bool                  _do_phase              = false;
    bool                 _continue_showed        = false;
    
    HudLayer        * _hud   = nullptr;
    
    PathField * pattern = nullptr;
    
    std::vector<Knife*>     _knifes;
    std::vector<Fruit*>     _fruits;
    std::vector<Node*>      _nodes_to_delete;
    std::vector<fruit_type> _fruits_in_mixer;
    std::vector<Coctail *>  _coctails_on_table;

    void fruitSplash(fruit_type _type, Point _position, int side);
    void fruitFlyToBlender(fruit_type _type, Point _position, int side);
    void showCoctailReward(RECIPE_TYPES recipe_type);
    
    void getCoctail(RECIPE_TYPES _type);
    void add_score_label(int score, Point pos, bool is_perfect);
    void playFriutHitSound(fruit_type _type);
    
    Sprite * table  = nullptr;
    Mixer * mixer   = nullptr;
    
    Color3B last_fruit_color = Color3B(255, 255, 255);
    
    void refresh_dark_mode();
    void refresh_weapon();
    
};

#endif /* Gameplayb2d_h */
