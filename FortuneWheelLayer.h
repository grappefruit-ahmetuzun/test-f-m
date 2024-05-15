//
//  FortuneWheelLayer.hpp
//  FruitsKnife-mobile
//
//  Created by Slavik on 6/6/18.
//

#ifndef FortuneWheelLayer_h
#define FortuneWheelLayer_h

#include "GameLayer.h"
#include "Wheel.h"
#include "SPButton.h"
#include "FlyingObject.h"

USING_NS_CC;

class FortuneWheelLayer : public GameLayer{
    
public:
    CREATE_FUNC(FortuneWheelLayer);
    
    virtual bool init() override;
    
    FortuneWheelLayer(){}
    ~FortuneWheelLayer(){}
    
    virtual bool onTouchBegan(Touch *touch, Event *event) override;
    
    Sprite * _background = nullptr;
    
    Wheel * _fortune_wheel  = nullptr;
    Sprite * _black_arrow   = nullptr;
    
    SPButton * _spin_button         = nullptr;
    SPButton * _spin_again_button   = nullptr;
    SPButton * _nothanks_button     = nullptr;
    SPButton * _next_level_button   = nullptr;
    
    void update(float delta) override;
    
    void spin();
    void spin_again();
    
    bool spinning   = false;
    int spin_count  = 0;
    
    float _rotation_for_sound                   = 0;
    float _previous_wheel_rotation_for_sounds   = 0;
    
    void animate_on_start();
    void show_spin_button();
    void show_next_level_button();
    
    std::function<void(objetive_recipe_info,Vec2)> _did_win_callback = nullptr;
    
    void restart_scene();
};

#endif /* FortuneWheelLayer_hpp */
