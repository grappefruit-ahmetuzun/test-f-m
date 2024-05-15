
#include "platform/CCPlatformConfig.h"
#include "PlatformManager.h"
#include "Settings.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "PlatformManagerIOS.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "NativeHelper.h"
#endif

#pragma mark
#pragma mark SHARE
#pragma mark

void PlatformManager::setShareDidFinishCallBack(std::function<void(bool)> callback){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::setShareDidFinishCallBack(callback);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::setShareCallback(callback);
#endif
}

void PlatformManager::share(const char* imageName,const char* str){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::share(str, imageName);
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFuncStr("showShareImageWithText", str,imageName);
#endif
}

void PlatformManager::share_gif(const char* imageName,const char* str,std::vector<cocos2d::Image *>gif_imgs){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::share_gif(str, imageName,gif_imgs);
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFuncStr("showShareImageWithText", str,imageName);
#endif
}

#pragma mark
#pragma mark INTERNET
#pragma mark

bool PlatformManager::isInternetConnection() {
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return PlatformManagerIOS::isInternetConnection();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return NativeHelper::getBoolFromFunc("checkForInternetConnection");
#endif
    return false;
}

#pragma mark
#pragma mark VIBRATE
#pragma mark

bool PlatformManager::isIpad(){
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        return PlatformManagerIOS::isIpad();
    #endif
    return false;
}

void PlatformManager::vibrate(int type){
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
   if (Settings::getStateOn(settings_vibration) == false){
       return;
   }
    
    bool is_ipad = isIpad();
    if (is_ipad) {
        return;
    }
    
    bool haptic_available = PlatformManagerIOS::haptic_available();
    
    if (haptic_available) {
        PlatformManagerIOS::vibro(type);
    }
    else{
//        float  _duration = 0.5f;
//        cocos2d::Device::vibrate(_duration);
    }
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    float  _duration = 0.5f;
//    cocos2d::Device::vibrate(_duration);
#endif

}

#pragma mark
#pragma GDPR
#pragma mark

void PlatformManager::preloadGDR(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFunc("preloadGDPR");
#endif
}

bool PlatformManager::isGDPR_Optin(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return PlatformManagerIOS::isGDPR_Optin();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return NativeHelper::getBoolFromFunc("isGDPR_Optin");
#endif
    return true;
}

void PlatformManager::openGDRP_window(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::openGDRP_window();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFunc("openGDRP_window");
#endif
}

bool PlatformManager::isCountryGDRP(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return PlatformManagerIOS::isCountryGDRP();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return NativeHelper::getBoolFromFunc("isCountryGDRP");
#endif
    return false;
}

#pragma mark
#pragma mark KETCHAPP
#pragma mark

void PlatformManager::ketchappPromotionShow(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFunc("ketchappPromotionShow");
#endif
}

void PlatformManager::ketchappPromotionLoad(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::ketchappPromotionLoad();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFunc("ketchappPromotionLoad");
#endif
}

void PlatformManager::showKetchappSquare(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::showKetchappSquare();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#endif
}

void PlatformManager::hideKetchappSquare(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::hideKetchappSquare();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#endif
}

void PlatformManager::fetchKetchappSquare(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::fetchKetchappSquare();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
#endif
}

bool PlatformManager::isKetchappSquareReady(){
    bool isKetchappSquareReady = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    isKetchappSquareReady = PlatformManagerIOS::isKetchappSquareReady();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
#endif
    return isKetchappSquareReady;
}

bool PlatformManager::isKetchappSquareShows(){
    bool isKetchappSquareShows = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    isKetchappSquareShows = PlatformManagerIOS::isKetchappSquareShows();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
#endif
    return isKetchappSquareShows;
}

#pragma mark
#pragma mark Game promotions
#pragma mark

int PlatformManager::get_app_id(promo_type type){
    
    int app_id = 0;
    
    switch (type) {
            
        case promo_type_summer_sports:  app_id = 1140680115;        break;
        case promo_type_basketball:     app_id = 1111665247;        break;
        case promo_type_soccer:         app_id = 1123455917;        break;
        case promo_type_pppap:          app_id = 1159035153;        break;
        case promo_type_winter_sports:  app_id = 0;                 break;
        case promo_type_ballz_shooter:  app_id = 1266679534;        break;
        case promo_type_ballz_spinner:  app_id = 1236104279;        break;
            
        case promo_type_knife_hit:  app_id = 1336527043;           break;
        case promo_type_dunk_shot:  app_id = 1301375510;           break;
        case promo_type_dunk_line:  app_id = 1349404829;           break;
        case promo_type_mr_gun:     app_id = 1370327712;           break;
            
        default:   break;
    }
    
    return app_id;
}

