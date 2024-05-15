//
//  Coctail.h
//  FruitsKnife-mobile
//
//  Created by Slavik on 5/22/18.
//

#ifndef Coctail_h
#define Coctail_h

#include "cocos2d.h"
#include "Game.h"
#include "Space.h"
#include "Recipes.h"

USING_NS_CC;

class Coctail : public Sprite {
    
public:
    
    Coctail(){}
    
    CREATE_FUNC(Coctail);
    
    void prepare(Size size, RECIPE_TYPES _type);
    
    RECIPE_TYPES _coctail_type = RECIPE_DEFAULT;
    
    Sprite * coctail_spr = nullptr;
    
private:
    
};

#endif /* Coctail_h */
