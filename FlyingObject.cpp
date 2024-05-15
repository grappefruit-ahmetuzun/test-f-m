//
//  FlyingCoin.cpp
//  hiball
//
//  Created by Viaceslav Adamovic on 22/02/2017.
//
//

#include "FlyingObject.h"
#include "Shop.h"

FlyingObject * FlyingObject::createWithType(FLYING_OBJECT_TYPE t){
    FlyingObject * sprite = new (std::nothrow) FlyingObject();
    sprite->setObject_type(t);
    
    if (t == FLYING_OBJECT_TYPE_COIN) {
        sprite->setTexture_title("settings/small_coin.png");
    }
    else if (t == FLYING_OBJECT_TYPE_GEM){
        sprite->setTexture_title("hud/blue_gem.png");
    }
    
    if (sprite && sprite->init()){
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool FlyingObject::init(){
    if (!Sprite::initWithFile(_texture_title.c_str())){
        return false;
    }
    return true;
}

void FlyingObject::prepare(bool add_trail){

    float tile_size    = getBoundingBox().size.width;
    
    if (add_trail) {
        tail = CustomMotionStreak::create(0.15f, 1.2f, tile_size, getTile_color(), "coin_motion_streak.png");
        tail->setBlendFunc({GL_ONE, GL_ONE_MINUS_SRC_ALPHA});
        tail->setOpacity(100);
        
        getParent()->addChild(tail, getLocalZOrder() - 1);
        
        updatePosition();
    }
}

void FlyingObject::updatePosition(){

    if (tail) {
        Point w_pos = getParent()->convertToWorldSpace(getPosition());
        tail->setPosition(w_pos);
        
        tail->setStroke(getBoundingBox().size.width * 0.65f);
    }
}
