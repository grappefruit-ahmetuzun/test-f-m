//
//  Gameplayb2d.cpp
//  hiball
//
//  Created by Marek on 1/8/17.
//
//

#include "Gameplayb2d.h"
#include "Game.h"
#include "SoundDirector.h"
#include "GB2ShapeCache-x.h"
#include "SPMath.h"
#include "GameScene.h"
#include "PlatformManager.h"
#include "SPMath.h"
#include "CoctailNameField.h"
#include "Shop.h"
#include "ShopManager.h"

bool Gameplayb2d::init(){
    
    if (!SPPhysicsLayer::init()){
        return false;
    }
    
    
    table = Sprite::create("ui/table_0.png");
    addChild(table, 200);
    table->setScale(getContainer()->getContentSize().width / table->getContentSize().width);
    table->setPosition(Point(getContentSize().width * 0.5f, getContentSize().height * 0.5f - getContainer()->getContentSize().height * 0.38f - table->getBoundingBox().size.height * 0.5f));
    
    
    mixer = Mixer::create();
    mixer->prepare(Size(getContainer()->getContentSize().width * 0.25f, getContainer()->getContentSize().height * 0.2f));
    mixer->setPosition(Point(getContentSize().width * 0.5f - getContainer()->getContentSize().width * 0.32f, table->getPositionY() + table->getBoundingBox().size.height * 0.45f + mixer->getBoundingBox().size.height * 0.5f));
    mixer->get_coctail = CC_CALLBACK_1(Gameplayb2d::getCoctail, this);
    addChild(mixer, 198);
    
    return true;
}

#pragma mark
#pragma mark game states

void Gameplayb2d::gameplay_prepare(){

    world->SetGravity(b2Vec2(0, -getContainer()->getContentSize().height * 0.01f));
    
    Knife *knife = add_knife();
    knife->setPosition(Vec2(getContentSize().width*0.5f, getContentSize().height*0.5f-(getContainer()->getContentSize().height*0.12f)));
    
    
//    _fruits_in_mixer.push_back(fruit_type_apple);
//    _fruits_in_mixer.push_back(fruit_type_apple);
//    _fruits_in_mixer.push_back(fruit_type_watermelon);
//    _fruits_in_mixer.push_back(fruit_type_watermelon);
//    _fruits_in_mixer.push_back(fruit_type_watermelon);
//    _fruits_in_mixer.push_back(fruit_type_orange);
//    _fruits_in_mixer.push_back(fruit_type_watermelon);
    
//    recipe_info recipe = Recipes::check_receipe(_fruits_in_mixer);
    
    current_level = LevelManager::getInstance()->get_current_level_info();
}

void Gameplayb2d::refresh_dark_mode(){
    
    bool dark_mode_on = Settings::getStateOn(settings_darkmode);
    
    if (dark_mode_on == true) {
        if (mixer) {
            mixer->_mixer_spine->setSkin("black");
        }
        
        if (table) {
            table->setTexture("ui/table_1.png");
            table->setScale(getContainer()->getContentSize().width / table->getContentSize().width);
        }
    }
    else{
        if (mixer) {
            mixer->_mixer_spine->setSkin("white");
        }
        
        if (table) {
            table->setTexture("ui/table_0.png");
            table->setScale(getContainer()->getContentSize().width / table->getContentSize().width);
        }
    }
}

void Gameplayb2d::refresh_weapon(){
    
    SHOP_ITEM selected = ShopManager::getInstance()->get_item_selected();
    
    for (int i = 0; i < _knifes.size(); i++) {
        Knife * k = _knifes.at(i);
    
        k->knife_skin->stopAllActions();
        k->knife_skin->setPosition(k->getContentSize()/2);
        
        k->refresh_skin();
        
        k->stopAllActions();
        k->setRotation(0);
        
        if (Shop::weapon_must_rotating(selected)) {
            k->runAction(RepeatForever::create(RotateBy::create(1.0f, 360)));
        }
        else{
            
            auto move1 = MoveTo::create(0.5f, Point(k->knife_skin->getPositionX(), k->getContentSize().height * 0.7f));
            auto ease1 = EaseInOut::create(move1, 2.2f);
            auto move2 = MoveTo::create(0.5f, Point(k->knife_skin->getPositionX(), k->getContentSize().height * 0.5f));
            auto ease2 = EaseInOut::create(move2, 2.2f);
            auto seq   = Sequence::create(ease1, ease2, NULL);
            auto repaet = RepeatForever::create(seq);
            k->knife_skin->runAction(repaet);
        }
    }
}

void Gameplayb2d::gameplay_start(){
    
    if (_gameStarted) {
        return;
    }
    
    _gameStarted = true;
    
    Knife *last_knife = _knifes.at(_knifes.size()-1);
    
    Vec2 move_pos = Vec2(getContentSize().width*0.5f,
                         getContentSize().height*0.5f-(getContainer()->getContentSize().height*0.3f));
    
    auto move = MoveTo::create(0.5f, move_pos);
    auto move_e = EaseElasticOut::create(move,1.5f);
    auto finished = CallFunc::create([this]{
        /*
         do_phase();
         scheduleUpdate();
        */
    });
    auto seq = Sequence::create(move_e,finished, NULL);
    last_knife->runAction(seq);
    
    _canSpawnPattern = true;
    _do_phase = true;
    //do_phase();
    scheduleUpdate();

}

void Gameplayb2d::game_continue_watched(){
    
    _gameOver = false;
    _lifesCount++;
    
    add_knife();
    
}

