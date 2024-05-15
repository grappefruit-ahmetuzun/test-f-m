//
//  Patterns.cpp
//  FruitsKnife-mobile
//
//  Created by Marek on 15/05/2018.
//

#include "Patterns.h"
#include "LevelManager.h"
#include "Game.h"
#include "Recipes.h"
#include "LevelManager.h"
#include "ShopManager.h"

Patterns::~Patterns(){
    
}

std::shared_ptr< Patterns > patternsInstance;

std::shared_ptr< Patterns > Patterns::getInstance() {
    if (patternsInstance){
        return patternsInstance;
    }
    
    patternsInstance = std::make_shared< Patterns >();
    return patternsInstance;
}

#pragma mark NEW!!!!

void Patterns::generate_new_coctails(){
    
    Game::setCoctailsCollected(0);

    objetive_recipe_info info1;
    objetive_recipe_info info2;
    objetive_recipe_info info3;
    objetive_recipe_info info4;
    
    std::vector<RECIPE_TYPES>recipes_coin   = Recipes::get_recipes(RECIPE_CATEGORY_COIN);
    std::vector<RECIPE_TYPES>recipes_gem    = Recipes::get_recipes(RECIPE_CATEGORY_GEM);
    std::vector<RECIPE_TYPES>recipes_knife  = Recipes::get_recipes(RECIPE_CATEGORY_KNIFE);
    
    {
        int seed = (int)std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(recipes_coin.begin(), recipes_coin.end(), std::default_random_engine(seed));
    }
    {
        int seed = (int)std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(recipes_gem.begin(), recipes_gem.end(), std::default_random_engine(seed));
    }
    {
        int seed = (int)std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(recipes_knife.begin(), recipes_knife.end(), std::default_random_engine(seed));
    }
    
    if (SPUserDefault::getInstance()->getBoolForKey("first_cooldown_coctail") == false) {
        SPUserDefault::getInstance()->setIntegerForKey("coctail_cooldown", random(3, 6));   // first cooldown set
        SPUserDefault::getInstance()->setBoolForKey("first_cooldown_coctail", true);
    }
    
    int cooldown = SPUserDefault::getInstance()->getIntegerForKey("coctail_cooldown", random(5,7));
    
    cooldown--;
    
    bool special_cooldown = false;
    
    if (cooldown <= 0) {
        // new cooldown set
        special_cooldown = true;
        if (random(1,100) > 90) {
            cooldown        = random(2, 3);
        }
        else {
            cooldown        = random(5, 7);
        }
    }
    
    SPUserDefault::getInstance()->setIntegerForKey("coctail_cooldown", cooldown);   // first cooldown set

    int fortune_knifes_unlocked          = 0;
    std::vector<SHOP_ITEM>fortune_knifes = Shop::get_knives(SHOP_PAGE_TYPE_KNIVES_FORTUNE_WHLLE_PAGE_1);
    
    std::vector<SHOP_ITEM> reserved_knives = is_current_level_have_knife();

    for (int x = 0; x < reserved_knives.size(); x++){
        SHOP_ITEM r_knife = reserved_knives.at(x);
        
        for (int y=0; y < fortune_knifes.size(); y++){
            SHOP_ITEM knife = fortune_knifes.at(y);
            
            if (r_knife == knife) {
                fortune_knifes.erase(fortune_knifes.begin() + y);
                y--;
            }
        }
    }
    
    for (int x=0; x < fortune_knifes.size(); x++){
        SHOP_ITEM knife = fortune_knifes.at(x);
        if (ShopManager::getInstance()->is_item_purchased(knife)) {
            fortune_knifes_unlocked++;
            fortune_knifes.erase(fortune_knifes.begin()+x);
            x--;
        }
    }
    
    

    int set_index = 1;

    if (fortune_knifes_unlocked == 0) {
        set_index = random(201, 204); // beginner rewards
    }
    else if (special_cooldown) {
        set_index = random(101, 115); // special reward patterns
    }
    else {
        set_index = random(1, 6); // usual rewards
    }
    
    if (set_index == 1) {
        
        info1.recipe_category   = RECIPE_CATEGORY_COIN;
        info1.coins_give        = 25 + (random(0,1) * random(0,1) * 25);
        info1.gems_give         = 0;
        info1.is_winner_1       = false;
        info1.is_winner_2       = false;
        
        info2.recipe_category   = RECIPE_CATEGORY_GEM;
        info2.coins_give        = 0;
        info2.gems_give         = 5 + random(0, 4) * 5;
        info2.is_winner_1       = false;
        info2.is_winner_2       = true;
        
        info3.recipe_category   = RECIPE_CATEGORY_COIN;
        info3.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info3.gems_give         = 0;
        info3.is_winner_1       = true;
        info3.is_winner_2       = false;
        
        info4.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info4.coins_give        = 0;
        info4.gems_give         = 0;
        info4.is_winner_1       = false;
        info4.is_winner_2       = false;
        
    }
    else if (set_index == 2) {

        info1.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info1.coins_give        = 0;
        info1.gems_give         = 0;
        info1.is_winner_1       = false;
        info1.is_winner_2       = false;
        
        info2.recipe_category   = RECIPE_CATEGORY_COIN;
        info2.coins_give        = 25 + (random(0,1) * random(0,1) * 25);
        info2.gems_give         = 0;
        info2.is_winner_1       = true;
        info2.is_winner_2       = false;

        info3.recipe_category   = RECIPE_CATEGORY_GEM;
        info3.coins_give        = 0;
        info3.gems_give         = 5 + random(0, 4) * 5;
        info3.is_winner_1       = false;
        info3.is_winner_2       = false;
        
        info4.recipe_category   = RECIPE_CATEGORY_COIN;
        info4.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info4.gems_give         = 0;
        info4.is_winner_1       = false;
        info4.is_winner_2       = true;

    }
    else if (set_index == 3) {
        
        info1.recipe_category   = RECIPE_CATEGORY_GEM;
        info1.coins_give        = 0;
        info1.gems_give         = 5 + random(0, 2) * 5;
        info1.is_winner_1       = true;
        info1.is_winner_2       = false;
        
        info2.recipe_category   = RECIPE_CATEGORY_COIN;
        info2.coins_give        = 25 + (random(0,1) * random(0,1) * 25);
        info2.gems_give         = 0;
        info2.is_winner_1       = false;
        info2.is_winner_2       = false;
        
        info3.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info3.coins_give        = 0;
        info3.gems_give         = 0;
        info3.is_winner_1       = false;
        info3.is_winner_2       = true;
        
        info4.recipe_category   = RECIPE_CATEGORY_COIN;
        info4.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info4.gems_give         = 0;
        info4.is_winner_1       = false;
        info4.is_winner_2       = false;
        
    }
    else if (set_index == 4) {
        
        info1.recipe_category   = RECIPE_CATEGORY_GEM;
        info1.coins_give        = 0;
        info1.gems_give         = 5 + random(0, 4) * 5;
        info1.is_winner_1       = false;
        info1.is_winner_2       = true;
        
        info2.recipe_category   = RECIPE_CATEGORY_COIN;
        info2.coins_give        = 25 + (random(0,1) * random(0,1) * 25);
        info2.gems_give         = 0;
        info2.is_winner_1       = false;
        info2.is_winner_2       = false;
        
        info3.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info3.coins_give        = 0;
        info3.gems_give         = 0;
        info3.is_winner_1       = false;
        info3.is_winner_2       = false;
        
        info4.recipe_category   = RECIPE_CATEGORY_COIN;
        info4.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info4.gems_give         = 0;
        info4.is_winner_1       = true;
        info4.is_winner_2       = false;
        
    }
    else if (set_index == 5) {
        
        info1.recipe_category   = RECIPE_CATEGORY_GEM;
        info1.coins_give        = 0;
        info1.gems_give         = 5 + random(0, 4) * 5;
        info1.is_winner_1       = false;
        info1.is_winner_2       = true;
        
        info2.recipe_category   = RECIPE_CATEGORY_COIN;
        info2.coins_give        = 25 + (random(0,1) * random(0,1) * 25);
        info2.gems_give         = 0;
        info2.is_winner_1       = true;
        info2.is_winner_2       = false;
        
        info3.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info3.coins_give        = 0;
        info3.gems_give         = 0;
        info3.is_winner_1       = false;
        info3.is_winner_2       = false;
        
        info4.recipe_category   = RECIPE_CATEGORY_COIN;
        info4.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info4.gems_give         = 0;
        info4.is_winner_1       = false;
        info4.is_winner_2       = false;
        
    }
    else if (set_index == 6) {
        
        info1.recipe_category   = RECIPE_CATEGORY_GEM;
        info1.coins_give        = 0;
        info1.gems_give         = 5 + random(0, 4) * 5;
        info1.is_winner_1       = true;
        info1.is_winner_2       = false;
        
        info2.recipe_category   = RECIPE_CATEGORY_COIN;
        info2.coins_give        = 25 + (random(0,1) * random(0,1) * 25);
        info2.gems_give         = 0;
        info2.is_winner_1       = false;
        info2.is_winner_2       = false;
        
        info3.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info3.coins_give        = 0;
        info3.gems_give         = 0;
        info3.is_winner_1       = false;
        info3.is_winner_2       = true;
        
        info4.recipe_category   = RECIPE_CATEGORY_COIN;
        info4.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info4.gems_give         = 0;
        info4.is_winner_1       = false;
        info4.is_winner_2       = false;
        
    }
    // special patterns
    else if (set_index == 101) {
        
        info1.recipe_category   = RECIPE_CATEGORY_GEM;
        info1.coins_give        = 0;
        info1.gems_give         = 5 + random(0, 1) * 5;
        info1.is_winner_1       = false;
        info1.is_winner_2       = true;
        
        info2.recipe_category   = RECIPE_CATEGORY_COIN;
        info2.coins_give        = 25 + (random(0,1) * random(0,1) * 25);
        info2.gems_give         = 0;
        info2.is_winner_1       = false;
        info2.is_winner_2       = false;
        
        info3.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info3.coins_give        = 0;
        info3.gems_give         = 5 + random(0, 1) * 5;
        info3.is_winner_1       = true;
        info3.is_winner_2       = false;
        
        info4.recipe_category   = RECIPE_CATEGORY_COIN;
        info4.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info4.gems_give         = 0;
        info4.is_winner_1       = false;
        info4.is_winner_2       = false;
        
    }
    else if (set_index == 102) {
        
        info1.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info1.coins_give        = 0;
        info1.gems_give         = 5 + random(0, 1) * 5;
        info1.is_winner_1       = true;
        info1.is_winner_2       = false;
        
        info2.recipe_category   = RECIPE_CATEGORY_COIN;
        info2.coins_give        = 25 + (random(0,1) * random(0,1) * 25);
        info2.gems_give         = 0;
        info2.is_winner_1       = false;
        info2.is_winner_2       = false;
        
        info3.recipe_category   = RECIPE_CATEGORY_GEM;
        info3.coins_give        = 0;
        info3.gems_give         = 15 + random(0, 2) * 5;
        info3.is_winner_1       = false;
        info3.is_winner_2       = false;
        
        info4.recipe_category   = RECIPE_CATEGORY_COIN;
        info4.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info4.gems_give         = 0;
        info4.is_winner_1       = false;
        info4.is_winner_2       = true;
        
    }
    else if (set_index == 103) {
        
        info1.recipe_category   = RECIPE_CATEGORY_GEM;
        info1.coins_give        = 0;
        info1.gems_give         = 5 + random(0, 1) * 5;
        info1.is_winner_1       = false;
        info1.is_winner_2       = true;
        
        info2.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info2.coins_give        = 0;
        info2.gems_give         = 5 + random(0, 1) * 5;
        info2.is_winner_1       = false;
        info2.is_winner_2       = false;
        
        info3.recipe_category   = RECIPE_CATEGORY_GEM;
        info3.coins_give        = 0;
        info3.gems_give         = 15 + random(0, 2) * 5;
        info3.is_winner_1       = false;
        info3.is_winner_2       = false;
        
        info4.recipe_category   = RECIPE_CATEGORY_COIN;
        info4.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info4.gems_give         = 0;
        info4.is_winner_1       = true;
        info4.is_winner_2       = false;
        
    }
    else if (set_index == 104) {
        
        info1.recipe_category   = RECIPE_CATEGORY_GEM;
        info1.coins_give        = 0;
        info1.gems_give         = 5 + random(0, 1) * 5;
        info1.is_winner_1       = false;
        info1.is_winner_2       = false;
        
        info2.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info2.coins_give        = 0;
        info2.gems_give         = 5 + random(0, 1) * 5;
        info2.is_winner_1       = false;
        info2.is_winner_2       = true;
        
        info3.recipe_category   = RECIPE_CATEGORY_GEM;
        info3.coins_give        = 0;
        info3.gems_give         = 15 + random(0, 2) * 5;
        info3.is_winner_1       = false;
        info3.is_winner_2       = false;
        
        info4.recipe_category   = RECIPE_CATEGORY_COIN;
        info4.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info4.gems_give         = 0;
        info4.is_winner_1       = true;
        info4.is_winner_2       = false;
        
    }
    else if (set_index == 105) {
        
        info1.recipe_category   = RECIPE_CATEGORY_GEM;
        info1.coins_give        = 0;
        info1.gems_give         = 5 + random(0, 1) * 5;
        info1.is_winner_1       = false;
        info1.is_winner_2       = false;
        
        info2.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info2.coins_give        = 0;
        info2.gems_give         = 5 + random(0, 1) * 5;
        info2.is_winner_1       = true;
        info2.is_winner_2       = false;
        
        info3.recipe_category   = RECIPE_CATEGORY_GEM;
        info3.coins_give        = 0;
        info3.gems_give         = 15 + random(0, 2) * 5;
        info3.is_winner_1       = false;
        info3.is_winner_2       = true;
        
        info4.recipe_category   = RECIPE_CATEGORY_COIN;
        info4.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info4.gems_give         = 0;
        info4.is_winner_1       = false;
        info4.is_winner_2       = false;
        
    }
    else if (set_index == 106) {
        
        info1.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info1.coins_give        = 0;
        info1.gems_give         = 5 + random(0, 1) * 5;
        info1.is_winner_1       = false;
        info1.is_winner_2       = false;
        
        info2.recipe_category   = RECIPE_CATEGORY_COIN;
        info2.coins_give        = 25 + (random(0,1) * random(0,1) * 25);
        info2.gems_give         = 0;
        info2.is_winner_1       = false;
        info2.is_winner_2       = false;
        
        info3.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info3.coins_give        = 0;
        info3.gems_give         = 15 + random(0, 2) * 5;
        info3.is_winner_1       = false;
        info3.is_winner_2       = true;
        
        info4.recipe_category   = RECIPE_CATEGORY_COIN;
        info4.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info4.gems_give         = 0;
        info4.is_winner_1       = true;
        info4.is_winner_2       = false;
        
    }
    else if (set_index == 107) {
        
        info1.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info1.coins_give        = 0;
        info1.gems_give         = 5 + random(0, 1) * 5;
        info1.is_winner_1       = false;
        info1.is_winner_2       = false;
        
        info2.recipe_category   = RECIPE_CATEGORY_COIN;
        info2.coins_give        = 25 + (random(0,1) * random(0,1) * 25);
        info2.gems_give         = 0;
        info2.is_winner_1       = true;
        info2.is_winner_2       = false;
        
        info3.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info3.coins_give        = 0;
        info3.gems_give         = 15 + random(0, 2) * 5;
        info3.is_winner_1       = false;
        info3.is_winner_2       = true;
        
        info4.recipe_category   = RECIPE_CATEGORY_COIN;
        info4.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info4.gems_give         = 0;
        info4.is_winner_1       = false;
        info4.is_winner_2       = false;
        
    }
    else if (set_index == 108) {
    
        info1.recipe_category   = RECIPE_CATEGORY_COIN;
        info1.coins_give        = 25 + (random(0,1) * random(0,1) * 25);
        info1.gems_give         = 0;
        info1.is_winner_1       = false;
        info1.is_winner_2       = false;
        
        info2.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info2.coins_give        = 0;
        info2.gems_give         = 15 + random(0, 2) * 5;
        info2.is_winner_1       = false;
        info2.is_winner_2       = false;
        
        info3.recipe_category   = RECIPE_CATEGORY_COIN;
        info3.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info3.gems_give         = 0;
        info3.is_winner_1       = true;
        info3.is_winner_2       = false;
        
        info4.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info4.coins_give        = 0;
        info4.gems_give         = 5 + random(0, 1) * 5;
        info4.is_winner_1       = false;
        info4.is_winner_2       = true;
        
    }
    else if (set_index == 109) {
        
        info1.recipe_category   = RECIPE_CATEGORY_COIN;
        info1.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info1.gems_give         = 0;
        info1.is_winner_1       = false;
        info1.is_winner_2       = false;
        
        info2.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info2.coins_give        = 0;
        info2.gems_give         = 15 + random(0, 2) * 5;
        info2.is_winner_1       = false;
        info2.is_winner_2       = false;
        
        info3.recipe_category   = RECIPE_CATEGORY_COIN;
        info3.coins_give        = 25 + (random(0,1) * random(0,1) * 25);
        info3.gems_give         = 0;
        info3.is_winner_1       = true;
        info3.is_winner_2       = false;
        
        info4.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info4.coins_give        = 0;
        info4.gems_give         = 5 + random(0, 1) * 5;
        info4.is_winner_1       = false;
        info4.is_winner_2       = true;
        
    }
    else if (set_index == 110) {
        
        info1.recipe_category   = RECIPE_CATEGORY_COIN;
        info1.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info1.gems_give         = 0;
        info1.is_winner_1       = false;
        info1.is_winner_2       = true;
        
        info2.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info2.coins_give        = 0;
        info2.gems_give         = 15 + random(0, 2) * 5;
        info2.is_winner_1       = true;
        info2.is_winner_2       = false;
        
        info3.recipe_category   = RECIPE_CATEGORY_GEM;
        info3.coins_give        = 0;
        info3.gems_give         = 15 + random(0, 2) * 5;
        info3.is_winner_1       = false;
        info3.is_winner_2       = false;
        
        info4.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info4.coins_give        = 0;
        info4.gems_give         = 5 + random(0, 1) * 5;
        info4.is_winner_1       = false;
        info4.is_winner_2       = false;
        
    }
    else if (set_index == 111) {
        
        info1.recipe_category   = RECIPE_CATEGORY_GEM;
        info1.coins_give        = 0;
        info1.gems_give         = 5 + random(0, 1) * 5;
        info1.is_winner_1       = false;
        info1.is_winner_2       = false;
        
        info2.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info2.coins_give        = 0;
        info2.gems_give         = 15 + random(0, 2) * 5;
        info2.is_winner_1       = true;
        info2.is_winner_2       = false;
        
        info3.recipe_category   = RECIPE_CATEGORY_GEM;
        info3.coins_give        = 0;
        info3.gems_give         = 15 + random(0, 2) * 5;
        info3.is_winner_1       = false;
        info3.is_winner_2       = false;
        
        info4.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info4.coins_give        = 0;
        info4.gems_give         = 5 + random(0, 1) * 5;
        info4.is_winner_1       = false;
        info4.is_winner_2       = true;
        
    }
    else if (set_index == 112) {
        
        info1.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info1.coins_give        = 0;
        info1.gems_give         = 5 + random(0, 1) * 5;
        info1.is_winner_1       = true;
        info1.is_winner_2       = false;
        
        info2.recipe_category   = RECIPE_CATEGORY_GEM;
        info2.coins_give        = 0;
        info2.gems_give         = 5 + random(0, 1) * 5;
        info2.is_winner_1       = false;
        info2.is_winner_2       = false;
        
        info3.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info3.coins_give        = 0;
        info3.gems_give         = 15 + random(0, 2) * 5;
        info3.is_winner_1       = false;
        info3.is_winner_2       = false;
        
        info4.recipe_category   = RECIPE_CATEGORY_GEM;
        info4.coins_give        = 0;
        info4.gems_give         = 15 + random(0, 2) * 5;
        info4.is_winner_1       = false;
        info4.is_winner_2       = true;

    }
    else if (set_index == 113) {
        
        info1.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info1.coins_give        = 0;
        info1.gems_give         = 5 + random(0, 1) * 5;
        info1.is_winner_1       = false;
        info1.is_winner_2       = false;
        
        info2.recipe_category   = RECIPE_CATEGORY_GEM;
        info2.coins_give        = 0;
        info2.gems_give         = 5 + random(0, 1) * 5;
        info2.is_winner_1       = true;
        info2.is_winner_2       = false;
        
        info3.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info3.coins_give        = 0;
        info3.gems_give         = 15 + random(0, 2) * 5;
        info3.is_winner_1       = false;
        info3.is_winner_2       = false;
        
        info4.recipe_category   = RECIPE_CATEGORY_GEM;
        info4.coins_give        = 0;
        info4.gems_give         = 15 + random(0, 2) * 5;
        info4.is_winner_1       = false;
        info4.is_winner_2       = true;
        
    }
    else if (set_index == 114) {
        
        info1.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info1.coins_give        = 0;
        info1.gems_give         = 5 + random(0, 1) * 5;
        info1.is_winner_1       = true;
        info1.is_winner_2       = false;
        
        info2.recipe_category   = RECIPE_CATEGORY_GEM;
        info2.coins_give        = 0;
        info2.gems_give         = 5 + random(0, 1) * 5;
        info2.is_winner_1       = false;
        info2.is_winner_2       = false;
        
        info3.recipe_category   = RECIPE_CATEGORY_COIN;
        info3.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info3.gems_give         = 0;
        info3.is_winner_1       = false;
        info3.is_winner_2       = true;
        
        info4.recipe_category   = RECIPE_CATEGORY_GEM;
        info4.coins_give        = 0;
        info4.gems_give         = 15 + random(0, 2) * 5;
        info4.is_winner_1       = false;
        info4.is_winner_2       = false;
        
    }
    else if (set_index == 115) {

        info1.recipe_category   = RECIPE_CATEGORY_COIN;
        info1.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info1.gems_give         = 0;
        info1.is_winner_1       = false;
        info1.is_winner_2       = false;

        info2.recipe_category   = RECIPE_CATEGORY_GEM;
        info2.coins_give        = 0;
        info2.gems_give         = 5 + random(0, 1) * 5;
        info2.is_winner_1       = false;
        info2.is_winner_2       = true;
        
        info3.recipe_category   = RECIPE_CATEGORY_COIN;
        info3.coins_give        = 25 + (random(0,1) * random(0,1) * 25);
        info3.gems_give         = 0;
        info3.is_winner_1       = false;
        info3.is_winner_2       = false;
        
        info4.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info4.coins_give        = 0;
        info4.gems_give         = 5 + random(0, 1) * 5;
        info4.is_winner_1       = true;
        info4.is_winner_2       = false;
 
    }
    
    // beginner rewards
    
    else if (set_index == 201) {
        
        info1.recipe_category   = RECIPE_CATEGORY_COIN;
        info1.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info1.gems_give         = 0;
        info1.is_winner_1       = false;
        info1.is_winner_2       = false;
        
        info2.recipe_category   = RECIPE_CATEGORY_GEM;
        info2.coins_give        = 0;
        info2.gems_give         = 5 + random(0, 1) * 5;
        info2.is_winner_1       = false;
        info2.is_winner_2       = false;
        
        info3.recipe_category   = RECIPE_CATEGORY_COIN;
        info3.coins_give        = 25 + (random(0,1) * random(0,1) * 25);
        info3.gems_give         = 0;
        info3.is_winner_1       = true;
        info3.is_winner_2       = false;
        
        info4.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info4.coins_give        = 0;
        info4.gems_give         = 5 + random(0, 1) * 5;
        info4.is_winner_1       = false;
        info4.is_winner_2       = true;
        
    }
    
    else if (set_index == 202) {
        
        info1.recipe_category   = RECIPE_CATEGORY_GEM;
        info1.coins_give        = 0;
        info1.gems_give         = 5 + random(0, 1) * 5;
        info1.is_winner_1       = false;
        info1.is_winner_2       = false;
        
        info2.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info2.coins_give        = 0;
        info2.gems_give         = 5 + random(0, 1) * 5;
        info2.is_winner_1       = false;
        info2.is_winner_2       = true;
        
        info3.recipe_category   = RECIPE_CATEGORY_GEM;
        info3.coins_give        = 0;
        info3.gems_give         = 15 + random(0, 1) * 5;
        info3.is_winner_1       = true;
        info3.is_winner_2       = false;
        
        info4.recipe_category   = RECIPE_CATEGORY_COIN;
        info4.coins_give        = 50 + (random(0,1) * random(0,1) * 25);
        info4.gems_give         = 0;
        info4.is_winner_1       = false;
        info4.is_winner_2       = false;
        
    }
    else if (set_index == 203) {
        
        
        info1.recipe_category   = RECIPE_CATEGORY_GEM;
        info1.coins_give        = 0;
        info1.gems_give         = 5 + random(0, 1) * 5;
        info1.is_winner_1       = false;
        info1.is_winner_2       = false;
        
        info2.recipe_category   = RECIPE_CATEGORY_COIN;
        info2.coins_give        = 25 + (random(0,1) * random(0,1) * 25);
        info2.gems_give         = 0;
        info2.is_winner_1       = false;
        info2.is_winner_2       = false;
        
        info3.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info3.coins_give        = 0;
        info3.gems_give         = 5 + random(0, 1) * 5;
        info3.is_winner_1       = false;
        info3.is_winner_2       = true;
        
        info4.recipe_category   = RECIPE_CATEGORY_COIN;
        info4.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info4.gems_give         = 0;
        info4.is_winner_1       = true;
        info4.is_winner_2       = false;
        
    }
    else if (set_index == 204) {
        
        
        info1.recipe_category   = RECIPE_CATEGORY_GEM;
        info1.coins_give        = 0;
        info1.gems_give         = 5 + random(0, 1) * 5;
        info1.is_winner_1       = false;
        info1.is_winner_2       = false;
        
        info2.recipe_category   = RECIPE_CATEGORY_COIN;
        info2.coins_give        = 25 + (random(0,1) * random(0,1) * 25);
        info2.gems_give         = 0;
        info2.is_winner_1       = false;
        info2.is_winner_2       = false;
        
        info3.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info3.coins_give        = 0;
        info3.gems_give         = 5 + random(0, 1) * 5;
        info3.is_winner_1       = true;
        info3.is_winner_2       = false;
        
        info4.recipe_category   = RECIPE_CATEGORY_COIN;
        info4.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info4.gems_give         = 0;
        info4.is_winner_1       = true;
        info4.is_winner_2       = false;
        
    }
    else {
        
        info1.recipe_category   = RECIPE_CATEGORY_COIN;
        info1.coins_give        = 50 + (random(0,1) * 25) + (random(0,1) * random(0,1) * 25);
        info1.gems_give         = 0;
        info1.is_winner_1       = false;
        info1.is_winner_2       = true;
        
        info2.recipe_category   = RECIPE_CATEGORY_GEM;
        info2.coins_give        = 0;
        info2.gems_give         = 5 + random(0, 1) * 5;
        info2.is_winner_1       = false;
        info2.is_winner_2       = false;
        
        info3.recipe_category   = RECIPE_CATEGORY_COIN;
        info3.coins_give        = 25 + (random(0,1) * random(0,1) * 25);
        info3.gems_give         = 0;
        info3.is_winner_1       = true;
        info3.is_winner_2       = false;
        
        info4.recipe_category   = RECIPE_CATEGORY_KNIFE;
        info4.coins_give        = 0;
        info4.gems_give         = 5 + random(0, 1) * 5;
        info4.is_winner_1       = false;
        info4.is_winner_2       = false;
        
    }
    
    std::vector<objetive_recipe_info>infos;
    infos.push_back(info1);
    infos.push_back(info2);
    infos.push_back(info3);
    infos.push_back(info4);
    
    // fill knife objects with knife ids
    

    
    if (fortune_knifes.size() > 1) {
        int seed = (int)std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(fortune_knifes.begin(), fortune_knifes.end(), std::default_random_engine(seed));
    }
    
    std::vector<int>reserverd_gems_ammount;
    reserverd_gems_ammount.push_back(25);
    reserverd_gems_ammount.push_back(25);
    reserverd_gems_ammount.push_back(25);
    reserverd_gems_ammount.push_back(25);
    
    int seed = (int)std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(reserverd_gems_ammount.begin(), reserverd_gems_ammount.end(), std::default_random_engine(seed));
    
    for (int x=0; x < infos.size(); x++) {
        
        objetive_recipe_info info = infos.at(x);
        
        if (info.recipe_category == RECIPE_CATEGORY_KNIFE) {
            
            if (fortune_knifes.size() > 0) {
                
                SHOP_ITEM knife      = fortune_knifes.at(0);
                infos.at(x).knife_id = knife;
                fortune_knifes.erase(fortune_knifes.begin()+0);
                
            }
            else{
                
                infos.at(x).recipe_category = RECIPE_CATEGORY_GEM;
                infos.at(x).gems_give       = reserverd_gems_ammount.at(0);
                
                reserverd_gems_ammount.erase(reserverd_gems_ammount.begin()+0);
                
            }
        }
    }

    //
    
    for (int x=0; x < infos.size(); x++) {
        
        objetive_recipe_info info = infos.at(x);
        
        if (info.recipe_category == RECIPE_CATEGORY_COIN) {
            infos.at(x).recipe_type = recipes_coin.at(0);
            recipes_coin.erase(recipes_coin.begin()+0);
        }
        else if (info.recipe_category == RECIPE_CATEGORY_GEM) {
            infos.at(x).recipe_type = recipes_gem.at(0);
            recipes_gem.erase(recipes_gem.begin()+0);
        }
        else if (info.recipe_category == RECIPE_CATEGORY_KNIFE) {
            infos.at(x).recipe_type = recipes_knife.at(0);
            recipes_knife.erase(recipes_knife.begin()+0);
        }
        
    }
    
    LevelManager::getInstance()->_data_model->save_coctail_objective(infos);

}

