//
//  FruitsObjectiveBar.cpp
//  FruitsKnife-mobile
//
//  Created by Marek on 28/05/2018.
//

#include "FruitsObjectiveBar.h"

void FruitsObjectiveBar::prepare(recipe_info recipe,float height){
    
    _recipe = recipe;
    
    Size s = Size(recipe._missions_requirement_types.size()*height, height);
    
    setTextureRect(Rect(0, 0, s.width, s.height));
    setOpacity(0);
    
    float width = s.height*1.0f;
    float pos_x = width*0.5f;
    
    for (int x=0; x < (int)recipe._missions_requirement_types.size(); x++) {
        fruit_type fruit = recipe._missions_requirement_types.at(x);
        
        Sprite * cell = Sprite::create("fruits_missions/z00.png");
        addChild(cell);

        cell->setScale(width*0.9f/cell->getContentSize().width);
        cell->setPosition(Vec2(pos_x, getContentSize().height*0.5f));
        
        Sprite *icon = Sprite::create(getFruitIcon(fruit));
        cell->addChild(icon);
        icon->setScale(cell->getContentSize().width*0.95f/icon->getContentSize().width);
        icon->setPosition(cell->getContentSize()*0.5f);
        icon->setTag(1);
        
        Label *_count_label = Label::createWithTTF(StringUtils::format("10"), "fonts/Blogger_Sans-Bold.otf", cell->getContentSize().height * 0.65f);
        _count_label->setPosition(cell->getContentSize().width*0.5f,
                                 -cell->getContentSize().height*0.5f);
        _count_label->setColor(Color3B(42,104,96));
        cell->addChild(_count_label);
        _count_label->setTag(2);
        
        Sprite *checkmark = Sprite::create("fruits_missions/chck.png");
        cell->addChild(checkmark);
        checkmark->setScale(cell->getContentSize().width*0.65f/checkmark->getContentSize().width);
        checkmark->setPosition(cell->getContentSize().width*0.5f,
                               -cell->getContentSize().height*0.4f);
        checkmark->setTag(3);
        
        cell->setTag((int)(fruit));
        
        cells.push_back(cell);
        
        pos_x+=width;
    }
    
    refresh_all_count_labels();
    
}

void FruitsObjectiveBar::refresh_all_count_labels(){
    
    /*
    for (int x=0; x < cells.size(); x++) {
        Sprite * cell     = cells.at(x);
        fruit_type f_type = (fruit_type)cell->getTag();
        int left          = Recipes::get_mission_fruits_left_to_collect(f_type);
        
        if (cell->getChildByTag(2)) {
            Label * count_label = (Label*)cell->getChildByTag(2);
            count_label->setString(StringUtils::format("%i",left));
            count_label->setVisible(left > 0);
        }
        
        if (cell->getChildByTag(3)) {
            Sprite * checkmark = (Sprite*)cell->getChildByTag(3);
            checkmark->setVisible(left <= 0);
        }
        
    }
    */
    
}

std::string FruitsObjectiveBar::getFruitIcon(fruit_type f_type){
    
    std::string icon = "";
    
    switch (f_type) {
            
        case fruit_type_watermelon:     icon = "fruits_missions/z01.png";  break;
        case fruit_type_orange:         icon = "fruits_missions/z02.png";  break;
        case fruit_type_lemon:          icon = "fruits_missions/z06.png";  break;
        case fruit_type_apple:          icon = "fruits_missions/z03.png";  break;
        case fruit_type_kivi:           icon = "fruits_missions/z04.png";  break;
        case fruit_type_pineapple:      icon = "fruits_missions/z07.png";  break;
        case fruit_type_mango:          icon = "fruits_missions/z05.png";  break;
            
        default:
            break;
    }
    
    return icon;
}
