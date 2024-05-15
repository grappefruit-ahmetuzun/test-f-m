//
//  CoctailObjectiveUI.hpp
//  FruitsKnife-mobile
//
//  Created by Marek on 05/06/2018.
//

#ifndef CoctailObjectiveUI_hpp
#define CoctailObjectiveUI_hpp

#include "cocos2d.h"
#include "SoundDirector.h"
#include "Recipes.h"
#include "Game.h"

USING_NS_CC;

class CoctailObjectiveUI : public Sprite{
    
public:
    
    CoctailObjectiveUI()
    {}
    
    CREATE_FUNC(CoctailObjectiveUI);
    
    void prepare(float height);
    
    void setText(std::string text);
    
    Label * label = nullptr;
    Sprite * icon = nullptr;
    
    void hide_all();
    void show_all();
    
private:
    
};

#endif /* CoctailObjectiveUI_hpp */
