//
//  WheelPart.hpp
//  Dottz
//
//  Created by Slavik on 4/26/17.
//
//

#ifndef WheelPart_h
#define WheelPart_h

#include "cocos2d.h"
#include "Shop.h"
#include "Recipes.h"

USING_NS_CC;


class WheelPart : public ProgressTimer {
    
public:
    
    WheelPart(){
    }
    ~WheelPart(){
    }
    
    CREATE_FUNC(WheelPart);
    
    virtual bool init() override;
    
    Sprite * fill_middle = nullptr;
    
    void prepare(objetive_recipe_info item);
    
    objetive_recipe_info _item;
    
    int index = 0;
    int index_of_manager = 0;

    Sprite * item_sprite     = nullptr;
    Label  * count_label     = nullptr;
    
    Sprite * white_line_1    = nullptr;
    Sprite * white_line_2    = nullptr;
    
    Sprite * red_circle      = nullptr;
    
    Sprite * item_bg         = nullptr;
    
    void update_positions(int all_segments_count, bool animated = false);
    
    static std::string getPartImage(RECIPE_CATEGORY _category);
    static std::string getPartObjectImage(RECIPE_CATEGORY _category);
    
    void hide_all_content();
    void show_all_content();
};

#endif /* WheelPart_h */
