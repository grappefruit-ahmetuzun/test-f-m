//
//  WheelPart.cpp
//  Dottz
//
//  Created by Slavik on 4/26/17.
//
//

#include "WheelPart.h"

bool WheelPart::init(){
    
    fill_middle = Sprite::create("fortune_wheel/empty.png");
    
    if (ProgressTimer::initWithSprite(fill_middle)) {
        
        return true;
    }
    return false;
}

void WheelPart::prepare(objetive_recipe_info item){
    
    _item = item;
    
    setType(cocos2d::ProgressTimer::Type::RADIAL);
    setMidpoint(Point(0.5f,0.5f));
    
    item_bg = Sprite::create("circle_0.png");
    item_bg->setColor(Color3B(255, 255, 255));
    addChild(item_bg);

    item_bg->setOpacity(0);
    
    std::string icon_name = WheelPart::getPartObjectImage(item.recipe_category);
    
    if (item.recipe_category == RECIPE_CATEGORY_KNIFE) {
        icon_name = Shop::get_knife_image((SHOP_ITEM)item.knife_id);
    }
    
    item_sprite = Sprite::create(icon_name.c_str());
    item_sprite->setScale(item_bg->getContentSize().height * 0.85f / item_sprite->getContentSize().height);
    item_sprite->setPosition(item_bg->getContentSize()/2);
    item_bg->addChild(item_sprite);
    
    if (item.recipe_category == RECIPE_CATEGORY_KNIFE) {
        item_sprite->setColor(Color3B(30, 30, 30));
        item_sprite->setOpacity(255 * 0.85f);
    }
    
    int count = 0;
    
    if (_item.recipe_category == RECIPE_CATEGORY_COIN) {
        count = _item.coins_give;
    }
    else if (_item.recipe_category == RECIPE_CATEGORY_GEM) {
        count = _item.gems_give;
    }
    
    count_label = Label::createWithTTF(StringUtils::format("%i", count), "fonts/Blogger_Sans-Bold.otf", getContentSize().height * 0.08f);
    count_label->setColor(Color3B(0, 0, 0));
    count_label->setAnchorPoint(Point(0.55f, 0.5f));
    addChild(count_label);
    
    
    if (_item.recipe_category == RECIPE_CATEGORY_KNIFE) {
        item_sprite->setRotation(45);
        count_label->setVisible(false);
        
        item_bg->setScale(getContentSize().height * 0.25f / item_bg->getContentSize().height);
    }
    else{
        item_bg->setScale(getContentSize().height * 0.18f / item_bg->getContentSize().height);
    }
    
    Size s = Size(getContentSize().height * 0.0125f, getContentSize().width * 0.5f);
    
    white_line_1 = Sprite::create();
    white_line_1->setTextureRect(Rect(0, 0, s.width, s.height));
    white_line_1->setAnchorPoint(Point(1.0f, 0.0f));
    white_line_1->setPosition(getContentSize()/2);
    addChild(white_line_1, 2);
    
    white_line_2 = Sprite::create();
    white_line_2->setTextureRect(Rect(0, 0, s.width, s.height));
    white_line_2->setAnchorPoint(Point(0.0f, 0.0f));
    white_line_2->setPosition(getContentSize()/2);
    addChild(white_line_2, 2);
    
    red_circle = Sprite::create("fortune_wheel/s01.png");
    red_circle->setScale(getContentSize().height * 0.06f / red_circle->getContentSize().height);
    red_circle->setAnchorPoint(Point(0.5f, 0.f));
    addChild(red_circle);
    
}

void WheelPart::hide_all_content(){
    
    if (item_bg) {
        item_bg->setVisible(false);
    }
    
    if (count_label) {
        count_label->setVisible(false);
    }

}

void WheelPart::show_all_content(){
    
    if (item_bg) {
        item_bg->setVisible(true);
    }
    
    if (count_label) {
        if (_item.recipe_category != RECIPE_CATEGORY_KNIFE) {
            count_label->setVisible(true);
        }
    }
}

