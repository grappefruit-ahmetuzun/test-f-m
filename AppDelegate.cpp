#include "AppDelegate.h"
#include "Space.h"
#include "SoundDirector.h"
#include "Game.h"
#include "GameScene.h"
#include "SPWorldTime.h"
#include "AdManager.h"
#include "PluginSdkboxPlay/PluginSdkboxPlay.h"
#include "PluginIAP/PluginIAP.h"
#include "PlatformManager.h"
#include "GB2ShapeCache-x.h"
#include "PreloadScreen.h"
#include "IAPConfig.h"

USING_NS_CC;

void AppDelegate::initGLContextAttrs(){
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages(){
    return 0;
}

bool AppDelegate::applicationDidFinishLaunching() {
    
    auto director = Director::getInstance();
    auto glview   = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("fruitmaster", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("fruitmaster");
#endif
        director->setOpenGLView(glview);
    }
    
    if (!glview) {
        glview = GLViewImpl::create("");
#if (PLATFORM_MAC)
        glview->setFrameSize(Director::getInstance()->getDeviceSize().width/2, Director::getInstance()->getDeviceSize().height/2);
#endif
        Director::getInstance()->setOpenGLView(glview);
        auto fs = glview->getFrameSize();
        glview->setDesignResolutionSize(fs.width, fs.height, ResolutionPolicy::SHOW_ALL);
    }
    
    //Director::getInstance()->setDisplayStats(true);
    Director::getInstance()->setAnimationInterval(1.0 / 60);
    
    FileUtils::getInstance()->setSearchPaths(SpaceDirector::getInstance()->getResourceSearchPaths());
    Director::getInstance()->setContentScaleFactor(SpaceDirector::getInstance()->getContentScaleFactor());
    
    Settings::set_first_state_as_enabled(settings_vibration);
    Settings::set_first_state_as_enabled(settings_darkmode);
    
    register_all_packages();
    
   // PlatformManager::push_cancelAll();
    
    SoundDirector::preload_sounds();
    
    if (Game::is_iOS()) {
        didFinishLaunchingSplashScreen();
    }
    else if (Game::is_Android()) {
        auto preload_scene = Scene::create();
        preload_scene->addChild(PreloadScreen::create());
        Director::getInstance()->runWithScene(preload_scene);

        auto delay = DelayTime::create(0.5f);
        auto call = CallFunc::create(CC_CALLBACK_0(AppDelegate::didFinishLaunchingSplashScreen, this));
        auto seq = Sequence::create(delay,call, NULL);
        preload_scene->runAction(seq);
    }
    
    return true;
}


void AppDelegate::didFinishLaunchingSplashScreen(){
    
    SPACE->preload_spine_json_data("spine/splash/",             "splash",                       true);
    SPACE->preload_spine_json_data("spine/watermellon/",        "watermelon_slice",             true);
    SPACE->preload_spine_json_data("spine/mixer/",              "mxer",                         true);
    SPACE->preload_spine_json_data("spine/orange/",             "orange_slice",                 true);
    SPACE->preload_spine_json_data("spine/lemon/",              "lemon_slice",                  true);
    SPACE->preload_spine_json_data("spine/pineapple/",          "pineapple_slice",              true);
    SPACE->preload_spine_json_data("spine/kivi/",               "kivi_slice",                   true);
    SPACE->preload_spine_json_data("spine/apple/",              "apple_slice",                  true);
    SPACE->preload_spine_json_data("spine/mango/",              "mango_slice",                  true);
    SPACE->preload_spine_json_data("spine/levelComplete/",      "starsLevelComplete",           true);
    SPACE->preload_spine_json_data("spine/onoff/",              "toggle",                       true);
    SPACE->preload_spine_json_data("spine/logo/",               "logo",                         true);
    
    std::vector<std::string>sounds_to_preload;
    sounds_to_preload.push_back("ev_slash_default");
    sounds_to_preload.push_back("ev_throw");
    sounds_to_preload.push_back("ev_hit_apple");
    sounds_to_preload.push_back("ev_hit_kiwi");
    sounds_to_preload.push_back("ev_hit_lemon");
    sounds_to_preload.push_back("ev_hit_orange");
    sounds_to_preload.push_back("ev_hit_pineapple");
    sounds_to_preload.push_back("ev_hit_watermelon");
    sounds_to_preload.push_back("ev_blender_blend");
    sounds_to_preload.push_back("ev_blender_shoot");
    sounds_to_preload.push_back("ev_blender_coctail_glass_land");
    sounds_to_preload.push_back("ev_blender_coctail_glass_slide");
    sounds_to_preload.push_back("ev_blender_rattle");
    sounds_to_preload.push_back("ev_hit_slo_mo");
    sounds_to_preload.push_back("ev_throw_slo_mo");
    sounds_to_preload.push_back("ev_timer_seq");
    
    sounds_to_preload.push_back("mixer_grad/ev_blender_grad_1");
    sounds_to_preload.push_back("mixer_grad/ev_blender_grad_2");
    sounds_to_preload.push_back("mixer_grad/ev_blender_grad_3");
    sounds_to_preload.push_back("mixer_grad/ev_blender_grad_4");
    sounds_to_preload.push_back("mixer_grad/ev_blender_grad_5");
    
    sounds_to_preload.push_back("ev_knife_miss");
    sounds_to_preload.push_back("ev_blender_shoot_coctail");
    
    sounds_to_preload.push_back("ev_coins_earn");
    sounds_to_preload.push_back("ev_level_complete_chimes");
    sounds_to_preload.push_back("ev_coctail_tiles_grid_appear");
    
    sounds_to_preload.push_back("ev_coin");
    sounds_to_preload.push_back("ev_gem");
    sounds_to_preload.push_back("ev_new_coctail_tile");
    sounds_to_preload.push_back("ev_reward");
    
    sounds_to_preload.push_back("fortunewheel/ev_fortune_reward_coins");
    sounds_to_preload.push_back("fortunewheel/ev_fortune_reward_gems");
    sounds_to_preload.push_back("fortunewheel/ev_fortune_reward_weapon");
    sounds_to_preload.push_back("fortunewheel/ev_fortune_wheel_appear");
    sounds_to_preload.push_back("fortunewheel/ev_fortune_wheel_reduce");
    sounds_to_preload.push_back("fortunewheel/ev_fortune_wheel_tick");
    sounds_to_preload.push_back("fortunewheel/ev_single_tile_to_wheel");
    sounds_to_preload.push_back("fortunewheel/ev_spin_button_appear");
    
    sounds_to_preload.push_back("shop/ev_shop_random");
    sounds_to_preload.push_back("shop/ev_shop_select_negative");
    sounds_to_preload.push_back("shop/ev_shop_select");
    sounds_to_preload.push_back("shop/ev_shop_unlock");
    
    sounds_to_preload.push_back("shop/ev_shop_spend_coins");
    sounds_to_preload.push_back("shop/ev_shop_spend_gems");
    
    for (int i = 0; i < sounds_to_preload.size(); i++) {
        std::string sound_path = sounds_to_preload.at(i);
        SoundDirector::preloadSoundByPath(sound_path.c_str());
    }
    
    // Textures preload
    
    TextureCache * cache = Director::getInstance()->getTextureCache();
    
    std::vector<std::string> images_for_preload;
    images_for_preload.push_back("go.png");
    images_for_preload.push_back("objects/apple.png");
    images_for_preload.push_back("objects/kivi.png");
    images_for_preload.push_back("objects/lemon.png");
    images_for_preload.push_back("objects/mango.png");
    images_for_preload.push_back("objects/orange.png");
    images_for_preload.push_back("objects/pineapple.png");
    images_for_preload.push_back("objects/watermelon.png");
    
    images_for_preload.push_back("fortune_wheel/again.png");
    images_for_preload.push_back("fortune_wheel/blue.png");
    images_for_preload.push_back("fortune_wheel/center.png");
    images_for_preload.push_back("fortune_wheel/empty.png");
    images_for_preload.push_back("fortune_wheel/fortune.png");
    images_for_preload.push_back("fortune_wheel/pink.png");
    images_for_preload.push_back("fortune_wheel/spin.png");
    images_for_preload.push_back("fortune_wheel/yellow.png");
    images_for_preload.push_back("fortune_wheel/beams.png");
    images_for_preload.push_back("fortune_wheel/popup.png");
    
    images_for_preload.push_back("ui/ribbon.png");
    images_for_preload.push_back("ui/ribbon_yellow.png");
 

    for (int i = 0; i < images_for_preload.size(); i++) {
        std::string n = images_for_preload.at(i);
        cache->addImageAsync(n.c_str(), nullptr);
    }
    
    //
    
    sdkbox::PluginSdkboxPlay::init();
    
    sdkbox::IAP::init();
    sdkbox::IAP::refresh();
    
    // GDPR ANDROID
    
    if (Game::is_Android()) {

        PlatformManager::ketchappPromotionLoad();
        /*PlatformManager::preloadGDR();
        
        bool did_see_gdpr = SPUserDefault::getInstance()->getBoolForKey("did_see_gdpr");
        SPUserDefault::getInstance()->setBoolForKey("did_see_gdpr", true);
        
        if (did_see_gdpr == false) {
            if (PlatformManager::isCountryGDRP()){
                PlatformManager::openGDRP_window();
            }
        }*/
        
    }
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        sdkbox::PluginSdkboxPlay::signin();
    
    #elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
        if (Game::is_gplay_connected()) {
            sdkbox::PluginSdkboxPlay::signin();
        }
    
    #endif
    
    int session = Game::getSession();
    
    if (session == 0) {
        Game::getInstance()->setPromotionsSequence();
    }

    // Run scene
    
    auto scene = GameScene::createScene();
    Director::getInstance()->runWithScene(scene);
    
    // Increase session
    
    Game::addSession(1);
    
}

void AppDelegate::applicationDidEnterBackground() {
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        Director::getInstance()->pause();
#else
    Director::getInstance()->stopAnimation();
   // SPWorldTime::getInstance()->application_become_not_active();
#endif

}

void AppDelegate::applicationWillEnterForeground() {
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Director::getInstance()->resume();
#else
    Director::getInstance()->startAnimation();
    //SPWorldTime::getInstance()->application_become_active();
#endif

}
