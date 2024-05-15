//
//  Fruit.cpp
//  FruitsKnife-mobile
//
//  Created by Marek on 11/05/2018.
//

#include "Fruit.h"

void Fruit::prepare(fruit_info info,Size container,b2World * world){
    
    _info      = info;
    _container = container;
    
    setContentSize(Size(container.width * 0.2f, container.width * 0.2f));
    setScale  (getSize          (_info.type)/getContentSize().width);
    
    b2CircleShape b_SHAPE;
    
    b_SHAPE.m_radius = (this->getBoundingBox().size.width / SPPHYSICS_PTM_RATIO  * 0.5f);
    
    b2FixtureDef b_FIXTURE;
    
    b_FIXTURE.density       = 1.f;
    b_FIXTURE.friction      = 1.0f;
    b_FIXTURE.restitution   = 0.5f;
    
    b_FIXTURE.filter.categoryBits = FRUIT_BITS;
    b_FIXTURE.filter.maskBits     = KNIFE_BITS;
    b_FIXTURE.shape               = &b_SHAPE;
    
    b2BodyDef b_DEF;
    b_DEF.type      = b2_dynamicBody;
    b_DEF.userData  = this;
    b_DEF.position.Set(this->getPositionX() / SPPHYSICS_PTM_RATIO,
                       this->getPositionY() / SPPHYSICS_PTM_RATIO);
    
    b2Body *b_BODY = world->CreateBody(&b_DEF);
    b_BODY->CreateFixture(&b_FIXTURE);
    
    this->bodyFallowSprite = false;
    this->body = b_BODY;
    
    
    Sprite * fruit_image = Sprite::create(getTexturePath(info.type));
    addChild(fruit_image);
    fruit_image->setScale(getContentSize().width / fruit_image->getContentSize().width);
    fruit_image->setPosition(getContentSize()/2);
    
    
    float angle     = random(15, 30);
    float duration  = random(0.8f, 1.2f);
    float ease_rate = random(2.0f, 2.4f);
    int repaet_count = random(1, 3);
    int final_r = 360;
    
    if (random(0, 1) == 1) {
        final_r = -final_r;
    }
    
    auto rotate1 = RotateTo::create(duration, -angle);
    auto ease1   = EaseInOut::create(rotate1, ease_rate);
    auto rotate2 = RotateTo::create(duration, angle);
    auto ease2   = EaseInOut::create(rotate2, ease_rate);
    auto seq     = Sequence::create(ease1, ease2, NULL);
    auto repeat  = Repeat::create(seq, repaet_count);
    auto rotate3 = RotateBy::create(duration, final_r);
    auto ease3   = EaseInOut::create(rotate3, ease_rate);
    auto seq2    = Sequence::create(repeat, ease3, NULL);
    auto repeatf = RepeatForever::create(seq2);
    
    fruit_image->runAction(repeatf);
}

std::string Fruit::getTexturePath(fruit_type type){
    
    std::string img_path = "objects/watermelon.png";
    
    switch (type) {
            
        case fruit_type_watermelon: img_path = "objects/watermelon.png";    break;
        case fruit_type_orange:     img_path = "objects/orange.png";        break;
        case fruit_type_lemon:      img_path = "objects/lemon.png";         break;
        case fruit_type_apple:      img_path = "objects/apple.png";         break;
        case fruit_type_kivi:       img_path = "objects/kivi.png";          break;
        case fruit_type_mango:      img_path = "objects/mango.png";         break;
        case fruit_type_pineapple:  img_path = "objects/pineapple.png";     break;
            
        default:
            break;
    }
    
    return img_path;
    
}

float Fruit::getSize(fruit_type type){
    
    float size = _container.width*0.15f;
    
    switch (type) {
            
        case fruit_type_watermelon: size = _container.width*0.2f;           break;
        case fruit_type_orange:     size = _container.width*0.165f;         break;
        case fruit_type_lemon:      size = _container.width*0.15f;          break;
        case fruit_type_bomb:       size = _container.width*0.165f;         break;
        case fruit_type_apple:      size = _container.width*0.16f;          break;
        case fruit_type_kivi:       size = _container.width*0.135f;         break;
        case fruit_type_pineapple:  size = _container.width*0.165f;         break;
            
        default:
            break;
    }
    
    return size;
    
}

void Fruit::updateFruit(){
    
    float rotation = Game::getRotationNode(this, 0);
    
    setRotation(rotation);

}
