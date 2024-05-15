//
//  GameOverLayer.hpp
//  FruitsKnife-mobile
//
//  Created by Marek on 17/05/2018.
//

#ifndef GameOverLayer_hpp
#define GameOverLayer_hpp

#include "GameLayer.h"
#include "CoinsAmmountSprite.h"
#include "Space.h"

USING_NS_CC;

struct GameOverInfo{
    int score                       = 0;
    int wave                        = 0;
    int level                       = 0;
    int high_score                  = 0;
    bool is_highscore_now           = false;
};

class GameOverLayer : public GameLayer{
    
public:
    
    CREATE_FUNC(GameOverLayer);
    
     GameOverLayer(){}
    ~GameOverLayer(){}
    
    GameOverInfo _info;
    
    void animateOnEnter (GameOverInfo info, float delay = 0);
    
    
    SPButton * restart_button        = nullptr;
    SPButton * leaderboards_button   = nullptr;
    SPButton * home_button           = nullptr;
    SPButton * social_button         = nullptr;
    SPButton * coins_video_button    = nullptr;
    SPButton * gems_video_button     = nullptr;
    SPButton * customize_button      = nullptr;
    SPButton * no_ads_button         = nullptr;
    SPButton * game_promo_button     = nullptr;
    
};

#endif /* GameOverLayer_hpp */
