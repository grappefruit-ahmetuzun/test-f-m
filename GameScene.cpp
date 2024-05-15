//
//  GameScene.cpp
//  hiball
//
//  Created by Marek on 10/15/16.
//
//

#include "GameScene.h"
#include "SoundDirector.h"
#include "Space.h"
#include "PlatformManager.h"
#include "SPWorldTime.h"
#include "LevelManager.h"
#include "CoctailsObjectiveLarge.h"
#include "ShopManager.h"
#include "SocialButtons.h"
#include "LoadingLayer.h"

USING_NS_CC;

Scene * GameScene::createScene(){
    
    auto scene = Scene::create();
    GameScene * layer = GameScene::create();
    layer->setTag(GAMESCENE_TAG);
    
    AdManager::getInstance()->      setDelegate(layer);
    IAPManager::getInstance()->     setDelegate(layer);
    
    scene->addChild(layer);
    
    //layer->game_prepare();
    
    return scene;
}

bool GameScene::init() {
    if (GameLayer::init()) {
        
        if (DEBUG_UNLOCK_COINS == 1) {
            Game::addCoins(2000);
        }
        
        if (DEBUG_UNLOCK_GEMS == 1) {
            Game::addGems(2000);
        }
        
        if (DEBUG_UNLOCK_ITEMS == 1) {
            std::vector<SHOP_ITEM> all_weapons = Shop::get_knives();
            
            for (int i = 0; i < all_weapons.size(); i++) {
                SHOP_ITEM item = all_weapons.at(i);
                ShopManager::getInstance()->set_item_purchase(item);
            }
        }
        
        if (DEBUG_FORTUNE_WHEEL == 1){
            Patterns::getInstance()->generate_new_coctails();
            Game::setCoctailsCollected(4);
        }
        
        //std::vector<objetive_recipe_info> fortune_wheel_objects = Recipes::get_objective_recipes();
        //Patterns::getInstance()->generate_new_coctails();
        
        /*
        for (int x=0; x < 1000; x++) {
            
            //   log("");
            Patterns::getInstance()->generate_new_coctails();
            std::vector<objetive_recipe_info> fortune_wheel_objects = Recipes::get_objective_recipes();
            
            std::string categories = "";
            
            for (objetive_recipe_info info : fortune_wheel_objects) {
                if (info.recipe_category == RECIPE_CATEGORY_GEM) {
                    int value = info.gems_give;
                    if (value <=0) {
                        log("COINS ARE 0!!!!!!");
                    }
                }
            }
            
        }
        */
        
        if (DEBUG_COCKTAILS_GENERATE == 1){
            
            std::string winner_1 = "";
            std::string winner_2 = "";
            
            for (int x=0; x < 100; x++) {
                
             //   log("");
                Patterns::getInstance()->generate_new_coctails();
                std::vector<objetive_recipe_info> fortune_wheel_objects = Recipes::get_objective_recipes();
                
                std::string categories = "";
                
                for (objetive_recipe_info info : fortune_wheel_objects) {
                    
                    std::string category = "";
                    
                    switch (info.recipe_category) {
                            
                        case RECIPE_CATEGORY_COIN:   category = "1";   break;
                        case RECIPE_CATEGORY_GEM:    category = "2";   break;
                        case RECIPE_CATEGORY_KNIFE:  category = "3";   break;
                            
                        default:
                            break;
                    }
                    
                    if (info.is_winner_1){
                        winner_1 = StringUtils::format("%s",category.c_str());
                    }
                    
                    if (info.is_winner_2){
                        winner_2 = StringUtils::format("%s",category.c_str());
                    }
                    
                    categories = StringUtils::format("%s %s",categories.c_str(),category.c_str());
                    
                }
                
                log("%s WIN: %s %s",categories.c_str(),winner_1.c_str(),winner_2.c_str());
                
            }
            
        }
        
        std::string bg_name = "background.png";
        
        _background = Sprite::create(bg_name.c_str());
        _background->setPosition(getContentSize()/2);
        _background->setScale(getContentSize().height / _background->getContentSize().height);
        
        if (_background->getBoundingBox().size.width < getContentSize().width) {
            _background->setScaleX(getContentSize().width / _background->getContentSize().width);
        }
        
        addChild(_background);
        
        if (Game::getInstance()->getDidShowLoading() == false) {
            Game::getInstance()->setDidShowLoading(true);
            LoadingLayer *l = LoadingLayer::create();
            addChild(l, 99999);
            auto delay  = DelayTime::create(2.5f);
            auto call_finish = CallFunc::create([this]{
                this->game_prepare();
            });
            auto remove = RemoveSelf::create();
            auto seq    = Sequence::create(delay,call_finish,remove, NULL);
            l->runAction(seq);
        }
        else{
            game_prepare();
        }
        
        scheduleUpdate();
        
        this->setKeyboardEnabled(true);
        
        return true;
    }
    return false;
}

