//
//  Recipes.cpp
//  FruitsKnife-mobile
//
//  Created by Marek on 22/05/2018.
//

#include "Recipes.h"
#include "Shop.h"
#include "LevelManager.h"

std::vector<objetive_recipe_info> Recipes::get_objective_recipes   (){
    
    std::vector<objetive_recipe_info>infos = LevelManager::getInstance()->_data_model->get_saved_cocktails_objectives();
    
    
    
    return infos;

}

std::vector<RECIPE_CATEGORY> Recipes::get_recipe_categories   (){
    
    std::vector<RECIPE_CATEGORY> cat;
    
    cat.push_back(RECIPE_CATEGORY_COIN);
    cat.push_back(RECIPE_CATEGORY_GEM);
    cat.push_back(RECIPE_CATEGORY_KNIFE);
    
    return cat;
}

Color3B Recipes::get_recipe_color(RECIPE_CATEGORY category){
    Color3B color = Color3B::YELLOW;
    
    switch (category) {
            
        case RECIPE_CATEGORY_COIN:      color = Color3B(254, 209, 56);  break;
        case RECIPE_CATEGORY_GEM:       color = Color3B(52,189,252);    break;
        case RECIPE_CATEGORY_KNIFE:     color = Color3B(250,119,217);   break;
            
        default:
            break;
    }
    
    return color;
}

RECIPE_CATEGORY Recipes::get_recipe_category     (RECIPE_TYPES recipe){
    
    std::vector<RECIPE_CATEGORY> categories = get_recipe_categories();
    
    for (int x=0; x < categories.size(); x++) {
        
        RECIPE_CATEGORY cat               = categories.at(x);
        std::vector<RECIPE_TYPES> recipes = get_recipes(cat);
        
        for (RECIPE_TYPES type : recipes) {
            if (type == recipe) {
                return cat;
            }
        }
        
    }
    
    return RECIPE_CATEGORY_COIN;
}

RECIPE_TYPES Recipes::getRandomRecipe(RECIPE_CATEGORY category){
    std::vector<RECIPE_TYPES> recipes = get_recipes(category);
    int index                         = random(0, (int)recipes.size()-1);
    return recipes.at(index);
}

std::vector<RECIPE_TYPES>Recipes::get_recipes(RECIPE_CATEGORY category){
    
    std::vector<RECIPE_TYPES> recipes;

    if (category == RECIPE_CATEGORY_COIN || category == RECIPE_CATEGORY_RANDOM){
        
        recipes.push_back(RECIPE_SUGAR_RUSH);
        recipes.push_back(RECIPE_SUNNY_BREEZE);
        recipes.push_back(RECIPE_SATISFACTION);
        recipes.push_back(RECIPE_SOUR_CRUSH);
        recipes.push_back(RECIPE_YUMMY_PUNCH);
        recipes.push_back(RECIPE_WATERLEMON);
        recipes.push_back(RECIPE_JUNGLE_SQUASH);
        
    }
    
     if (category == RECIPE_CATEGORY_GEM || category == RECIPE_CATEGORY_RANDOM){
         
         recipes.push_back(RECIPE_LEGENDARY_DUO);
         recipes.push_back(RECIPE_TRIPLE_SMILE);
         recipes.push_back(RECIPE_FRESH_MATCH);
         recipes.push_back(RECIPE_COOL_SPIKES);
         recipes.push_back(RECIPE_HAPPY_MIX);
         recipes.push_back(RECIPE_SIMPLE_IS_BEST);
         recipes.push_back(RECIPE_PERFECT_MORNING);
         recipes.push_back(RECIPE_MUNCHY_CRUNCHY);
         
     }
    
    if (category == RECIPE_CATEGORY_KNIFE || category == RECIPE_CATEGORY_RANDOM){
        
        recipes.push_back(RECIPE_KICKSTART);
        recipes.push_back(RECIPE_HIGH_END);
        recipes.push_back(RECIPE_TRIBAL_BLEND);
        recipes.push_back(RECIPE_SO_GOOD);
        recipes.push_back(RECIPE_GROOVY_BEAT);
        recipes.push_back(RECIPE_FREEZING_STING);
        recipes.push_back(RECIPE_ICEBREAKER);
        recipes.push_back(RECIPE_THE_TWISTER);
        recipes.push_back(RECIPE_WOOPY_MUSH);
        recipes.push_back(RECIPE_WHAT);
        
    }

    return recipes;
}