void Gameplayb2d::game_over(float delay){
    
    _gameOver = true;
    
    _delegate->gameplay_gameover(delay);
    
}

#pragma Game Objects

void Gameplayb2d::do_phase(float delay){
    
    if (_gameOver) {
        return;
    }
    
    if (_canSpawnPattern == false){
        return;
    }
    
    if (pattern) {
        pattern->removeFromParentAndCleanup(true);
        pattern = nullptr;
    }

    float move_speed_bottom  = getContainer()->getContentSize().width*0.575f;
    
    gameplay_info gp_info;
    gp_info.score = _score;
    gp_info.wave = _wave;
    gp_info.highscore = Game::getScore();
    gp_info.fruits_in_mixer = (int)_fruits_in_mixer.size();
    
    int wave = current_level.wave;
    
    int patterns = (int)current_level._patterns.size();
    
    if (DEBUG_FORTUNE_WHEEL == 1) {
        patterns = 1;
    }
    
    if (wave >= patterns) {
        
        for (Knife * knife: _knifes) {
            knife->knife_skin->runAction(FadeTo::create(0.2f, 0));
        }
        
        // LEVEL COMPLETED
        _canSpawnPattern = false;
        Patterns::getInstance()->generate_new_level();
        _delegate->gameplay_level_complete();
        return;
    }
    
    pattern_info p_info      = current_level._patterns.at(wave);
    Pattern * pattern_object = Patterns::getInstance()->get_pattern(p_info);
    
    current_level.wave++;
    
    Game::getInstance()->setWave_count_for_continue(Game::getInstance()->getWave_count_for_continue() + 1);
    
    if (pattern_object->fruits.size() == 0){
        log("NO FRUITS ADDED!!!!!");
        return;
    }
    
    float path_field_w       = getContainer()->getContentSize().width;
    Size  path_field_size    = Size(path_field_w,path_field_w);
    
    pattern = PathField::create();
    addChild(pattern, 50);
    pattern->setMoveSpeed  (move_speed_bottom);
    pattern->setPosition   (Vec2(getContentSize().width*0.5f,getContentSize().height*0.5f+(getContainer()->getContentSize().height*0.2f)));
    pattern->prepare       (path_field_size,pattern_object);
    
    Vector<FiniteTimeAction *>actions;
    for (int x=0; x < pattern_object->actions.size(); x++) {
        ActionInterval * action = pattern_object->actions.at(x);
        actions.pushBack(action);
    }
    auto seq = Sequence::create(actions);
    pattern->runAction(RepeatForever::create(seq));
    
    for (int x=0; x < pattern_object->fruits.size(); x++) {
        fruit_type f = pattern_object->fruits.at(x);
        fruit_info info;
        info.type = f;
        Fruit * fruit = spawn_object(info, pattern);
        fruit->setLocalZOrder(1);
        fruit->bodyFallowSprite = true;
        pattern->add_object(fruit, x);
        _fruits_in_pattern++;
    }

    pattern->setScale(0);

    auto scale = ScaleTo::create(0.5f, 1.0f);
    auto scale_e = EaseElasticOut::create(scale,0.75f);
    pattern->runAction(scale_e);
    
    _lifesCount = pattern->_pattern->lifes_count;
    _wave++;
    _hud->set_wave(_wave);
    _canSpawnPattern = false;
    
    _hud->_lifes_label->setString("");//(StringUtils::format("LIFES: %i",_lifesCount));
   // _hud->_pathsIndicator->setMaxSteps(_lifesCount);
   // _hud->_pathsIndicator->setAvailable(_lifesCount);
    
}

Knife * Gameplayb2d::add_knife(){
    
    Knife *_knife = Knife::create();
    addChild(_knife, 40);
    
    SHOP_ITEM item = ShopManager::getInstance()->get_item_selected();
    
    _knife->setTextureRect(Rect(0, 0, getContainer()->getContentSize().height * 0.1f, getContainer()->getContentSize().height * 0.1f));
  
    _knife->setColor(Color3B::RED);
    _knife->setOpacity(0);

    Vec2 move_pos = Vec2(getContentSize().width*0.5f,
                         getContentSize().height*0.5f - (getContainer()->getContentSize().height*0.3f));
    _knife->setPosition(move_pos);
    _knife->setTag(physic_object_knife);
    
    _knife->prepare(world);
    
    
    
    float normal_scale = _knife->getScale();
    _knife->setScale(0);
    
    auto scale      = ScaleTo::create(0.5f, normal_scale);
    auto scale_ease = EaseElasticOut::create(scale, 0.75f);
    _knife->runAction(scale_ease);
    
    
    if (Shop::weapon_must_rotating(item)) {
        _knife->runAction(RepeatForever::create(RotateBy::create(1.0f, 360)));
    }
    else{
        
        auto move1 = MoveTo::create(0.5f, Point(_knife->knife_skin->getPositionX(), _knife->getContentSize().height * 0.7f));
        auto ease1 = EaseInOut::create(move1, 2.2f);
        auto move2 = MoveTo::create(0.5f, Point(_knife->knife_skin->getPositionX(), _knife->getContentSize().height * 0.5f));
        auto ease2 = EaseInOut::create(move2, 2.2f);
        auto seq   = Sequence::create(ease1, ease2, NULL);
        auto repaet = RepeatForever::create(seq);
        _knife->knife_skin->runAction(repaet);
    }
    
    _knifes.push_back(_knife);
    
    return _knife;
}

