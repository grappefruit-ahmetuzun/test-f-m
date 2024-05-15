//
//  ShopItemPreview.h
//  FruitsKnife-mobile
//
//  Created by Slavik on 6/5/18.
//

#ifndef ShopItemPreview_h
#define ShopItemPreview_h

#include "cocos2d.h"
#include "Shop.h"

USING_NS_CC;

class ShopItemPreview : public Sprite{
 
public:
    
    CREATE_FUNC(ShopItemPreview);
    
    void setItem(SHOP_ITEM _type,bool animated);
    
    Sprite    * _item_sprite        = nullptr;
};

#endif /* ShopItemPreview_h */
