//
//  IAPManager.cpp
//  SummerGames
//
//  Created by Slavik on 27/06/16.
//
//

#include "IAPManager.h"
#include <cstring>

using namespace sdkbox;

std::shared_ptr< IAPManager > iapManagerInstance;

std::shared_ptr< IAPManager > IAPManager::getInstance() {
    if (iapManagerInstance){
        return iapManagerInstance;
    }
    
    iapManagerInstance = std::make_shared< IAPManager >();
    return iapManagerInstance;
}

void IAPManager::preload(){
    
}

sdkbox::Product IAPManager::get_product_by_id(std::string id){
    Product p;
    
    for (int i = 0; i < all_available_products.size(); i++) {
        sdkbox::Product _product = all_available_products.at(i);
        if (Game::is_same_strings(_product.name, id)) {
            p = _product;
            break;
        }
    }
    
    return p;
}


#pragma mark IAPListener

void IAPManager::onRestoreComplete(bool ok, const std::string &msg){
    //SPLoading::stop();
    Director::getInstance()->getEventDispatcher()->setEnabled(true);
    
    if (_delegate) {
        _delegate->shopStars_In_App_PurchasesFailed(this);
    }
    
}

void IAPManager::onInitialized(bool ok){
    //AnalitycsManager::logEvent("GAME_INAPP", "ON_INITIALIZED", StringUtils::format("OK: %i",ok), 0);
}

void IAPManager::onSuccess(sdkbox::Product const& p){
    CCLOG("Purchase Success: %s", p.id.c_str());
    CCLOG("Purchase Sucess name: %s", p.name.c_str());
    
    Director::getInstance()->getEventDispatcher()->setEnabled(true);
    
    //SPLoading::stop();
    
    if (p.name.length()) {
        
        // Stars purchase
        
        purchase_id stars_purchase_id = IAPConfig::getStarPurchaseId(p.name.c_str());
        
        if (stars_purchase_id != purchase_id_unknown) {
            
            // Unlock disable ads
            
            if (stars_purchase_id == purchase_id_elite_subscription) {
                
                if (_delegate) {
                    _delegate->in_app_did_purchase_subscription(stars_purchase_id);
                }
                
            }
            else if (stars_purchase_id == purchase_id_remove_ads) {
                if (_delegate) {
                    _delegate->shopDidPurchaseDisableAds(this, false);
                }
            }
            
        }
        
        if (PlatformManager::isGDPR_Optin()){
            
            int sessionsCount = UserDefault::getInstance()->getIntegerForKey("Ses");
          
        }
    PlatformManager::validateAndTrackPurchase(p.receiptCipheredPayload.c_str(),p.receipt.c_str(),p.price.c_str(),p.currencyCode.c_str(),p.id.c_str(),p.transactionID.c_str());
    }
    
    
    if (_delegate) {
        _delegate->shopStars_In_App_PurchasesSuccess(this);
    }
    
}

void IAPManager::onFailure(sdkbox::Product const& p, const std::string &msg){
    CCLOG("Purchase Failed: %s", msg.c_str());
    
    if (_delegate) {
        _delegate->shopStars_In_App_PurchasesFailed(this);
    }
    
    bool is_non_consumable_failed = false;
    
    bool is_android = Game::is_Android();
    
    // RESTORE NON-CONSUMABLE PURCHASE
    
    if (p.name.length() && p.type == NON_CONSUMABLE && is_android) {
        
        if (std::strcmp(p.name.c_str(), "subscription_elite") == 0) {
            is_non_consumable_failed = true;
        }
        
    }
    
    if (is_non_consumable_failed) {
        
        // restore
        //log("Try to restore non-consumable purchases");
        
        // WHY CANNOT IAP DO RESTORE INSTANTLY ???
        
        auto delay = DelayTime::create(0.5f);
        auto call = CallFunc::create([]{
            sdkbox::IAP::restore();
        });
        Director::getInstance()->getRunningScene()->runAction(Sequence::create(delay,call, NULL));
        
        //
        
    }
    
    // PURCHASE FAILED
    
    else{

        MessageBox("Please try again later","Purchase failed");
        
        sdkbox::IAP::refresh();
    }
    
    Director::getInstance()->getEventDispatcher()->setEnabled(true);
    
}

void IAPManager::onCanceled(sdkbox::Product const& p){
    
    
    CCLOG("Purchase Canceled: %s", p.id.c_str());
    
    Director::getInstance()->getEventDispatcher()->setEnabled(true);
    
    if (_delegate) {
        _delegate->shopStars_In_App_PurchasesCanceled(this);
    }
}

void IAPManager::onRestored(sdkbox::Product const& p){
    CCLOG("Purchase Restored: %s", p.name.c_str());
    Director::getInstance()->getEventDispatcher()->setEnabled(true);
    
    if (p.name.length()) {
        purchase_id purchase_id = IAPConfig::getStarPurchaseId(p.name);
        
        if (purchase_id == purchase_id_elite_subscription) {
            
            if (_delegate) {
                _delegate->in_app_did_restore_subscription(purchase_id);
            }
            
        }
        else if (purchase_id == purchase_id_remove_ads) {
            
            if (IAPConfig::didPurchase_disable_ads() == false) {
                MessageBox("In-App purchases restored","Restored successfully");
            }
            
            if (_delegate) {
                _delegate->shopDidPurchaseDisableAds(this, true);
            }
            
        }
        else{
            if (_delegate) {
                _delegate->shopStars_In_App_PurchasesFailed(this);
            }
        }
        
    }
    else{
        if (_delegate) {
            _delegate->shopStars_In_App_PurchasesFailed(this);
        }
    }
    
    // SPLoading::stop();
    
}

void IAPManager::onProductRequestSuccess(std::vector<sdkbox::Product> const &products){
    
    if (products.size()) {
        sdkBoxDidRefresh = true;
    }
    
    for (int x = 0; x < products.size(); x++){
        Product product = products.at(x);
        all_available_products.push_back(product);
        
        log("\nproduct name %s",product.name.c_str());
        log("product price %s",product.price.c_str());
        log("product title %s",product.title.c_str());
        log("product description %s",product.description.c_str());
        log("product price float %f",product.priceValue);
        IAP_Type type = product.type;
        log("product type %i",type);
        if (type == NON_CONSUMABLE) {
        }
        log("product receipt ? %s",product.receipt.c_str());
        log("product receiptCipheredPayload ? %s",product.receiptCipheredPayload.c_str());
        // productsInfoArray.push_back(product);
    }
}

void IAPManager::onProductRequestFailure(const std::string &msg){
    //CCLOG("Fail to load products: %s",msg.c_str());
    sdkBoxDidRefresh = false;
    
    if (_delegate) {
        _delegate->shopStars_In_App_PurchasesItemsRequestFailed(this);
    }
    //   AnalitycsManager::logEvent("GAME_INAPP", "REQUEST_FAILURE", msg.c_str(), 0);
}

