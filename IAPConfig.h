//
//  IAPConfig.h
//  SoccerGame
//
//  Created by Marek on 6/8/16.
//
//

#ifndef IAPConfig_hpp
#define IAPConfig_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "SPUserDefault.h"
#include "Game.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "NativeHelper.h"
#endif

enum purchase_id{
    purchase_id_unknown                         = -1,
    purchase_id_elite_subscription              = 0,
    purchase_id_remove_ads
};

class IAPConfig{
    
public:
    
    static bool didPurchase_disable_ads()  {
        return SPUserDefault::getInstance()->getBoolForKey("disable_ads_purchase");
    }
    
    static void setPurchase_disable_ads(bool d){
        SPUserDefault::getInstance()->setBoolForKey("disable_ads_purchase", d);
        if (d == true){
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                    NativeHelper::callFunc("setAsNoAdsEnabled");
        #endif
        }
    }
    
    static std::string getStarPurchasesIAPKey(purchase_id p_id){
        std::string key = "";
        
        switch (p_id) {
                
            case purchase_id_elite_subscription:     key = "subscription_elite";                       break;
            case purchase_id_remove_ads:             key = "remove_ads";                               break;
                
            default:   break;
        }
        
        return key;
    }
    
    static purchase_id getStarPurchaseId(std::string iap_key){
        purchase_id p_id = purchase_id_unknown;
        
        if (iap_key == getStarPurchasesIAPKey(purchase_id_elite_subscription)) {
            p_id = purchase_id_elite_subscription;
        }
        if (iap_key == getStarPurchasesIAPKey(purchase_id_remove_ads)) {
            p_id = purchase_id_remove_ads;
        }
        
        return p_id;
    }
    
    
};

#endif /* IAPConfig_h */

