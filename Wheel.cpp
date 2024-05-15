//
//  Wheel.cpp
//  Dottz
//
//  Created by Slavik on 4/26/17.
//
//

#include "Wheel.h"


bool Wheel::init(){
    if (Sprite::initWithFile("fortune_wheel/fortune.png")) {
        

        return true;
    }
    
    return false;
}

void Wheel::prepare(){
    
    std::vector<objetive_recipe_info> fortune_wheel_objects = Recipes::get_objective_recipes();
    
    float radius = (360.0f / fortune_wheel_objects.size());
    
    for (int i = 0; i < fortune_wheel_objects.size(); i++) {
        
        objetive_recipe_info item = fortune_wheel_objects.at(i);
        
        std::string texture_name = WheelPart::getPartImage(item.recipe_category);
        
        WheelPart * part = WheelPart::create();
        part->index = i;
        part->index_of_manager = i;
        part->setPosition(getContentSize()/2);
        part->setScale(getContentSize().width * 0.98f / part->getContentSize().width);
        addChild(part, 10 + i);

        part->prepare(item);
        part->update_positions((int)fortune_wheel_objects.size());
        _all_parts.push_back(part);
        
        part->hide_all_content();
    }
    
    setRotation(-radius/2);
    
    
    Sprite * center = Sprite::create("fortune_wheel/center.png");
    center->setScale(getContentSize().width * 0.2f / center->getContentSize().width);
    center->setPosition(getContentSize()/2);
    addChild(center, 999);
}

WheelPart * Wheel::get_part_by_index(int index){
    for (int i = 0; i < _all_parts.size(); i++) {
        WheelPart * p = _all_parts.at(i);
        
        if (p->index_of_manager == index) {
            return p;
        }
    }
    return nullptr;
}

WheelPart * Wheel::get_winner_part(int spin_index){
    
    for (int i = 0; i < _all_parts.size(); i++) {
        WheelPart * p = _all_parts.at(i);
        
        objetive_recipe_info _item = p->_item;
        if (spin_index == 1) {
            if (_item.is_winner_1 == true) {
                return p;
            }
        }
        else if (spin_index == 2){
            if (_item.is_winner_2 == true) {
                return p;
            }
        }
    }
    return nullptr;
}

void Wheel::remove_part(WheelPart * part){
    
    part->setLocalZOrder(0);
    
    float animation_duration = 0.4f;
    float erase_duration     = 2.65f;
    
    for (int i = 0; i < _all_parts.size(); i++) {
        WheelPart * p = _all_parts.at(i);
        
        if (part == p) {
            _all_parts.erase(_all_parts.begin() + i);
            break;
        }
    }
    
    auto delay_            = DelayTime::create(0.3f);
    auto scale             = ScaleTo::create(animation_duration, 0);
    auto ease_rotate_old   = EaseInOut::create(scale, erase_duration);
    auto callf             = CallFunc::create([this]{
        can_spin = true;
    });
    auto remove            = RemoveSelf::create();
    auto seq               = Sequence::create(delay_, ease_rotate_old, callf, remove, NULL);
    
    part->runAction(seq);
    
    
    auto delay_for_update  = DelayTime::create(0.3f);
    auto callf_for_update  = CallFunc::create([this]{
        for (int i = 0; i < _all_parts.size(); i++) {
            WheelPart * part = _all_parts.at(i);
            part->index = i;
            part->index_of_manager = i;
            part->update_positions((int)_all_parts.size(), true);
        }
    });
    auto seq_for_update    = Sequence::create(delay_for_update, callf_for_update, NULL);
    runAction(seq_for_update);
}