recipe_info Recipes::getReceipe(RECIPE_TYPES type){
    
    recipe_info recipe;
    recipe.type = type;
    
    switch (type) {
            
        case RECIPE_DEFAULT:
        {
            recipe.texture_name = "coctails/standart_cocktail.png";
            recipe.coctail_scale = 0.75f;
            recipe.coin_reward = 1;
            
        }
            break;
            
        case RECIPE_SUGAR_RUSH:
        {
            
            recipe.name = "SUGAR RUSH";
            recipe.coin_reward = 5;
            
            recipe._fruits.push_back(fruit_type_watermelon);
            recipe._fruits.push_back(fruit_type_watermelon);
            recipe._fruits.push_back(fruit_type_watermelon);
            
            recipe.add_mission_requirement(fruit_type_watermelon, 25);
        
            recipe.texture_name = "coctails/1_SUGAR_RUSH.png";
            recipe.coctail_scale = 0.95f;
            
        }
            break;
            
        case RECIPE_SUNNY_BREEZE:
        {
            
            recipe.name = "SUNNY BREEZE";
            recipe.coin_reward = 5;
            
            recipe._fruits.push_back(fruit_type_orange);
            recipe._fruits.push_back(fruit_type_orange);
            recipe._fruits.push_back(fruit_type_lemon);
            
            recipe.add_mission_requirement(fruit_type_orange, 35);
            recipe.add_mission_requirement(fruit_type_lemon, 25);
            
            recipe.texture_name  = "coctails/2_SUNNY_BREEZE.png";
            recipe.coctail_scale = 1.2f;
        }
            break;
            
        case RECIPE_SATISFACTION:
        {
            
            recipe.name = "SATISFACTION";
            recipe.coin_reward = 5;
            
            recipe._fruits.push_back(fruit_type_orange);
            recipe._fruits.push_back(fruit_type_lemon);
            recipe._fruits.push_back(fruit_type_apple);
            
            recipe.add_mission_requirement(fruit_type_orange, 25);
            recipe.add_mission_requirement(fruit_type_lemon, 25);
            recipe.add_mission_requirement(fruit_type_apple, 25);
            
            recipe.texture_name = "coctails/5_SATISFACTION.png";
            recipe.coctail_scale = 1.f;
            
        }
            break;
            
        case RECIPE_SOUR_CRUSH:
        {
            
            recipe.name = "LEMONZILLA";
            recipe.coin_reward = 5;
            
            recipe._fruits.push_back(fruit_type_lemon);
            recipe._fruits.push_back(fruit_type_lemon);
            recipe._fruits.push_back(fruit_type_lemon);
            
            recipe.add_mission_requirement(fruit_type_lemon, 75);
            
            recipe.texture_name = "coctails/12_LEMONZILLA.png";
            recipe.coctail_scale = 1.2f;
            
        }
            break;
            
        case RECIPE_YUMMY_PUNCH:
        {
            
            recipe.name = "YUMMY PUNCH";
            recipe.coin_reward = 5;
            
            recipe._fruits.push_back(fruit_type_orange);
            recipe._fruits.push_back(fruit_type_apple);
            recipe._fruits.push_back(fruit_type_pineapple);
            
            recipe.add_mission_requirement(fruit_type_orange,    50);
            recipe.add_mission_requirement(fruit_type_apple,     25);
            recipe.add_mission_requirement(fruit_type_pineapple, 25);
            
            
            recipe.texture_name = "coctails/3_YUMMY_PUNCH.png";
            recipe.coctail_scale = 1.25f;
            
        }
            break;
        
        case RECIPE_WATERLEMON:
        {
            
            recipe.name = "WATER-LEMON";
            recipe.coin_reward = 10;
            
            recipe._fruits.push_back(fruit_type_watermelon);
            recipe._fruits.push_back(fruit_type_lemon);
            
            recipe.add_mission_requirement(fruit_type_watermelon, 30);
            recipe.add_mission_requirement(fruit_type_lemon, 30);
            
            recipe.texture_name  = "coctails/4_WATERLEMON.png";
            recipe.coctail_scale = 0.95f;
            
        }
            break;

        case RECIPE_JUNGLE_SQUASH:
        {
            
            recipe.name = "JUNGLE SQUASH";
            recipe.coin_reward = 10;
            
            recipe._fruits.push_back(fruit_type_watermelon);
            recipe._fruits.push_back(fruit_type_orange);
            recipe._fruits.push_back(fruit_type_pineapple);
            
            recipe.add_mission_requirement(fruit_type_watermelon,    30);
            recipe.add_mission_requirement(fruit_type_orange,     30);
            recipe.add_mission_requirement(fruit_type_pineapple, 30);
            
            recipe.texture_name = "coctails/6_JUNGLE_SQUASH.png";
            recipe.coctail_scale = 0.6f;
            
        }
            break;
            
        case RECIPE_LEGENDARY_DUO:
        {
            
            recipe.name = "LEGENDARY DUO";
            recipe.coin_reward = 10;
            
            recipe._fruits.push_back(fruit_type_pineapple);
            recipe._fruits.push_back(fruit_type_apple);
            
            recipe.add_mission_requirement(fruit_type_pineapple,    50);
            recipe.add_mission_requirement(fruit_type_apple,     50);
            
            recipe.texture_name = "coctails/7_LEGENDARY_DUO.png";
            recipe.coctail_scale = 1.05f;
            
        }
            break;
            
        case RECIPE_FRESH_MATCH:
        {
            
            recipe.name = "FRESH MATCH";
            recipe.coin_reward = 10;
            
            recipe._fruits.push_back(fruit_type_watermelon);
            recipe._fruits.push_back(fruit_type_orange);
            recipe._fruits.push_back(fruit_type_apple);
            
            recipe.add_mission_requirement(fruit_type_watermelon,    50);
            recipe.add_mission_requirement(fruit_type_orange,     50);
            recipe.add_mission_requirement(fruit_type_apple,     25);
            
            recipe.texture_name = "coctails/8_FRESH_MATCH.png";
            recipe.coctail_scale = 0.9f;
            
        }
            break;
            
            
        case RECIPE_TRIPLE_SMILE:
        {
            
            recipe.name = "TRIPLE SMILE";
            recipe.coin_reward = 10;
            
            recipe._fruits.push_back(fruit_type_watermelon);
            recipe._fruits.push_back(fruit_type_pineapple);
            recipe._fruits.push_back(fruit_type_kivi);
            
            recipe.add_mission_requirement(fruit_type_watermelon,    33);
            recipe.add_mission_requirement(fruit_type_pineapple,     33);
            recipe.add_mission_requirement(fruit_type_kivi,         33);
            
            recipe.texture_name = "coctails/14_TRIPLE_SMILE.png";
            recipe.coctail_scale = 1.f;
            
        }
            break;
            
        case RECIPE_COOL_SPIKES:
        {
            
            recipe.name = "COOL SPIKES";
            recipe.coin_reward = 15;
            
            recipe._fruits.push_back(fruit_type_watermelon);
            recipe._fruits.push_back(fruit_type_lemon);
            recipe._fruits.push_back(fruit_type_pineapple);
            
            recipe.add_mission_requirement(fruit_type_watermelon,    25);
            recipe.add_mission_requirement(fruit_type_lemon,     75);
            recipe.add_mission_requirement(fruit_type_pineapple,     50);
            
            recipe.texture_name = "coctails/9_COOL_SPIKES.png";
            recipe.coctail_scale = 1.f;
            
        }
            break;
            
            
        case RECIPE_HAPPY_MIX:
        {
            
            recipe.name = "HAPPY MIX";
            recipe.coin_reward = 15;
            
            recipe._fruits.push_back(fruit_type_lemon);
            recipe._fruits.push_back(fruit_type_apple);
            recipe._fruits.push_back(fruit_type_pineapple);
            
            recipe.add_mission_requirement(fruit_type_lemon,        30);
            recipe.add_mission_requirement(fruit_type_apple,        50);
            recipe.add_mission_requirement(fruit_type_pineapple,    70);
            
            recipe.texture_name = "coctails/10_HAPPY_MIX.png";
            recipe.coctail_scale = 0.9f;
            
        }
            break;
            
            
        case RECIPE_SIMPLE_IS_BEST:
        {
            
            recipe.name = "AMAZANGA";
            recipe.coin_reward = 15;
            
            recipe._fruits.push_back(fruit_type_orange);
            recipe._fruits.push_back(fruit_type_pineapple);
            recipe._fruits.push_back(fruit_type_kivi);
            
            
            recipe.add_mission_requirement(fruit_type_orange,        30);
            recipe.add_mission_requirement(fruit_type_pineapple,     70);
            recipe.add_mission_requirement(fruit_type_kivi,        30);
            
            recipe.texture_name = "coctails/11_AMAZANGA.png";
            recipe.coctail_scale = 1.f;
            
        }
            break;

        case RECIPE_PERFECT_MORNING:
        {
            
            recipe.name = "PERFECT MORNING";
            recipe.coin_reward = 15;
            
            recipe._fruits.push_back(fruit_type_watermelon);
            recipe._fruits.push_back(fruit_type_lemon);
            recipe._fruits.push_back(fruit_type_kivi);
            
            recipe.add_mission_requirement(fruit_type_watermelon,        75);
            recipe.add_mission_requirement(fruit_type_lemon,             25);
            recipe.add_mission_requirement(fruit_type_kivi,             50);
            
            recipe.texture_name = "coctails/15_PERFECT_MORNING.png";
            recipe.coctail_scale = 1.f;
            
        }
            break;
            
        case RECIPE_MUNCHY_CRUNCHY:
        {
            
            recipe.name = "MUNCHY CRUNCHY";
            recipe.coin_reward = 15;
            
            recipe._fruits.push_back(fruit_type_orange);
            recipe._fruits.push_back(fruit_type_apple);
            recipe._fruits.push_back(fruit_type_mango);
            
            recipe.add_mission_requirement(fruit_type_orange,    50);
            recipe.add_mission_requirement(fruit_type_apple,     50);
            recipe.add_mission_requirement(fruit_type_mango,    25);
            
            recipe.texture_name = "coctails/16_MUNCHY_CRUNCHY.png";
            recipe.coctail_scale = 1.f;
            
        }
            break;
            
        case RECIPE_KICKSTART:
        {
            
            recipe.name = "KICKSTART";
            recipe.coin_reward = 20;
            
            recipe._fruits.push_back(fruit_type_orange);
            recipe._fruits.push_back(fruit_type_apple);
            recipe._fruits.push_back(fruit_type_kivi);
            
            recipe.add_mission_requirement(fruit_type_orange,        30);
            recipe.add_mission_requirement(fruit_type_apple,         50);
            recipe.add_mission_requirement(fruit_type_kivi,        70);
            
            recipe.texture_name = "coctails/13_KICKSTART.png";
            recipe.coctail_scale = 1.15f;
            
        }
            break;
            
        case RECIPE_HIGH_END:
        {
            
            recipe.name = "HIGH END";
            recipe.coin_reward = 20;
            
            recipe._fruits.push_back(fruit_type_pineapple);
            recipe._fruits.push_back(fruit_type_kivi);
            recipe._fruits.push_back(fruit_type_mango);
            
            recipe.add_mission_requirement(fruit_type_pineapple,    50);
            recipe.add_mission_requirement(fruit_type_kivi,         50);
            recipe.add_mission_requirement(fruit_type_mango,       50);
            
            recipe.texture_name = "coctails/17_HIGH_END.png";
            recipe.coctail_scale = 1.2f;
            
        }
            break;
            
            
        case RECIPE_TRIBAL_BLEND:
        {
            
            recipe.name = "TRIBAL BLEND";
            recipe.coin_reward = 20;
            
            recipe._fruits.push_back(fruit_type_lemon);
            recipe._fruits.push_back(fruit_type_pineapple);
            recipe._fruits.push_back(fruit_type_mango);
            
            recipe.add_mission_requirement(fruit_type_lemon,        25);
            recipe.add_mission_requirement(fruit_type_pineapple,    50);
            recipe.add_mission_requirement(fruit_type_mango,       75);
            
            recipe.texture_name = "coctails/18_TRIBAL_BLEND.png";
            recipe.coctail_scale = 1.25f;
        
        }
            break;
            
            
        case RECIPE_SO_GOOD:
        {
            
            recipe.name = "SO GOOD";
            recipe.coin_reward = 20;
            
            recipe._fruits.push_back(fruit_type_watermelon);
            recipe._fruits.push_back(fruit_type_orange);
            recipe._fruits.push_back(fruit_type_mango);
            
            recipe.add_mission_requirement(fruit_type_watermelon,        50);
            recipe.add_mission_requirement(fruit_type_orange,            100);
            recipe.add_mission_requirement(fruit_type_mango,            25);
            
            recipe.texture_name = "coctails/19_SO_GOOD.png";
            recipe.coctail_scale = 0.8f;
        
        }
            break;
            
            
        case RECIPE_GROOVY_BEAT:
        {
            
            recipe.name = "GROOVY BEAT";
            recipe.coin_reward = 20;
            
            recipe._fruits.push_back(fruit_type_apple);
            recipe._fruits.push_back(fruit_type_pineapple);
            recipe._fruits.push_back(fruit_type_mango);
            
            recipe.add_mission_requirement(fruit_type_apple,             75);
            recipe.add_mission_requirement(fruit_type_pineapple,         50);
            recipe.add_mission_requirement(fruit_type_mango,            100);
            
            recipe.texture_name = "coctails/20_GROOVY_BEAT.png";
            recipe.coctail_scale = 1.15f;
            
        }
            break;
            
            
        case RECIPE_FREEZING_STING:
        {
            
            recipe.name = "FREEZING STING";
            recipe.coin_reward = 25;
            
            recipe._fruits.push_back(fruit_type_lemon);
            recipe._fruits.push_back(fruit_type_pineapple);
            recipe._fruits.push_back(fruit_type_kivi);
            
            recipe.add_mission_requirement(fruit_type_lemon,             75);
            recipe.add_mission_requirement(fruit_type_pineapple,         50);
            recipe.add_mission_requirement(fruit_type_kivi,            100);
            
            recipe.texture_name = "coctails/21_FREEZING_STING.png";
            recipe.coctail_scale = 1.2f;
            
        }
            break;
            
            
        case RECIPE_ICEBREAKER:
        {
            
            recipe.name = "ICEBREAKER";
            recipe.coin_reward = 25;
            
            recipe._fruits.push_back(fruit_type_orange);
            recipe._fruits.push_back(fruit_type_apple);
            recipe._fruits.push_back(fruit_type_mango);
            
            recipe.add_mission_requirement(fruit_type_orange,        100);
            recipe.add_mission_requirement(fruit_type_apple,         50);
            recipe.add_mission_requirement(fruit_type_mango,        150);
            
            recipe.texture_name = "coctails/22_ICE_BREAKER.png";
            recipe.coctail_scale = 1.05f;
            
        }
            break;
            
            
        case RECIPE_THE_TWISTER:
        {
            
            recipe.name = "THE TWISTER";
            recipe.coin_reward = 25;
            
            recipe._fruits.push_back(fruit_type_watermelon);
            recipe._fruits.push_back(fruit_type_lemon);
            recipe._fruits.push_back(fruit_type_kivi);
            
            recipe.add_mission_requirement(fruit_type_watermelon,    100);
            recipe.add_mission_requirement(fruit_type_lemon,         150);
            recipe.add_mission_requirement(fruit_type_kivi,         100);
            
            recipe.texture_name = "coctails/23_THE_TWISTER.png";
            recipe.coctail_scale = 1.1f;
            
        }
            break;
            
            
        case RECIPE_WOOPY_MUSH:
        {
            
            recipe.name = "WOOPY MUSH";
            recipe.coin_reward = 25;
            
            recipe._fruits.push_back(fruit_type_orange);
            recipe._fruits.push_back(fruit_type_kivi);
            recipe._fruits.push_back(fruit_type_mango);
            
            recipe.add_mission_requirement(fruit_type_orange,    150);
            recipe.add_mission_requirement(fruit_type_kivi,      50);
            recipe.add_mission_requirement(fruit_type_mango,     150);
            
            recipe.texture_name = "coctails/24_WOOPY_MUSH.png";
            recipe.coctail_scale = 1.f;
            
        }
            break;
            
            
        case RECIPE_WHAT:
        {
            
            recipe.name = "WHAT?";
            recipe.coin_reward = 25;
            
            recipe._fruits.push_back(fruit_type_watermelon);
            recipe._fruits.push_back(fruit_type_kivi);
            recipe._fruits.push_back(fruit_type_mango);
            
            recipe.add_mission_requirement(fruit_type_watermelon,    200);
            recipe.add_mission_requirement(fruit_type_kivi,          200);
            recipe.add_mission_requirement(fruit_type_mango,         75);
            
            recipe.texture_name = "coctails/25_WHAT.png";
            recipe.coctail_scale = 1.25f;
            
        }
            break;
            
        default:
            break;
    }
    
    return recipe;
}