void GameScene::game_prepare(){
    
    _slowmo_sprite = Sprite::create("knife_effect/vignette.png");
    addChild(_slowmo_sprite);
    _slowmo_sprite->setPosition(getContentSize()/2);
    _slowmo_sprite->setScale(getContentSize().height / _slowmo_sprite->getContentSize().height);
    _slowmo_sprite->setOpacity(0);
    
    if (_slowmo_sprite->getBoundingBox().size.width < getContentSize().width) {
        _slowmo_sprite->setScaleX(getContentSize().width / _slowmo_sprite->getContentSize().width);
    }
    
    if (SPPHYSICS_DEBUG == 1){
        _background->setVisible(false);
        _slowmo_sprite->setVisible(false);
    }
    
    _hud_layer = HudLayer::create();
    addChild(_hud_layer, 9999);
    _hud_layer->darkmode_button->setVoidTouchDownCallback(CC_CALLBACK_0(GameScene::didSelect_menu_darkmode, this));
    _hud_layer->settings_button->setVoidTouchDownCallback(CC_CALLBACK_0(GameScene::didSelect_menu_settings, this));
    
    float offset = getContentSize().width*0.05f;
    
    _coins = CoinsAmmountSprite::createWithHeight(getContentSize().height * 0.04f);
    addChild(_coins, 20000);
    _coins->setAnchorPoint(Vec2(0.5f, 0.5f));
    _coins->setPosition((getContentSize().width * 0.5f + getContainer()->getContentSize().width - offset) - _coins->getContentSize().width * 0.5f, getHeaderUIDefaultPosY());
    _coins->setTouchAreaScale(1.25f);
    _coins->setLabelOnRight(false);
    _coins->getCoinsLabel()->setColor(Color3B(111, 157, 158));
    _coins->setActive(false);
    //_coins->setVoidTouchDownCallback(   CC_CALLBACK_0(GameScene::didSelect_menu_purchases, this));
    _hud_layer->_coins = _coins;
    _hud_layer->refresh_coins(0, false);
    
    _coins->getCoinSprite()->setTexture("settings/small_coin.png");
    _coins->getCoinSprite()->setScale((_coins->getCoinHeight() * 0.75f) / _coins->getCoinSprite()->getContentSize().height);
    //
    
    
    _gems = CoinsAmmountSprite::createWithHeight(getContentSize().height * 0.04f);
    addChild(_gems, 20000);
    _gems->setAnchorPoint(Vec2(0.5f, 0.5f));
    _gems->setPosition((getContentSize().width * 0.5f + getContainer()->getContentSize().width - offset) - _gems->getContentSize().width * 0.5f,
                       getHeaderUIDefaultPosY() - _coins->getContentSize().height*1.0f);
    _gems->setTouchAreaScale(1.25f);
    _gems->setLabelOnRight(false);
    _gems->getCoinsLabel()->setColor(Color3B(111, 157, 158));
    _gems->setActive(false);
    _hud_layer->_gems = _gems;
    _hud_layer->refresh_gems(0, false);
    
    _gems->getCoinSprite()->setTexture("hud/blue_gem.png");
    _gems->getCoinSprite()->setScale((_gems->getCoinHeight() * 0.75f) / _gems->getCoinSprite()->getContentSize().height);
    
    //
    
    _game_b2d_layer = Gameplayb2d::create();
    _game_b2d_layer->_hud = _hud_layer;
    addChild(_game_b2d_layer);
    _game_b2d_layer->setDelegate(this);
    _game_b2d_layer->gameplay_prepare();
    
    _hud_layer->set_level_percents(0);
    
    _left_border = Sprite::create();
    _left_border->setTextureRect(Rect(0, 0, (getContentSize().width-(getContainer()->getContentSize().width))/2, getContentSize().height*2));
    _left_border->setPosition(Point(_left_border->getContentSize().width*0.5f, getContentSize().height*0.5f));
    _left_border->setColor(Color3B::BLACK);
    addChild(_left_border, 999);
    
    _right_border = Sprite::create();
    _right_border->setTextureRect(Rect(0, 0, (getContentSize().width-(getContainer()->getContentSize().width))/2, getContentSize().height*2));
    _right_border->setPosition(Point(getContentSize().width - (_right_border->getContentSize().width*0.5f), getContentSize().height*0.5f));
    _right_border->setColor(Color3B::BLACK);
    addChild(_right_border, 999);
    
    if (PlatformManager::isKetchappSquareShows()) {
        PlatformManager::hideKetchappSquare();
    }
    
    _game_b2d_layer->setScore(Game::getInstance()->getGameScoreOnGameOver());
    
    gameplay_score_didchange(_game_b2d_layer->getScore());
    
    Game::getInstance()->setGameScoreOnGameOver(0);
    
    if (Game::getInstance()->getDidSeeMenu() == false){
        Game::getInstance()->setDidSeeMenu(true);
        
        _menu_layer = MenuLayer::create();
        addChild(_menu_layer);
        _menu_layer->prepare();
        _menu_layer->customzie_button->setVoidTouchDownCallback(CC_CALLBACK_0(GameScene::didSelect_menu_customize, this));
        
        _hud_layer->animate_menu_start();
        _menu_layer->animate_menu_start();
        
        _hud_layer->darkmode_button->setVisible(true);
        _hud_layer->settings_button->setVisible(true);
        
    }
    else{

        _hud_layer->_coctails_objective->setVisible(false);
        _game_b2d_layer->gameplay_start();
        //_hud_layer->_wave_field->setVisible(true);
        _hud_layer->_score_label->setVisible(true);
        
    }
    
    if (PlatformManager::isKetchappSquareShows()) {
        PlatformManager::hideKetchappSquare();
    }

//    auto delay = DelayTime::create(2.0f);
//    auto callf = CallFunc::create([this]{
//        gameplay_level_complete();
//    });
//    auto seq = Sequence::create(delay, callf, NULL);
//    runAction(seq);
    
    game_refresh_dark_mode();
    
}

#pragma mark
#pragma mark Android Back

void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
    
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE) {
        
        if (_shop_layer) {
            didSelect_back_shop();
        }
        else if (_settings_layer){
            didSelect_back_settings();
        }
        else if (_game_b2d_layer){
            if (_game_b2d_layer->getGameStarted()) {
                if (_exit) {
                    didSelect_exit_layer_no();
                }
                else{
                    showExitToMenuLayer();
                }
            }
            else{
                if (_exit) {
                    didSelect_exit_layer_no();
                }
                else{
                    showQuitTheGameLayer();
                }
            }
        }
        
    }
    
}

#pragma mark
#pragma mark Android Exit

void GameScene::showExitToMenuLayer(){
    if (_exit) {
        return;
    }
    
    if (!_exit) {
        _exit = ExitLayer::create();
        _exit->prepare("EXIT TO MENU?");
        addChild(_exit,9999);
    }
    
    _exit->_noButton->  setVoidTouchDownCallback(CC_CALLBACK_0(GameScene::didSelect_exit_layer_no,     this));
    _exit->_yesButton-> setVoidTouchDownCallback(CC_CALLBACK_0(GameScene::didSelect_exit_to_main_menu, this));
}

void GameScene::showQuitTheGameLayer(){
    
    if (_exit) {
        return;
    }
    
    if (!_exit) {
        _exit = ExitLayer::create();
        _exit->prepare("QUIT THE GAME?");
        addChild(_exit,9999);
    }
    
    _exit->_noButton->  setVoidTouchDownCallback(CC_CALLBACK_0(GameScene::didSelect_exit_layer_no, this));
    _exit->_yesButton-> setVoidTouchDownCallback(CC_CALLBACK_0(GameScene::didSelect_quit_the_game, this));
}

void GameScene::didSelect_exit_layer_no(){
    if (_exit) {
        _exit->removeFromParentAndCleanup(true);
        _exit = nullptr;
    }
}

void GameScene::didSelect_exit_to_main_menu(){
    didSelect_gameover_home();
}

void GameScene::didSelect_quit_the_game(){
    Director::getInstance()->end();
}

void GameScene::game_refresh_dark_mode(){
    if (_hud_layer) {
        _hud_layer->refrsh_dark_mode_button();
    }
    
    if (_menu_layer) {
        _menu_layer->refrsh_dark_mode_button();
    }
    
    
    if (_game_b2d_layer) {
        _game_b2d_layer->refresh_dark_mode();
    }
    
    bool dark_mode_on = Settings::getStateOn(settings_darkmode);
    
    if (dark_mode_on == true) {
        _background->setTexture("background_1.png");
        
        _left_border->setColor(Color3B(7,32,44));
        _right_border->setColor(Color3B(7,32,44));
    }
    else{
        _background->setTexture("background.png");
        
        _left_border->setColor(Color3B(117, 145, 157));
        _right_border->setColor(Color3B(117, 145, 157));
    }
    
    _background->setScale(getContentSize().height / _background->getContentSize().height);
    
    if (_background->getBoundingBox().size.width < getContentSize().width) {
        _background->setScaleX(getContentSize().width / _background->getContentSize().width);
    }
    
}

