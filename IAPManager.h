//
//  IAPManager.h
//  SummerGames
//
//  Created by Slavik on 27/06/16.
//
//

#ifndef IAPManager_h
#define IAPManager_h

#include "cocos2d.h"
#include "PluginIAP/PluginIAP.h"
#include "IAPConfig.h"
#include "SPUserDefault.h"

USING_NS_CC;

class ShopInAppManagerDelegate;
class IAPManager : public Ref,public sdkbox::IAPListener{
    
public:
    
    static std::shared_ptr< IAPManager > getInstance();
    
    IAPManager():
    _delegate(nullptr),
    sdkBoxDidRefresh(false)
    {
        sdkbox::IAP::setListener(this);
    };
    virtual ~IAPManager(){};
    
    sdkbox::Product get_product_by_id(std::string id);
    
private:
    
    CC_SYNTHESIZE(ShopInAppManagerDelegate *,            _delegate,               Delegate);
    CC_SYNTHESIZE(bool,                                  sdkBoxDidRefresh ,       SdkBoxDidRefresh);
    
    // IAPListener
    
    virtual void onInitialized(bool ok) override;
    virtual void onSuccess(sdkbox::Product const& p) override;
    virtual void onFailure(sdkbox::Product const& p, const std::string &msg) override;
    virtual void onCanceled(sdkbox::Product const& p) override;
    virtual void onRestored(sdkbox::Product const& p) override;
    virtual void onProductRequestSuccess(std::vector<sdkbox::Product> const &products) override;
    virtual void onProductRequestFailure(const std::string &msg) override;
    virtual void onRestoreComplete(bool ok, const std::string &msg) override;
    
    //
    
    std::vector<sdkbox::Product> all_available_products;
    
    void preload();
    
};

class ShopInAppManagerDelegate
{
public:
    
    virtual void shopStars_PurchaseSuccess              (IAPManager *shop,int stars_count,purchase_id purchase_id) {};
    virtual void shopDidPurchaseDisableAds              (IAPManager *shop,bool from_restore_inapp){};
    
    virtual void shopStars_In_App_PurchasesSuccess   (IAPManager *shop) {};
    virtual void shopStars_In_App_PurchasesFailed    (IAPManager *shop) {};
    virtual void shopStars_In_App_PurchasesItemsRequestFailed    (IAPManager *shop) {};
    virtual void shopStars_In_App_PurchasesCanceled  (IAPManager *shop) {};
    
    virtual void in_app_did_purchase_subscription(purchase_id purchase_id) {};
    virtual void in_app_did_restore_subscription(purchase_id purchase_id) {};
    
};

#endif /* IAPManager_h */


