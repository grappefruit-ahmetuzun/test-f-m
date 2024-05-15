//
//  ShopLayerCellItem.h
//  KnifesGame-mobile
//
//  Created by Viaceslav Adamovic on 22/01/2018.
//

#ifndef ShopLayerCellItem_h
#define ShopLayerCellItem_h

#include "CoinsAmmountSprite.h"
#include "Shop.h"

class ShopLayerCellItem : public Sprite {
    
public:
    
    ShopLayerCellItem(){};
    ~ShopLayerCellItem(){};
    
    CREATE_FUNC(ShopLayerCellItem);
    
    void updateContent();
    
    void setItem(ShopItem i);
    
    void    setSelected         (bool s);
    void    setIsPurchased      (bool purchased);
    
    void    setSelected         (bool s,bool animated,const std::function<void()> &finished);
    
    bool    isSelected()        {return _selected;}
    
    ShopItem              _item;
    Sprite              * _content                  = nullptr;
    Sprite              * _item_sprite              = nullptr;
    Sprite              * _selected_frame           = nullptr;
   
  
    bool _selected                                  = false;
    bool _purchased                                 = false;
    
    SHOP_PAGE_TYPE _shop_category = SHOP_PAGE_TYPE_UNKNOWN;
    
private:
    
};

#endif /* ShopLayerCellItem_h */