Fruit * Gameplayb2d::spawn_object(fruit_info info,Node *parent){
    
    Fruit * fruit =  nullptr;
    
    fruit = Fruit::create();
    parent->addChild(fruit);
    fruit->setTag(physic_object_fruit);
    
    fruit->prepare(info, getContainer()->getContentSize(), world);
    
    _fruits.push_back(fruit);

    return fruit;
    
}

#pragma mark
#pragma mark Update

void Gameplayb2d::update(float dt){
    
    dt = 1/60.f;
    
    if (_do_phase == true){
        _do_phase = false;
        do_phase();
    }
    
    for (int x=0; x < _knifes.size(); x++) {
        Knife * knife = _knifes.at(x);
        knife->update_shot(dt);
        
        if (knife->getPosition().y > getContentSize().height+(knife->getBoundingBox().size.height*0.5f)) {
            
            if (_lifesCount > 1) {
                _lifesCount--;
            }
            else{
                if (knife->getFruits_hit_count() == 0) {
                    _lifesCount--;
                    
                    if (_delegate) {
                        _delegate->gameplay_miss_star();
                    }
                }
            }
            
           // _hud->_lifes_label->setString(StringUtils::format("LIFES: %i",_lifesCount));
            
            if (/*knife->getFruits_hit_count() == 0*/_lifesCount == 0) {
                SoundDirector::playSound("ev_knife_miss");
                game_over(0.8f);
            }

            /*
            _knifes.erase(_knifes.begin()+x);
            x--;
            knife->removeBodyAndSprite();
            */
            knife->setRemove_from_array(true);
        }
        
        if (knife->getRemove_from_array()) {
            _knifes.erase(_knifes.begin()+x);
            x--;
            knife->removeBodyAndSprite();
        }
        
    }
    
    if (pattern) {
        if (pattern->_pattern_movable_objects.size() == 0 && _do_phase == false && _canSpawnPattern == false) {
            _canSpawnPattern = true;
            
            auto d = DelayTime::create(1);
            auto call = CallFunc::create([this]{
                _knife_count = 0;
                _fruits_in_pattern = 0;
                this->add_knife();
                this->_do_phase = true;
            });
            auto seq= Sequence::create(d,call, NULL);
            runAction(seq);
            
        }
    }

    bool all_fruits_smashed = true;
    
    for (int x=0; x < _fruits.size(); x++) {
        Fruit * fruit = _fruits.at(x);
      
        fruit->updateFruit();
        
        if (fruit->getRemove_from_array() == true) {
            _fruits.erase(_fruits.begin()+x);
            x--;
            fruit->removeBodyAndSprite();
        }
        
        if (fruit->_info.type != fruit_type_bomb) {
            all_fruits_smashed = false;
        }
        
    }
    
    /*
    if (all_fruits_smashed && getActionByTag(5000) == nullptr) {
        
        for (int x=0; x < _fruits.size(); x++) {
            Fruit * fruit = _fruits.at(x);
            _fruits.erase(_fruits.begin()+x);
            x--;
            fruit->removeBodyAndSprite();
        }
        
        do_phase(0.5f);
    }
    */
    
    
    for (int i = 0; i < _nodes_to_delete.size(); i++) {
        Node * node_to_delete = _nodes_to_delete.at(i);
        node_to_delete->removeFromParentAndCleanup(true);
        node_to_delete = nullptr;
    }
    _nodes_to_delete.clear();
    
    SPPhysicsLayer::update(dt);
    
}

#pragma mark
#pragma mark Touches

bool Gameplayb2d::onTouchBegan(Touch *touch, Event *event){
    
//    if (_knife_count >= _fruits_in_pattern){
//        return true;
//    }
    
    if (pattern) {
        if (pattern->_pattern_movable_objects.size() == 0) {
            return true;
        }
    }
    
    if (_knifes.size() < 1) {
        return true;
    }

    Knife *last_knife = _knifes.at(_knifes.size()-1);
    last_knife->stopAllActions();
    last_knife->setScale(getContainer()->getContentSize().height * 0.1f/ last_knife->getContentSize().height);
    
    auto move_y         = MoveBy::create(1.15f, Vec2(0, getContentSize().height*3.0f));
    last_knife->runAction(move_y);
    
    last_knife->knife_skin->stopAllActions();
    last_knife->knife_skin->setPosition(last_knife->getContentSize()/2);
    
    
    float angle = 360 * 5.0f;
    
    if (Shop::weapon_must_rotating(ShopManager::getInstance()->get_item_selected()) == false) {
        last_knife->knife_skin->setRotation(180);
        angle = 360 * 7.f;
    }
    
    auto rotate         = RotateBy::create(1.15f, angle);
    last_knife->runAction(rotate);
    
    last_knife->shoot();
    
     if (_knife_count != _fruits_in_pattern){
         SoundDirector::playSound("ev_throw");
     }
    
    _knife_count++;
    
    if (_knife_count == _fruits_in_pattern){
        _knifes.at(_knifes.size()-1)->last_knife_shoot_effect();
        
        /*
        Director::getInstance()->getScheduler()->setTimeScale(0.35f);
        
        _delegate->gameplay_slow_motion(true);
        SoundDirector::playSound("ev_throw_slo_mo");
        
        auto d = DelayTime::create(0.35f);
        auto call = CallFunc::create([this]{
            Director::getInstance()->getScheduler()->setTimeScale(1.0f);
            _delegate->gameplay_slow_motion(false);
        });
        auto s = Sequence::create(d,call, NULL);
        runAction(s);
        */
        
    }
    
    if (_lifesCount == 1){
        // last knife
        
    }
    else if (_knife_count < _fruits_in_pattern){
        add_knife();
    }

    return true;
}