std::vector<SHOP_ITEM> Patterns::is_current_level_have_knife(){
    
    std::vector<SHOP_ITEM> knives;
    
    std::vector<objetive_recipe_info>infos = LevelManager::getInstance()->_data_model->get_saved_cocktails_objectives();
    
    for (int i = 0; i < infos.size(); i++) {
        objetive_recipe_info _info = infos.at(i);
        if (_info.recipe_category == RECIPE_CATEGORY_KNIFE) {
            knives.push_back((SHOP_ITEM)_info.knife_id);
        }
    }
    
    return knives;
}

void Patterns::generate_new_level(){
    
    int level     = LevelManager::get_level_number();
    level++;
    LevelManager::set_level_number(level);
    level_info l  = Patterns::getInstance()->get_new_level(level);
    LevelManager::getInstance()->_data_model->save_level(l);
   
}

level_info Patterns::get_current_level(){
    level_info l = LevelManager::getInstance()->_data_model->getSavedLevel();
    bool debug_level = false;
    if (debug_level) {
        l = get_new_level(1);
    }
    return l;
}

level_info Patterns::get_new_level(int level_number){
    
    level_info l;
    
    auto add_pattern = [&l](int stage,int wave){
        l._patterns.push_back(Patterns::getInstance()->get_pattern_info(stage,wave));
    };
    
    int waves_count = 5;
    
    if (level_number <= 3) {
        waves_count = 3;
    }
    else if (level_number <= 10) {
        waves_count = 4;
    }
    else {
        waves_count = 5;
    }
    
    if (PATTERN_DEBUG_ENABLED) {
        waves_count = PATTERN_DEBUG_WAVES;
    }
    
    for (int x=0; x < waves_count; x++) {
        add_pattern(level_number,x+1);
    }
    
    return l;
    
}

