//
//  SoundDirector.h
//  infinityloop
//
//  Created by Marek Reichenbach on 6/23/15.
//
//

#ifndef __riverJump__SoundDirector__
#define __riverJump__SoundDirector__

#include "cocos2d.h"

/*
 Use:
 1. add sound_id to gSound enum;
 2. add sound path to gSoundName;
*/

enum gSound {
    
    gSound_unknown                      = -1,
    gSound_button_click                 = 0,
    gSound_continue                     = 2
};

enum gSound_ball_hit_type {
    
    gSound_ball_hit_type_unknown              = -1,
    gSound_ball_hit_type_hoop                 = 0,
    gSound_ball_hit_type_wall                 = 1
    
};

class SoundDirector : cocos2d::Ref{
public:
    
    static void preload_sounds();   // call in appdelegate
    static void preloadSoundByPath(std::string path);
    
    
    static void playSound   (std::string path, bool loop = false);
    static void playSound   (gSound type, bool loop = false);
    static void stopBgMusic();
    static void playBgMusic (std::string path, bool loop = false);
    static void playBgMusic (gSound type, bool loop = true);
    static void stopSounds();
    
    static void setBackgroundMusicOn    (bool on);
    static void setSoundEffectsOn       (bool on);
    static void setSound                (bool on);

    void playContinueSound();
    void stopContinueSound();
    
    int continue_sound_id = 0;
    
    static bool is_music_enabled();
    static bool is_sound_effects_enabled();
    static bool is_sound_enabled();
    static bool is_music_playing();
    
    CC_SYNTHESIZE(bool, _collideSoundMute, CollideSoundMute);
    
public:
    
    static std::shared_ptr< SoundDirector > getInstance();
    SoundDirector(){};
    
    void preload();
    
    static std::string getSoundPath(gSound sound_id){
        std::string sound_name = SoundDirector::getInstance()->fullSoundPath(SoundDirector::getInstance()->gSoundName(sound_id));
        return sound_name.c_str();
    }
    
    cocos2d::Node * _delayNode = nullptr;
    
private:
    
    void refresh_sound_effects();
    void refresh_music();
    std::string fullSoundPath(std::string soundName);
    
    std::string gSoundName(gSound type){
        std::string name = "";
        std::string effectPrefix = "";
        
        switch (type)
        {
                
            case gSound_button_click:                  name = "button_click";                          break;
            case gSound_continue:                      name = "ev_timer_seq";                          break;
                
            default:break;
        }
        
        return name;
    }

};

#endif /* defined(__infinityloop__SoudDirector__) */
