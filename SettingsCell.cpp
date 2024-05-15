//
//  SettingsCell.cpp
//  hiball
//
//  Created by Marek on 1/7/17.
//
//

#include "SettingsCell.h"
#include "Game.h"
#include "Space.h"

void SettingsCell::updateContent(){
    SPCollectionViewCell::updateContent();
    
    if (_type == settings_none) {
        return;
    }
    
    std::string name        = Settings::getName(_type);
    
    float objects_height = getContentSize().height * 0.5f;

    if (!_title) {
        _title = Label::createWithTTF("0", "fonts/Blogger_Sans-Bold.otf", objects_height * 0.75f);
        addChild(_title);
        _title->setColor(Color3B(85, 160, 157));
        _title->setAnchorPoint(Vec2(0, 0.5f));
    }
    
    
    _toggle_spine_animation = SPACE->get_spine_skeleton_animation("spine/toggle/", "toggle", true);
    addChild(_toggle_spine_animation, 100);
    _toggle_spine_animation->clearTracks();
    _toggle_spine_animation->update(0);
    _toggle_spine_animation->setTimeScale(1.5f);
    _toggle_spine_animation->setScale((objects_height) / _toggle_spine_animation->getBoundingBox().size.height);
    _toggle_spine_animation->setPosition(Vec2(getContentSize().width - (_toggle_spine_animation->getBoundingBox().size.width*0.5f), getContentSize().height*0.5f));
    
    //
    
    _title->setString   (name);
    _title->setPosition (Vec2(0, getContentSize().height*0.5f));

    
    changeState(false);
    
}

void SettingsCell::changeState(bool animated){
    
    bool        stateOn     = Settings::getStateOn(_type);
        
    std::string animation = "";
    
    if (animated) {
        if (stateOn == true) {
            animation = "turn_on";
        }
        else{
            animation = "turn_off";
        }
    }
    else{
        if (stateOn == true) {
            animation = "idle_on";
        }
        else{
            animation = "idle_off";
        }
    }
    
    _toggle_spine_animation->setAnimation(0, animation.c_str(), false);
    
}