pattern_info Patterns::get_pattern_info(int stage,int wave){
    
    pattern_info p;
    
    gameplay_info gameplay;
    
    gameplay.level = LevelManager::getInstance()->get_level_number();
    gameplay.stage = stage;
    gameplay.wave  = wave;
   
    auto add_point = [&p](float x,float y){
        p._path_points.push_back(Vec2(x, y));
    };
    
    auto add_fruit = [&p](fruit_type fruit){
        fruit_info f;
        f.type = fruit;
        p._fruits.push_back(f);
    };
    
    auto add_action = [&p](float duration, float angle, ACTION_EASE_TYPE ease = EASE_INOUT, float rate = 1.0f){
        action_info action;
        
        action.duration = duration;
        action.angle = angle;
        action.ease = ease;
        action.rate = rate;
        
        p._actions.push_back(action);
    };
    
    int pattern_index = random(0, 3);
    
    // 0
    
    if (PATTERN_DEBUG_ENABLED) {
        pattern_index = PATTERN_DEBUG_NUMBER;
    }
    
    if (pattern_index == 0) {
        
        add_point(25,25);
        add_point(25,50);
        add_point(25,75);
        add_point(50,25);
        add_point(50,50);
        add_point(50,75);
        add_point(75,25);
        add_point(75,50);
        add_point(75,75);

        
        std::vector<fruit_type>fruits = get_fruits(3, gameplay);
        
        fruit_type type_1 = fruits.at(0);
        fruit_type type_2 = fruits.at(1);
        fruit_type type_3 = fruits.at(2);
        
        int fruit_type = random(1,5);
        
        if (PATTERN_DEBUG_ENABLED) {
            fruit_type = gameplay.wave;
        }
        
        if (fruit_type == 1) { // 3 lines

            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_3);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_3);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_3);
            
        }
        else if (fruit_type == 2) { // diagonal
            
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_2);
            add_fruit(type_2);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_2);
            add_fruit(type_2);
            add_fruit(type_1);
        }
        else if (fruit_type == 3) { // cross
            
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_2);
            add_fruit(type_2);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_1);
            
        }
        else if (fruit_type == 4) { // five dice
            
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_1);
            
        }
        else {                      // all the same
            
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            
        }
        
    }
    else if (pattern_index == 1) {
        
        add_point(25,25);
        add_point(50,25);
        add_point(75,25);
        add_point(37.5f,50);
        add_point(62.5f,50);
        add_point(50,75);

        std::vector<fruit_type>fruits = get_fruits(3, gameplay);
        
        fruit_type type_1 = fruits.at(0);
        fruit_type type_2 = fruits.at(1);
        fruit_type type_3 = fruits.at(2);
        
        int fruit_type = random(1, 6);
        
        if (PATTERN_DEBUG_ENABLED) {
            fruit_type = gameplay.wave;
        }
        
        if (fruit_type == 1) {
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_2);
            add_fruit(type_3);
        }
        else if (fruit_type == 2) {
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_2);
            add_fruit(type_1);
        }
        else if (fruit_type == 3) {
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_2);
            add_fruit(type_2);
        }
        else if (fruit_type == 4) {
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_2);
            add_fruit(type_1);
        }
        else if (fruit_type == 5) {
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
        }
        else {
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
        }
        
    }
    else if (pattern_index == 2) {
        
        add_point(37,75);
        add_point(37,50);
        add_point(37,25);
        add_point(63,75);
        add_point(63,50);
        add_point(63,25);
        
        std::vector<fruit_type>fruits = get_fruits(3, gameplay);
        
        fruit_type type_1 = fruits.at(0);
        fruit_type type_2 = fruits.at(1);
        fruit_type type_3 = fruits.at(2);
        
        int fruit_type = random(1,4);
        
        if (PATTERN_DEBUG_ENABLED) {
            fruit_type = gameplay.wave;
        }
        
        if (fruit_type == 1) {
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_2);
            add_fruit(type_2);
        }
        else if (fruit_type == 2) {
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_3);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_3);
        }
        else if (fruit_type == 3) {
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_1);
        }
        else if (fruit_type == 4) {
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
        }
        
    }
    else if (pattern_index == 3) {
        
        p.circle_radius = random(60, 70);

        std::vector<fruit_type>fruits = get_fruits(3, gameplay);
        
        fruit_type type_1 = fruits.at(0);
        fruit_type type_2 = fruits.at(1);
        fruit_type type_3 = fruits.at(2);
        
        int fruit_type = random(1, 9);
        
        if (PATTERN_DEBUG_ENABLED) {
            fruit_type = gameplay.wave;
        }
        
        if (fruit_type == 1) {
            
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_2);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_2);
            
        }
        else if (fruit_type == 2) {
            
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_1);
            add_fruit(type_2);
            
        }
        else if (fruit_type == 3) {
            
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_2);
            
        }
        else if (fruit_type == 4) {
            
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_2);
            
        }
        else if (fruit_type == 5) {
            
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_2);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_2);
            
        }
        else if (fruit_type == 6) {
            
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_2);
            add_fruit(type_2);
            add_fruit(type_2);
            
        }
        else if (fruit_type == 7) {
            
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_3);
            add_fruit(type_2);
            add_fruit(type_1);
            add_fruit(type_2);
            add_fruit(type_3);
            add_fruit(type_2);
            
        }
        else {
            
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            add_fruit(type_1);
            
        }
        
    }
    
    int direction_change = 1;
    if (random(0,1)) {
        direction_change *= -1;
    }
    
    if (PATTERN_DEBUG_ROTATION) {
        
        int randomDuration = random(1.25f, 1.75f);
                              
        add_action(randomDuration, random(120,160) * direction_change, EASE_INOUT, 2.5f);
        add_action(randomDuration, random(240,320) * direction_change, EASE_INOUT, 2.5f);
        
    }
    else if (gameplay.level <= 3) {
        if (gameplay.wave == 3) {
            int randomVar = random(420,540) * direction_change;
            
            add_action(random(2.75f, 3.75f), randomVar, EASE_INOUT, 2.5f);
            add_action(random(2.75f, 3.75f), -randomVar, EASE_INOUT, 2.5f);
        }
        else if (random(0,2) > 0) {
            add_action(random(2.25f, 3.f), 360 * direction_change, EASE_INOUT, 1.0f);
        }
        else {
            add_action(random(2.5f, 3.25f), 360 * direction_change, EASE_INOUT, 2.0f);
        }
    }
    else if (gameplay.level <= 5) {
        if (gameplay.wave == 3) {
            int randomVar = random(420,540) * direction_change;
            
            add_action(random(2.25f, 2.75f), randomVar, EASE_INOUT, 2.5f);
            add_action(random(2.25f, 2.75f), -randomVar, EASE_INOUT, 2.5f);
        }
        else if (random(0,2) > 0) {
            add_action(random(2.f, 2.5f), 360 * direction_change, EASE_INOUT, 1.0f);
        }
        else {
            add_action(random(2.f, 2.5f), 360 * direction_change, EASE_INOUT, 2.0f);
        }
    }
    else if (wave >= 5 && random(0,1)) {
        add_action(random(3.f, 3.5f), random(620,740) * direction_change, EASE_INOUT, 2.5f);
    }
    else if (wave >= 5 && random(0,1)) {
        add_action(random(4.f, 5.f), random(900,1000) * direction_change, EASE_INOUT, 2.f);
    }
    else if (wave >= 5 && random(0,1)) {
        add_action(random(1.f, 1.5f), random(150,210) * direction_change, EASE_INOUT, 2.5f);
    }
    else if (wave >= 5 && random(0,1)) {
        int randomDuration = random(1.5f, 2.f);
        
        add_action(randomDuration, random(120,160) * direction_change, EASE_INOUT, 2.25f);
        add_action(randomDuration, random(240,320) * direction_change, EASE_INOUT, 2.25f);
    }
    else if (wave >= 4 && random(0,1)) {
        int randomVar = random(150,210) * direction_change;
        
        add_action(random(1.f, 1.5f), randomVar, EASE_INOUT, 2.5f);
        add_action(random(1.f, 1.5f), randomVar, EASE_INOUT, 2.5f);
        add_action(random(1.f, 1.5f), (-1) * randomVar, EASE_INOUT, 2.5f);
    }
    else if (wave >= 4 && random(0,1)) {
        add_action(random(2.f, 2.5f), random(420,540) * direction_change, EASE_INOUT, 2.5f);
    }
    else if (wave >= 3 && random(0,1)) {
        add_action(random(3.25f, 4.25f), random(800,900) * direction_change, EASE_INOUT, 2.f);
    }
    else if (wave >= 3 && random(0,1)) {
        add_action(random(1.f, 1.25f), random(200,250) * direction_change, EASE_INOUT, 2.5f);
    }
    else if (wave >= 2 && random(0,1)) {
        int randomVar = random(420,540) * direction_change;
        
        add_action(random(1.75f, 2.75f), randomVar, EASE_INOUT, 2.5f);
        add_action(random(1.75f, 2.75f), -randomVar, EASE_INOUT, 2.5f);
    }
    else if (wave >= 2 && random(0,1)) {
        add_action(random(4.f, 4.5f), random(800,900) * direction_change, EASE_INOUT, 2.f);
    }
    else if (random(0,2) > 0) {
        add_action(random(1.75f, 2.5f), 360 * direction_change, EASE_INOUT, 1.0f);
    }
    else {
        add_action(random(1.75f, 2.5f), 360 * direction_change, EASE_INOUT, 2.0f);
    }

    return p;
    
}

