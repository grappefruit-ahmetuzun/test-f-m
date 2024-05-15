//
//  Knife.cpp
//  FruitsKnife-mobile
//
//  Created by Marek on 15/05/2018.
//

#include "Knife.h"
#include "ShopManager.h"

void Knife::prepare(b2World * world){
    
    b2BodyDef bodydef;
    bodydef.userData    = this;
    bodydef.type        = b2_staticBody;
    bodydef.position.Set(getPositionX() / SPPHYSICS_PTM_RATIO,
                         getPositionY() / SPPHYSICS_PTM_RATIO);
    
    b2Body * _body = world->CreateBody(&bodydef);
    
    this->body = _body;
    this->bodyFallowSprite = true;
    this->body->SetBullet(true);
    
    Size _body_size = Size(this->getBoundingBox().size);
    
    // body fixture
    {
        
        
        b2CircleShape body_shape;
        
        body_shape.m_radius = ((this->getBoundingBox().size.height * 0.75f) / SPPHYSICS_PTM_RATIO  * 0.5f);
        
        b2FixtureDef body_fixture;
        body_fixture.density                 = 0.0f;
        body_fixture.friction                = 0.0f;
        body_fixture.restitution             = 0.0f;
        body_fixture.filter.categoryBits     = KNIFE_BITS;
        body_fixture.filter.maskBits         = FRUIT_BITS;
        body_fixture.isSensor                = true;
        body_fixture.shape =& body_shape;
        
        _body->CreateFixture(&body_fixture);
        
        
    }
    
    if (SPPHYSICS_DEBUG == 1){
        runAction(FadeTo::create(0.5f, 50));
    }
    
    knife_skin = Sprite::create("weapons/weapon_0.png");
    addChild(knife_skin);
    
    refresh_skin();
    
}

void Knife::last_knife_shoot_effect(){
    
    if (beam) {
        beam->runAction(FadeTo::create(0.1f, 0));
    }
    
   // tailEnable("motionStreakSquare.png",3.5f, getBoundingBox().size.width*1.5f, Color3B::WHITE,10.0f, nullptr);
    
}

void Knife::add_beam(){
    
    beam = Sprite::create("knife_effect/beams.png");
    addChild(beam,-1);
    
    beam->setScale(getContentSize().width*15.0f/beam->getContentSize().width);
    beam->setPosition(getContentSize()*0.5f);
    beam->setOpacity(255*0.5f);
    
    auto rotate = RotateBy::create(3.0f, 360);
    beam->runAction(RepeatForever::create(rotate));
    
    auto scale_by_1   = ScaleBy::create(0.5f, 0.75f);
    auto scale_by_2   = ScaleBy::create(0.5f, 1.25f);
    auto scale_by     = Sequence::create(scale_by_1,scale_by_2, NULL);
    auto scale_by_rep = RepeatForever::create(scale_by);
    beam->runAction(scale_by_rep);
    
}

void Knife::shoot(){
    

    
}

void Knife::removeFromParentAndCleanup(bool cleanup){
    tailDisable();
    Node::removeFromParentAndCleanup(cleanup);
}

void Knife::tailEnable(std::string tail_name, float fade, float radius, const cocos2d::Color3B color, float duration, std::function<void()> callback) {
    
    if (!tail) {
        
        tail = CustomMotionStreak::create(fade, 1.0f, radius, color, tail_name.c_str());
        tail->setColor(color);
        tail->setTimeToDestroy(duration, callback);
        getParent()->addChild(tail, getLocalZOrder()-1);
        
    }
    else {
        tail->setColor(color);
        tail->setTimeToDestroy(duration, callback);
    }
    
}

void Knife::tailDisable(){
    
    if (tail) {
        tail->removeFromParent();
        tail = nullptr;
    }
    
}

void Knife::update_shot(float dt){
    
    if (tail) {
        tail->setPosition(getPosition());
        //    tail->setStroke(getRadius()*2);
        tail->update(dt);
    }
    
}

void Knife::refresh_skin(){
    
    SHOP_ITEM item = ShopManager::getInstance()->get_item_selected();
    
    float scale_offset = Shop::get_knife_custom_scale_offset(item);
    
    knife_skin->setTexture(Shop::get_knife_image(item));
    knife_skin->setScale(getContentSize().height * (1.0f + scale_offset) / knife_skin->getContentSize().height);
    knife_skin->setPosition(getContentSize()/2);
}
