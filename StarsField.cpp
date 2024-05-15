//
//  StarsField.cpp
//  FruitsKnife-mobile
//
//  Created by Slavik on 5/30/18.
//

#include "StarsField.h"

#include "Game.h"

bool StarsField::init(){
    if (Sprite::init()) {
        
        return true;
    }
    return false;
}

void StarsField::prepare(float height){
    
    int stars_count = 3;
    
    setContentSize(Size(0, height));
     
    float width = 0;
    float space_between_knives = height * 0.3f;
     
     
    for (int i = 0; i < stars_count; i++) {
        Sprite * star = Sprite::create("ui/heart.png");
        star->setScale(getContentSize().height * 0.8f / star->getContentSize().height);
        star->setPosition(Point(star->getBoundingBox().size.width * 0.5f + (star->getBoundingBox().size.width * i) + (space_between_knives * i), getContentSize().height * 0.5f));
        addChild(star);
        width = star->getPosition().x + star->getBoundingBox().size.width * 0.5f;
     
        stars.push_back(star);
    }
     
    setContentSize(Size(width, getContentSize().height));
     
    set_stars_count(stars_count);
     
}

void StarsField::set_stars_count(int count){
    
    for (int i = 0; i < stars.size(); i++) {
        Sprite * star = stars.at(i);
        
        if (i <= count) {
            star->setColor(Color3B(236, 103, 98));
        }
        else{
            star->setColor(Color3B(47, 77, 92));
        }
    }
}

void StarsField::hide(){
    
    for (int i = 0; i < stars.size(); i++) {
        Sprite * star = stars.at(i);
        
        auto fade = FadeTo::create(0.2f, 0);
        star->runAction(fade);
    }
}