recipe_info Recipes::check_receipe(std::vector<fruit_type>fruits){
    
    // erase the same type fruits
    
    sort( fruits.begin(), fruits.end() );
    fruits.erase( unique( fruits.begin(), fruits.end() ), fruits.end() );
    
    //
    
    recipe_info recipe_output;
    recipe_output.type = RECIPE_DEFAULT;
    
    std::vector<RECIPE_TYPES> recipes = get_recipes(RECIPE_CATEGORY_RANDOM);
    
    for (int x=0; x < recipes.size(); x++) {
        
        std::vector<fruit_type> fruits_copy;
        
        for (fruit_type f : fruits) {
            fruits_copy.push_back(f);
        }
        
        recipe_info recipe = getReceipe(recipes.at(x));
        
        if (recipe._fruits.size() != fruits.size()) {
            continue;
        }
        
        for (int f = 0; f < recipe._fruits.size(); f++) {
            
            fruit_type recipe_fruit = recipe._fruits.at(f);
            
            for (int e = 0; e < fruits_copy.size(); e++) {
                fruit_type mixer_fruit = fruits_copy.at(e);
                if (recipe_fruit == mixer_fruit) {
                    fruits_copy.erase(fruits_copy.begin()+e);
                    break;
                }
            }
            
        }
        
        if (fruits_copy.size() == 0) {
            // found a recipe;
            return recipe;
        }
        
    }
    
    return recipe_output;
}

