//
//  SettingsLayer.cpp
//  BasketDunk
//
//  Created by Marek on 23/10/2017.
//
//

#include "SettingsLayer.h"
#include "SoundDirector.h"
#include "PlatformManager.h"
#include "Game.h"
#include "IAPManager.h"
#include "SettingsLayer.h"
#include "SocialButtons.h"

void SettingsLayer::animateOnEnter(bool show_estoty_social){
    
    setTouchBlock(true);
    
    Sprite * _background = Sprite::create();
    _background->setTextureRect(Rect(0, 0, getContentSize().width, getContentSize().height));
    _background->setPosition(getContentSize()/2);
    addChild(_background);
    
    Sprite *_left_border = Sprite::create();
    _left_border->setTextureRect(Rect(0, 0, (getContentSize().width-(getContainer()->getContentSize().width))/2, getContentSize().height));
    _left_border->setPosition(Point(_left_border->getContentSize().width*0.5f, getContentSize().height*0.5f));
    _left_border->setColor(Color3B::BLACK);
    addChild(_left_border, 3);
    
    Sprite *_right_border = Sprite::create();
    _right_border->setTextureRect(Rect(0, 0, (getContentSize().width-(getContainer()->getContentSize().width))/2, getContentSize().height));
    _right_border->setPosition(Point(getContentSize().width - (_right_border->getContentSize().width*0.5f), getContentSize().height*0.5f));
    _right_border->setColor(Color3B::BLACK);
    addChild(_right_border, 3);
    
    
    bool dark_mode_on = Settings::getStateOn(settings_darkmode);
    
    if (dark_mode_on == true) {
        _left_border->setColor(Color3B(0, 0, 0));
        _right_border->setColor(Color3B(0, 0, 0));
        
        _background->setColor(Color3B(12, 30, 35));
    }
    else{
        _left_border->setColor(Color3B(117, 145, 157));
        _right_border->setColor(Color3B(117, 145, 157));
        
        _background->setColor(Color3B(225, 241, 241));
    }
    
    _background->setScale(getContentSize().height / _background->getContentSize().height);
    
    if (_background->getBoundingBox().size.width < getContentSize().width) {
        _background->setScaleX(getContentSize().width / _background->getContentSize().width);
    }
    
    float top_label_pos_y = getTitleLabel()->getPositionY();
    

    
    getBackButton()->setLocalZOrder(4);
    getBackButton()->setPositionY(getHeaderUIDefaultPosY()/*-getContentSize().height * 0.0075f*/);
    getBackButton()->getContentSprite()->setColor(Color3B(85, 160, 157));
    
    getTitleLabel()->setString("SETTINGS");
    getTitleLabel()->setColor(Color3B(85, 160, 157));
    
    
    
    float scroll_w = getContainer()->getContentSize().width*0.65f;
    
    Size s;
    s.width     = scroll_w;
    s.height    = (getContainer()->getContentSize().height * 0.075f) * Settings::getItems().size();
    
    // lists
    
    SPCollectionView *_collectionView = SPCollectionView::createWithSize(s);
    addChild(_collectionView,2);
    //_collectionView->setIndicatorEnabled(true);
    _collectionView->setOpacity(0);
    _collectionView->setAnchorPoint(Point(0.5f,0.5f));
    _collectionView->setCollectionViewDelegate(this);
    _collectionView->setScaleCellonTouch(true);
    _collectionView->setScrollEnabled(false);
    _collectionView->setClippingEnabled(false);

    _collectionView->reloadData();
    
    _list_chars = _collectionView;
    _list_chars->reloadData();
    _list_chars->scrollToTop();
    
    gdpr_button = SPButton::createWithImage("settings/privacy.png");
    addChild(gdpr_button, 5);
    gdpr_button->setScale(getContainer()->getContentSize().width * 0.5f / gdpr_button->getContentSize().width);
    gdpr_button->setPosition(Vec2((getContentSize().width * 0.5f),
                                     (getContentSize().height * 0.5f) + (getContainer()->getContentSize().height * 0.05f)));
    
    if (PlatformManager::isCountryGDRP() == false) {
        gdpr_button->setVisible(false);
    }
    else{
        gdpr_button->setPositionY(gdpr_button->getPositionY()+getContainer()->getContentSize().height*0.1f);
    }
    
    float pos_scroll_from = top_label_pos_y - (gdpr_button->getPositionY() + gdpr_button->getBoundingBox().size.height * 0.5f);

    
    _collectionView->setPosition(Vec2(getContentSize().width*0.5f,
                                      (gdpr_button->getPositionY() +
                                       gdpr_button->getBoundingBox().size.height * 0.5f) +
                                      pos_scroll_from/2));
    
    Sprite * blue_field = Sprite::create("settings/blue_waves.png");
    blue_field->setScaleX(getContainer()->getContentSize().width / blue_field->getContentSize().width);
    blue_field->setScaleY(getContentSize().height * 0.4f / blue_field->getContentSize().height);
    blue_field->setPosition(Point(getContentSize().width * 0.5f, blue_field->getBoundingBox().size.height * 0.5f));
    
    addChild(blue_field, 5);
    
    SocialButtons *_social_buttons = SocialButtons::create();
    _social_buttons->setPosition(Point(blue_field->getPositionX(), blue_field->getPositionY() + blue_field->getBoundingBox().size.height * 0.5f - getContainer()->getContentSize().height * 0.18f));
    _social_buttons->prepare(getContainer()->getContentSize().width);
    addChild(_social_buttons, 6);
    _social_buttons->_social_reward_give_callback = _coins_give_callback;
    
    noads_button = SPButton::createWithImage("no_ads/remove.png");
    addChild(noads_button);
    noads_button->setScale(getContainer()->getContentSize().height*0.075f/noads_button->getContentSize().height);
    
    restore_button = SPButton::createWithImage("no_ads/restore.png");
    addChild(restore_button);
    restore_button->setScale(getContainer()->getContentSize().height*0.075f/restore_button->getContentSize().height);
    
    noads_button->setPositionY(blue_field->getPositionY()+blue_field->getBoundingBox().size.height*0.5f+
                               noads_button->getBoundingBox().size.height);
    
    restore_button->setPositionY(blue_field->getPositionY()+blue_field->getBoundingBox().size.height*0.5f+
                               restore_button->getBoundingBox().size.height);
    
    if (gdpr_button->isVisible() == false) {
        restore_button->setPositionY(gdpr_button->getPositionY());
        noads_button->setPositionY(gdpr_button->getPositionY());
    }
    
    Game::align_x_side_by_side(noads_button, restore_button, getContainer()->getContentSize().width*0.05f);
    
    refresh_noads_buttons();
    
}