void GameScene::submit_leaderboards_values(){
    
    // Sumbit score
    
    bool is_signedin = false;
    
    if (Game::is_iOS()) {
        if (sdkbox::PluginSdkboxPlay::isSignedIn() == true) {
            is_signedin = true;
        }
    }
    
    if (Game::is_Android()) {
        if (Game::is_gplay_connected() == true) {
            is_signedin = true;
        }
    }
    
    if (is_signedin) {
        
        int best_score = Game::getScore();
        int level      = LevelManager::getInstance()->get_level_number();
        
        sdkbox::PluginSdkboxPlay::submitScore("highscore", best_score);
        sdkbox::PluginSdkboxPlay::submitScore("level",     level);
        
    }
    
}

#pragma mark
#pragma mark Shop

void GameScene::didSelectWeapon(){
    _game_b2d_layer->refresh_weapon();
}

void GameScene::didSelect_shop_video(){
    
    if (AdManager::getInstance()->is_available_VideoAd()){
        AdManager::getInstance()->show_VideoAd(WATCH_VIDEO_TYPE_SHOP_COINS);
    }

}

void GameScene::refresh_coins(){
    _hud_layer->refresh_gems(0);
    _hud_layer->refresh_coins(0);
}

void GameScene::didDoubleSelect(){
    
    didSelectWeapon();
    didSelect_back_shop();
    
}

#pragma mark
#pragma mark Settings

void GameScene::give_coins_from_settings(int coins, float after_delay,Vec2 from_position){
    
    auto d = DelayTime::create(after_delay);
    auto call = CallFunc::create([this,from_position,coins]{
        
        SoundDirector::playSound("ev_reward");
        Game::addCoins(coins);
        
        auto seq = Sequence::create(DelayTime::create(0.9f),CallFunc::create([this]{
            this->_hud_layer->refresh_coins(0,true);
        }), NULL);
        runAction(seq);
        
        for (int x=0; x< coins; x++) {
            gameplay_coins_fly(from_position, FLYING_OBJECT_TYPE_COIN,nullptr);
        }
        
    });
    auto seq = Sequence::create(d,call, NULL);
    runAction(seq);
    
}

void GameScene::didSelect_settings_privacy(){
    PlatformManager::openGDRP_window();
}

void GameScene::didSelect_settings_remove_ads(){
    
    if (IAPConfig::didPurchase_disable_ads() == false) {
        
        if (PlatformManager::isInternetConnection() == false) {
            MessageBox(NO_INTERNET_INFO, NO_INTERNET_TITLE);
            return;
        }
        
        open_inapp_loading_layer(LOADING_TYPE_PURCHASE);
        
        std::string purchase_id = IAPConfig::getStarPurchasesIAPKey(purchase_id_remove_ads);
        sdkbox::IAP::purchase(purchase_id.c_str());
    }
    
}

void GameScene::didSelect_settings_restore_purchases(){
    
    if (PlatformManager::isInternetConnection() == false) {
        MessageBox(NO_INTERNET_INFO, NO_INTERNET_TITLE);
        return;
    }
    
    sdkbox::IAP::restore();
    open_inapp_loading_layer(LOADING_TYPE_PURCHASE);
    
}

#pragma mark
#pragma mark Shop


#pragma mark
#pragma mark Back

void GameScene::didSelect_back_shop(){
    if (_shop_layer) {
        _shop_layer->removeFromParentAndCleanup(true);
        _shop_layer = nullptr;
    }
}

void GameScene::didSelect_back_settings(){
    if (_settings_layer) {
        _settings_layer->removeFromParentAndCleanup(true);
        _settings_layer = nullptr;
    }
}

void GameScene::didSelect_back_fortune_weapon_unlock(){
    if (_weapon_unlock_popup) {
        _weapon_unlock_popup->removeFromParentAndCleanup(true);
        _weapon_unlock_popup = nullptr;
    }
}

#pragma mark
#pragma mark WeaponUnlockPopup

void GameScene::didSelect_equp(){
    
    SHOP_ITEM item = _weapon_unlock_popup->_item;
    
    ShopManager::getInstance()->set_item_selected(item);
    
    didSelect_back_fortune_weapon_unlock();
    
}

#pragma mark
#pragma mark Menu

void GameScene::didSelect_menu_darkmode(){
    Settings::setStateOn(settings_darkmode, !Settings::getStateOn(settings_darkmode));
    game_refresh_dark_mode();
}

void GameScene::didSelect_menu_settings(){
    
    if (PlatformManager::isKetchappSquareShows()) {
        PlatformManager::hideKetchappSquare();
    }
    
    if (!_settings_layer) {
        _settings_layer = SettingsLayer::create();
        _settings_layer->_coins_give_callback =                                     CC_CALLBACK_3(GameScene::give_coins_from_settings,                      this);
        _settings_layer->animateOnEnter(true);
        _settings_layer->setDelegate(this);
        addChild(_settings_layer, 10000);
        _settings_layer->getBackButton()->setVoidTouchDownCallback(                 CC_CALLBACK_0(GameScene::didSelect_back_settings,                       this));
        _settings_layer->gdpr_button->setVoidTouchDownCallback(                     CC_CALLBACK_0(GameScene::didSelect_settings_privacy,                    this));
        _settings_layer->noads_button->setVoidTouchDownCallback(                    CC_CALLBACK_0(GameScene::didSelect_settings_remove_ads,                 this));
        _settings_layer->restore_button->setVoidTouchDownCallback(                  CC_CALLBACK_0(GameScene::didSelect_settings_restore_purchases,          this));
        
    }
    
    if (PlatformManager::isKetchappSquareShows()) {
        PlatformManager::hideKetchappSquare();
    }
    
}

void GameScene::didSelect_menu_customize(){
    
    if (!_shop_layer) {
        _shop_layer = ShopLayer::create();
        addChild(_shop_layer, 10000);
        _shop_layer->getBackButton()->setVoidTouchDownCallback(CC_CALLBACK_0(GameScene::didSelect_back_shop, this));
        _shop_layer->_video_button_callback = CC_CALLBACK_0(GameScene::didSelect_shop_video, this);
        _shop_layer->_refresh_weapon_callback = CC_CALLBACK_0(GameScene::didSelectWeapon, this);
        _shop_layer->_refresh_coins = CC_CALLBACK_0(GameScene::refresh_coins, this);
        _shop_layer->_double_selected_item = CC_CALLBACK_0(GameScene::didDoubleSelect, this);
    }
    
    if (PlatformManager::isKetchappSquareShows()) {
        PlatformManager::hideKetchappSquare();
    }
    
}


#pragma mark
#pragma Fortune Wheel

