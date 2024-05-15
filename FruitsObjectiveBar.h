//
//  FruitsObjectiveBar.hpp
//  FruitsKnife-mobile
//
//  Created by Marek on 28/05/2018.
//

#ifndef FruitsObjectiveBar_hpp
#define FruitsObjectiveBar_hpp

#include "cocos2d.h"
#include "SoundDirector.h"
#include "Recipes.h"
#include "Game.h"

USING_NS_CC;

class FruitsObjectiveBar : public Sprite{
    
public:
    
    FruitsObjectiveBar()
    {}
    
    CREATE_FUNC(FruitsObjectiveBar);
    
    void prepare(recipe_info recipe,float height);
    
    std::vector<Sprite *>cells;
    
    recipe_info _recipe;
    
    void refresh_all_count_labels();
    
private:
    
    std::string getFruitIcon(fruit_type f_type);
    
};

#endif /* FruitsObjectiveBar_hpp */
