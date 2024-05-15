//
//  HudLayer.h
//  FruitsKnife-mobile
//
//  Created by Slavik on 5/15/18.
//

#ifndef HudLayer_h
#define HudLayer_h

#include "GameLayer.h"
#include "CoinsAmmountSprite.h"
#include "Space.h"
#include "PathIndicator.h"
#include "FruitsObjectiveBar.h"
#include "LevelBar.h"
#include "StarsField.h"
#include "CoctailObjectiveUI.h"

USING_NS_CC;

class HudLayer : public GameLayer{
    
public:
    CREATE_FUNC(HudLayer);
    
    HudLayer(){}
    ~HudLayer(){}
    
    virtual bool onTouchBegan(Touch *touch, Event *event) override;
    
    CoinsAmmountSprite      * _coins                    = nullptr;
    CoinsAmmountSprite      * _gems                     = nullptr;
    Label                   * _score_label              = nullptr;
    Label                   * _lifes_label              = nullptr;
    LevelBar                * _level_bar                = nullptr;
    CoctailObjectiveUI      * _coctails_objective  = nullptr;
    
    SPButton * settings_button = nullptr;
    SPButton * darkmode_button = nullptr;
    
    virtual bool init() override;
    void animate_menu_start();
    
    void refresh_coins(int custom_value, bool animated = true);
    void refresh_gems (int custom_value, bool animated = true);
    
    void animate_onGameStart();
    void animate_onGameEnd();
    
    void set_knifes_count(int count);
    void set_wave(int wave);
    //void set_lefes(int lifes);
    void set_level_percents(float percents);
    
    std::vector<Sprite *> _all_knifes;
    
    void refrsh_dark_mode_button();
    
};

#endif /* HudLayer_h */