void Gameplayb2d::onTouchMoved(Touch *touch, Event * event){
}

void Gameplayb2d::onTouchEnded(Touch *touch, Event *event){
}

#pragma mark
#pragma mark Physics

void Gameplayb2d::collisionContactDidBegin(SPPhysicsSprite *sp1, SPPhysicsSprite *sp2, Point contactPoint, SPPhysicsContact contact){
    collisionHandle(sp1,sp2,contact,true,false);
}

void Gameplayb2d::collisionContactDidEnd(SPPhysicsSprite *sp1, SPPhysicsSprite *sp2,Point contactPoint, SPPhysicsContact contact){
    collisionHandle(sp1,sp2,contact,false,true);
}

void Gameplayb2d::collisionHandle(SPPhysicsSprite *sp1, SPPhysicsSprite *sp2, SPPhysicsContact contact, bool collision_begin, bool collision_end){
    
    Knife                     * knife            = nullptr;
    Fruit                     * fruit            = nullptr;
    
    std::vector<SPPhysicsSprite *> _collide_objects;
    _collide_objects.push_back(sp1);
    _collide_objects.push_back(sp2);
    
    for (SPPhysicsSprite * collide_object : _collide_objects) {
        
        if (collide_object->body == NULL) {
            continue;
        }
        
        if (collide_object->destroyBody ||
            collide_object->body->IsActive() == false) {
            continue;
        }
        
        if (collide_object->getTag() == physic_object_knife) {
            knife = (Knife *)collide_object;
        }
        else if (collide_object->getTag() == physic_object_fruit) {
            fruit = (Fruit *)collide_object;
        }
        
    }
    
    if (fruit && knife) {
        
        if (collision_begin) {
            
            fruit->body->SetActive(false);
            
            Point fruit_pos         = fruit->getParent()->convertToWorldSpace(fruit->getPosition());
            
            if (fruit->_info.type == fruit_type_bomb) {
                
                // gameover & boom
                
                fruit->body->SetActive(false);
                knife->body->SetActive(false);
                
                knife->stopAllActions();
                knife->setRemove_from_array(true);
                
                game_over(0.15f);

                return;
            }
            
            /*
            Recipes::did_mission_objective_fruit(fruit->_info.type);
            _hud->_fruits_bar->refresh_all_count_labels();
            */
            
            if (KNIFE_HIT_MULTIPLE_FRUITS == 1) {
                
            } else {
                knife->stopAllActions();
                knife->setRemove_from_array(true);
            }
            
            _fruitsHitCount++;
            
            // REFRESH THE LEVEL BAR
            
            int fruits_all = current_level.getFruitsCount();
            int fruits_hit = _fruitsHitCount;
            float percent  = (fruits_hit*100)/fruits_all;
            //log("percent %f",percent);
            _hud->set_level_percents(percent);

            if (knife->getFruits_hit_count() == 0) {
                if (_lifesCount > 1) {
                    _lifesCount--;
                  //  _hud->_lifes_label->setString(StringUtils::format("LIFES: %i",_lifesCount));
                  //  _hud->_pathsIndicator->setAvailable(_lifesCount);
                }
    
            }

            playFriutHitSound(fruit->_info.type);
            
            PlatformManager::vibrate(2);
            
            if (_lifesCount == 1 && knife->getFruits_hit_count() == 0){
                add_knife();
            }
            
            knife->setFruits_hit_count(knife->getFruits_hit_count()+1);
            
            int score_add = knife->getFruits_hit_count();
            _score+=score_add;
            
            _delegate->gameplay_score_didchange(_score);
            
            add_score_label(score_add, fruit_pos, false);
            
            int side = 0;
            
            if (knife->getPositionX() > fruit->getPositionX() + fruit->getBoundingBox().size.width * 0.15f) {
                side = 1; // right
            }
            else if (knife->getPositionX() <= fruit->getPositionX() - fruit->getBoundingBox().size.width * 0.15f) {
                side = 2; // left
            }
            
            fruitSplash(fruit->_info.type, fruit_pos, side);
            fruitFlyToBlender(fruit->_info.type, fruit_pos, side);
            
            pattern->remove_object(fruit);
            fruit->setVisible(false);
            fruit->setRemove_from_array(true);
            
            if (pattern) {
                if (pattern->_pattern_movable_objects.size() == 0) {
                     pattern->setVisible(false);
                    if (_knifes.size() > 0) {
                        for (Knife * k : _knifes) {
                            if (k->getFruits_hit_count() == 0) {
                                k->setRemove_from_array(true);
                            }
                        }
                    }
                }
            }
        }
    }
}

bool Gameplayb2d::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB){
    return SPPhysicsLayer::ShouldCollide(fixtureA, fixtureB);
}

