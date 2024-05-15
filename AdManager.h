//
//  AdManager.hpp
//  SummerGames
//
//  Created by Slavik on 27/06/16.
//
//

#ifndef AdManager_h
#define AdManager_h

#include "cocos2d.h"

USING_NS_CC;

enum WATCH_VIDEO_TYPE{
    WATCH_VIDEO_TYPE_UNKNOWN                    = 0,
    WATCH_VIDEO_TYPE_CONTINUE_GAMEPLAY          = 1,
    WATCH_VIDEO_TYPE_SHOP_COINS                 = 2,
    WATCH_VIDEO_TYPE_REWARD_SPIN_AGAIN          = 3,
    WATCH_VIDEO_TYPE_GAMEOVER_COINS             = 4,
    WATCH_VIDEO_TYPE_GAMEOVER_GEMS              = 5
};

enum WATCH_VIDEO_STATE{
    
    WATCH_VIDEO_STATE_UNKNOWN               = -1,
    WATCH_VIDEO_STATE_COMPLETED             = 0,
    WATCH_VIDEO_STATE_FAIL_TO_COMPLETE_AD   = 1,
    WATCH_VIDEO_STATE_FAIL_TO_SHOW_AD       = 2,
    WATCH_VIDEO_STATE_AUDIO_START           = 3,
    WATCH_VIDEO_STATE_AUDIO_END             = 4,
    WATCH_VIDEO_STATE_VIDEO_FETCHED         = 5,
    WATCH_VIDEO_STATE_FAILED_ON_RESUME      = 6,
    WATCH_VIDEO_STATE_FAILED_FETCH          = 7
    
};


enum INTERSTITIAL_STATE{
    
    INTERSTITIAL_STATE_UNKNOWN               = -1,
    INTERSTITIAL_STATE_FAILED_TO_SHOW        = 0,
    INTERSTITIAL_STATE_FAILED_TO_RECEIVE     = 1,
    INTERSTITIAL_STATE_SHOWED                = 2,
    INTERSTITIAL_STATE_CLOSED                = 3,
    INTERSTITIAL_STATE_RECEIVED              = 4
    
};

class AdManagerDelegate;
class AdManager{

public:
    
    static std::shared_ptr< AdManager > getInstance();
    
    AdManager():
    _delegate(nullptr)
    {};
    virtual ~AdManager();

    
    WATCH_VIDEO_TYPE currentWatchVideoType  = WATCH_VIDEO_TYPE_UNKNOWN;
    
    bool is_available_VideoAd();
    bool is_available_Interstitial();
    
    void fetch_VideoAd(WATCH_VIDEO_TYPE type = WATCH_VIDEO_TYPE_SHOP_COINS);
    void fetch_BannerAd();
    void fetch_InterstitialAd();
    
    void show_VideoAd(WATCH_VIDEO_TYPE type = WATCH_VIDEO_TYPE_SHOP_COINS);
    void show_BannerAd();
    void show_InterstitialAd();
    
    void hide_BannerAd();
    
    void callback_ad_video(std::string tag, int state);
    void callback_interstitial(int state);
    
    
private:
    
    CC_SYNTHESIZE(AdManagerDelegate *,      _delegate,               Delegate);
    
};

class AdManagerDelegate {
    
public:
    
    virtual void ad_video_didchange_state(WATCH_VIDEO_TYPE type,WATCH_VIDEO_STATE state) {};
    virtual void interstitial_didchange_state(INTERSTITIAL_STATE state) {};
    
};

#endif /* AdManager_h */
