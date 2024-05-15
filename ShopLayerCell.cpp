//
//  ShopLayerCell.cpp
//  bottlechallenge
//
//  Created by Marek on 26/09/2016.
//
//

#include "ShopLayerCell.h"

void ShopLayerCell::updateContent(){
    SPCollectionViewCell::updateContent();
    
    setOpacity(0);
    
    int rows    = 0;
    int columns = 0;
    
    Size cell_size = Size(getContentSize().width / items_count.x, getContentSize().width / items_count.y);
    
    float px = cell_size.width * 0.5f;
    float py = getContentSize().height - (cell_size.height * 0.5f);
    
    for (int i = 0; i < items.size(); i++) {
        CellItem item = items.at(i);
        
        ShopLayerCellItem * cell_i = ShopLayerCellItem::create();
        
        cell_i->_shop_category = _shop_category;
        
        cell_i->setContentSize(cell_size * 0.9f);
        addChild(cell_i);
        cell_i->setPosition(Point(px,py));
        
        cell_i->setItem(item._item);
        cell_i->setSelected(item._selected);
        cell_i->setIsPurchased(item._purchased);
        
        cell_i->updateContent();
        
        float full_scale = cell_i->getScale();
        cell_i->setScale(0);
        
        auto scale = ScaleTo::create(0.5f, full_scale);
        auto ease  = EaseElasticOut::create(scale, 0.7f);
        auto delay = DelayTime::create(0.03f * i);
        auto seq   = Sequence::create(delay, ease, NULL);
        cell_i->runAction(seq);
        
        if (_collection_view) {
            _collection_view->addInteligentSprite(cell_i);
        }
        
        _all_items.push_back(cell_i);
        
        columns++;
        px+=cell_size.width;
        
        if (columns >= items_count.x) {
            columns = 0;
            rows++;
            px = cell_size.width * 0.5f;
            py-=cell_size.height;
        }
    }
}

