//
//  ShopLayerCellItem.cpp
//  KnifesGame-mobile
//
//  Created by Viaceslav Adamovic on 22/01/2018.
//

#include "ShopLayerCellItem.h"
#include "Shop.h"

void ShopLayerCellItem::updateContent(){
    
    setOpacity(0);
    
    if (_content == nullptr){
        std::string content_texture = Shop::getCellBg(_shop_category, true);
        _content = Sprite::create(content_texture.c_str());
        addChild(_content);
        _content->setScale(getContentSize().width /_content->getContentSize().width);
        _content->setPosition(getContentSize()*0.5f);
    }
    
    if (!_item_sprite){
        _item_sprite = Sprite::create(_item._imgPath.c_str());
        _content->addChild(_item_sprite);

        //float scale = Shop::get_knife_scale(_item._id);

        
        _item_sprite->setScale((_content->getContentSize().height * 0.75f) / _item_sprite->getContentSize().height);
        _item_sprite->setRotation(45);
        _item_sprite->setPosition(Vec2(_content->getContentSize().width * 0.5f, _content->getContentSize().height * 0.5f));
    }

    if (!_selected_frame){
        _selected_frame = Sprite::create("shop/selected.png");
        _content->addChild(_selected_frame);
        _selected_frame->setScale(_content->getContentSize().width/_selected_frame->getContentSize().width);
        _selected_frame->setPosition(_content->getContentSize()*0.5f);
        _selected_frame->setColor(Color3B(255,234,55));
    }

    if (_purchased) {
        _item_sprite->setColor(Color3B(255, 255, 255));
        _content->setColor(Shop::getPageColor(_shop_category, false));
    }
    else{
        _item_sprite->setColor(Color3B(0, 0, 0));
        _content->setColor(Shop::getPageColor(_shop_category, true));
    }
    
    setSelected(_selected, false, nullptr);
    
    if (_selected) {
        _selected_frame->setVisible(true);
    }
    else{
        _selected_frame->setVisible(false);
    }
}

void ShopLayerCellItem::setSelected(bool s){
    _selected = s;
}

void ShopLayerCellItem::setIsPurchased(bool purchased){
    _purchased = purchased;
}

void ShopLayerCellItem::setSelected(bool s,bool animated,const std::function<void()> &finished){
    _selected = s;
}

void ShopLayerCellItem::setItem(ShopItem i){
    _item = i;
}
