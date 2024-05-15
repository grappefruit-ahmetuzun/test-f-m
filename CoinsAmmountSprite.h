//
//  CoinsAmmountSprite.hpp
//  SummerGames
//
//  Created by Marek on 7/17/16.
//
//

#ifndef CoinsAmmountSprite_hpp
#define CoinsAmmountSprite_hpp

#include "SPButton.h"

USING_NS_CC;

class CoinsAmmountSprite : public SPButton {
    
public:
    
    CoinsAmmountSprite():
    _labelOnRight(false)
    {}
    ~CoinsAmmountSprite()
    {};
    
    static CoinsAmmountSprite * createWithHeight(float height);
    
    void setCoins(int coint, bool animated = true);
    
    void update_coins(float dt);
    
    bool init() override;
    
    void fade_out(float duration,float delay);
    void fade_in(float duration,float delay);
    void animate_on_collect();
    
    Label  * getCoinsLabel();
    Sprite * getCoinSprite();
    Sprite * perfect_run = nullptr;
    
    void color_white();
    void color_dark();
    
    
    bool can_scale_on_collect = true;
    
    float getCoinHeight();
    
    std::string label_prefix = "";
    
    void color_black_n_white();
    void color_colorfull();
    
    float epmty_area = 0;
    
    float next_coins = 0;
    float coins_now  = 0;
    
private:
    
    Sprite * _coinSprite    = nullptr;
    Label  * _coinsLabel    = nullptr;
    
    Sprite * _bubble            = nullptr;
    Label  * _bubbleLabel       = nullptr;
    Sprite * _bubbleContainer   = nullptr;
    
    CC_SYNTHESIZE(bool, _labelOnRight, LabelOnRight);
    
    void setCurrentCoins(int coint);
    
};

#endif /* CoinsAmmountSprite_hpp */
