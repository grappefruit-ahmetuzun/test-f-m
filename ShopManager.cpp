//
//  ShopManager.cpp
//  SummerGames
//
//  Created by Marek on 18/07/16.
//
//

#include "ShopManager.h"
#include "Shop.h"
#include <iostream>
#include <ctime>
#include "PlatformManager.h"

std::shared_ptr<ShopManager> shop_managerInstance;

std::shared_ptr<ShopManager> ShopManager::getInstance() {
    if (shop_managerInstance){
        return shop_managerInstance;
    }
    
    shop_managerInstance = std::make_shared< ShopManager >();
    return shop_managerInstance;
}

void ShopManager::preload(){
   
     _data_items = new ShopDataModel("knifedsaljd9776");
    
    if (_data_items->isPurchased(KNIFE_TYPE_DEFAULT_WEAPON) == false) {
        _data_items->purchase(KNIFE_TYPE_DEFAULT_WEAPON);
        set_item_not_new(KNIFE_TYPE_DEFAULT_WEAPON);
    }
    
    if (_data_items->isPurchased(KNIFE_TYPE_WEAPON_7) == false) {
        _data_items->purchase(KNIFE_TYPE_WEAPON_7);
        set_item_selected(KNIFE_TYPE_WEAPON_7);
        set_item_not_new(KNIFE_TYPE_WEAPON_7);
    }
    
    _selected_knife    = (SHOP_ITEM)SPUserDefault::getInstance()->getIntegerForKey("pknife");
    
//    if (_selected_knife == 0) {
//        _data_items->purchase(KNIFE_TYPE_WEAPON_7);
//        set_item_selected(KNIFE_TYPE_WEAPON_7);
//        set_item_not_new(KNIFE_TYPE_WEAPON_7);
//    }

}

void ShopManager::set_item_selected(SHOP_ITEM item){
    
    SHOP_ITEMS_CATEGORY category = Shop::getItemCategory(item);
    
    if (category == SHOP_ITEMS_KNIVES) {
        _selected_knife = item;
        SPUserDefault::getInstance()->setIntegerForKey("pknife", _selected_knife);
    }
    
    if (_delegate) {
        _delegate->shop_item_selected_didchange(item);
    }
    
}

void ShopManager::set_item_purchase(SHOP_ITEM item){
    _data_items->purchase(item);
}

void ShopManager::set_item_not_new(SHOP_ITEM item){
    _data_items->set_as_not_new(item);
}

// getters

ShopItem ShopManager::get_item(SHOP_ITEM item){
    ShopItem i;
    i._id       = item;
    i._imgPath  = Shop::get_knife_image(item);
    return i;
}

std::vector<SHOP_ITEM> ShopManager::get_items_purchased(SHOP_ITEMS_CATEGORY category){

    std::vector<SHOP_ITEM>items_purchased        = _data_items->get_items();
    
    if (category == SHOP_ITEMS_UNKNOWN) {
        return items_purchased;
    }
    
    std::vector<SHOP_ITEM>items_by_category;
    
    for (int x=0; x < items_purchased.size(); x++) {
        SHOP_ITEM item = items_purchased.at(x);
        if (Shop::getItemCategory(item) == category) {
            items_by_category.push_back(item);
        }
    }
    
    return items_by_category;
}

std::vector<SHOP_ITEM> ShopManager::get_items_locked(SHOP_ITEMS_CATEGORY category){
    std::vector<SHOP_ITEM>items = Shop::get_knives();
    std::vector<SHOP_ITEM>locked;
    for (int x=0; x < items.size(); x++) {
        SHOP_ITEM item = items.at(x);
        if (_data_items->isPurchased(item) == false) {
            locked.push_back(item);
        }
    }
    return locked;
}
SHOP_ITEM ShopManager::get_item_selected(SHOP_ITEMS_CATEGORY category){
    if (category == SHOP_ITEMS_KNIVES) {
        return _selected_knife;
    }
    return _selected_knife;
}

bool ShopManager::is_item_not_new(SHOP_ITEM item){
    return _data_items->is_not_new(item);
}

bool ShopManager::is_item_purchased(SHOP_ITEM item){
 
//    if (item == WEAPON_TYPE_M739) {
//
//        SUBSCRIPTION_STATE subscription_state = Subscribtions::getInstance()->getCurrentSubscriptionState();
//
//        if (subscription_state == SUBSCRIPTION_STATE_SUBSCRIBE_ACTIVE) {
//            return true;
//        }
//        else{
//            return false;
//        }
//
//    }

    return _data_items->isPurchased(item);
}
