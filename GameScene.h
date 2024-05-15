//
//  GameScene.h
//  bottlechallenge
//
//  Created by Marek on 22/09/2016.
//
//

#ifndef GameScene_h
#define GameScene_h

#include "GameLayer.h"
#include "Gameplayb2d.h"
#include "AdManager.h"
#include "PluginSdkboxPlay/PluginSdkboxPlay.h"
#include "CoinsAmmountSprite.h"
#include "HudLayer.h"
#include "MenuLayer.h"
#include "GameOverLayer.h"
#include "LevelManager.h"
#include "LevelCompleteLayer.h"
#include "Settings.h"
#include "ContinueLayer.h"
#include "ShopLayer.h"
#include "SettingsLayer.h"
#include "FlyingObject.h"
#include "WeaponUnlockPopup.h"
#include "PluginIAP/PluginIAP.h"
#include "IAPManager.h"
#include "PurchaseLoadingLayer.h"
#include "ExitLayer.h"

#define GAMESCENE_TAG  11247

class GameScene :
public GameLayer,
public GameplayDelegate,
public AdManagerDelegate,
public sdkbox::SdkboxPlayListener,
public SettingsDelegate,
public ShopInAppManagerDelegate
{
    
public:
    
    GameScene()
    {}
    ~GameScene(){};
    
    static cocos2d::Scene * createScene();
    CREATE_FUNC(GameScene);
    
    bool init() override;
    void game_prepare();
    
private:
    
    Gameplayb2d                 * _game_b2d_layer           = nullptr;
    CoinsAmmountSprite          * _coins                    = nullptr;
    CoinsAmmountSprite          * _gems                     = nullptr;
    HudLayer                    * _hud_layer                = nullptr;
    MenuLayer                   * _menu_layer               = nullptr;
    GameOverLayer               * _gameover_layer           = nullptr;
    Sprite                      * _slowmo_sprite            = nullptr;
    LevelCompleteLayer          * _level_complete_layer     = nullptr;
    Sprite                      * _background               = nullptr;
    ContinueLayer               * _continue_layer           = nullptr;
    ShopLayer                   * _shop_layer               = nullptr;
    SettingsLayer               * _settings_layer           = nullptr;
    WeaponUnlockPopup           * _weapon_unlock_popup      = nullptr;
    PurchaseLoadingLayer        * _purchase_loading_layer   = nullptr;
    ExitLayer                   * _exit                     = nullptr;
    
    Sprite *_left_border   = nullptr;
    Sprite * _right_border = nullptr;
    
    std::vector<FlyingObject * > _flying_objects;
    float coin_sound_delay = 0;
    
private:
    
    // Android Back
    
    void onKeyReleased          (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) override;
    
    // Android Exit
    void showExitToMenuLayer    ();
    void showQuitTheGameLayer   ();
    void didSelect_exit_layer_no();
    void didSelect_exit_to_main_menu();
    void didSelect_quit_the_game();
    
    // Coins
    
    void refresh_coins();
    
    // Shop
    
    void didSelectWeapon();
    void didSelect_shop_video();
    void didDoubleSelect();
    
    // Settings

    void give_coins_from_settings(int coins, float after_delay,Vec2 from_position);
    void didSelect_settings_privacy();
    void didSelect_settings_remove_ads();
    void didSelect_settings_restore_purchases();
    
    // Back
    
    void didSelect_back_shop();
    void didSelect_back_settings();
    void didSelect_back_fortune_weapon_unlock();
    
    // WeaponUnlockPopup

    void didSelect_equp();
    
    void game_refresh_dark_mode();
    void submit_leaderboards_values();
    
    // Menu
    
    void didSelect_menu_darkmode();
    void didSelect_menu_settings();
    void didSelect_menu_customize();
    
    // Game Over
    
    void didSelect_gameover_restart();
    void didSelect_gameover_home();
    void didSelect_gameover_leaderboards();
    void didSelect_gameover_customize();
    void didSelect_gameover_coins_video();
    void didSelect_gameover_gems_video();
    void didSelect_gameover_no_ads();
    
    // GameplayDelegate
    
    virtual void gameplay_score_didchange(int score)    override;
    virtual void gameplay_gameover       (float delay)  override;
    virtual void gameplay_slow_motion    (bool enable)  override;
    virtual void gameplay_miss_star      ()             override;
    virtual void gameplay_level_complete ()             override;
    virtual void gameplay_coins_fly      (Vec2 point,FLYING_OBJECT_TYPE object_type,std::function<void()> on_end) override;
    
    // Fortune wheel
    
    void didCollect_fortune_wheel_reward(objetive_recipe_info info,Vec2 position);
    
    // Continue
    
    void game_show_continue();
    void didSelect_continue_continue();
    void didSelect_continue_nothanks(bool from_video_skip = false);
    void didSelect_continue_timefinished();
    
    // Level Completed
    
    void didSelect_levelcompleted_next();
    
    // Insterstitial
    
    bool interstitial_check_and_show();
    
    // touches
    
    virtual bool onTouchBegan(Touch *touch, Event *event)      override;
    virtual void onTouchMoved(Touch *touch, Event *event)      override;
    virtual void onTouchEnded(Touch *touch, Event *event)      override;
    
    // AdManagerDelegate
    
    virtual void ad_video_didchange_state(WATCH_VIDEO_TYPE type,WATCH_VIDEO_STATE state) override;
    virtual void interstitial_didchange_state(INTERSTITIAL_STATE state) override;
    
    // SdkboxPlayListener
    
    virtual void onConnectionStatusChanged( int status ) override;
    virtual void onScoreSubmitted( const std::string& leaderboard_name, long score, bool maxScoreAllTime, bool maxScoreWeek, bool maxScoreToday ) override;
    virtual void onIncrementalAchievementUnlocked( const std::string& achievement_name ) override;
    virtual void onIncrementalAchievementStep( const std::string& achievement_name, double step ) override;
    virtual void onAchievementUnlocked( const std::string& achievement_name, bool newlyUnlocked ) override;
    
    // SettingsDelegate
    
    virtual void settings_did_change(settings_type t) override;
    
    // Coins/Gems fly
    
    void gameplay_collect_object_with_fly   (FLYING_OBJECT_TYPE _f_type, Vec2 world_pos, int coins_ammount, std::function<void()> on_end, float object_width);
    
    // Update
    
    virtual void update(float dt) override;
    
    // In-App Loading
    
    void open_inapp_loading_layer(LOADING_TYPE _type);
    void close_inapp_loading_layer();
    
    // ShopInAppManagerDelegate
    
    virtual void shopStars_PurchaseSuccess              (IAPManager *shop,int stars_count,purchase_id purchase_id) override;
    virtual void shopDidPurchaseDisableAds              (IAPManager *shop,bool from_restore_inapp) override;
    
    virtual void shopStars_In_App_PurchasesSuccess   (IAPManager *shop) override;
    virtual void shopStars_In_App_PurchasesFailed    (IAPManager *shop) override;
    virtual void shopStars_In_App_PurchasesItemsRequestFailed    (IAPManager *shop) override;
    virtual void shopStars_In_App_PurchasesCanceled  (IAPManager *shop) override;
    
    virtual void in_app_did_purchase_subscription(purchase_id purchase_id) override;
    virtual void in_app_did_restore_subscription(purchase_id purchase_id) override;
    
};

#endif /* GameScene_hpp */