void GameScene::didCollect_fortune_wheel_reward(objetive_recipe_info info,Vec2 position){
    
     if (info.recipe_category == RECIPE_CATEGORY_KNIFE){
         
         SoundDirector::playSound("fortunewheel/ev_fortune_reward_weapon");
         
         auto seq = Sequence::create(DelayTime::create(0.5f),CallFunc::create([this,info]{

             SHOP_ITEM item = (SHOP_ITEM)info.knife_id;
             ShopManager::getInstance()->set_item_purchase(item);
             
             if (!_weapon_unlock_popup) {
                 _weapon_unlock_popup = WeaponUnlockPopup::create();
                 addChild(_weapon_unlock_popup, 9999999);
                 _weapon_unlock_popup->prepare(item);
                 _weapon_unlock_popup->close_button->setVoidTouchDownCallback(CC_CALLBACK_0(GameScene::didSelect_back_fortune_weapon_unlock, this));
                 _weapon_unlock_popup->equip_button->setVoidTouchDownCallback(CC_CALLBACK_0(GameScene::didSelect_equp, this));
             }
             
         }), NULL);
         runAction(seq);
         
        return;
    }
    
    if (info.recipe_category == RECIPE_CATEGORY_COIN){
        
        SoundDirector::playSound("fortunewheel/ev_fortune_reward_coins");
        
        Game::addCoins(info.coins_give);
        
        auto seq = Sequence::create(DelayTime::create(0.9f),CallFunc::create([this]{
            this->_hud_layer->refresh_coins(0,true);
        }), NULL);
        runAction(seq);
        
        int give = info.coins_give;
        if (give > 25) {
            give = 25;
        }
        
        for (int x=0; x< give; x++) {
            gameplay_coins_fly(position, FLYING_OBJECT_TYPE_COIN,nullptr);
        }
        
    }
    else if (info.recipe_category == RECIPE_CATEGORY_GEM){
        
        SoundDirector::playSound("fortunewheel/ev_fortune_reward_gems");
        
        Game::addGems(info.gems_give);
        
        auto seq = Sequence::create(DelayTime::create(0.9f),CallFunc::create([this]{
            this->_hud_layer->refresh_gems(0,true);
        }), NULL);
        runAction(seq);
        
        for (int x=0; x< info.gems_give; x++) {
            gameplay_coins_fly(position, FLYING_OBJECT_TYPE_GEM,nullptr);
        }
        
    }
    
}

#pragma mark
#pragma mark Continue

void GameScene::game_show_continue(){
    
    if (!_continue_layer) {
        _continue_layer = ContinueLayer::create();
        addChild(_continue_layer, 99999);
        _continue_layer->prepare();
        _continue_layer->_continue_button->setVoidTouchDownCallback(CC_CALLBACK_0(GameScene::didSelect_continue_continue,       this));
        _continue_layer->_nothanks_button->setVoidTouchDownCallback([this]{
            didSelect_continue_nothanks();
        });
        _continue_layer->_animation_did_finish_callback =           CC_CALLBACK_0(GameScene::didSelect_continue_timefinished,   this);
    }
    
}

void GameScene::didSelect_continue_continue(){
    
    if (AdManager::getInstance()->is_available_VideoAd()) {
        
        if (_continue_layer) {
            _continue_layer->stop_sound();
        }
        
        
        AdManager::getInstance()->show_VideoAd(WATCH_VIDEO_TYPE_CONTINUE_GAMEPLAY);
    }
    
}

void GameScene::didSelect_continue_nothanks(bool from_video_skip){
    
    if (_continue_layer) {
        _continue_layer->stop_sound();
        _continue_layer->removeFromParentAndCleanup(true);
        _continue_layer = nullptr;
    }
    
    gameplay_gameover(from_video_skip);
}

void GameScene::didSelect_continue_timefinished(){
    didSelect_continue_nothanks();
}

#pragma mark
#pragma mark Game Over

void GameScene::didSelect_gameover_restart(){
    Director::getInstance()->replaceScene(TransitionFade::create(0.3f, GameScene::createScene(), Color3B::BLACK));
}

void GameScene::didSelect_gameover_home(){
    Game::getInstance()->setDidSeeMenu(false);
    Director::getInstance()->replaceScene(TransitionFade::create(0.3f, GameScene::createScene(), Color3B::BLACK));
}

void GameScene::didSelect_gameover_leaderboards(){
    
    if (Game::is_iOS()) {
        if (sdkbox::PluginSdkboxPlay::isSignedIn() == false) {
            sdkbox::PluginSdkboxPlay::signin();
            return;
        }
    }
    
    if (Game::is_Android()) {
        if (Game::is_gplay_connected() == false) {
            sdkbox::PluginSdkboxPlay::signin();
            return;
        }
    }
    
    sdkbox::PluginSdkboxPlay::showAllLeaderboards();
}

void GameScene::didSelect_gameover_customize(){
    didSelect_menu_customize();
}

void GameScene::didSelect_gameover_coins_video(){
    if (AdManager::getInstance()->is_available_VideoAd()) {
        AdManager::getInstance()->show_VideoAd(WATCH_VIDEO_TYPE_GAMEOVER_COINS);
    }
}

void GameScene::didSelect_gameover_gems_video(){
    if (AdManager::getInstance()->is_available_VideoAd()) {
        AdManager::getInstance()->show_VideoAd(WATCH_VIDEO_TYPE_GAMEOVER_GEMS);
    }
}

void GameScene::didSelect_gameover_no_ads(){
    
    didSelect_settings_remove_ads();

}


#pragma mark
#pragma mark GameplayDeletate

void GameScene::gameplay_score_didchange(int score){
    
    _hud_layer->_score_label->setString(StringUtils::format("%i", score).c_str());
    
}

