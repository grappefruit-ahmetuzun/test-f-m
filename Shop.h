//
//  Shop.hpp
//  SummerGames
//
//  Created by Marek on 7/17/16.
//
//

#ifndef Shop_h
#define Shop_h

#include "cocos2d.h"
#include "Game.h"
#include "SoundDirector.h"

USING_NS_CC;

using namespace std;


enum SHOP_ITEM{
    
    item_unknown                            = -2,
    item_none                               = -1,
    
    KNIFE_TYPE_DEFAULT_WEAPON               = 0,
    KNIFE_TYPE_WEAPON_1,
    KNIFE_TYPE_WEAPON_2,
    KNIFE_TYPE_WEAPON_3,
    KNIFE_TYPE_WEAPON_4,
    KNIFE_TYPE_WEAPON_5,
    KNIFE_TYPE_WEAPON_6,
    KNIFE_TYPE_WEAPON_7,
    KNIFE_TYPE_WEAPON_8,
    KNIFE_TYPE_WEAPON_9,
    KNIFE_TYPE_WEAPON_10,
    KNIFE_TYPE_WEAPON_11,
    KNIFE_TYPE_WEAPON_12,
    KNIFE_TYPE_WEAPON_13,
    KNIFE_TYPE_WEAPON_14,
    KNIFE_TYPE_WEAPON_15,
    KNIFE_TYPE_WEAPON_16,
    KNIFE_TYPE_WEAPON_17,
    KNIFE_TYPE_WEAPON_18,
    KNIFE_TYPE_WEAPON_19,
    KNIFE_TYPE_WEAPON_20,
    KNIFE_TYPE_WEAPON_21,
    KNIFE_TYPE_WEAPON_22,
    KNIFE_TYPE_WEAPON_23,
    KNIFE_TYPE_WEAPON_24,
    KNIFE_TYPE_WEAPON_25,
    KNIFE_TYPE_WEAPON_26,
    KNIFE_TYPE_WEAPON_27,
    KNIFE_TYPE_WEAPON_28,
    KNIFE_TYPE_WEAPON_29,
    KNIFE_TYPE_WEAPON_30,
    KNIFE_TYPE_WEAPON_31,
    KNIFE_TYPE_WEAPON_32,
    KNIFE_TYPE_WEAPON_33,
    KNIFE_TYPE_WEAPON_34,
    KNIFE_TYPE_WEAPON_35,
    KNIFE_TYPE_WEAPON_36,
    KNIFE_TYPE_WEAPON_37,
    KNIFE_TYPE_WEAPON_38,
    KNIFE_TYPE_WEAPON_39,
    KNIFE_TYPE_WEAPON_40,
    KNIFE_TYPE_WEAPON_41,
    KNIFE_TYPE_WEAPON_42,
    KNIFE_TYPE_WEAPON_43,
    KNIFE_TYPE_WEAPON_44,
    KNIFE_TYPE_WEAPON_45,
    KNIFE_TYPE_WEAPON_46,
    KNIFE_TYPE_WEAPON_47,
    KNIFE_TYPE_WEAPON_48,
    KNIFE_TYPE_WEAPON_49,
    KNIFE_TYPE_WEAPON_50,
    KNIFE_TYPE_WEAPON_51,
    KNIFE_TYPE_WEAPON_52,
    KNIFE_TYPE_WEAPON_53,
    KNIFE_TYPE_WEAPON_54,
    KNIFE_TYPE_WEAPON_55,
    KNIFE_TYPE_WEAPON_56,
    KNIFE_TYPE_WEAPON_57,
    KNIFE_TYPE_WEAPON_58,
    KNIFE_TYPE_WEAPON_59,
    KNIFE_TYPE_WEAPON_60,
    KNIFE_TYPE_WEAPON_61,
    KNIFE_TYPE_WEAPON_62,
    KNIFE_TYPE_WEAPON_63,
    KNIFE_TYPE_WEAPON_64

    
};

enum SHOP_ITEMS_CATEGORY{
    
    SHOP_ITEMS_UNKNOWN              = -1,
    SHOP_ITEMS_KNIVES               = 0,
    
};


