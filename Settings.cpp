//
//  Settings.cpp
//  hiball
//
//  Created by Marek on 1/7/17.
//
//

#include "Settings.h"
#include "SPUserDefault.h"
#include "SoundDirector.h"
#include "IAPConfig.h"

std::string Settings::getName(settings_type t){
    std::string name = "";
    
    switch (t) {
            
        case settings_sound_on:        name = "SOUNDS";            break;
        case settings_music_on:        name = "MUSIC";             break;
        case settings_noads:           name = "NO ADS";            break;
        case settings_vibration:       name = "VIBRATION";         break;
        case settings_darkmode:        name = "NIGHT MODE";          break;
            
        default:    break;
    }
    
    return name;
}

void  Settings::set_first_state_as_enabled(settings_type t){
    
    std::string first_check_string     = StringUtils::format("settings_first_%i",(int)t);
    bool        first_launch_checked   = SPUserDefault::getInstance()->getBoolForKey(first_check_string.c_str());
    
    if (first_launch_checked == false) {
        SPUserDefault::getInstance()->setBoolForKey(first_check_string.c_str(),true);
        setStateOn(t, true);
    }
    
}
    
bool Settings::getStateOn(settings_type t){
    if (t == settings_music_on) {
        return SoundDirector::is_music_enabled();
    }
    else if (t == settings_sound_on){
        return SoundDirector::is_sound_effects_enabled();
    }
    else if (t == settings_noads){
        return IAPConfig::didPurchase_disable_ads();
    }
    return SPUserDefault::getInstance()->getBoolForKey(StringUtils::format("settings_%i",(int)t).c_str());
}

void Settings::setStateOn(settings_type t, bool on){
    if (t == settings_noads) {
        return; // custom
    }
    else if (t == settings_music_on){
        SoundDirector::setBackgroundMusicOn(on);
        return;
    }
    else if (t == settings_sound_on){
        SoundDirector::setSoundEffectsOn(on);
        return;
    }
    else if (t == settings_darkmode){
        
        if (Game::getInstance()->is_tutorial_completed() == true) {
            
            if (on) {
               // SoundDirector::playSound("darkmode/night");
            }
            else{
              //  SoundDirector::playSound("darkmode/day");
            }
            
        }
        
    }
    SPUserDefault::getInstance()->setBoolForKey(StringUtils::format("settings_%i",(int)t).c_str(),on);
}
