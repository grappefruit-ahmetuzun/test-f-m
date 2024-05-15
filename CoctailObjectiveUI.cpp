//
//  CoctailObjectiveUI.cpp
//  FruitsKnife-mobile
//
//  Created by Marek on 05/06/2018.
//

#include "CoctailObjectiveUI.h"
#include "Game.h"

void CoctailObjectiveUI::prepare(float height){

    Size s = Size(height*3, height);
    
    setTextureRect(Rect(0, 0, s.width, s.height));
    setOpacity(0);
    
    label = Label::createWithTTF(StringUtils::format("10"), "fonts/Blogger_Sans-Medium.otf", getContentSize().height * 0.65f);
    label->setPosition(getContentSize().width*0.625f,
                       getContentSize().height*0.425f);
    label->setColor(Color3B(250,106,107));
    addChild(label,1);
    
    icon = Sprite::create("coctail_objective/z223.png");
    addChild(icon);
    icon->setScale(getContentSize().height*1.0f/icon->getContentSize().height);
  //  icon->setColor(label->getColor());
    icon->setPositionY(getContentSize().height*0.5f);
    icon->setPositionX(getContentSize().width*0.5f);
    
}

void CoctailObjectiveUI::setText(std::string text){
    
    label->setString(text.c_str());
 //   Game::align_x_side_by_side(icon, label, getContentSize().height*0.2f);
    
}

void CoctailObjectiveUI::hide_all(){
    icon->setOpacity(0);
    label->setOpacity(0);
}

void CoctailObjectiveUI::show_all(){
    icon->runAction(FadeTo::create(0.25f, 255));
    label->runAction(FadeTo::create(0.25f, 255));
}