void GameScene::gameplay_gameover(float delay){
    
    if (delay > 0) {
        
        auto d = DelayTime::create(delay);
        auto c = CallFunc::create([this]{
            this->gameplay_gameover(0);
        });
        auto s =Sequence::create(d,c, NULL);
        runAction(s);
        
        return;
    }
    
    if (_gameover_layer != nullptr) {
        return;
    }
    
    bool video_is_available = AdManager::getInstance()->is_available_VideoAd();
    
    int wave_count = Game::getInstance()->getWave_count_for_continue();
    
    if (_game_b2d_layer->_continue_showed == false && video_is_available == true && wave_count > 2) {
        _game_b2d_layer->_continue_showed = true;
        
        
        game_show_continue();

        return;
    }
    
    int increase_gameover = 1;
    Game::getInstance()->setGameover_count_for_ketchapp_square(Game::getInstance()->getGameover_count_for_ketchapp_square() + increase_gameover);
    
    Game::getInstance()->setWave_count_for_continue(0);
    
    int wave        = _game_b2d_layer->getWave();
    wave-=1;
    int loose_count = Game::getLooseCount(wave);
    Game::setLooseCount(loose_count+1, wave);
 
    _hud_layer->animate_onGameEnd();
    
    int score_now  = _game_b2d_layer->getScore();
    int best_score = Game::getScore();
    
    GameOverInfo info;
    info.score              = score_now;
    info.wave               = _game_b2d_layer->getWave();
    info.level              = LevelManager::get_level_number();
    info.high_score         = best_score;
    
    //AdManager::getInstance()->show_BannerAd();
    
    bool interstitial_showed = this->interstitial_check_and_show();
    
    // ketchapp square
    
    if (IAPConfig::didPurchase_disable_ads() == false) {
        if (Game::getInstance()->getGameover_count_for_ketchapp_square() >= 3) {
            
            if (PlatformManager::isKetchappSquareReady()) {
                Game::getInstance()->setGameover_count_for_ketchapp_square(0);
                PlatformManager::showKetchappSquare();
            }
            
            PlatformManager::fetchKetchappSquare();
        }
        else if (Game::getInstance()->getGameover_count_for_ketchapp_square() >= 1){
            PlatformManager::fetchKetchappSquare();
        }
    }
    
    if (score_now > best_score) {
        info.is_highscore_now = true;
        Game::setScore(score_now);
    }
    
    PlatformManager::gameplay_finished(score_now);
    
    Game::getInstance()->setGameover_count_for_game_promo(Game::getInstance()->getGameover_count_for_game_promo() - 1);

    _gameover_layer = GameOverLayer::create();
    addChild(_gameover_layer, 9999);
    _gameover_layer->animateOnEnter(info);
    _gameover_layer->restart_button->setVoidTouchDownCallback(          CC_CALLBACK_0(GameScene::didSelect_gameover_restart,            this));
    _gameover_layer->home_button->setVoidTouchDownCallback(             CC_CALLBACK_0(GameScene::didSelect_gameover_home,               this));
    _gameover_layer->customize_button->setVoidTouchDownCallback(        CC_CALLBACK_0(GameScene::didSelect_gameover_customize,          this));
    _gameover_layer->no_ads_button->setVoidTouchDownCallback(           CC_CALLBACK_0(GameScene::didSelect_gameover_no_ads,             this));
    _gameover_layer->leaderboards_button->setVoidTouchDownCallback(     CC_CALLBACK_0(GameScene::didSelect_gameover_leaderboards,       this));
    _gameover_layer->coins_video_button->setVoidTouchDownCallback(      CC_CALLBACK_0(GameScene::didSelect_gameover_coins_video,        this));
    _gameover_layer->gems_video_button->setVoidTouchDownCallback(       CC_CALLBACK_0(GameScene::didSelect_gameover_gems_video,         this));
    
    _gameover_layer->coins_video_button->setVisible(false);
    _gameover_layer->gems_video_button->setVisible(false);
    _gameover_layer->no_ads_button->setVisible(false);
    _gameover_layer->social_button->setVisible(false);
    _gameover_layer->customize_button->setVisible(false);
    _gameover_layer->game_promo_button->setVisible(false);
    
    int gameover_counter = Game::getInstance()->getGameover_count_for_game_promo();
    
    if (interstitial_showed && IAPConfig::didPurchase_disable_ads() == false) {
        _gameover_layer->no_ads_button->setVisible(true);
    }
    else{
        _gameover_layer->social_button->setVisible(true);
    }
    
    
    if (gameover_counter <= 0) {
        Game::getInstance()->setGameover_count_for_game_promo(random(15, 25));
        _gameover_layer->game_promo_button->setVisible(true);
    }
    else{
        
        if (video_is_available) {
            
            int rand = random(1, 100);
            
            if (rand <= 70) {
                
                int rand2 = random(1, 100);
                
                if (rand2 <= 75) {
                    _gameover_layer->coins_video_button->setVisible(true);
                }
                else{
                    _gameover_layer->gems_video_button->setVisible(true);
                }
            }
            else{
                _gameover_layer->customize_button->setVisible(true);
            }
        }
        else{
            _gameover_layer->customize_button->setVisible(true);
        }
    }
    
    submit_leaderboards_values();
    
}

void GameScene::gameplay_slow_motion(bool enable){
    
    float opacity = enable ? 255 : 0;
    float time    = enable ? 0.05f : 0.5f;
    
    _slowmo_sprite->stopAllActions();
    
    auto fade = FadeTo::create(time, opacity);
    _slowmo_sprite->runAction(fade);
    
}

void GameScene::gameplay_miss_star(){
    
//    float width = getContainer()->getContentSize().width * 0.05f;
//
//    for (int i = 0; i < 4; i++) {
//        Sprite * line = Sprite::create();
//        line->setColor(Color3B::RED);
//        line->setOpacity(180);
//        addChild(line, 999999);
//
//        if (i == 0) {
//            line->setTextureRect(Rect(0, 0, width, getContentSize().height));
//            line->setPosition(Point((getContentSize().width * 0.5f - getContainer()->getContentSize().width * 0.5f) + line->getBoundingBox().size.width * 0.5f, getContentSize().height * 0.5f));
//        }
//        else if (i == 1){
//            line->setTextureRect(Rect(0, 0, width, getContentSize().height));
//            line->setPosition(Point(getContentSize().width * 0.5f + getContainer()->getContentSize().width * 0.5f - line->getBoundingBox().size.width * 0.5f, getContentSize().height * 0.5f));
//        }
//        else if (i == 2){
//            line->setTextureRect(Rect(0, 0, getContainer()->getContentSize().width - (width * 2.0f), width));
//            line->setPosition(Point(getContentSize().width * 0.5f, getContentSize().height -  line->getBoundingBox().size.height * 0.5f));
//        }
//        else if (i == 3){
//            line->setTextureRect(Rect(0, 0, getContainer()->getContentSize().width - (width * 2.0f), width));
//            line->setPosition(Point(getContentSize().width * 0.5f, line->getBoundingBox().size.height * 0.5f));
//        }
//
//        auto fade   = FadeTo::create(0.3f, 0);
//        auto ease   = EaseIn::create(fade, 0.65f);
//        auto remove = RemoveSelf::create();
//        auto seq    = Sequence::create(ease, remove, NULL);
//        line->runAction(seq);
//    }
//
    
    Sprite * go = Sprite::create("go.png");
    go->setPosition(getContentSize()/2);
    go->setScale(getContainer()->getContentSize().width / go->getContentSize().width, getContentSize().height / go->getContentSize().height);
    go->setColor(Color3B::RED);
    go->setOpacity(180);
    addChild(go,999999);
    
    
    auto fade   = FadeTo::create(0.4f, 0);
    auto ease   = EaseIn::create(fade, 0.65f);
    auto remove = RemoveSelf::create();
    auto seq    = Sequence::create(ease, remove, NULL);
    go->runAction(seq);
    
    {
        Sprite * missed = Sprite::create("ui/missed.png");
        missed->setPosition(Point(getContentSize().width * 0.5f, getHeaderUIDefaultPosY() - getContainer()->getContentSize().height * 0.05f));
        missed->setScale(getContainer()->getContentSize().width * 0.25f / missed->getContentSize().width);
        addChild(missed, 999999);
        missed->setScale(0);
        
        auto scale  = ScaleTo::create(0.4f, getContainer()->getContentSize().width * 0.25f / missed->getContentSize().width);
        auto ease1  = EaseElasticOut::create(scale, 0.5f);
        auto delay  = DelayTime::create(0.2f);
        auto fade   = FadeTo::create(0.3f, 0);
        auto ease   = EaseIn::create(fade, 0.65f);
        auto remove = RemoveSelf::create();
        auto seq    = Sequence::create(ease1, delay, ease, remove, NULL);
        missed->runAction(seq);
    }

}

