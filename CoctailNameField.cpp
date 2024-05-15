//
//  CoctailNameField.cpp
//  FruitsKnife-mobile
//
//  Created by Slavik on 5/24/18.
//

#include "CoctailNameField.h"

void CoctailNameField::prepare(Size size, RECIPE_TYPES _type){
    
    setContentSize(size);

    _coctail_type = _type;
    
    
    
    Sprite * field = Sprite::create("ui/new_cocktail_flag.png");
    field->setScale(getContentSize().width / field->getContentSize().width);
    field->setPosition(Point(getContentSize().width * 0.5f, getContentSize().height * 0.5f));
    addChild(field);
    
    
    Label * header_label = Label::createWithTTF(StringUtils::format("NEW RECIPE FOUND!"), "fonts/Blogger_Sans-Bold.otf", field->getContentSize().height * 0.17f);
    header_label->setPosition(field->getContentSize().width * 0.5f, field->getContentSize().height * 0.7f);
    header_label->setColor(Color3B(255, 255, 255));
    field->addChild(header_label);
    
    
    recipe_info info = Recipes::getReceipe(_type);
    
    Label * name_label = Label::createWithTTF(StringUtils::format("%s", info.name.c_str()), "fonts/Blogger_Sans-Bold.otf", field->getContentSize().height * 0.28f);
    name_label->setPosition(field->getContentSize().width * 0.5f, field->getContentSize().height * 0.4f);
    name_label->setColor(Color3B(201, 98, 38));
    field->addChild(name_label);
    
    
    if (header_label->getBoundingBox().size.width > field->getContentSize().width * 0.7f) {
        name_label->setScale(field->getContentSize().width * 0.7f / header_label->getBoundingBox().size.width);
    }
    
    
    
    Sprite * beams = Sprite::create("ui/beamz.png");
    beams->setScale(field->getContentSize().width * 1.75f / beams->getContentSize().width);
    beams->setPosition(Point(field->getContentSize().width * 0.5f, field->getContentSize().height * 0.5f));
    field->addChild(beams, -1);
    
    auto rotate = RotateBy::create(0.2f, 30);
    auto repeat = RepeatForever::create(rotate);
    beams->runAction(repeat);
    
}

