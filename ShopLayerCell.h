//
//  ShopLayerCell.hpp
//  bottlechallenge
//
//  Created by Marek on 26/09/2016.
//
//

#ifndef ShopLayerCell_h
#define ShopLayerCell_h

#include "SPCollectionView.h"
#include "Shop.h"
#include "ShopLayerCellItem.h"

struct CellItem{
    ShopItem _item;
    bool _selected   = false;
    bool _purchased  = false;
};

class ShopLayerCell : public SPCollectionViewCell {
    
public:
    
    ShopLayerCell(){};
    ~ShopLayerCell(){};
    
    CREATE_FUNC(ShopLayerCell);
    
    virtual void updateContent() override;

    std::vector<CellItem>items;
    
    std::vector<ShopLayerCellItem *> _all_items;
    
    SHOP_PAGE_TYPE _shop_category = SHOP_PAGE_TYPE_UNKNOWN;
    
    Vec2 items_count = Vec2(0, 0);
    
    SPCollectionView * _collection_view = nullptr;
    
private:

};

#endif /* ShopLayerCell_hpp */
