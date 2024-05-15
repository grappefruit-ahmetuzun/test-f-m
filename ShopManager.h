//
//  ShopManager.hpp
//  SummerGames
//
//  Created by Marek on 18/07/16.
//
//

#ifndef ShopManager_h
#define ShopManager_h

#include "cocos2d.h"
#include "SPUserDefault.h"
#include "ShopDataModel.h"
#include "Shop.h"
#include "Game.h"

USING_NS_CC;


class ShopManagerDelegate;
class ShopManager : public Ref{
public:
    
    static std::shared_ptr< ShopManager > getInstance();
    ShopManager():
    _delegate(nullptr)
    {
        preload();
    };
    
    void set_item_selected                                  (SHOP_ITEM item);
    void set_item_purchase                                  (SHOP_ITEM item);
    void set_item_not_new                                   (SHOP_ITEM item);
    
    std::vector<SHOP_ITEM>  get_items_purchased             (SHOP_ITEMS_CATEGORY category = SHOP_ITEMS_KNIVES);
    std::vector<SHOP_ITEM>  get_items_locked                (SHOP_ITEMS_CATEGORY category = SHOP_ITEMS_KNIVES);
    SHOP_ITEM               get_item_selected               (SHOP_ITEMS_CATEGORY category = SHOP_ITEMS_KNIVES);
    ShopItem                get_item                        (SHOP_ITEM item);

    bool                    is_item_not_new                 (SHOP_ITEM item);
    bool                    is_item_purchased               (SHOP_ITEM item);

    
private:
    
    void preload();
    
    ShopDataModel * _data_items = nullptr;
    
    SHOP_ITEM _selected_knife    = KNIFE_TYPE_WEAPON_7;
    
    CC_SYNTHESIZE(ShopManagerDelegate *,            _delegate,              Delegate);
    
};

class ShopManagerDelegate
{
public:
    
    virtual void shop_item_selected_didchange   (SHOP_ITEM item_id){};
    
};

#endif /* ShopManager_hpp */
