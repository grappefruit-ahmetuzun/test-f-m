//
//  Game.hpp
//  bottlechallenge
//
//  Created by Marek on 22/09/2016.
//
//

#ifndef Game_h
#define Game_h

#include <stdio.h>
#include "cocos2d.h"
#include "SPUserDefault.h"
#include "PlatformManager.h"

USING_NS_CC;

#define DEBUG_UNLOCK_ITEMS          0
#define DEBUG_UNLOCK_COINS          0
#define DEBUG_UNLOCK_GEMS           0
#define DEBUG_FORTUNE_WHEEL         0

#define DEBUG_COCKTAILS_GENERATE    0

#define NO_INTERNET_INFO  "Please check your\ninternet connection"
#define NO_INTERNET_TITLE "Warning"

#define k_VIDEO_REWARD_SHOP                 35

#define k_VIDEO_REWARD_COINS_GAMEOVER       35
#define k_VIDEO_REWARD_GEMS_GAMEOVER        5

#define KNIFE_BITS               0x0001
#define FRUIT_BITS               0x0002

#define KNIFE_HIT_MULTIPLE_FRUITS 1

/*
0x0001 --
0x0002 --
0x0004
0x0008
0x0010
0x0020
0x0040
0x0080
0x0100
0x0200
0x0400
0x0800
0x1000
0x2000
0x4000
 */

#define PLAY_SOUND_FROM_SERVER 0

enum share_type{
    
    share_type_unknown                          = -1,
    share_type_game_over                        = 0,
    share_type_main_menu                        = 1
    
};

enum RECIPE_CATEGORY{
    
    RECIPE_CATEGORY_NONE                      = -1,
    RECIPE_CATEGORY_RANDOM,
    RECIPE_CATEGORY_COIN,
    RECIPE_CATEGORY_GEM,
    RECIPE_CATEGORY_KNIFE
    
};

enum RECIPE_TYPES{
    
    RECIPE_NONE                      = -2,
    RECIPE_DEFAULT                   = -1,
    RECIPE_SUGAR_RUSH                = 0,
    RECIPE_SUNNY_BREEZE,
    RECIPE_WATERLEMON,
    RECIPE_YUMMY_PUNCH,
    RECIPE_SOUR_CRUSH,
    RECIPE_JUNGLE_SQUASH,
    RECIPE_LEGENDARY_DUO,
    RECIPE_FRESH_MATCH,
    RECIPE_COOL_SPIKES,
    RECIPE_HAPPY_MIX,
    RECIPE_SIMPLE_IS_BEST,
    RECIPE_SATISFACTION,
    RECIPE_KICKSTART,
    RECIPE_TRIPLE_SMILE,
    RECIPE_PERFECT_MORNING,
    RECIPE_MUNCHY_CRUNCHY,
    RECIPE_HIGH_END,
    RECIPE_TRIBAL_BLEND,
    RECIPE_SO_GOOD,
    RECIPE_GROOVY_BEAT,
    RECIPE_FREEZING_STING,
    RECIPE_ICEBREAKER,
    RECIPE_THE_TWISTER,
    RECIPE_WOOPY_MUSH,
    RECIPE_WHAT,
    
};

struct objetive_recipe_info{
    
    RECIPE_TYPES        recipe_type;
    RECIPE_CATEGORY     recipe_category;
    
    bool is_winner_1 = false;
    bool is_winner_2 = false;
    
    int coins_give = 0;
    int gems_give  = 0;
    int knife_id   = 0;
    
};

enum physic_object_tags{
    
    physic_object_unknown               = -1,
    physic_object_knife                 = 0,
    physic_object_fruit                 = 1
    
};

enum fruit_type{
    
    fruit_type_unknown               = -1,
    fruit_type_none                  = 0,
    fruit_type_random                = 1,
    
    fruit_type_watermelon            = 2,
    fruit_type_orange,
    fruit_type_lemon,
    fruit_type_apple,
    fruit_type_kivi,
    fruit_type_pineapple,
    fruit_type_mango,
    
    fruit_type_bomb
    
};

enum ACTION_EASE_TYPE{
    
