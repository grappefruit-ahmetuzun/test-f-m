//
//  AdManager.cpp
//  SummerGames
//
//  Created by Slavik on 27/06/16.
//
//

#include "AdManager.h"
#include "PlatformManager.h"
#include "Game.h"
#include "SimpleAudioEngine.h"
#include "IAPConfig.h"

AdManager::~AdManager(){

}

std::shared_ptr< AdManager > adManagerInstance;

std::shared_ptr< AdManager > AdManager::getInstance() {
    if (adManagerInstance){
        return adManagerInstance;
    }
    
    adManagerInstance = std::make_shared< AdManager >();
    PlatformManager::setCallBack(CC_CALLBACK_2(AdManager::callback_ad_video, adManagerInstance));
    PlatformManager::setInterstitialCallback(CC_CALLBACK_1(AdManager::callback_interstitial, adManagerInstance));
    return adManagerInstance;
}

bool AdManager::is_available_VideoAd(){
    return PlatformManager::isHeyzapAvalaible();
}

bool AdManager::is_available_Interstitial(){
     return PlatformManager::isInterstitialAvailable();
}

void AdManager::fetch_VideoAd(WATCH_VIDEO_TYPE type){
    if (!PlatformManager::isHeyzapAvalaible()) {
        currentWatchVideoType = type;
        PlatformManager::fetchVideoAds();
    }
    else{
        callback_ad_video("", 5);
    }
}

void AdManager::fetch_BannerAd(){
    
}

void AdManager::fetch_InterstitialAd(){
    PlatformManager::preloadInterstisial();
}

void AdManager::show_VideoAd(WATCH_VIDEO_TYPE type){
    
    Director::getInstance()->getEventDispatcher()->setEnabled(false);
    
    currentWatchVideoType = type;
    
    if (PlatformManager::isHeyzapAvalaible()) {
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
    }
    
    PlatformManager::showVideoAds(CC_CALLBACK_2(AdManager::callback_ad_video, this));
    
}

void AdManager::hide_BannerAd(){
    PlatformManager::hideAd();
}

void AdManager::show_BannerAd(){
    
    if (IAPConfig::didPurchase_disable_ads() == true) {
        return;
    }
    
    PlatformManager::showAd();
}

void AdManager::show_InterstitialAd(){
    
    if (IAPConfig::didPurchase_disable_ads() == true) {
        return;
    }
    
    PlatformManager::showInterstisial();
}

#pragma mark callbacks

void AdManager::callback_ad_video(std::string tag, int state){

    if (state == 0) {
        //log("test_______________________ COMPLETED");
        
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
        
        if (_delegate) {
            _delegate->ad_video_didchange_state(currentWatchVideoType,WATCH_VIDEO_STATE_COMPLETED);
        }
        
        Director::getInstance()->getEventDispatcher()->setEnabled(true);

    }
    else if(state == 1){
        //log("test_______________________ FAIL TO COMPLETE AD");
        
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
        
        if (_delegate) {
            _delegate->ad_video_didchange_state(currentWatchVideoType, WATCH_VIDEO_STATE_FAIL_TO_COMPLETE_AD);
        }
        
        Director::getInstance()->getEventDispatcher()->setEnabled(true);
        
        //sdkbox::PluginGoogleAnalytics::logEvent("AD_STATS", "VIDEO_AD", "Cancelled", 0);
    
    }
    else if (state == 2){
        //log("test_______________________ FAIL TO SHOW AD");
        
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
        
        if (_delegate) {
            _delegate->ad_video_didchange_state(currentWatchVideoType, WATCH_VIDEO_STATE_FAIL_TO_SHOW_AD);
        }
        
        Director::getInstance()->getEventDispatcher()->setEnabled(true);
    }
    else if(state == 3){
        //log("test_______________________ AUDIO STARTS");
    }
    else if(state == 4){
        //log("test_______________________ AUDIO ENDS");
    }
    else if(state == 5){
        // log("test_______________________ VIDEO FETCHED");
        if (_delegate) {
            _delegate->ad_video_didchange_state(currentWatchVideoType, WATCH_VIDEO_STATE_VIDEO_FETCHED);
        }
    }
    else if(state == 6){
        //log("test_______________________ FAILED ON RESUME FROM BG");

        
//        if (_shop_stars_layer) {
//            ((ShopStarsCell *)_shop_stars_layer->getCollectionView()->getCellAt(0, 3))->reloadVideoCell(PlatformManager::isHeyzapAvalaible(), false);
//        }

    }
    else if(state == 7){
        //log("test_______________________ VIDEO FAILED TO FETCH");
    }

}

void AdManager::callback_interstitial(int state) {
    
    if (state == 0) {
        //log("test_______________________ FAILED_TO_SHOW");
        
        if (_delegate) {
            _delegate->interstitial_didchange_state(INTERSTITIAL_STATE_FAILED_TO_SHOW);
        }
    }
    else if(state == 1){
        //log("test_______________________ FAILED_TO_RECEIVE");
        
        if (_delegate) {
            _delegate->interstitial_didchange_state(INTERSTITIAL_STATE_FAILED_TO_RECEIVE);
        }
    }
    else if (state == 2){
        //log("test_______________________ SHOWED");
        
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
        
        if (_delegate) {
            _delegate->interstitial_didchange_state(INTERSTITIAL_STATE_SHOWED);
        }
    }
    else if(state == 3){
        //log("test_______________________ CLOSED");
        
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
        
        if (_delegate) {
            _delegate->interstitial_didchange_state(INTERSTITIAL_STATE_CLOSED);
        }
    }
    else if(state == 4){
        //log("test_______________________ RECEIVED");
        
        if (_delegate) {
            _delegate->interstitial_didchange_state(INTERSTITIAL_STATE_RECEIVED);
        }
    }
}