void Gameplayb2d::fruitSplash(fruit_type _type, Point _position, int side){
    
    std::string animation_name = "";
    
    if (side == 1) {
        animation_name = "left";
    }
    else if (side == 2){
        animation_name = "right";
    }
    
    SkeletonAnimation * _effect = SPACE->get_spine_skeleton_animation("spine/splash/", "splash", true);
    _effect->clearTracks();
    _effect->setSkin(Recipes::get_splash_skin_name(_type));
    _effect->update(0);
    _effect->setScale((getContainer()->getContentSize().height * 0.2f) / _effect->getBoundingBox().size.height);
    _effect->setPosition(_position);
    addChild(_effect, 90);
    _effect->setTimeScale(1.0f);
    _effect->setCompleteListener([this, _effect, animation_name](spTrackEntry* entry){
        if (Game::is_same_strings(entry->animation->name, "splash")) {
            _nodes_to_delete.push_back(_effect);
        }
    });
    _effect->setAnimation(0, "splash", false);
    
    if (animation_name.length() > 0) {
        //_effect->addAnimation(1, animation_name, false);
    }
   
   // auto jump = JumpTo::create(0.5f, _position, getContainer()->getContentSize().height * random(0.1f, 0.2f), 1);
   // auto ease = EaseIn::create(jump, 2.2f);
   // _effect->runAction(ease);
    
    spBone * rotator_big        = _effect->findBone("rotator_big");
    spBone * rotator_mid        = _effect->findBone("rotator_mid");
    spBone * rotator_sml        = _effect->findBone("rotator_sml");
    spBone * rotator_blur       = _effect->findBone("rotator_blur");
    spBone * rotator_splash     = _effect->findBone("rotator_splash");
    
    if (rotator_big) {
        rotator_big->rotation = random(0, 360);
    }
    if (rotator_mid) {
        rotator_mid->rotation = random(0, 360);
    }
    if (rotator_sml) {
        rotator_sml->rotation = random(0, 360);
    }
    if (rotator_blur) {
        rotator_blur->rotation = random(0, 360);
    }
    if (rotator_splash) {
        rotator_splash->rotation = random(0, 360);
    }
    
    _effect->updateTransform();
}

void Gameplayb2d::fruitFlyToBlender(fruit_type _type, Point _position, int side){
    
    
    float duration = 0;
    
    for (int i = 0; i < 2; i++) {
        
        int zored = 91;
        
        if (i == 1) {
            zored = 89;
        }
        
        std::string folder_name = "spine/watermellon/";
        std::string file_name   = "watermelon_slice";
        float scale_offset      = 0.78f;
        
        if (_type == fruit_type_orange) {
            folder_name  = "spine/orange/";
            file_name    = "orange_slice";
            scale_offset = 0.6f;
        }
        else if (_type == fruit_type_lemon) {
            folder_name  = "spine/lemon/";
            file_name    = "lemon_slice";
            scale_offset = 0.6f;
        }
        else if (_type == fruit_type_pineapple) {
            folder_name  = "spine/pineapple/";
            file_name    = "pineapple_slice";
            scale_offset = 0.7f;
        }
        else if (_type == fruit_type_kivi) {
            folder_name  = "spine/kivi/";
            file_name    = "kivi_slice";
            scale_offset = 0.55f;
        }
        else if (_type == fruit_type_apple) {
            folder_name  = "spine/apple/";
            file_name    = "apple_slice";
            scale_offset = 0.6f;
        }
        else if (_type == fruit_type_mango) {
            folder_name  = "spine/mango/";
            file_name    = "mango_slice";
            scale_offset = 0.6f;
        }
        
        SkeletonAnimation * _effect = SPACE->get_spine_skeleton_animation(folder_name.c_str(), file_name.c_str(), true);
        _effect->clearTracks();
        _effect->update(0);
        _effect->setScale((getContainer()->getContentSize().height * scale_offset) / _effect->getBoundingBox().size.height);
        _effect->setPosition(_position);
        addChild(_effect, zored);
        _effect->setTimeScale(1.0f);
        
        
        
        std::string last_animation_side = "R";
        if (i == 1) {
            last_animation_side = "L";
        }
        
        
        
        std::string animation_1_name = StringUtils::format("split_%s", last_animation_side.c_str());
      
        _effect->clearTracks();
        
        if (_effect) {
            _effect->setAnimation(0, animation_1_name, false);
        }
        
        
        Point end_point = Point(mixer->getPositionX(), mixer->getPositionY() + mixer->getBoundingBox().size.height * 0.4f);
        
        float right_offset = random(0.15f, 0.25f);
        
        Point point_1 = Point(_effect->getPositionX() + getContainer()->getContentSize().width * right_offset, _effect->getPositionY() - getContainer()->getContentSize().width * right_offset);
        Point point_2 = point_1;
        
        if (i == 1) {
            
            float left_offset = random(0.08f, 0.12f);
            
            point_1 = Point(end_point.x - getContainer()->getContentSize().width * left_offset, _effect->getPositionY() - getContainer()->getContentSize().width * left_offset);
            point_2 = point_1;
        }
        
        ccBezierConfig bezier;
        bezier.controlPoint_1 = point_1;
        bezier.controlPoint_2 = point_2;
        bezier.endPosition    = end_point;
        
        
        if (i == 0) {
            duration = random(0.4f, 0.5f);
        }
        else if (i == 1) {
            duration += random(0.05f, 0.1f);
        }
        
        float rate = random(0.65f, 1.2f);
        
        auto bezierTo = BezierTo::create(duration, bezier);
        auto scaleTo  = ScaleTo::create(duration, _effect->getScale() * 0.65f);
        auto spawn    = Spawn::create(bezierTo, scaleTo, NULL);
        auto callf    = CallFunc::create([this, _effect, _type]{
            _nodes_to_delete.push_back(_effect);
            
            int steps = random(4, 8);
            
            Point pos = Point(mixer->getPosition().x, mixer->getPositionY() + mixer->getBoundingBox().size.height * 0.35f);
            
            for (int i = 0; i < steps; i++) {
                
                float radius = getContentSize().width * random(0.15f, 0.35f);
                
                float angle = random(0, 80);
                
                if (random(0, 1) == 1) {
                    angle = -angle;
                }
                
                Point endPoint_item;
                endPoint_item.x          = sinf(CC_DEGREES_TO_RADIANS(angle)) * radius;
                endPoint_item.y          = cosf(CC_DEGREES_TO_RADIANS(angle)) * radius;
                Point final_pos_of_item  = Point(pos.x + endPoint_item.x, pos.y + endPoint_item.y);
                
                Sprite * circle = Sprite::create("circle_0_small.png");
                addChild(circle, 197);
                circle->setScale(getContainer()->getContentSize().width * random(0.01f, 0.02f) / circle->getContentSize().width);
                circle->setPosition(pos);
                circle->setColor(Recipes::getColorByfruitType(_type));
                
                
                float time          = random(1.2f, 1.6f);
                
                auto move           = MoveTo::create(time, final_pos_of_item);
                auto ease_m         = EaseOut::create(move, 2.2f);
                float scale_time    = random(0.4f, 0.8f);
                auto scale          = ScaleTo::create(scale_time, 0);
                auto easescale      = EaseIn::create(scale, 2.2f);
                auto spawn          = Spawn::create(ease_m,easescale, NULL);
                auto seq            = Sequence::create(spawn, RemoveSelf::create(), NULL);
                circle->runAction(seq);
            }
            
            
            
        });
        auto ease = EaseIn::create(spawn, rate);
        
        if (i == 0) {
            auto seq  = Sequence::create(ease, callf, NULL);
            _effect->runAction(seq);
        }
        else if (i == 1){
            auto callf2    = CallFunc::create([this, _type]{
                
                _fruits_in_mixer.push_back(_type);
                
                if (mixer) {
                    
                    int fruits_in_mixer_count = (int)_fruits_in_mixer.size();
                    
                    mixer->changeMixerFilledSegments(fruits_in_mixer_count, _type);
                    
                    int fruits_count       = (int)this->_fruits_in_mixer.size();
                    std::string sound_name = "mixer_grad/ev_blender_grad_";
                    sound_name.append(StringUtils::format("%i", fruits_count));

                    SoundDirector::playSound(sound_name.c_str());
                    
                    if (fruits_in_mixer_count >= _fruits_in_pattern) {
                        
                        last_fruit_color = Recipes::getColorByfruitType(_fruits_in_mixer.at(_fruits_in_mixer.size() - 1));
                        
                        PlatformManager::vibrate(6);
                        
                        SoundDirector::playSound("ev_blender_blend");
                        
                        recipe_info recipe = Recipes::check_receipe(_fruits_in_mixer);
                        //log("RECIPE NAME %s",recipe.name.c_str());
                        
                        mixer->mixNow(recipe.type);                        
                        _fruits_in_mixer.clear();
                        
                    }
                    
                }
            });
            auto seq  = Sequence::create(ease, callf2, callf, NULL);
            _effect->runAction(seq);
        }
        
        float angle = random(90, 360);
        if (i == 0) {
            angle = -angle;
        }
        
        auto rotate = RotateBy::create(duration, angle);
        auto ease_r = EaseIn::create(rotate, rate);
        _effect->runAction(ease_r);
    }
}