Color3B Recipes::getColorByfruitType(fruit_type _type){
    Color3B color = Color3B(255, 255, 255);
    
    switch (_type) {
        case fruit_type_watermelon:     color = Color3B(225, 71, 88);   break;
        case fruit_type_orange:         color = Color3B(235, 144, 57);  break;
        case fruit_type_lemon:          color = Color3B(249, 233, 81);  break;
        case fruit_type_apple:          color = Color3B(253, 250, 221); break;
        case fruit_type_kivi:           color = Color3B(143, 217, 73);  break;
        case fruit_type_pineapple:      color = Color3B(250, 238, 158); break;
        case fruit_type_mango:          color = Color3B(249, 225, 77);  break;
            
        default: break;
    }
    
    return color;
}

std::string Recipes::get_spine_slot_name(fruit_type _type){
    
    switch (_type) {
        case fruit_type_watermelon:     return "watermelon";
        case fruit_type_orange:         return "orange";
        case fruit_type_lemon:          return "lemon";
        case fruit_type_apple:          return "apple";
        case fruit_type_kivi:           return "kivi";
        case fruit_type_pineapple:      return "pineapple";
        case fruit_type_mango:          return "mango";
            
        default: break;
    }
    
    return "off";
}

std::string Recipes::get_splash_skin_name(fruit_type _type){
    switch (_type) {
        case fruit_type_watermelon:     return "watermelon";
        case fruit_type_orange:         return "orange";
        case fruit_type_lemon:          return "lemon";
        case fruit_type_apple:          return "apple";
        case fruit_type_kivi:           return "kivi";
        case fruit_type_pineapple:      return "pineapple";
        case fruit_type_mango:          return "mango";
            
        default: break;
    }
    
    return "pineapple";
}
