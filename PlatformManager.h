

#ifndef __PlatformManager__
#define __PlatformManager__

#include "cocos2d.h"

#pragma mark - Macros

#define USER_MESSAGE(NAME) PlatformManager::showMessage(NAME);

enum promo_type{
    
    promo_type_none             = -1,
    promo_type_summer_sports    = 0,
    promo_type_basketball       = 1,
    promo_type_soccer           = 2,
    promo_type_pppap            = 3,
    promo_type_winter_sports    = 4,
    promo_type_mannequin        = 6,
    promo_type_ballz_shooter    = 7,
    promo_type_ballz_spinner    = 8,
    promo_type_knife_hit        = 9,
    promo_type_dunk_shot        = 10,
    promo_type_dunk_line        = 11,
    promo_type_mr_gun           = 12
    
};

enum default_weapon_type{
    
    default_weapon_knife                          = 0,
    default_weapon_shuriken                       = 1,
    
};

class PlatformManager {
public:
    
    // Share
    
    static void share(const char* imageName, const char* str);
    static void share_gif(const char* imageName, const char* str,std::vector<cocos2d::Image *>gif_imgs);
    static void setShareDidFinishCallBack(std::function<void(bool)> callback);
    
    // Internet
    
    static bool isInternetConnection();
    
    // Vibrate
    
    static void vibrate(int type);
    
    // GDRP
    
    static void preloadGDR();
    static bool isGDPR_Optin();
    static void openGDRP_window();
    static bool isCountryGDRP();
    
    // Ketchapp
    
    static void ketchappPromotionShow();
    static void ketchappPromotionLoad();
    
    static void showKetchappSquare();
    static void hideKetchappSquare();
    static void fetchKetchappSquare();
    static bool isKetchappSquareReady();
    static bool isKetchappSquareShows();
    
    // Promotions of other games open
    
    static int          get_app_id      (promo_type type);
    static std::string  get_game_scheme (promo_type type);
    static std::string  get_game_url    (promo_type type);
    static void         open_game       (promo_type type);  // use this
    
    // HEYZAP
    
    static void fetchVideoAds();
    static void stopVideoAds();
    static void showVideoAds(std::function<void(const char *data, int state)> callback);
    static void setCallBack(std::function<void(const char *data, int state)> callback);
    static void setInterstitialCallback(std::function<void(const int state)> callback);
    static bool isHeyzapAvalaible();
    static bool isInterstitialAvailable();
    
    //BANNER
    
    static void showAd();
    static void hideAd();
    static void showInterstisial();
    static void preloadInterstisial();
    static void ads_pauseExpensiveWork();
    static void ads_resumeExpensiveWork();
    
    
    // PUSH NOTIFICATIONS
    
    static void push_set(int push_id,int time_since_now,const char * body_text);
    static void push_cancelAll();
    
    
    static void open_facebook();
    static void open_twitter();
    static void open_instagram();
    
    static void open_facebook_estoty();
    static void open_twitter_estoty();
    static void open_instagram_estoty();
    
    // VibroPick
    static bool isIphoneX();
    static bool isIpad();
    static bool haptic_available();
    
    
    //Review
    static bool availableNativeReview();
    static void requestReview();
    
    // GameAnalitycs
    static void gameplay_start();
    static void gameplay_finished(int stage);
    static default_weapon_type gameAnalytics_get_default_weapon_type();
    
    // Subscriptions
    
    static void setSubscriptionCallback(std::function<void(bool)> callback);
    static void refreshSubscriptionState();
    static void open_webview_with_info(std::string info,std::string title,bool is_url);
    
    static void validateAndTrackPurchase(const char *signature, const char *receipt, const char *price, const char *currency,const char *productId,const char *transactionId);

};

#endif