void Gameplayb2d::add_score_label(int score, Point pos, bool is_perfect){
    
    float font_height  = getContainer()->getContentSize().height * 0.02f;
    float fly_distance = getContainer()->getContentSize().height * 0.05f;
    std::string title  = StringUtils::format("+%i", score);
    
    if (is_perfect) {
        font_height  = getContainer()->getContentSize().height * 0.0165f;
        fly_distance = getContainer()->getContentSize().height * 0.075f;
    }
    
    /*
    Label * _score_label = Label::createWithTTF(title.c_str(), "fonts/Blogger_Sans-Bold.otf", font_height);
    _score_label->setColor(Color3B(62, 160, 157));
    addChild(_score_label, 10);
    _score_label->setOpacity(0);
    _score_label->setPosition(pos);
    
    auto scale      = ScaleTo::create(0.85f, 2.5f);
    auto move       = MoveBy::create(0.85f, Point(0, fly_distance));
    auto fade       = FadeTo::create(0.05f, 255);
    auto fade2      = FadeTo::create(0.3f, 0);
    auto delay      = DelayTime::create(0.75f);
    auto seq        = Sequence::create(fade, delay, fade2, NULL);
    auto spawn      = Spawn::create(scale, move, seq, NULL);
    auto ease       = EaseOut::create(spawn, 2.0f);
    auto remove     = RemoveSelf::create();
    auto seq2       = Sequence::create(ease, remove, NULL);
    _score_label->runAction(seq2);
    */
    
    float height = getContainer()->getContentSize().height * 0.04f;
   // height*=(1.0f+(0.1f*score));
    
    Label * label = Label::createWithTTF(title.c_str(), "fonts/Blogger_Sans-Bold.otf", height);
    label->setAlignment(TextHAlignment::CENTER);
    addChild(label,1000);
    
    bool dark_mode_on = Settings::getStateOn(settings_darkmode);
    
    if (dark_mode_on == true) {
        label->setColor(Color3B(255, 223, 46));
    }
    else{
        label->setColor(Color3B(62, 160, 157));
    }
    label->setPosition(pos);
    
    label->setScale(0);
    
    auto scale = ScaleTo::create(0.75f, 1);
    auto scale_e = EaseElasticOut::create(scale,01.5f);
    label->runAction(scale_e);
    
    auto move_by = MoveBy::create(1.25f, Vec2(0, getContainer()->getContentSize().height*0.1f));
    auto fade = FadeTo::create(0.25f, 0);
    auto seq = Sequence::create(Spawn::create(move_by,Sequence::create(DelayTime::create(0.65f),fade, NULL), NULL),RemoveSelf::create(), NULL);
    label->runAction(seq);
    
}

