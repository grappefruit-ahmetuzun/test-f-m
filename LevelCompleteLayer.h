//
//  LevelCompleteLayer.h
//  FruitsKnife-mobile
//
//  Created by Slavik on 5/30/18.
//

#ifndef LevelCompleteLayer_h
#define LevelCompleteLayer_h

#include "GameLayer.h"
#include "Space.h"
#include "CoctailsObjectiveLarge.h"
#include "CoctailObjectiveUI.h"
#include "FortuneWheelLayer.h"

USING_NS_CC;

class LevelCompleteLayer : public GameLayer{
    
public:
    
    CREATE_FUNC(LevelCompleteLayer);
    
    LevelCompleteLayer(){}
    ~LevelCompleteLayer(){}
    
    CoctailsObjectiveLarge * objectives = nullptr;
    CoctailObjectiveUI     * objective_indicator = nullptr;
    
    SPButton * next_level_button   = nullptr;
    SPButton * claim_reward_button = nullptr;
    
    FortuneWheelLayer * _fortuneWheelLayer = nullptr;
    
    void show_next_level_button();
    void show_claim_reward_button();

    void animateOnEnter(int lvl);
    void animate_show_objectives();
    
    void on_claim_reward_press();
    
    Sprite * field                      = nullptr;
    Sprite * beamz                      = nullptr;
    SkeletonAnimation * _effect         = nullptr;
    Label * level_label                 = nullptr;
    CoctailsObjectiveLarge * obj        = nullptr;
    
};

#endif /* LevelCompleteLayer_h */
