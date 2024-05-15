//
//  CoctailsObjectiveLarge.hpp
//  FruitsKnife-mobile
//
//  Created by Marek on 05/06/2018.
//

#ifndef CoctailsObjectiveLarge_hpp
#define CoctailsObjectiveLarge_hpp

#include "cocos2d.h"
#include "SoundDirector.h"
#include "Recipes.h"
#include "Game.h"
#include "Coctail.h"

USING_NS_CC;

class CoctailsObjectiveLarge : public Sprite{
    
public:
    
    CoctailsObjectiveLarge()
    {}
    
    CREATE_FUNC(CoctailsObjectiveLarge);
    
    void prepare(Size size);
    
    void hide_all();
    void animate_cells_appear();
    void animate_winner_cell();
    
    std::vector<Sprite*> _cells;
    
private:
    

    std::vector<Coctail*> _coctails;
    
};

#endif /* CoctailsObjectiveLarge_hpp */