void Gameplayb2d::playFriutHitSound(fruit_type _type){
    switch (_type) {
        case fruit_type_watermelon:         SoundDirector::playSound("ev_hit_watermelon");              break;
        case fruit_type_orange:             SoundDirector::playSound("ev_hit_orange");                  break;
        case fruit_type_lemon:              SoundDirector::playSound("ev_hit_lemon");                   break;
        case fruit_type_apple:              SoundDirector::playSound("ev_hit_apple");                   break;
        case fruit_type_kivi:               SoundDirector::playSound("ev_hit_kiwi");                    break;
        case fruit_type_pineapple:          SoundDirector::playSound("ev_hit_pineapple");               break;
            
        default:                            SoundDirector::playSound("ev_slash_default");               break;
    }
}

void Gameplayb2d::getCoctail(RECIPE_TYPES _type){
    
    int wave     = current_level.wave;
    int patterns = (int)current_level._patterns.size();
    
    if (wave >= patterns) {
        
        int collected = Game::getCoctailsCollected();
        
        std::vector<objetive_recipe_info> fortune_wheel_objects = Recipes::get_objective_recipes();
        
        if (collected < fortune_wheel_objects.size()) {
            
            objetive_recipe_info recipe = fortune_wheel_objects.at(collected);
            _type                       = recipe.recipe_type;
            
            Game::setCoctailsCollected(collected+1);
        }
        else{
            _type = RECIPE_SUGAR_RUSH;  // ERROR case
        }

    }
    else{
        _type = RECIPE_DEFAULT;
    }

    //
    
    Coctail * _coctail = Coctail::create();
    _coctail->prepare(Size(getContainer()->getContentSize().width * 0.15f, getContainer()->getContentSize().height * 0.12f), _type);
    _coctail->setPosition(mixer->getPosition());
    _coctail->setRotation(0);
    addChild(_coctail, 190);
    
    _coctails_on_table.push_back(_coctail);
    
    float pos_y = table->getPositionY() + table->getBoundingBox().size.height * 0.45f + _coctail->getBoundingBox().size.height * 0.5f;
    
//
//    if (_type != RECIPE_DEFAULT) {
//
//        SoundDirector::playSound("ev_blender_shoot_coctail");
//
//        auto show_coctail_name = CallFunc::create([this, _type]{
//
//            CoctailNameField * nameField = CoctailNameField::create();
//            nameField->prepare(Size(getContainer()->getContentSize().width * 0.7f, getContainer()->getContentSize().height * 0.2f), _type);
//            nameField->setPosition(Point(getContentSize().width * 0.5f, getContentSize().height * 0.5f + this->getContainer()->getContentSize().height * 0.2f));
//            this->addChild(nameField, 180);
//
//            nameField->setScale(0.0f);
//
//            auto scale   = ScaleTo::create(0.6f, 1.0f);
//            auto ease    = EaseElasticOut::create(scale, 0.75f);
//            auto delay   = DelayTime::create(1.f);
//            auto scale2  = ScaleTo::create(0.3f, 0);
//            auto ease2   = EaseIn::create(scale2, 1.8f);
//            auto remove  = RemoveSelf::create();
//            auto seq     = Sequence::create(ease, delay, ease2, remove, NULL);
//            nameField->runAction(seq);
//
//        });
//        auto delay2 = DelayTime::create(0.15f);
//        auto seq11  = Sequence::create(delay2, show_coctail_name, NULL);
//        runAction(seq11);
//    }
//
    float dur = 0.8f;
    
    float x_pos  = getContentSize().width * 0.5f + ((_coctail->getContentSize().width * 1.05f) * _coctails_on_table.size());
    
    float h      = random(0.225f, 0.3f);
    
    std::string shoot_sound = "ev_blender_shoot";
    if (_type != RECIPE_DEFAULT) {
     //   shoot_sound = "ev_blender_shoot_coctail";
    }
    
    auto audio1  = CallFunc::create([this,shoot_sound]{    SoundDirector::playSound(shoot_sound.c_str());});
    auto jump    = JumpTo::create(dur, Point(x_pos, pos_y), getContainer()->getContentSize().height * /*0.4f*/h, 1);
    auto rotate  = RotateBy::create(dur, 360);
    auto ease_r  = EaseInOut::create(rotate, 2.3f);
    auto spawn   = Spawn::create(jump, ease_r, NULL);
    auto ease1   = EaseInOut::create(spawn, 0.85f);
    auto audio2  = CallFunc::create([this, _type, _coctail]{ SoundDirector::playSound("ev_blender_coctail_glass_land");
        
        for (int i = 0; i < _coctails_on_table.size(); i++) {
            Coctail * c = _coctails_on_table.at(i);
            if (_coctail == c) {
                _coctails_on_table.erase(_coctails_on_table.begin() + i);
                break;
            }
        }
        
    });
    auto jump2   = JumpTo::create(0.2f, Point(x_pos + (getContainer()->getContentSize().width * 0.06f), pos_y), getContainer()->getContentSize().height * 0.05f, 1);
    auto ease2   = EaseInOut::create(jump2, 0.85f);
    auto audio3  = CallFunc::create([this]{    SoundDirector::playSound("ev_blender_coctail_glass_slide");    });
    auto move    = MoveTo::create(0.4f, Point(getContentSize().width + _coctail->getBoundingBox().size.width, pos_y));
    auto ease3   = EaseInOut::create(move, 2.2f);
    auto delay   = DelayTime::create(0.8f);
    auto remove  = RemoveSelf::create();
    auto reward_show = CallFunc::create([this,_type]{
        this->showCoctailReward(_type);
    });
    auto seq     = Sequence::create(audio1, ease1, audio2, ease2, delay, audio3,reward_show, ease3, remove, NULL);
    
    _coctail->runAction(seq);
    
    
    
    int steps = random(10, 15);
    
    Point pos = Point(mixer->getPosition().x, mixer->getPositionY() + mixer->getBoundingBox().size.height * 0.5f);
    
    for (int i = 0; i < steps; i++) {
        
        float radius = getContentSize().width * random(0.3f, 0.5f);
        
        float angle = random(0, 80);
        
        if (random(0, 1) == 1) {
            angle = -angle;
        }
        
        Point endPoint_item;
        endPoint_item.x          = sinf(CC_DEGREES_TO_RADIANS(angle)) * radius;
        endPoint_item.y          = cosf(CC_DEGREES_TO_RADIANS(angle)) * radius;
        Point final_pos_of_item  = Point(pos.x + endPoint_item.x, pos.y + endPoint_item.y);
        
        Sprite * circle = Sprite::create("circle_0_small.png");
        addChild(circle, 197);
        circle->setScale(getContainer()->getContentSize().width * random(0.02f, 0.035f) / circle->getContentSize().width);
        circle->setPosition(pos);
        circle->setColor(last_fruit_color);
        
        
        float time          = random(1.2f, 1.6f);
        
        auto move           = MoveTo::create(time, final_pos_of_item);
        auto ease_m         = EaseOut::create(move, 2.2f);
        float scale_time    = random(0.4f, 0.8f);
        auto scale          = ScaleTo::create(scale_time, 0);
        auto easescale      = EaseIn::create(scale, 2.2f);
        auto spawn          = Spawn::create(ease_m,easescale, NULL);
        auto seq            = Sequence::create(spawn, RemoveSelf::create(), NULL);
        circle->runAction(seq);
    }
    
    
}

