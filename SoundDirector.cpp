//
//  SoudDirector.cpp
//  infinityloop
//
//  Created by Marek Reichenbach on 6/23/15.
//
//

#include "SoundDirector.h"
#include "SimpleAudioEngine.h"
#include "Game.h"

USING_NS_CC;

using namespace CocosDenshion;

std::shared_ptr< SoundDirector > soundInstance;

std::shared_ptr< SoundDirector > SoundDirector::getInstance() {
    if (soundInstance){
        return soundInstance;
    }
    soundInstance = std::make_shared< SoundDirector >();
    return soundInstance;
}

std::string SoundDirector::fullSoundPath(std::string soundName){
    std::string folderByFormatName;
    std::string format;
    format = ".mp3";
    folderByFormatName = "MP3/";
    return std::string("").append(folderByFormatName).append(soundName).append(format);
}


void SoundDirector::preload(){
    
    _collideSoundMute = false;
    
    bool first_launch = UserDefault::getInstance()->getBoolForKey("sound_first_launch");
    if (!first_launch) {
        setSound(true);
        UserDefault::getInstance()->setBoolForKey("sound_first_launch", true);
    }

    for (int x = 0; x < 500; x++) {
        gSound sid              = (gSound)x;
        std::string sound_name  = gSoundName(sid);
        if (sound_name.length() == 0) {
            continue;
        }
        std::string name        = fullSoundPath(sound_name.c_str());
    
        SimpleAudioEngine::getInstance()->preloadEffect(name.c_str());
    }
    
    
    refresh_sound_effects();
    refresh_music();
    
}

void SoundDirector::preload_sounds(){
    SoundDirector::getInstance()->preload();
}

void SoundDirector::preloadSoundByPath(std::string path){

    std::string name        = SoundDirector::getInstance()->fullSoundPath(path);
    SimpleAudioEngine::getInstance()->preloadEffect(name.c_str());
    
}

void SoundDirector::playContinueSound(){
    std::string name  = SoundDirector::getInstance()->fullSoundPath(SoundDirector::getInstance()->gSoundName(gSound_continue));
    continue_sound_id = SimpleAudioEngine::getInstance()->playEffect(name.c_str(), false);
}

void SoundDirector::stopContinueSound(){
    SimpleAudioEngine::getInstance()->stopEffect(continue_sound_id);
}

void SoundDirector::playSound(std::string path, bool loop){
    
    if (is_sound_effects_enabled() == false) {
        return;
    }
    
    std::string full_path = SoundDirector::getInstance()->fullSoundPath(path);
    
    SimpleAudioEngine::getInstance()->playEffect(full_path.c_str(), loop);
}

void SoundDirector::playSound(gSound type, bool loop){
    if (is_sound_effects_enabled() == false) {
        return;
    }
    if (type == gSound_unknown) {
        return;
    }
    
    std::string name = SoundDirector::getInstance()->fullSoundPath(SoundDirector::getInstance()->gSoundName(type));
    SimpleAudioEngine::getInstance()->playEffect(name.c_str(), loop);
}

void SoundDirector::playBgMusic(std::string path, bool loop){
    
    if (is_music_enabled() == false) {
        return;
    }
    
    std::string full_path = SoundDirector::getInstance()->fullSoundPath(path);
    SimpleAudioEngine::getInstance()->playBackgroundMusic(full_path.c_str(), loop);
}


void SoundDirector::playBgMusic(gSound type, bool loop){
    if (is_music_enabled() == false) {
        return;
    }
    std::string name = SoundDirector::getInstance()->fullSoundPath(SoundDirector::getInstance()->gSoundName(type));
    SimpleAudioEngine::getInstance()->playBackgroundMusic(name.c_str(),loop);
}

void SoundDirector::stopBgMusic(){
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void SoundDirector::stopSounds(){
    SimpleAudioEngine::getInstance()->stopAllEffects();
}

void SoundDirector::refresh_sound_effects(){
    SimpleAudioEngine::getInstance()->setEffectsVolume(SoundDirector::is_sound_effects_enabled() == true ? 1 : 0);
}

void SoundDirector::refresh_music(){
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(SoundDirector::is_music_enabled() == true ? 1.f : 0);
}

#pragma mark setters

void SoundDirector::setBackgroundMusicOn(bool on){
    UserDefault::getInstance()->setBoolForKey("gamemusic", on);
    SoundDirector::getInstance()->refresh_music();
}

void SoundDirector::setSoundEffectsOn(bool on){
    UserDefault::getInstance()->setBoolForKey("gamesoundEffects", on);
    SoundDirector::getInstance()->refresh_sound_effects();
}

void SoundDirector::setSound(bool on){
    setBackgroundMusicOn(on);
    setSoundEffectsOn(on);
}

#pragma mark getters

bool SoundDirector::is_music_enabled(){
    return UserDefault::getInstance()->getBoolForKey("gamemusic");
}

bool SoundDirector::is_sound_effects_enabled(){
    return UserDefault::getInstance()->getBoolForKey("gamesoundEffects");
}

bool SoundDirector::is_sound_enabled(){
    return (is_music_enabled() && is_sound_effects_enabled());
}

bool SoundDirector::is_music_playing(){
    return SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
}