void SettingsLayer::refresh_noads_buttons(){
    
    if (noads_button) {
        
        bool purchased_no_ads = IAPConfig::didPurchase_disable_ads();
        
        if (purchased_no_ads) {
            noads_button->getContentSprite()->setTexture("no_ads/removed.png");
        }
        else{
            noads_button->getContentSprite()->setTexture("no_ads/remove.png");
        }
        
    }
    
}

// SPCollectionViewDelegate

float SettingsLayer::getSeperatorAfter(SPCollectionView *collectionView,int section) {
    return 0;
}

float SettingsLayer::getSeperatorBefore              (SPCollectionView *collectionView,int section){
    return 0;
}

void SettingsLayer::didSelectCell                  (SPCollectionView *collectionView,SPCollectionViewCell *cell){
    
    SettingsCell * settings_cell = (SettingsCell *)cell;
    settings_type t              = settings_cell->getType();
    
    if (_delegate) {
        _delegate->settings_did_change(t);
    }
    
   // Settings::setStateOn(t, !Settings::getStateOn(t));

    if (t == settings_vibration) {
        if (Settings::getStateOn(settings_vibration)) {
            PlatformManager::vibrate(2);
        }
    }
    
    SoundDirector::playSound(gSound_button_click);
    
    settings_cell->changeState(true);
    //settings_cell->updateContent();
    
}

int SettingsLayer::getNumberOfSections             (SPCollectionView *colectionView){
    return 1;
}

int SettingsLayer::getNumberOfItems                (SPCollectionView *colectionView,int section){
    return (int)Settings::getItems().size();
}

Size SettingsLayer::getCellSize                    (SPCollectionView *colectionView,int section,int item){
    Size s = Size(colectionView->getContentSize().width, getContainer()->getContentSize().height * 0.075f);
    return s;
}

SPCollectionViewCell * SettingsLayer::getCellItem                     (SPCollectionView *colectionView,int section,int item){
    
    SettingsCell *cell = (SettingsCell *)colectionView->dequeCellItem(section, item);
    
    if (!cell) {
        cell = SettingsCell::create();
        colectionView->addCell(cell, section, item);
    }
    
    cell->setType(Settings::getItems().at(item));
    
    cell->setForceDisableScaleOnTouch(true);
    
    return cell;
}



