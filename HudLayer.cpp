//
//  HudLayer.cpp
//  FruitsKnife-mobile
//
//  Created by Slavik on 5/15/18.
//

#include "HudLayer.h"
#include "Game.h"
#include "SoundDirector.h"
#include "Settings.h"

bool HudLayer::init(){
    if (!GameLayer::init()){
        return false;
    }
    
    _score_label = Label::createWithTTF(StringUtils::format("0"), "fonts/Blogger_Sans-Bold.otf", getContainer()->getContentSize().height * 0.055f);
    _score_label->setPosition(getContentSize().width * 0.5f - getContainer()->getContentSize().width * 0.36f,
                              getHeaderUIDefaultPosY() - getContainer()->getContentSize().height * 0.01f);
    _score_label->setColor(Color3B(111, 157, 158));
    //_score_label->setAnchorPoint(Point(0.0f, 0.5f));
    addChild(_score_label);
    
    
    _lifes_label = Label::createWithTTF(StringUtils::format(""), "fonts/Blogger_Sans-Bold.otf", getContentSize().height * 0.035f);
    _lifes_label->setPosition(getContentSize().width*0.1f,getContentSize().height*0.4f);
    _lifes_label->setColor(Color3B::BLACK);
    _lifes_label->setAnchorPoint(Vec2(0.f, 0.5f));
    addChild(_lifes_label);
    
    _level_bar = LevelBar::create();
    _level_bar->setScale(getContainer()->getContentSize().width * 0.4f / _level_bar->getContentSize().width);
    _level_bar->setPosition(Point(getContentSize().width * 0.5f, getHeaderUIDefaultPosY()));
    addChild(_level_bar);
    
    
    
    settings_button = SPButton::createWithImage("menu/settings.png");
    settings_button->setScale(getContainer()->getContentSize().width * 0.07f / settings_button->getContentSize().width);
    addChild(settings_button);
    settings_button->setPosition(getContentSize().width * 0.5f - getContainer()->getContentSize().width * 0.395f, getHeaderUIDefaultPosY() - getContainer()->getContentSize().height * 0.002f);
    settings_button->setTouchAreaScale(1.5f);
    settings_button->setVisible(false);
    
    darkmode_button = SPButton::createWithImage("dark_mode/icon1.png");
    darkmode_button->setScale(getContainer()->getContentSize().width * 0.1f / darkmode_button->getContentSize().width);
    addChild(darkmode_button);
    darkmode_button->setPosition(getContentSize().width * 0.5f - getContainer()->getContentSize().width * 0.28f, getHeaderUIDefaultPosY() + getContainer()->getContentSize().height * 0.003f);
    darkmode_button->setTouchAreaScale(1.5f);
    darkmode_button->soundNameOntouchEnd = "";
    darkmode_button->setVisible(false);
    
    _coctails_objective = CoctailObjectiveUI::create();
    addChild(_coctails_objective);
    _coctails_objective->prepare(getContainer()->getContentSize().height*0.05f);
    _coctails_objective->setPosition(Vec2(getContentSize().width*0.5f,
                                          _level_bar->getPositionY()-
                                          _level_bar->getBoundingBox().size.height*0.5f-
                                          _coctails_objective->getContentSize().height*0.75f));
    
    int collected = Game::getCoctailsCollected();
    int objective = Game::getCoctailsCollectObjective();
    
    _coctails_objective->setText(StringUtils::format("%i/%i",collected,objective).c_str());
    
    scheduleUpdate();
    
    refrsh_dark_mode_button();
    
    return true;
}

void HudLayer::animate_menu_start(){
    
    //_wave_field->setVisible(false);
    _score_label->setVisible(false);
    
}

void HudLayer::refrsh_dark_mode_button(){
    
    bool dark_mode_on = Settings::getStateOn(settings_darkmode);
    if (dark_mode_on == true) {
        darkmode_button->getContentSprite()->setTexture("dark_mode/icon2.png");
    }
    else{
        darkmode_button->getContentSprite()->setTexture("dark_mode/icon1.png");
    }
    
    if (_level_bar) {
        _level_bar->refresh_color();
    }
    
}

void HudLayer::refresh_coins(int custom_value, bool animated){
    
    int coins = 0;
    
    if (custom_value > 0) {
        coins = custom_value;
    }
    else{
        coins = Game::getCoins();
    }
    
    _coins->setCoins(coins, animated);
    float offset = getContainer()->getContentSize().width*0.05f;
    _coins->setPositionX((getContentSize().width * 0.5f + getContainer()->getContentSize().width * 0.5f - offset) - _coins->getContentSize().width*0.5f);
}

void HudLayer::refresh_gems (int custom_value, bool animated){
    
    int coins = 0;
    
    if (custom_value > 0) {
        coins = custom_value;
    }
    else{
        coins = Game::getGems();
    }
    
    _gems->setCoins(coins, animated);
    float offset = getContainer()->getContentSize().width*0.05f;
    _gems->setPositionX((getContentSize().width * 0.5f + getContainer()->getContentSize().width * 0.5f - offset) - _gems->getContentSize().width*0.55f);
    
}

void HudLayer::set_knifes_count(int count){
    return;
    
    for (int i = 0; i < _all_knifes.size(); i++) {
        Sprite * knife = _all_knifes.at(i);
        knife->setColor(Color3B::BLACK);
    }
    
    
    int val = count - 1;
    
    for (int i = 0; i < _all_knifes.size(); i++) {
        Sprite * knife = _all_knifes.at(i);
        if (i <= val) {
            knife->setColor(Color3B::WHITE);
        }
    }
}

void HudLayer::set_wave(int wave){
   // if (_wave_label) {
   //     _wave_label->setString(StringUtils::format("WAVE %i",wave));
   // }
}



void HudLayer::set_level_percents(float percents){
    if (_level_bar) {
        _level_bar->setPercentage(percents, true, nullptr);
    }
}

void HudLayer::animate_onGameStart(){
    
    if (_coctails_objective) {
        Game::getInstance()->runRecursiveAction(_coctails_objective, FadeOut::create(0.15f));
    }
    
}

void HudLayer::animate_onGameEnd(){

    std::vector<Node*>nodes_to_fade;
    nodes_to_fade.push_back(_score_label);
  //  nodes_to_fade.push_back(_wave_field);
  //  nodes_to_fade.push_back(_wave_label);
    
    for (Node * node : nodes_to_fade) {
        node->runAction(FadeTo::create(0.15f, 0));
    }
    
    if (_level_bar) {
        auto fade = FadeTo::create(0.15f, 0);
        
        _level_bar->runAction(fade);
        _level_bar->_progress->runAction(fade->clone());
        _level_bar->_level_label->runAction(fade->clone());
    }
    
//    if (_stars_field) {
//        _stars_field->hide();
//    }
}

bool HudLayer::onTouchBegan(Touch *touch, Event *event){
    return false;
}
