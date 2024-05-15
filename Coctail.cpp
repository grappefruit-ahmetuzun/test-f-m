//
//  Coctail.cpp
//  FruitsKnife-mobile
//
//  Created by Slavik on 5/22/18.
//

#include "Coctail.h"

void Coctail::prepare(Size size, RECIPE_TYPES _type){
    
    setContentSize(size);
    
    _coctail_type = _type;
    
    std::string texture = "coctails/standart_cocktail.png";
    float scale         = 1.0f;
    
    recipe_info info    = Recipes::getReceipe(_type);
    
    texture = info.texture_name;
    scale   = info.coctail_scale;
    
    coctail_spr = Sprite::create(texture.c_str());
    coctail_spr->setScale(getContentSize().width * scale / coctail_spr->getContentSize().width);
    coctail_spr->setPosition(Point(getContentSize().width * 0.5f, coctail_spr->getBoundingBox().size.height * 0.5f));
    addChild(coctail_spr);
}