void Gameplayb2d::showCoctailReward(RECIPE_TYPES recipe_type){
    
    //SoundDirector::playSound("ev_coins_earn");
    
    Vec2 point_from = Vec2(getContentSize().width*0.5f+(getContainer()->getContentSize().width*0.3f), getContainer()->getContentSize().height*0.3f);
    
    if (_coctails_on_table.size() > 0){
        Coctail *coctail = _coctails_on_table.at(0);
        point_from       = coctail->getParent()->convertToWorldSpace(coctail->getPosition());
    }
    
    bool is_gem = false;
    int give_ammout = 0;
    
     if (recipe_type == RECIPE_DEFAULT) {
         
         int coins_give = 3;
         int random_val     = random(0,100);
         
         if (random_val >= 0 && random_val < 50) {
             coins_give = 1;
         }
         else if (random_val >= 50 && random_val < 80){
             coins_give = 2;
         }
         else{
             coins_give = 3;
         }
         
         give_ammout = coins_give;
         
         Game::addCoins(give_ammout);
         
         auto seq = Sequence::create(DelayTime::create(1.0f),CallFunc::create([this]{
             _hud->refresh_coins(0,true);
         }), NULL);
         runAction(seq);
         
         for (int x=0; x< coins_give; x++) {
             _delegate->gameplay_coins_fly(point_from, FLYING_OBJECT_TYPE_COIN,nullptr);
         }
         
     }
     else{
         
         int gems_give  = 5;
         is_gem         = true;
         give_ammout    = gems_give;
         
         Game::addGems(give_ammout);
         
         auto seq = Sequence::create(DelayTime::create(1.0f),CallFunc::create([this]{
             _hud->refresh_gems(0,true);
         }), NULL);
         runAction(seq);

         for (int x=0; x< gems_give; x++) {
             _delegate->gameplay_coins_fly(point_from, FLYING_OBJECT_TYPE_GEM,nullptr);
         }
         
     }
    
    recipe_info info       = Recipes::getReceipe(recipe_type);
    std::string coin_label = StringUtils::format("+%i COINS",give_ammout);
    
    if (give_ammout == 1) {
       coin_label = StringUtils::format("+%i COIN",give_ammout);
    }
    
    if (is_gem){
        coin_label = StringUtils::format("+%i GEMS",give_ammout);
        
        if (give_ammout == 1) {
            coin_label = StringUtils::format("+%i GEM",give_ammout);
        }
    }
    
    Label * label = Label::createWithTTF(coin_label.c_str(), "fonts/Blogger_Sans-Bold.otf", getContainer()->getContentSize().height * 0.035f);
    label->setAlignment(TextHAlignment::CENTER);
    addChild(label,1000);
    label->setColor(Color3B(62, 160, 157));
    label->setPosition(Vec2(getContentSize().width*0.5f+(getContainer()->getContentSize().width*0.35f), getContainer()->getContentSize().height*0.3f));
    
    auto move_by = MoveBy::create(1.0f, Vec2(0, getContainer()->getContentSize().height*0.1f));
    auto fade = FadeTo::create(0.75f, 0);
    auto seq = Sequence::create(Spawn::create(move_by,Sequence::create(DelayTime::create(0.25f),fade, NULL), NULL),RemoveSelf::create(), NULL);
    label->runAction(seq);
    
}