void GameScene::gameplay_level_complete(){
    
    SoundDirector::playSound("ev_level_complete_chimes");
    
    for (int x = 0; x < 8; x++) {
        Game::setLooseCount(0, x);
    }
    
    std::string level_string = StringUtils::format("%i",LevelManager::get_level_number());
    
    
    if (!_level_complete_layer) {
        _level_complete_layer = LevelCompleteLayer::create();
        addChild(_level_complete_layer, 999);
        _level_complete_layer->animateOnEnter(LevelManager::get_level_number()-1);
    }
    
    _level_complete_layer->_fortuneWheelLayer->_did_win_callback = CC_CALLBACK_2(GameScene::didCollect_fortune_wheel_reward, this);
    
    _hud_layer->_score_label->runAction(FadeTo::create(0.15f, 0));
    Game::getInstance()->runRecursiveAction(_hud_layer->_level_bar, FadeTo::create(0.15f, 0));
    
    Game::getInstance()->setGameScoreOnGameOver(_game_b2d_layer->getScore());
    
    Game::getInstance()->setDidSeeMenu(false);
    
    auto call_show_objective = CallFunc::create([this]{
        _level_complete_layer->animate_show_objectives();
        
        auto finished_call = CallFunc::create([this]{
            
            bool objective_completed = Game::getCoctailsCollected() >= Game::getCoctailsCollectObjective();
            
            if (objective_completed == true) {
                
                // fortune wheel
                
                Game::setCoctailsCollected(0);
                
                auto relead_scene = CallFunc::create([this]{
                    _level_complete_layer->show_claim_reward_button();
                });
                auto relead_seq = Sequence::create(DelayTime::create(0.4f),relead_scene, NULL);
                this->runAction(relead_seq);
                
            }
            else{
                
                auto relead_scene = CallFunc::create([this]{
                    _level_complete_layer->show_next_level_button();
                    _level_complete_layer->next_level_button->setVoidTouchDownCallback(CC_CALLBACK_0(GameScene::didSelect_levelcompleted_next, this));
               
                    int level = LevelManager::getInstance()->get_level_number();
                    
                    if (level > 2) {
                        Game::getInstance()->setGameover_count_for_ads(4);
                        interstitial_check_and_show();
                    }
                 
                });
                auto relead_seq = Sequence::create(DelayTime::create(0.4f),relead_scene, NULL);
                this->runAction(relead_seq);
                
            }
            
        });
        
        auto call_winner = CallFunc::create([this]{
            this->_level_complete_layer->objectives->animate_winner_cell();
            this->_level_complete_layer->objective_indicator->show_all();
        });
        
        auto seqc =Sequence::create(DelayTime::create(0.75f),
                                   call_winner,
                                   finished_call, NULL);
        runAction(seqc);
        
    });
    auto seq = Sequence::create(DelayTime::create(0.75f),call_show_objective, NULL);
    runAction(seq);
    
    int score_now  = _game_b2d_layer->getScore();
    int best_score = Game::getScore();
    if (score_now > best_score) {
        Game::setScore(score_now);
    }
    
    submit_leaderboards_values();
    
}

void GameScene::gameplay_coins_fly(Vec2 point,FLYING_OBJECT_TYPE object_type,std::function<void()> on_end){
    
    this->gameplay_collect_object_with_fly(object_type, point, 1,on_end,getContainer()->getContentSize().width * 0.07f);
    
}

#pragma mark
#pragma mark Level Completed

void GameScene::didSelect_levelcompleted_next(){
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameScene::createScene(), Color3B::BLACK));
}

#pragma mark
#pragma mark Interstitial

bool GameScene::interstitial_check_and_show(){
    
    int increase_gameover = 1;
    
    Game::getInstance()->setGameover_count_for_ads(Game::getInstance()->getGameover_count_for_ads() + increase_gameover);

    int level_number   = LevelManager::get_level_number();
    int gameover_count = Game::getInstance()->getGameover_count_for_ads();
    //int score_now      = _game_b2d_layer->getScore();
    //int wave           = _game_b2d_layer->getWave();
   
    if (gameover_count >= 3 && level_number > 1){
        
        if (AdManager::getInstance()->is_available_Interstitial()) {
            Game::getInstance()->setGameover_count_for_ads(0);
            AdManager::getInstance()->show_InterstitialAd();
        }
        
        AdManager::getInstance()->fetch_InterstitialAd();
    }
    else if (gameover_count >= 1) {
        AdManager::getInstance()->fetch_InterstitialAd();
    }
    
    return false;
}

bool GameScene::onTouchBegan(Touch *touch, Event *event){
    
    if (touch->getStartLocation().y < getContentSize().height * 0.05f ||
        touch->getStartLocation().y > getContentSize().height*0.95f) {
        return false;
    }
    
//    if (touch->getStartLocation().y >= getContentSize().height * 0.8f &&
//        touch->getStartLocation().y <= getContentSize().height*0.95f) {
//        Director::getInstance()->replaceScene(GameScene::createScene());
//        return false;
//    }
    
    if (_game_b2d_layer->getGameStarted() == false) {
        PlatformManager::gameplay_start();
        _game_b2d_layer->gameplay_start();
        _menu_layer->removeFromParentAndCleanup(true);
        _menu_layer = nullptr;
        //_hud_layer->_wave_field->setVisible(true);
        _hud_layer->animate_onGameStart();
        _hud_layer->_score_label->setVisible(true);
        _hud_layer->darkmode_button->setVisible(false);
        _hud_layer->settings_button->setVisible(false);
        return false;
    }
    
    return _game_b2d_layer->onTouchBegan(touch, event);
}

void GameScene::onTouchMoved(Touch *touch, Event *event){
    _game_b2d_layer->onTouchMoved(touch, event);
}

void GameScene::onTouchEnded(Touch *touch, Event *event){
    _game_b2d_layer->onTouchEnded(touch, event);
}

#pragma mark
#pragma mark AdManagerDelegate

