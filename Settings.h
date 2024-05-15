//
//  Settings.hpp
//  hiball
//
//  Created by Marek on 1/7/17.
//
//

#ifndef Settings_hpp
#define Settings_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Game.h"
#include "PlatformManager.h"

USING_NS_CC;

enum settings_type {
    
    settings_none = -1,
    settings_sound_on = 1,
    settings_music_on = 2,
    settings_noads = 3,
    settings_vibration = 4,
    settings_darkmode = 5
    
};

class SettingsDelegate{
    
public:
        
virtual void settings_did_change(settings_type t){};
    
};

class Settings {
    
public:
    
    static std::vector<settings_type>getItems(){
        std::vector<settings_type>v;
        
        v.push_back(settings_sound_on);
        
        if (PlatformManager::haptic_available() == true) {
             v.push_back(settings_vibration);
            
        }
        
//        if (PlatformManager::isIpad() == false) {
//            v.push_back(settings_vibration);
//        }
        
        //v.push_back(settings_darkmode);
        
        return v;
    }
    
    static std::string    getName   (settings_type t);
    static bool           getStateOn(settings_type t);
    static void           set_first_state_as_enabled(settings_type t);
    
    static void           setStateOn(settings_type t, bool on);
    
};

#endif /* Settings_hpp */