Pattern * Patterns::get_pattern(pattern_info p_info){
    
    Pattern * p      = Pattern::create();
    auto add_action  = [p](float duration, float angle, ACTION_EASE_TYPE ease = EASE_INOUT, float rate = 1.0f){
        
        ActionInterval * action = RotateBy::create(duration, angle);
        
        if (ease != EASE_NONE) {
            if (ease == EASE_INOUT) {
                action = EaseInOut::create(action, rate);
            }
        }
        
        p->actions.push_back(action);
        
    };

    if (p_info.circle_radius == 0) {
        for (int x=0; x < p_info._path_points.size(); x++) {
            Vec2 point = p_info._path_points.at(x);
            p->add_point(point.x, point.y);
        }
    }
    else{
        p->add_circle(p_info.circle_radius, (int)p_info._fruits.size());
    }

    for (int x=0; x < p_info._fruits.size(); x++) {
        fruit_type f = p_info._fruits.at(x).type;
        p->fruits.push_back(f);
    }
    
    for (int x=0; x < p_info._actions.size(); x++) {
        action_info a = p_info._actions.at(x);
        add_action(a.duration,a.angle,a.ease,a.rate);
    }
    
    return p;
}
















fruit_type Patterns::get_random_fruit(gameplay_info gameplay){
    
    std::vector<fruit_type>fruits = get_fruits(10,gameplay);
    int                    index  = random(0, (int)fruits.size()-1);
    fruit_type type               = fruits.at(index);
    return type;
    
}