std::string PlatformManager::get_game_scheme(promo_type type){
    std::string scheme = "";
    
    switch (type) {
        case promo_type_summer_sports:  scheme = "summersports";                    break;
        case promo_type_basketball:     scheme = "ketchappbasketball";              break;
        case promo_type_soccer:         scheme = "ketchappfootball";                break;
        case promo_type_pppap:          scheme = "ppapketchapp";                    break;
        case promo_type_winter_sports:  scheme = "ketchappwintersports";            break;
        case promo_type_ballz_shooter:  scheme = "com.ketchapp.ballzshooter";       break;
        case promo_type_ballz_spinner:  scheme = "com.ketchapp.fingerspinner";      break;
            
        case promo_type_dunk_shot:      scheme = "com.ketchapp.dunkshot";           break;
        case promo_type_knife_hit:      scheme = "com.ketchapp.knifehit";           break;
        case promo_type_dunk_line:      scheme = "com.ketchapp.dunkline";           break;
        case promo_type_mr_gun:         scheme = "com.ketchapp.mrgun";              break;
            
        default:   break;
    }
    
    return scheme;
}

std::string PlatformManager::get_game_url(promo_type type){
    std::string url = "";
    
    if (type == promo_type_summer_sports) {
        if ((CC_TARGET_PLATFORM == CC_PLATFORM_IOS))
            return "https://itunes.apple.com/app/ketchapp-summer-sports/id1140680115";
        return "http://play.google.com/store/apps/details?id=com.ketchapp.summersports";
    }
    else if (type == promo_type_basketball){
        if ((CC_TARGET_PLATFORM == CC_PLATFORM_IOS))
            return "https://itunes.apple.com/app/ketchapp-basketball/id1111665247";
        return "http://play.google.com/store/apps/details?id=com.ketchapp.ketchappbasketball";
    }
    else if (type == promo_type_soccer){
        if ((CC_TARGET_PLATFORM == CC_PLATFORM_IOS))
            return "https://itunes.apple.com/app/ketchapp-football/id1123455917";
        return "https://play.google.com/store/apps/details?id=com.ketchapp.ketchappfootball";
    }
    else if (type == promo_type_pppap){
        if ((CC_TARGET_PLATFORM == CC_PLATFORM_IOS))
            return "https://itunes.apple.com/app/pineapple-pen/id1159035153";
        return "http://play.google.com/store/apps/details?id=com.ketchapp.pineapplepen";
    }
    else if (type == promo_type_winter_sports){
        if ((CC_TARGET_PLATFORM == CC_PLATFORM_IOS))
            return "";
        return "";
    }
    else if (type == promo_type_ballz_shooter){
        if ((CC_TARGET_PLATFORM == CC_PLATFORM_IOS))
            return "https://itunes.apple.com/app/ballz-shooter/id1266679534";
        return "http://play.google.com/store/apps/details?id=com.ketchapp.ballzshooter";
    }
    else if (type == promo_type_ballz_spinner){
        if ((CC_TARGET_PLATFORM == CC_PLATFORM_IOS))
            return "https://itunes.apple.com/app/finger-spinner/id1236104279";
        return "http://play.google.com/store/apps/details?id=com.ketchapp.fingerspinner";
    }
    
    else if (type == promo_type_dunk_shot){
        if ((CC_TARGET_PLATFORM == CC_PLATFORM_IOS))
            return "https://itunes.apple.com/app/dunk-shot/id1301375510";
        return "http://play.google.com/store/apps/details?id=com.ketchapp.dunkshot";
    }
    else if (type == promo_type_knife_hit){
        if ((CC_TARGET_PLATFORM == CC_PLATFORM_IOS))
            return "https://itunes.apple.com/app/knife-hit/id1336527043";
        return "http://play.google.com/store/apps/details?id=com.ketchapp.knifehit";
    }
    else if (type == promo_type_dunk_line){
        if ((CC_TARGET_PLATFORM == CC_PLATFORM_IOS))
            return "https://itunes.apple.com/app/dunk-line/id1349404829";
        return "http://play.google.com/store/apps/details?id=com.ketchapp.dunkline";
    }
    else if (type == promo_type_mr_gun){
        if ((CC_TARGET_PLATFORM == CC_PLATFORM_IOS))
            return "https://itunes.apple.com/app/mr-gun/id1370327712";
        return "http://play.google.com/store/apps/details?id=com.ketchapp.mrgun";
    }
    
    return "";
}

void PlatformManager::open_game(promo_type promo_id){
    
    std::string url         = get_game_url(promo_id);
    std::string scheme      = get_game_scheme(promo_id);
    int app_id              = get_app_id(promo_id);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::openUrl(app_id,url.c_str(), scheme.c_str());
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::Application::getInstance()->openURL(url.c_str());
#endif
    
}



#pragma mark
#pragma mark HEYZAPP
#pragma mark

void PlatformManager::fetchVideoAds(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::fetchVideoAds();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFunc("fetchHeyzapVideoAd");
#endif
}

void PlatformManager::showVideoAds(std::function<void(const char *data, int state)> callback){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::showVideoAds(callback);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFuncForHeyzapWithCallback("showHeyzapVideoAdWithCallBack", callback);
#endif
}

