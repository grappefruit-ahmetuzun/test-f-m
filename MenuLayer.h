//
//  MenuLayer.hpp
//  FruitsKnife-mobile
//
//  Created by Marek on 16/05/2018.
//

#ifndef MenuLayer_hpp
#define MenuLayer_hpp

#include "GameLayer.h"
#include "CoinsAmmountSprite.h"
#include "Space.h"

USING_NS_CC;

class MenuLayer : public GameLayer{
    
public:
    
    CREATE_FUNC(MenuLayer);
    
     MenuLayer(){}
    ~MenuLayer(){}
    
    void prepare();
    void animate_menu_start();
    
    Sprite  * logo                  = nullptr;
    Label   * tap_to_start_label    = nullptr;
    Label   * wave_label            = nullptr;
    
    SPButton * rate_button          = nullptr;
    SPButton * gift_button          = nullptr;
    SPButton * leaderboards_button  = nullptr;
    SPButton * customzie_button     = nullptr;
    
    void refrsh_dark_mode_button();
    
};

#endif /* MenuLayer_hpp */
