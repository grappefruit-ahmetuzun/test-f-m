//
//  CoctailNameField.h
//  FruitsKnife-mobile
//
//  Created by Slavik on 5/24/18.
//

#ifndef CoctailNameField_h
#define CoctailNameField_h

#include "cocos2d.h"
#include "Game.h"
#include "Space.h"
#include "Recipes.h"

USING_NS_CC;

class CoctailNameField : public Sprite {
    
public:
    
    CoctailNameField(){}
    
    CREATE_FUNC(CoctailNameField);
    
    void prepare(Size size, RECIPE_TYPES _type);
    
    RECIPE_TYPES _coctail_type = RECIPE_DEFAULT;
    
private:
    
};

#endif /* CoctailNameField_h */
