//
//  Recipes.hpp
//  FruitsKnife-mobile
//
//  Created by Marek on 22/05/2018.
//

#ifndef Recipes_hpp
#define Recipes_hpp

#include "SPUserDefault.h"
#include "Game.h"
#include "PlatformManager.h"
#include "Pattern.h"

USING_NS_CC;

struct recipe_info{
    
    RECIPE_TYPES type        = RECIPE_DEFAULT;
    std::string name         = "UNKNOWN";
    std::string texture_name = "coctails/standart_cocktail.png";
    float coctail_scale      = 1.0f;
    int coin_reward          = 1;
    
    std::vector<fruit_type> _fruits;
    
    std::vector<fruit_type>      _missions_requirement_types;
    std::vector<int>             _missions_requirement_count;
    
    void add_mission_requirement(fruit_type type,int count){
        _missions_requirement_types.push_back(type);
        _missions_requirement_count.push_back(count);
    }
    
    int get_mission_requirement(fruit_type type){
        
        for (int x=0; x<_missions_requirement_count.size();x++){
            fruit_type fruit = _missions_requirement_types.at(x);
            if (fruit == type){
                int count = _missions_requirement_count.at(x);
                return count;
            }
        }
        
        return 10;
    }
    
};

class Recipes{
    
public:
    
    static std::vector<objetive_recipe_info>    get_objective_recipes   ();
    static std::vector<RECIPE_CATEGORY>         get_recipe_categories   ();
    static RECIPE_CATEGORY                      get_recipe_category     (RECIPE_TYPES recipe);
    static Color3B                              get_recipe_color        (RECIPE_CATEGORY category);
    static RECIPE_TYPES                         getRandomRecipe         (RECIPE_CATEGORY category);
    static std::vector<RECIPE_TYPES>            get_recipes             (RECIPE_CATEGORY category);
    static recipe_info                          getReceipe              (RECIPE_TYPES type);
    static recipe_info                          check_receipe           (std::vector<fruit_type>fruits);
    static Color3B                              getColorByfruitType     (fruit_type _type);
    static std::string                          get_spine_slot_name     (fruit_type _type);
    static std::string                          get_splash_skin_name    (fruit_type _type);
    
};

#endif /* Recipes_hpp */
