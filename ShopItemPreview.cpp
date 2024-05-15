//
//  ShopItemPreview.cpp
//  FruitsKnife-mobile
//
//  Created by Slavik on 6/5/18.
//

#include "ShopItemPreview.h"

void ShopItemPreview::setItem(SHOP_ITEM _type,bool animated){
    
    if (!_item_sprite) {
        _item_sprite = Sprite::create(Shop::get_knife_image(_type));
        addChild(_item_sprite);
        _item_sprite->setScale(getContentSize().height / _item_sprite->getContentSize().height);
        _item_sprite->setPosition(Point(getContentSize().width * 0.5f, getContentSize().height * 0.5f));
    }

    std::string image_name = Shop::get_knife_image(_type);
    
    _item_sprite->setRotation(0);
    
    _item_sprite->setTexture(image_name.c_str());
    _item_sprite->setScale(getContentSize().height / _item_sprite->getContentSize().height);
    _item_sprite->setRotation(Shop::get_knife_rotation(_type));
    

    if (animated) {
        
        _item_sprite->stopAllActions();
        
        float scale = _item_sprite->getScale();
        
        _item_sprite->setScale(0);
        
        auto scale1 = ScaleTo::create(0.4f, scale);
        auto ease   = EaseElasticOut::create(scale1, 0.65f);
        _item_sprite->runAction(ease);
    }
}