void GameScene::ad_video_didchange_state(WATCH_VIDEO_TYPE type, WATCH_VIDEO_STATE state){
    if (state == WATCH_VIDEO_STATE_VIDEO_FETCHED) {
        
        if (_shop_layer) {
            _shop_layer->refresh_video_reward_button();
        }
        
    }
    else if (state == WATCH_VIDEO_STATE_COMPLETED){
        
        if (type == WATCH_VIDEO_TYPE_CONTINUE_GAMEPLAY) {
            
            auto d = DelayTime::create(0.25f);
            auto c = CallFunc::create([this]{
                
                if (_continue_layer) {
                    _continue_layer->stop_sound();
                    _continue_layer->removeFromParentAndCleanup(true);
                    _continue_layer = nullptr;
                }
                
                _game_b2d_layer->game_continue_watched();
                
            });
            runAction(Sequence::create(d,c, NULL));
            
        }
        else if (type == WATCH_VIDEO_TYPE_GAMEOVER_COINS){
            
            auto d = DelayTime::create(0.25f);
            auto c = CallFunc::create([this]{
                
                SoundDirector::playSound("ev_reward");
                Game::addCoins(k_VIDEO_REWARD_COINS_GAMEOVER);
                
                auto seq = Sequence::create(DelayTime::create(0.9f),CallFunc::create([this]{
                    this->_hud_layer->refresh_coins(0,true);
                }), NULL);
                runAction(seq);
                
                Vec2 video_button_pos = getContentSize()*0.5f;
                
                if (_gameover_layer) {
                    if (_gameover_layer->coins_video_button) {
                        video_button_pos = _gameover_layer->coins_video_button->getParent()->convertToWorldSpace(_gameover_layer->coins_video_button->getPosition());
                        _gameover_layer->coins_video_button->setVisible(false);
                    }
                }
                
                for (int x=0; x < 25; x++) {
                    gameplay_coins_fly(video_button_pos, FLYING_OBJECT_TYPE_COIN,nullptr);
                }
                
            });
            runAction(Sequence::create(d,c, NULL));
        }
        else if (type == WATCH_VIDEO_TYPE_GAMEOVER_GEMS){
            
            auto d = DelayTime::create(0.25f);
            auto c = CallFunc::create([this]{
                
                SoundDirector::playSound("ev_reward");
                Game::addGems(k_VIDEO_REWARD_GEMS_GAMEOVER);
                
                auto seq = Sequence::create(DelayTime::create(0.9f),CallFunc::create([this]{
                    this->_hud_layer->refresh_gems(0,true);
                }), NULL);
                runAction(seq);
                
                Vec2 gem_button_pos = getContentSize()*0.5f;
                
                if (_gameover_layer) {
                    if (_gameover_layer->gems_video_button) {
                        gem_button_pos = _gameover_layer->gems_video_button->getParent()->convertToWorldSpace(_gameover_layer->gems_video_button->getPosition());
                        _gameover_layer->gems_video_button->setVisible(false);
                    }
                }
                
                for (int x=0; x < 5; x++) {
                    gameplay_coins_fly(gem_button_pos, FLYING_OBJECT_TYPE_GEM,nullptr);
                }
                
            });
            runAction(Sequence::create(d,c, NULL));
        }
        else if (type == WATCH_VIDEO_TYPE_SHOP_COINS){
            
            auto d = DelayTime::create(0.25f);
            auto c = CallFunc::create([this]{
                
                SoundDirector::playSound("ev_reward");
                Game::addCoins(k_VIDEO_REWARD_SHOP);
                
                auto seq = Sequence::create(DelayTime::create(0.9f),CallFunc::create([this]{
                    this->_hud_layer->refresh_coins(0,true);
                }), NULL);
                runAction(seq);
                
                Vec2 video_button_pos = getContentSize()*0.5f;
                if (_shop_layer) {
                    if (_shop_layer->_video_button) {
                        video_button_pos = _shop_layer->_video_button->getParent()->convertToWorldSpace(_shop_layer->_video_button->getPosition());
                    }
                    
                    _shop_layer->refresh_coin_button_animation();
                }
                
                for (int x=0; x< 25; x++) {
                    gameplay_coins_fly(video_button_pos, FLYING_OBJECT_TYPE_COIN,nullptr);
                }
                
            });
            runAction(Sequence::create(d,c, NULL));
            
        }
        else if (type == WATCH_VIDEO_TYPE_REWARD_SPIN_AGAIN){
            
            auto d = DelayTime::create(0.25f);
            auto c = CallFunc::create([this]{
                
                if (_level_complete_layer) {
                    if (_level_complete_layer->_fortuneWheelLayer) {
                        _level_complete_layer->_fortuneWheelLayer->_fortune_wheel->can_spin = true;
                        _level_complete_layer->_fortuneWheelLayer->spin();
                        
                        if (_level_complete_layer->getActionByTag(2233)) {
                            _level_complete_layer->stopActionByTag(2233);
                        }
                        
                        _level_complete_layer->_fortuneWheelLayer->_nothanks_button->stopAllActions();
                        _level_complete_layer->_fortuneWheelLayer->_nothanks_button->setVisible(false);
                        _level_complete_layer->_fortuneWheelLayer->_nothanks_button->setActive(false);
                    }
                }
                
            });
            runAction(Sequence::create(d,c, NULL));
        }
        
        //AdManager::getInstance()->fetch_VideoAd();
        
    }
    else if (state == WATCH_VIDEO_STATE_FAIL_TO_COMPLETE_AD){
        
        if (type == WATCH_VIDEO_TYPE_CONTINUE_GAMEPLAY){
            auto d = DelayTime::create(0.25f);
            auto c = CallFunc::create([this]{
                
                if (_continue_layer) {
                    this->didSelect_continue_nothanks(true);
                }
                
            });
            runAction(Sequence::create(d,c, NULL));
        }
        
        //AdManager::getInstance()->fetch_VideoAd();
    }
    else if (state == WATCH_VIDEO_STATE_FAILED_FETCH){
        
        //AdManager::getInstance()->fetch_VideoAd();
    }
}

void GameScene::interstitial_didchange_state(INTERSTITIAL_STATE state){
    
    
}

#pragma mark
#pragma mark SdkboxPlayListener

void GameScene::onConnectionStatusChanged( int status ){
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    if (status == 1000) {
        Game::set_gplay_connected(true);
    }
    else{
        // Game::set_gplay_connected(false);
    }
    
#endif
    
}

void GameScene::onScoreSubmitted( const std::string& leaderboard_name, long score, bool maxScoreAllTime, bool maxScoreWeek, bool maxScoreToday ){
    
}

void GameScene::onIncrementalAchievementUnlocked( const std::string& achievement_name ){
    
}

void GameScene::onIncrementalAchievementStep( const std::string& achievement_name, double step ){
    
}

void GameScene::onAchievementUnlocked( const std::string& achievement_name, bool newlyUnlocked ) {
    
}

#pragma mark
#pragma mark SettingsDelegate

void GameScene::settings_did_change(settings_type t){
    Settings::setStateOn(t, !Settings::getStateOn(t));
}

#pragma mark Update