std::vector<fruit_type>Patterns::get_fruits(int max_size,gameplay_info gameplay){
    
    // rules for fruits in pattern
    
    std::vector<fruit_type>fruits;
    
    std::vector<fruit_type>available_fruits;
    
    int fruit_type_roll_chance = gameplay.fruit_type_roll;
    
    available_fruits.push_back(fruit_type_watermelon);
    available_fruits.push_back(fruit_type_orange);
    available_fruits.push_back(fruit_type_lemon);
    
    int apple_chance        = 50;
    int pineapple_chance    = 40;
    int kivi_chance         = 30;
    int mango_chance        = 20;
    
    int spawn_rule_modifier = 0;
    
    if (gameplay.wave <= 1) {
        
        spawn_rule_modifier = 0;
        
        // no additional chance
        
    }
    else if (gameplay.wave <= 2) {
        
        spawn_rule_modifier = 10;

    }
    else if (gameplay.wave <= 3) {
        
        spawn_rule_modifier = 20;
        
    }
    else if (gameplay.wave <= 4) {
        
        spawn_rule_modifier = 30;
        
    }
    else if (gameplay.wave <= 5) {
        
        spawn_rule_modifier = 40;
        
    }
    else {
        
        spawn_rule_modifier = 50;
        
    }
    
    apple_chance     += spawn_rule_modifier;
    pineapple_chance += spawn_rule_modifier;
    kivi_chance      += spawn_rule_modifier;
    mango_chance     += spawn_rule_modifier;

    if (gameplay.stage < 2) {
        apple_chance = 0;
    }
    if (gameplay.stage < 5) {
        pineapple_chance = 0;
    }
    if (gameplay.stage < 10) {
        kivi_chance = 0;
    }
    if (gameplay.stage < 20) {
        mango_chance = 0;
    }
    
    if (apple_chance > fruit_type_roll_chance) {
        available_fruits.push_back(fruit_type_apple);
    }
    if (pineapple_chance > fruit_type_roll_chance) {
        available_fruits.push_back(fruit_type_pineapple);
    }
    if (kivi_chance > fruit_type_roll_chance) {
        available_fruits.push_back(fruit_type_kivi);
    }
    if (mango_chance > fruit_type_roll_chance) {
        available_fruits.push_back(fruit_type_mango);
    }
    
    if (max_size > available_fruits.size()) {
        if (random(0,1)) {
            available_fruits.push_back(fruit_type_watermelon);
        }
        else {
            available_fruits.push_back(fruit_type_orange);
        }
    }
    
    int seed = (int)std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(available_fruits.begin(), available_fruits.end(), std::default_random_engine(seed));
    
    for (int x=0; x < max_size; x++) {
        //int index                 = random(0, (int)available_fruits.size()-1);
        fruit_type fruit_to_spawn = available_fruits.at(x); //index);
        fruits.push_back(fruit_to_spawn);
    }
    
   // fruits[fruits.size()-1] = fruit_type_none;
    
    // shuffle

    return fruits;
    
}