bool PlatformManager::isHeyzapAvalaible(){
    bool isHeyzapAvalaible = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    isHeyzapAvalaible = PlatformManagerIOS::isHeyzapAvalaible();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    isHeyzapAvalaible = NativeHelper::getBoolFromFunc("isHeyzapAvailable");
#endif
    return isHeyzapAvalaible;
}

bool PlatformManager::isInterstitialAvailable(){
    bool isHeyzapAvalaible = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    isHeyzapAvalaible = PlatformManagerIOS::isInterstitialAvailable();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    isHeyzapAvalaible = NativeHelper::getBoolFromFunc("isInterstitialAvailable");
#endif
    return isHeyzapAvalaible;
}

void PlatformManager::setCallBack(std::function<void(const char *data, int state)> callback){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::setCallBack(callback);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::setHeyzapCallback(callback);
#endif
}

void PlatformManager::setInterstitialCallback(std::function<void(const int state)> callback){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::setInterstitialCallback(callback);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //NativeHelper::setHeyzapCallback(callback);
#endif
}

void PlatformManager::stopVideoAds(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFunc("stopHeyzapVideoAd");
#endif
}

#pragma mark
#pragma mark BANNER
#pragma mark

void PlatformManager::showAd(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::showAd();
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFunc("showAd");
#endif
}

void PlatformManager::hideAd(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::hideAd();
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFunc("hideAd");
#endif
}

void PlatformManager::showInterstisial(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::showInterstisial();
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFunc("showInterstitial");
#endif
}

void PlatformManager::preloadInterstisial(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::preloadInterstisial();
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFunc("preloadInterstitial");
#endif
}

void PlatformManager::ads_pauseExpensiveWork(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::ads_pauseExpensiveWork();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFunc("ads_pauseExpensiveWork");
#endif
}

void PlatformManager::ads_resumeExpensiveWork(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::ads_resumeExpensiveWork();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFunc("ads_resumeExpensiveWork");
#endif
}

#pragma mark
#pragma mark PUSH NOTIFICATIONS
#pragma mark


// PUSH NOTIFICATIONS

void PlatformManager::push_set(int push_id,int time_since_now,const char * body_text){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::push_set(push_id, time_since_now, body_text);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::show(body_text, time_since_now, push_id);
#endif
    
}

void PlatformManager::push_cancelAll(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::push_cancelAll();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::cancel(0);
#endif
}




void PlatformManager::open_facebook(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::open_facebook();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFunc("open_facebook");
#endif
}

void PlatformManager::open_twitter(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::open_twitter();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFunc("open_twitter");
#endif
}

void PlatformManager::open_instagram(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::open_instagram();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFunc("open_instagram");
#endif
}



void PlatformManager::open_facebook_estoty(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::open_facebook_estoty();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFunc("open_facebook_estoty");
#endif
}

void PlatformManager::open_twitter_estoty(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::open_twitter_estoty();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFunc("open_twitter_estoty");
#endif
}

void PlatformManager::open_instagram_estoty(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::open_instagram_estoty();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFunc("open_instagram_estoty");
#endif
}

bool PlatformManager::isIphoneX(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return PlatformManagerIOS::isIphoneX();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return false;
#endif
}

bool PlatformManager::haptic_available(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return PlatformManagerIOS::haptic_available();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return false;
#endif
}


void PlatformManager::requestReview(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::requestReview();
#endif
}

bool PlatformManager::availableNativeReview(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return PlatformManagerIOS::availableNativeReview();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return false;
#endif
}

void PlatformManager::gameplay_start(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return PlatformManagerIOS::gameplay_start();
#endif
}

void PlatformManager::gameplay_finished(int stage){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return PlatformManagerIOS::gameplay_finished(stage);
#endif
}

default_weapon_type PlatformManager::gameAnalytics_get_default_weapon_type(){
    
    default_weapon_type type = default_weapon_knife;

    int weapon_saved = SPUserDefault::getInstance()->getIntegerForKey("choosen_def_weapon");
    
    if (weapon_saved == 1) {
        type = default_weapon_shuriken;
    }
    
    return type;
}

// Subscriptions

void PlatformManager::setSubscriptionCallback(std::function<void(bool)> callback){
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::setSubscriptionCallback(callback);
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::setSubscriptionCallback(callback);
#endif
    
}

void PlatformManager::refreshSubscriptionState(){
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::refreshSubscriptionState();
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFunc("refreshSubscriptionState");
#endif
    
}

void PlatformManager::open_webview_with_info(std::string info,std::string title,bool is_url){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::open_webview_with_info(info,title,is_url);
#endif
}

void PlatformManager::validateAndTrackPurchase(const char *signature, const char *receipt, const char *price, const char *currency,const char *productId,const char *transactionId){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PlatformManagerIOS::validateAndTrackPurchase(price, currency, productId, transactionId);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeHelper::callFuncStr("validateAndTrackPurchase", signature, receipt, price, currency);
#endif
}