enum SHOP_PAGE_TYPE{
    SHOP_PAGE_TYPE_UNKNOWN                              = -1,
    SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_1                  = 0,
    SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_2                  = 1,
    SHOP_PAGE_TYPE_KNIVES_GEM_PAGE_1                    = 2,
    SHOP_PAGE_TYPE_KNIVES_FORTUNE_WHLLE_PAGE_1          = 3
};



struct ShopItem{
    SHOP_ITEM    _id      = item_unknown;
    std::string  _imgPath = "";
};

class Shop{
    
public:
    
    static SHOP_ITEMS_CATEGORY getItemCategory(SHOP_ITEM item){
        
        if (item >= KNIFE_TYPE_DEFAULT_WEAPON){
            return SHOP_ITEMS_KNIVES;
        }
        return SHOP_ITEMS_UNKNOWN;
    }
    

    static int getItemPrice(SHOP_PAGE_TYPE page = SHOP_PAGE_TYPE_UNKNOWN){
        
        int price = 250;
        
        if (page == SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_1) {
            price = 500;
        }
        else if (page == SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_2) {
            price = 250;
        }
        else if (page == SHOP_PAGE_TYPE_KNIVES_GEM_PAGE_1) {
            price = 100;
        }
        
        return price;
        
    }

    static std::vector<SHOP_ITEM> get_knives(SHOP_PAGE_TYPE page = SHOP_PAGE_TYPE_UNKNOWN){
        std::vector<SHOP_ITEM> knives;
        
        if (page == SHOP_PAGE_TYPE_UNKNOWN || page == SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_1) {
            knives.push_back(KNIFE_TYPE_DEFAULT_WEAPON);
            knives.push_back(KNIFE_TYPE_WEAPON_17);
            knives.push_back(KNIFE_TYPE_WEAPON_18);
            knives.push_back(KNIFE_TYPE_WEAPON_19);
            
            knives.push_back(KNIFE_TYPE_WEAPON_20);
            knives.push_back(KNIFE_TYPE_WEAPON_21);
            knives.push_back(KNIFE_TYPE_WEAPON_22);
            knives.push_back(KNIFE_TYPE_WEAPON_23);
            
            knives.push_back(KNIFE_TYPE_WEAPON_24);
            knives.push_back(KNIFE_TYPE_WEAPON_25);
            knives.push_back(KNIFE_TYPE_WEAPON_26);
            knives.push_back(KNIFE_TYPE_WEAPON_27);
            
            knives.push_back(KNIFE_TYPE_WEAPON_28);
            knives.push_back(KNIFE_TYPE_WEAPON_29);
            knives.push_back(KNIFE_TYPE_WEAPON_30);
            knives.push_back(KNIFE_TYPE_WEAPON_31);
            
        }
        if (page == SHOP_PAGE_TYPE_UNKNOWN || page == SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_2) {
         
            knives.push_back(KNIFE_TYPE_WEAPON_7);
            knives.push_back(KNIFE_TYPE_WEAPON_1);
            knives.push_back(KNIFE_TYPE_WEAPON_2);
            knives.push_back(KNIFE_TYPE_WEAPON_3);
            
            knives.push_back(KNIFE_TYPE_WEAPON_4);
            knives.push_back(KNIFE_TYPE_WEAPON_5);
            knives.push_back(KNIFE_TYPE_WEAPON_6);
            knives.push_back(KNIFE_TYPE_WEAPON_8);
            
            knives.push_back(KNIFE_TYPE_WEAPON_9);
            knives.push_back(KNIFE_TYPE_WEAPON_10);
            knives.push_back(KNIFE_TYPE_WEAPON_11);
            knives.push_back(KNIFE_TYPE_WEAPON_12);
            
            knives.push_back(KNIFE_TYPE_WEAPON_13);
            knives.push_back(KNIFE_TYPE_WEAPON_14);
            knives.push_back(KNIFE_TYPE_WEAPON_15);
            knives.push_back(KNIFE_TYPE_WEAPON_16);
        }
        if (page == SHOP_PAGE_TYPE_UNKNOWN || page == SHOP_PAGE_TYPE_KNIVES_GEM_PAGE_1) {
            
            knives.push_back(KNIFE_TYPE_WEAPON_33);
            knives.push_back(KNIFE_TYPE_WEAPON_34);
            knives.push_back(KNIFE_TYPE_WEAPON_35);
            knives.push_back(KNIFE_TYPE_WEAPON_36);
            
            knives.push_back(KNIFE_TYPE_WEAPON_37);
            knives.push_back(KNIFE_TYPE_WEAPON_38);
            knives.push_back(KNIFE_TYPE_WEAPON_39);
            knives.push_back(KNIFE_TYPE_WEAPON_40);
            
            knives.push_back(KNIFE_TYPE_WEAPON_41);
            knives.push_back(KNIFE_TYPE_WEAPON_42);
            knives.push_back(KNIFE_TYPE_WEAPON_43);
            knives.push_back(KNIFE_TYPE_WEAPON_44);
            
            knives.push_back(KNIFE_TYPE_WEAPON_45);
            knives.push_back(KNIFE_TYPE_WEAPON_46);
            knives.push_back(KNIFE_TYPE_WEAPON_47);
            knives.push_back(KNIFE_TYPE_WEAPON_48);
        }
        if (page == SHOP_PAGE_TYPE_UNKNOWN || page == SHOP_PAGE_TYPE_KNIVES_FORTUNE_WHLLE_PAGE_1) {
            
            knives.push_back(KNIFE_TYPE_WEAPON_49);
            knives.push_back(KNIFE_TYPE_WEAPON_50);
            knives.push_back(KNIFE_TYPE_WEAPON_51);
            knives.push_back(KNIFE_TYPE_WEAPON_52);
            
            knives.push_back(KNIFE_TYPE_WEAPON_53);
            knives.push_back(KNIFE_TYPE_WEAPON_54);
            knives.push_back(KNIFE_TYPE_WEAPON_55);
            knives.push_back(KNIFE_TYPE_WEAPON_56);
            
            knives.push_back(KNIFE_TYPE_WEAPON_57);
            knives.push_back(KNIFE_TYPE_WEAPON_58);
            knives.push_back(KNIFE_TYPE_WEAPON_59);
            knives.push_back(KNIFE_TYPE_WEAPON_60);
            
            knives.push_back(KNIFE_TYPE_WEAPON_61);
            knives.push_back(KNIFE_TYPE_WEAPON_62);
            knives.push_back(KNIFE_TYPE_WEAPON_63);
            knives.push_back(KNIFE_TYPE_WEAPON_64);
        }
        
        
        return knives;
    }
    
    
    static Color3B getPageColor(SHOP_PAGE_TYPE page, bool locked){
        
        if (page == SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_1 || page == SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_2) {
            if (locked) {
                return Color3B(50,186,175);
            }
            else{
                return Color3B::WHITE;
            }
        }
        else if (page == SHOP_PAGE_TYPE_KNIVES_GEM_PAGE_1) {
            if (locked) {
                return Color3B(44,182,242);
            }
            else{
                return Color3B::WHITE;
            }
        }
        else if (page == SHOP_PAGE_TYPE_KNIVES_FORTUNE_WHLLE_PAGE_1) {
            if (locked) {
                return Color3B(239,132,205);
            }
            else{
                return Color3B::WHITE;
            }
        }
       
        return Color3B(255, 255, 255);
        
    }
    
    static std::string getCellBg(SHOP_PAGE_TYPE page, bool locked){
        return "shop/unlocked.png";
    }
    
    static std::string get_knife_image(SHOP_ITEM item);
    static std::string get_knife_name(SHOP_ITEM item);
    static float get_knife_scale(SHOP_ITEM item);
    static float get_knife_custom_scale_offset(SHOP_ITEM item);
    static float get_knife_rotation(SHOP_ITEM item);
    
    static std::string get_page_name(SHOP_PAGE_TYPE page);
    
    static bool weapon_must_rotating(SHOP_ITEM item);
};

#endif /* Shop_h */
