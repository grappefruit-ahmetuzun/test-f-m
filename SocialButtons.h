//
//  SocialButtons.h
//  FruitsKnife-mobile
//
//  Created by Slavik on 6/6/18.
//

#ifndef SocialButtons_h
#define SocialButtons_h

#include "cocos2d.h"
#include "Shop.h"

USING_NS_CC;

class SocialButtons : public Sprite{
    
public:
    
    CREATE_FUNC(SocialButtons);
    
    void prepare(float width);
    
public:
    
    std::function<void(int, float, Vec2)> _social_reward_give_callback = nullptr;
    
    static bool get_social_reward(int status){
        return SPUserDefault::getInstance()->getBoolForKey(StringUtils::format("social_reward_%i", status).c_str());
    }
    static void set_social_reward(int status){
        SPUserDefault::getInstance()->setBoolForKey(StringUtils::format("social_reward_%i", status).c_str(), true);
    }
    
};

#endif /* SocialButtons_h */
