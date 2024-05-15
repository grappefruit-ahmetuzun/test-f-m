//
//  Mixer.h
//  FruitsKnife-mobile
//
//  Created by Slavik on 5/22/18.
//

#ifndef Mixer_h
#define Mixer_h

#include "cocos2d.h"
#include "Game.h"
#include "Space.h"
#include "Recipes.h"

USING_NS_CC;

class Mixer : public Sprite{
    
public:
    
    Mixer(){}
    
    CREATE_FUNC(Mixer);
    
    void prepare(Size size);
    
    SkeletonAnimation * _mixer_spine = nullptr;
    
    void changeMixerFilledSegments(int segments, fruit_type _f_type);
    
    void mixNow(RECIPE_TYPES _receipe);
    
    int current_segment = 0;
    
    RECIPE_TYPES _receipe_type     = RECIPE_DEFAULT;
    fruit_type   _next_fruit_type  = fruit_type_unknown;
    
    std::function<void(RECIPE_TYPES)> get_coctail = nullptr;
    
private:
    
    void setSegmentsCount(int count);
    
};

#endif /* Mixer_h */