void GameScene::gameplay_collect_object_with_fly   (FLYING_OBJECT_TYPE _f_type, Vec2 world_pos, int coins_ammount, std::function<void()> on_end, float object_width){
    
    Point to            = Point(0, 0);
    float fly_duration  = 0;
    
    if (_f_type == FLYING_OBJECT_TYPE_COIN) {
        fly_duration = random(0.8f, 1.2f);
        to           = _hud_layer->_coins->getCoinSprite()->getParent()->convertToWorldSpace(_hud_layer->_coins->getCoinSprite()->getPosition());
        to.x        -=  _hud_layer->_coins->getCoinSprite()->getBoundingBox().size.width*0.5f;
    }
    else if (_f_type == FLYING_OBJECT_TYPE_GEM) {
        fly_duration = random(0.8f, 1.2f);
        to           = _hud_layer->_gems->getCoinSprite()->getParent()->convertToWorldSpace(_hud_layer->_gems->getCoinSprite()->getPosition());
        to.x        -=  _hud_layer->_gems->getCoinSprite()->getBoundingBox().size.width*0.5f;
    }
    
    FlyingObject * fly_object = FlyingObject::createWithType(_f_type);
    fly_object->setPosition(world_pos);
    addChild(fly_object, 9999+1);
    fly_object->prepare(false);
    fly_object->setScale(object_width / fly_object->getContentSize().width);
    
//    auto rotate = RotateBy::create(0.1f, 40);
//    auto repaet = RepeatForever::create(rotate);
//    fly_object->runAction(repaet);
    
    _flying_objects.push_back(fly_object);
    
    float point_1_x = 0;
    float point_1_y = 0;
    
    float point_2_x = 0;
    float point_2_y = 0;
    
    float dist_x = to.x - world_pos.x;
    if (dist_x < 0) {
        dist_x = 0;
    }
    
    float dist_y = to.y - world_pos.y;
    if (dist_y < 0) {
        dist_y = 0;
    }
    
  //  if (_f_type == FLYING_OBJECT_TYPE_COIN) {
        
        {
            float radius_of_item    = getContentSize().width * 0.3f;
            float random_angle      = random(180, 270);
            Point endPoint_item;
            endPoint_item.x         = sinf(CC_DEGREES_TO_RADIANS(random_angle)) * radius_of_item;
            endPoint_item.y         = cosf(CC_DEGREES_TO_RADIANS(random_angle)) * radius_of_item;
            Point final_pos_of_item = Point(world_pos.x + endPoint_item.x, world_pos.y + endPoint_item.y);
            
            point_1_x = final_pos_of_item.x;
            point_1_y = final_pos_of_item.y;
        }
        
        {
            float radius_of_item    = getContentSize().width * 0.4f;
            float random_angle      = random(0, 90);
            Point endPoint_item;
            endPoint_item.x         = sinf(CC_DEGREES_TO_RADIANS(random_angle)) * radius_of_item;
            endPoint_item.y         = cosf(CC_DEGREES_TO_RADIANS(random_angle)) * radius_of_item;
            Point final_pos_of_item = Point(to.x - endPoint_item.x, to.y - endPoint_item.y);
            
            point_2_x = final_pos_of_item.x;
            point_2_y = final_pos_of_item.y;
        }
   // }
    
    ccBezierConfig bezier;
    bezier.controlPoint_1 = Point(point_1_x, point_1_y);
    bezier.controlPoint_2 = Point(point_2_x, point_2_y);
    bezier.endPosition = to;
    
    auto bezierTo = BezierTo::create(fly_duration, bezier);
    auto callf = CallFunc::create([this, fly_object, on_end,_f_type]{
        
        if (this->coin_sound_delay <= 0){
            
            coin_sound_delay = 0.05f;
            
            if (_f_type == FLYING_OBJECT_TYPE_COIN){
                 SoundDirector::playSound("ev_coin");
            }
            else if (_f_type == FLYING_OBJECT_TYPE_GEM){
                 SoundDirector::playSound("ev_gem");
            }
           
        }
        
        if (on_end) {
            on_end();
        }
        
        fly_object->_must_be_deleted = true;
    });
    auto ease = EaseIn::create(bezierTo, random(1.2f, 2.3f));
    auto seq  = Sequence::create(ease, callf, NULL);
    fly_object->runAction(seq);
}

void GameScene::update(float dt){
    
    //bool video_ready = AdManager::getInstance()->is_available_VideoAd();
    // log("video ready %i",video_ready);
    
    coin_sound_delay-=dt;
    
    for (int i = 0; i < _flying_objects.size(); i++) {
        FlyingObject * obj = _flying_objects.at(i);
        
        if (obj->_must_be_deleted) {
            if (obj->tail) {
                obj->tail->removeFromParentAndCleanup(true);
                obj->tail = nullptr;
            }
            
            obj->removeFromParentAndCleanup(true);
            obj = nullptr;
            _flying_objects.erase(_flying_objects.begin() + i);
            i--;
            continue;
        }
        obj->updatePosition();
    }
}

#pragma mark
#pragma mark In-App Loading

void GameScene::open_inapp_loading_layer(LOADING_TYPE _type){
    if (!_purchase_loading_layer) {
        _purchase_loading_layer = PurchaseLoadingLayer::createWithType(_type);
        addChild(_purchase_loading_layer, 99999);
    }
}

void GameScene::close_inapp_loading_layer(){
    if (_purchase_loading_layer) {
        _purchase_loading_layer->removeFromParentAndCleanup(true);
        _purchase_loading_layer = nullptr;
    }
}

#pragma mark
#pragma mark ShopInAppManagerDelegate

void GameScene::shopStars_PurchaseSuccess              (IAPManager *shop,int stars_count,purchase_id purchase_id) {
    close_inapp_loading_layer();
}

void GameScene::shopDidPurchaseDisableAds              (IAPManager *shop,bool from_restore_inapp){
    
    if (IAPConfig::didPurchase_disable_ads() == false) {
        
        IAPConfig::setPurchase_disable_ads(true);
        AdManager::getInstance()->hide_BannerAd();
        
        if (_settings_layer) {
            _settings_layer->refresh_noads_buttons();
        }
        
        if (_gameover_layer) {
            if (_gameover_layer->no_ads_button) {
                _gameover_layer->no_ads_button->setVisible(false);
            }
        }
        
    }
    
    close_inapp_loading_layer();
}

void GameScene::shopStars_In_App_PurchasesSuccess   (IAPManager *shop) {
    close_inapp_loading_layer();
}

void GameScene::shopStars_In_App_PurchasesFailed    (IAPManager *shop) {
    close_inapp_loading_layer();
}

void GameScene::shopStars_In_App_PurchasesItemsRequestFailed    (IAPManager *shop) {
    close_inapp_loading_layer();
}

void GameScene::shopStars_In_App_PurchasesCanceled  (IAPManager *shop) {
    close_inapp_loading_layer();
}

void GameScene::in_app_did_purchase_subscription(purchase_id purchase_id){
    close_inapp_loading_layer();
}

void GameScene::in_app_did_restore_subscription(purchase_id purchase_id){
    close_inapp_loading_layer();
}




