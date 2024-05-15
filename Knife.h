//
//  Knife.hpp
//  FruitsKnife-mobile
//
//  Created by Marek on 15/05/2018.
//

#ifndef Knife_hpp
#define Knife_hpp

#include "SPPhysicsSprite.h"
#include "Game.h"
#include "Space.h"
#include "CustomMotionStreak.h"
#include "Shop.h"

USING_NS_CC;

class Knife : public SPPhysicsSprite{
    
public:
    
    Knife():
    _fruits_hit_count(0)
    {}
    
    CREATE_FUNC(Knife);
    
    void prepare(b2World * world);
    void last_knife_shoot_effect();
    void add_beam();
    
    CC_SYNTHESIZE(int, _fruits_hit_count, Fruits_hit_count);
    
    void shoot();
    void update_shot(float dt);
    void tailEnable(std::string tail_name, float fade, float radius,  const cocos2d::Color3B color, float duration, std::function<void()> callback);
    void tailDisable();
    virtual void removeFromParentAndCleanup(bool cleanup) override;
    
    CustomMotionStreak * tail = nullptr;
    Sprite * beam = nullptr;
    
    Sprite * knife_skin = nullptr;
    
    void refresh_skin();
    
private:
    
};

#endif /* Knife_hpp */
