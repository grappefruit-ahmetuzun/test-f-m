//
//  Shop.cpp
//  SummerGames
//
//  Created by Marek on 7/17/16.
//
//

#include "Shop.h"
#include "ShopManager.h"

std::string Shop::get_knife_image(SHOP_ITEM item){
    return StringUtils::format("weapons/weapon_%i.png", item);
}

float Shop::get_knife_scale(SHOP_ITEM item){
    
    switch (item) {
        case KNIFE_TYPE_DEFAULT_WEAPON:       return 1.0f;
        default: break;
    }
    
    return 1.0f;
}

float Shop::get_knife_rotation(SHOP_ITEM item){
    
    switch (item) {
        case KNIFE_TYPE_DEFAULT_WEAPON:       return 0;
        default: break;
    }
    
    return 45;
}

bool Shop::weapon_must_rotating(SHOP_ITEM item){
    
    if (item == KNIFE_TYPE_DEFAULT_WEAPON ||
        item == KNIFE_TYPE_WEAPON_17 ||
        item == KNIFE_TYPE_WEAPON_18 ||
        item == KNIFE_TYPE_WEAPON_19 ||
        item == KNIFE_TYPE_WEAPON_20 ||
        item == KNIFE_TYPE_WEAPON_20 ||
        item == KNIFE_TYPE_WEAPON_21 ||
        item == KNIFE_TYPE_WEAPON_22 ||
        item == KNIFE_TYPE_WEAPON_23 ||
        item == KNIFE_TYPE_WEAPON_24 ||
        item == KNIFE_TYPE_WEAPON_25 ||
        item == KNIFE_TYPE_WEAPON_26 ||
        item == KNIFE_TYPE_WEAPON_27 ||
        item == KNIFE_TYPE_WEAPON_28 ||
        item == KNIFE_TYPE_WEAPON_29 ||
        item == KNIFE_TYPE_WEAPON_31 ||
        item == KNIFE_TYPE_WEAPON_32 ||
        item == KNIFE_TYPE_WEAPON_38 ||
        item == KNIFE_TYPE_WEAPON_39 ||
        item == KNIFE_TYPE_WEAPON_42 ||
        item == KNIFE_TYPE_WEAPON_45 ||
        item == KNIFE_TYPE_WEAPON_30 ||
        item == KNIFE_TYPE_WEAPON_49 ||
        item == KNIFE_TYPE_WEAPON_51 ||
        item == KNIFE_TYPE_WEAPON_52 ||
        item == KNIFE_TYPE_WEAPON_53 ||
        item == KNIFE_TYPE_WEAPON_54 ||
        item == KNIFE_TYPE_WEAPON_57 ||
        item == KNIFE_TYPE_WEAPON_58 ||
        item == KNIFE_TYPE_WEAPON_59 ||
        item == KNIFE_TYPE_WEAPON_60 ||
        item == KNIFE_TYPE_WEAPON_61 ||
        item == KNIFE_TYPE_WEAPON_64) {
        return true;
    }
    return false;
}

float Shop::get_knife_custom_scale_offset(SHOP_ITEM item){
    
    if (item == KNIFE_TYPE_WEAPON_1 ||
        item == KNIFE_TYPE_WEAPON_2 ||
        item == KNIFE_TYPE_WEAPON_3 ||
        item == KNIFE_TYPE_WEAPON_4 ||
        item == KNIFE_TYPE_WEAPON_5 ||
        item == KNIFE_TYPE_WEAPON_6 ||
        item == KNIFE_TYPE_WEAPON_7 ||
        item == KNIFE_TYPE_WEAPON_8 ||
        item == KNIFE_TYPE_WEAPON_9 ||
        item == KNIFE_TYPE_WEAPON_10 ||
        item == KNIFE_TYPE_WEAPON_11 ||
        item == KNIFE_TYPE_WEAPON_12 ||
        item == KNIFE_TYPE_WEAPON_13 ||
        item == KNIFE_TYPE_WEAPON_14 ||
        item == KNIFE_TYPE_WEAPON_15 ||
        item == KNIFE_TYPE_WEAPON_16 ||
        item == KNIFE_TYPE_WEAPON_33 ||
        item == KNIFE_TYPE_WEAPON_34 ||
        item == KNIFE_TYPE_WEAPON_35 ||
        item == KNIFE_TYPE_WEAPON_36 ||
        item == KNIFE_TYPE_WEAPON_37 ||
        item == KNIFE_TYPE_WEAPON_38 ||
        item == KNIFE_TYPE_WEAPON_40 ||
        item == KNIFE_TYPE_WEAPON_41 ||
        item == KNIFE_TYPE_WEAPON_43 ||
        item == KNIFE_TYPE_WEAPON_44 ||
        item == KNIFE_TYPE_WEAPON_48 ||
        item == KNIFE_TYPE_WEAPON_55 ||
        item == KNIFE_TYPE_WEAPON_56 ||
        item == KNIFE_TYPE_WEAPON_62 ||
        item == KNIFE_TYPE_WEAPON_63 ||
        item == KNIFE_TYPE_WEAPON_64){
        return 0.3f;
    }
    else if (item == KNIFE_TYPE_WEAPON_61) {
        return 0.15f;
    }
    
    return 0.0f;
}

std::string Shop::get_page_name(SHOP_PAGE_TYPE page){
    switch (page) {
        case SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_1:
        case SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_2:            return "BUY FOR COINS";
        case SHOP_PAGE_TYPE_KNIVES_GEM_PAGE_1:              return "BUY FOR GEMS";
        case SHOP_PAGE_TYPE_KNIVES_FORTUNE_WHLLE_PAGE_1:    return "FORTUNE WEAPONS";
            
        default: break;
    }
    return "";
}