void WheelPart::update_positions(int all_segments_count, bool animated){
    
    float radius_of_part = (360.0f / all_segments_count);
    float percentage_of_segment = (radius_of_part * 100.0f) / 360.0f;
    

    float radius_of_item    = getContentSize().width * 0.315f;
    
    if (_item.recipe_category == RECIPE_CATEGORY_KNIFE) {
        radius_of_item    = getContentSize().width * 0.285f;
    }
    
    Point endPoint_item;
    endPoint_item.x         = sinf(CC_DEGREES_TO_RADIANS(radius_of_part / 2)) * radius_of_item;
    endPoint_item.y         = cosf(CC_DEGREES_TO_RADIANS(radius_of_part / 2)) * radius_of_item;
    Point final_pos_of_item = Point(getContentSize().width/2 + endPoint_item.x, getContentSize().height/2 + endPoint_item.y);

    
    float radius_of_red_circle   = getContentSize().width * 0.505f;
    Point endPoint_red_circle;
    endPoint_red_circle.x         = sinf(CC_DEGREES_TO_RADIANS(0)) * radius_of_red_circle;
    endPoint_red_circle.y         = cosf(CC_DEGREES_TO_RADIANS(0)) * radius_of_red_circle;
    Point final_pos_of_red_circle = Point(getContentSize().width/2 + endPoint_red_circle.x, getContentSize().height/2 + endPoint_red_circle.y);
    
    
    
    float radius_of_label   = getContentSize().width * 0.18f;
    Point endPoint_label;
    endPoint_label.x        = sinf(CC_DEGREES_TO_RADIANS(radius_of_part / 2)) * radius_of_label;
    endPoint_label.y        = cosf(CC_DEGREES_TO_RADIANS(radius_of_part / 2)) * radius_of_label;
    
    Point final_pos_of_label = Point(getContentSize().width/2 + endPoint_label.x, getContentSize().height/2 + endPoint_label.y);
    
    
    if (animated) {
        
        float animation_duration = 0.6f;
        float erase_duration     = 2.65f;
        
        auto progress = ProgressTo::create(animation_duration, percentage_of_segment);
        auto rotate   = RotateTo::create(animation_duration, radius_of_part * index);
        auto spawn    = Spawn::create(progress, rotate, NULL);
        auto ease     = EaseInOut::create(spawn, erase_duration);
        runAction(ease);
        
        if (item_bg) {
            auto move_item       = MoveTo::create(animation_duration, final_pos_of_item);
            auto ease_item_move  = EaseInOut::create(move_item, erase_duration);
            item_bg->runAction(ease_item_move);
            
            auto rotate_item        = RotateTo::create(animation_duration, radius_of_part / 2);
            auto ease_rotation_item = EaseInOut::create(rotate_item, erase_duration);
            item_bg->runAction(ease_rotation_item);
            
        }
        
        if (count_label) {
            auto move_label       = MoveTo::create(animation_duration, final_pos_of_label);
            auto ease_label_move  = EaseInOut::create(move_label, erase_duration);
            count_label->runAction(ease_label_move);
            
            auto rotate_label        = RotateTo::create(animation_duration, radius_of_part / 2);
            auto ease_rotation_label = EaseInOut::create(rotate_label, erase_duration);
            count_label->runAction(ease_rotation_label);
        }
        
        if (white_line_1) {
            auto rorate_separator  = RotateTo::create(animation_duration, radius_of_part);
            auto ease_rotate       = EaseInOut::create(rorate_separator, erase_duration);
            white_line_1->runAction(ease_rotate);
        }
        
        if (white_line_2) {
            auto rorate_separator2  = RotateTo::create(animation_duration, 0);
            auto ease_rotate2       = EaseInOut::create(rorate_separator2, erase_duration);
            white_line_2->runAction(ease_rotate2);
        }
        
        if (red_circle) {
            auto move_label       = MoveTo::create(animation_duration, final_pos_of_red_circle);
            auto ease_label_move  = EaseInOut::create(move_label, erase_duration);
            red_circle->runAction(ease_label_move);
            
            auto rotate_label        = RotateTo::create(animation_duration, 0);
            auto ease_rotation_label = EaseInOut::create(rotate_label, erase_duration);
            red_circle->runAction(ease_rotation_label);
        }
    }
    else{
        
        if (item_bg) {
            item_bg->setPosition(final_pos_of_item);
            item_bg->setRotation(radius_of_part / 2);
        }
      
        if (count_label) {
            count_label->setPosition(final_pos_of_label);
            count_label->setRotation(radius_of_part / 2);
        }
        
        if (white_line_1) {
            white_line_1->setRotation(radius_of_part);
        }
        
        if (white_line_2) {
            white_line_2->setRotation(0);
        }
        
        if (red_circle) {
            red_circle->setRotation(0);
            red_circle->setPosition(final_pos_of_red_circle);
        }
        
        setPercentage(percentage_of_segment);
        setRotation(radius_of_part * index);
    }
}

std::string WheelPart::getPartImage(RECIPE_CATEGORY _category){
    
    switch (_category) {
        case RECIPE_CATEGORY_COIN:  return "fortune_wheel/yellow.png";
        case RECIPE_CATEGORY_GEM:   return "fortune_wheel/blue.png";
        case RECIPE_CATEGORY_KNIFE: return "fortune_wheel/pink.png";
            
        default: break;
    }
    
    return "fortune_wheel/empty.png";
}

std::string WheelPart::getPartObjectImage(RECIPE_CATEGORY _category){
    
    switch (_category) {
        case RECIPE_CATEGORY_COIN:  return "fortune_wheel/coin.png";
        case RECIPE_CATEGORY_GEM:   return "hud/blue_gem.png";
        case RECIPE_CATEGORY_KNIFE: return "fortune_wheel/knife.png";
            
        default: break;
    }
    
    return "fortune_wheel/coin.png";
}