    EASE_INOUT_UNKNOWN                = -1,
    EASE_NONE                         = 0,
    EASE_INOUT                        = 1
    
};

struct fruit_info{
    
    fruit_type   type           = fruit_type_random;
    
};

struct action_info{
    
    float            duration      = 1.0f;
    float            angle         = 360.0f;
    float            rate          = 1.0f;
    ACTION_EASE_TYPE ease          = EASE_INOUT;
    
};

struct pattern_info{
    
    std::vector<Vec2>          _path_points;
    std::vector<fruit_info>    _fruits;
    std::vector<action_info>   _actions;
    
    int  circle_radius = 0;
  //  int  circle_fruits_count = 0;
    
};

struct level_info{
    std::vector<pattern_info> _patterns;
    int wave = 0;
    
    int getFruitsCount(){
        int count = 0;
        for (int x = 0;x < _patterns.size(); x++){
            pattern_info pattern = _patterns.at(x);
            count+=(int)pattern._fruits.size();
        }
        return count;
    }
    
};

class Game {
    
public:
    
    static bool is_Android(){
        return CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID;
    }
    
    static bool is_iOS(){
        return CC_TARGET_PLATFORM == CC_PLATFORM_IOS;
    }
    
    static std::string getAppstoreUrl(bool multiple_urls = false){
        std::string url_ios     = "https://itunes.apple.com/app/fruit-master/id1404967851";
        std::string url_android = "http://play.google.com/store/apps/details?id=com.ketchapp.fruitmaster";
        
        if (multiple_urls) {
            return StringUtils::format("iOS: %s\nAndroid: %s",url_ios.c_str(),url_android.c_str());
        }
        
        if ((CC_TARGET_PLATFORM == CC_PLATFORM_IOS))
            return url_ios;
        return url_android;
    }
    
    static std::string getGameHashTag(){
        return "#MrGun";
    }

public:
    
    // LOOSE COUNTS
    
    static void setLooseCount(int loose_count,int wave){
        SPUserDefault::getInstance()->setIntegerForKey(StringUtils::format("loose_count_%i",wave).c_str(), loose_count);
    }
    
    static int getLooseCount(int wave){
        return SPUserDefault::getInstance()->getIntegerForKey(StringUtils::format("loose_count_%i",wave).c_str());
    }
    
    // COCTAILES COLLECTED
    
    static int getCoctailsCollected(){
        return SPUserDefault::getInstance()->getIntegerForKey("coctails_collected");
    }
    
    static int getCoctailsCollectObjective(){
        return 4;
    }
    
    static void setCoctailsCollected(int collected){
        SPUserDefault::getInstance()->setIntegerForKey("coctails_collected", collected);
    }
    
    // COINS
    
    static int getCoins(){
        return SPUserDefault::getInstance()->getIntegerForKey("coins");
    }
    
    static void addCoins(int c);
    
    static void setCoins(int coins){
        SPUserDefault::getInstance()->setIntegerForKey("coins", coins);
    }
    
    // GEMS
    
    static int getGems(){
        return SPUserDefault::getInstance()->getIntegerForKey("gems");
    }
    
    static void addGems(int c);
    
    static void setGems(int coins){
        SPUserDefault::getInstance()->setIntegerForKey("gems", coins);
    }
    
    // VIDEO AD
    
    static int getVideoRewardCoinsShop(){
        return 25;
    }
    
    static int getVideoRewardCoinsGameOver(){
        return 25;
    }
    
    static int getVideoRewardStarsShop(){
        return 25;
    }
    
    // SCORE
    
    static int getScore(int mode_id = 0){
        return SPUserDefault::getInstance()->getIntegerForKey(StringUtils::format("score_%i",mode_id).c_str());
    }
    
    static int addScore(int add,int mode_id = 0){
        int score = getScore(mode_id);
        score+=add;
        return SPUserDefault::getInstance()->getIntegerForKey(StringUtils::format("score_%i",mode_id).c_str());
    }
    
    static void setScore(int score,int mode_id = 0){
        SPUserDefault::getInstance()->setIntegerForKey(StringUtils::format("score_%i",mode_id).c_str(), score);
    }
    
    // TUTORIAL
    
