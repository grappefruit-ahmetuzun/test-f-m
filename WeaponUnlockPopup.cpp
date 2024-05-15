//
//  WeaponUnlockPopup.cpp
//  FruitsKnife-mobile
//
//  Created by Slavik on 6/12/18.
//

#include "WeaponUnlockPopup.h"

bool WeaponUnlockPopup::init(){
    if (!GameLayer::init()){
        return false;
    }
    
    return true;
}

void WeaponUnlockPopup::prepare(SHOP_ITEM item){
    
    _item = item;
    
    Sprite * _background = Sprite::create();
    _background->setTextureRect(Rect(0, 0, getContentSize().width, getContentSize().height));
    _background->setPosition(getContentSize()/2);
    addChild(_background);
    _background->setColor(Color3B(0, 0, 0));
    _background->setOpacity(0);
    
    _background->runAction(Sequence::create(FadeTo::create(0.15f, 255 * 0.55f), NULL));
    
    
    Sprite * popup = Sprite::create("fortune_wheel/popup.png");
    popup->setScale(getContainer()->getContentSize().width * 0.75f / popup->getContentSize().width);
    popup->setPosition(Point(getContentSize().width * 0.5f, getContentSize().height * 0.55f));
    addChild(popup, 99);
    
    Sprite * beams = Sprite::create("fortune_wheel/beams.png");
    popup->addChild(beams);
    beams->setScale(popup->getContentSize().width * 1.25f / beams->getContentSize().width);
    beams->setPosition(Point(popup->getContentSize().width * 0.5f, popup->getContentSize().height * 0.735f));
    
    
    Sprite * item_sprite = Sprite::create(Shop::get_knife_image(_item));
    popup->addChild(item_sprite);
    item_sprite->setScale(popup->getContentSize().height * 0.25f / item_sprite->getContentSize().height);
    item_sprite->setPosition(beams->getPosition());
    item_sprite->setRotation(45);
    
    auto rotate = RotateBy::create(0.2f, 20);
    auto repaet = RepeatForever::create(rotate);
    beams->runAction(repaet);
    
    
    equip_button = SPButton::createWithImage("fortune_wheel/equip.png");
    popup->addChild(equip_button);
    equip_button->setScale(popup->getContentSize().height * 0.15f / equip_button->getContentSize().height);
    equip_button->setPosition(Point(popup->getContentSize().width * 0.5f, popup->getContentSize().height * 0.15f));
    
    
    close_button = SPButton::createWithImage("fortune_wheel/x.png");
    popup->addChild(close_button);
    close_button->setScale(popup->getContentSize().height * 0.1f / close_button->getContentSize().height);
    close_button->setPosition(Point(popup->getContentSize().width * 0.975f, popup->getContentSize().height * 0.98f));
    
    
    Label * _info_label = Label::createWithTTF("FORTUNE WEAPON\nUNLOCKED!", "fonts/Blogger_Sans-Bold.otf", popup->getContentSize().height * 0.065f);
    _info_label->setPosition(popup->getContentSize().width * 0.5f, popup->getContentSize().height * 0.365f);
    _info_label->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    _info_label->setColor(Color3B::BLACK);
    popup->addChild(_info_label);
    
    
    float scale_val = popup->getScale();
    popup->setScale(0);
    
    auto scale = ScaleTo::create(0.35f, scale_val);
    auto scale_e = EaseElasticOut::create(scale,1.5f);
    popup->runAction(Sequence::create(scale_e, NULL));
}

bool WeaponUnlockPopup::onTouchBegan(Touch *touch, Event *event){
    return true;
}