    static bool isTutorial(){
        return SPUserDefault::getInstance()->getBoolForKey("tutorial");
    }
    
    static void setTutorial(bool t){
        SPUserDefault::getInstance()->setBoolForKey("tutorial", t);
    }
    
    //
    
    static bool is_same_strings(std::string _string1, std::string _string2){
        if (strcmp(_string1.c_str(), _string2.c_str()) == 0) {
            return true;
        }
        return false;
    }
    
    // Google Play
    
    static bool is_gplay_connected(){
        return SPUserDefault::getInstance()->getBoolForKey("gplayconnected");
    }
    
    static void set_gplay_connected(bool connected){
        SPUserDefault::getInstance()->setBoolForKey("gplayconnected", connected);
        UserDefault::getInstance()->flush();
    }
    
    // Share
    
    static std::string getShareText(){
        int score = Game::getScore();
        return StringUtils::format("I've just scored %i in %s game! %s Can you beat me?", score,Game::getGameHashTag().c_str(),getAppstoreUrl(false).c_str());
    }
    
    static float getRotationWorld(Node* node);
    static float getRotationNode(Node* node, float worldRotationDegrees);
    
    // Session
    
    static int getSession(){
        return SPUserDefault::getInstance()->getIntegerForKey("Ses");
    }
    
    static void addSession(int count){
        SPUserDefault::getInstance()->setIntegerForKey("Ses", getSession() + count);
    }
    
    static void align_x_side_by_side(Node *left,Node *right,float offset);
    
    static promo_type get_next_promotion();
    
    static bool is_update_now(){
        
        std::string game_version = Application::getInstance()->getVersion();
        
        if (SPUserDefault::getInstance()->getBoolForKey(StringUtils::format("is_update_%s", game_version.c_str()).c_str()) == false) {
            SPUserDefault::getInstance()->setBoolForKey(StringUtils::format("is_update_%s", game_version.c_str()).c_str(), true);
            if (Game::getSession() > 0) {
                Game::getInstance()->setIs_update_now(true);
            }
            return true;
        }
        return false;
    }

public:
    
    static std::shared_ptr< Game > getInstance();
    
    Game():
    _gameover_count_for_ads(0),
    _gameover_count_for_ketchapp_square(0),
    _is_update_now(false),
    _didSeeMenu(false),
    _wave_count_for_continue(0),
    _gameScoreOnGameOver(0),
    _logo_animation_showed(false),
    _gameover_count_for_game_promo(random(15, 25)),
    _didShowLoading(false)
    {
    };
    virtual ~Game(){};
    
    void runRecursiveAction(Node *node,ActionInterval *action);
    void setPromotionsSequence();
    void show_mission_complete_notification(int mission);
    
    Label *show_text_label_info(Vec2 world_pos,std::string text,float scale_by =1);
    
    bool is_tutorial_completed(){
        return SPUserDefault::getInstance()->getBoolForKey("tutorial_completed");
    }
    
    void set_tutorials_as_completed(){
        SPUserDefault::getInstance()->setBoolForKey("tutorial_completed", true);
    }

    CC_SYNTHESIZE(int,      _gameScoreOnGameOver,                   GameScoreOnGameOver);
    CC_SYNTHESIZE(int,      _gameover_count_for_ads,                Gameover_count_for_ads);
    CC_SYNTHESIZE(int,      _gameover_count_for_ketchapp_square,    Gameover_count_for_ketchapp_square);
    CC_SYNTHESIZE(int,      _gameover_count_for_game_promo,         Gameover_count_for_game_promo);
    CC_SYNTHESIZE(bool,     _is_update_now,                         Is_update_now);
    CC_SYNTHESIZE(bool,     _didSeeMenu,                            DidSeeMenu);
    CC_SYNTHESIZE(int,      _wave_count_for_continue,               Wave_count_for_continue);
    CC_SYNTHESIZE(bool,     _logo_animation_showed,                 Logo_animation_showed);
    CC_SYNTHESIZE(bool,     _didShowLoading,                        DidShowLoading);
    
    float pointPairToBearingDegrees(const cocos2d::Point &startingPoint, const cocos2d::Point &endingPoint);

};

#endif /* Game_hpp */
