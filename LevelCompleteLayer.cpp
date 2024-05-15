//
//  LevelCompleteLayer.cpp
//  FruitsKnife-mobile
//
//  Created by Slavik on 5/30/18.
//

#include "LevelCompleteLayer.h"
#include "WheelPart.h"
#include "Settings.h"

void LevelCompleteLayer::animateOnEnter(int lvl) {
    
//    getBg()->setColor(Color3B(221, 242, 242));
//    getBg()->setOpacity(0);
//    getBg()->runAction(FadeTo::create(0.15f, 255*0.8f));
    
    Vec2 ribbon_pos = Point(getContentSize().width * 0.5f, getContentSize().height * 0.5f + getContainer()->getContentSize().height * 0.25f);
    
    std::string ribbon_texture = "ui/ribbon.png";
    
    bool dark_mode_on = Settings::getStateOn(settings_darkmode);
    
    if (dark_mode_on == true) {
        ribbon_texture = "ui/ribbon_yellow.png";
    }
    
    field = Sprite::create(ribbon_texture.c_str());
    field->setScale(getContainer()->getContentSize().width / field->getContentSize().width);
    field->setPosition(ribbon_pos);
    addChild(field, 5);
    
    level_label = Label::createWithTTF(StringUtils::format("LEVEL %i COMPLETED!", lvl), "fonts/Blogger_Sans-Bold.otf", getContentSize().height * 0.035f);
    level_label->setPosition(field->getContentSize().width * 0.5f, field->getContentSize().height * 0.485f);
    level_label->setSkewY(8);
    field->addChild(level_label);
    level_label->setOpacity(0);
    
    level_label->setColor(Color3B(237, 112, 107));
    
    if (dark_mode_on == true) {
        level_label->setColor(Color3B(34, 80, 88));
    }
    
    beamz = Sprite::create("ui/beamz.png");
    beamz->setPosition(field->getPosition());
    beamz->setScale(getContainer()->getContentSize().width * 0.8f / beamz->getContentSize().width);
    addChild(beamz, 3);
    
    if (dark_mode_on == true) {
        beamz->setOpacity(255 * 0.5f);
    }
    else{
        beamz->setOpacity(255 * 0.75f);
    }
    
    auto rotate = RotateBy::create(0.2f, 30);
    auto repaet = RepeatForever::create(rotate);
    beamz->runAction(repaet);
    
    
    _effect = SPACE->get_spine_skeleton_animation("spine/levelComplete/", "starsLevelComplete", true);
    _effect->clearTracks();
    _effect->update(0);
    _effect->setScale((getContainer()->getContentSize().height * 0.4f) / _effect->getBoundingBox().size.height);
    _effect->setPosition(field->getPosition());
    addChild(_effect, 4);
    _effect->setTimeScale(1.0f);
    _effect->setVisible(false);
    
    
    field->setPosition(ribbon_pos+Vec2(0, +getContainer()->getContentSize().height*0.1f));
    field->setOpacity(0);
    
    float dur = 0.5f;
    
    auto move  = MoveTo::create(dur, ribbon_pos);
    auto ease  = EaseElasticOut::create(move, 0.5f);
    field->runAction(ease);
    
    auto fade  = FadeTo::create(dur, 255);
    auto easef  = EaseInOut::create(fade, 2.3f);
    field->runAction(easef);
    
    auto fade2 = FadeTo::create(dur, 255);
    level_label->runAction(fade2);
    
    auto delay = DelayTime::create(0.2f);
    auto callf = CallFunc::create([this]{
        _effect->setVisible(true);
        _effect->setAnimation(0, "start2", false);
        _effect->addAnimation(0, "idle", true);
    });
    auto seq1 = Sequence::create(delay, callf, NULL);
    runAction(seq1);
    
    
    beamz->setScale(0);
    auto scale = ScaleTo::create(dur, getContainer()->getContentSize().width * 0.8f / beamz->getContentSize().width);
    auto ease22 = EaseElasticOut::create(scale, 0.65f);
    beamz->runAction(ease22);
    
    obj = CoctailsObjectiveLarge::create();
    addChild(obj, 10);
    obj->prepare(Size(getContainer()->getContentSize().width, getContainer()->getContentSize().height*0.115f));
    obj->setPosition(getContentSize()*0.5f);
    obj->hide_all();
    objectives = obj;
    
    objective_indicator = CoctailObjectiveUI::create();
    addChild(objective_indicator);
    objective_indicator->prepare(getContainer()->getContentSize().height*0.05f);
    objective_indicator->setPosition(Vec2(obj->getPositionX(),
                                          obj->getPositionY()- (obj->getContentSize().height*0.5f)-objective_indicator->getContentSize().height*0.75f));
    
    int collected = Game::getCoctailsCollected();
    int objective = Game::getCoctailsCollectObjective();
    
    //objective_indicator->setText(StringUtils::format("%i/%i COLLECTED",collected,objective).c_str());
    objective_indicator->setText(StringUtils::format("%i/%i",collected,objective).c_str());
    objective_indicator->hide_all();
    
    _fortuneWheelLayer = FortuneWheelLayer::create();
    _fortuneWheelLayer->setVisible(false);
    addChild(_fortuneWheelLayer, 8);
    
}

void LevelCompleteLayer::show_next_level_button(){
    
    next_level_button = SPButton::createWithImage("gameover/next.png");
    addChild(next_level_button, 10);
    next_level_button->setScale(getContainer()->getContentSize().width*0.55f/next_level_button->getContentSize().width);
    next_level_button->setPosition(Vec2(getContentSize().width*0.5f, getContentSize().height*0.5f-(getContainer()->getContentSize().height*0.325f)));
    
    auto scale = ScaleTo::create(0.5f, next_level_button->getScale());
    next_level_button->setScale(0);
    auto scale_e = EaseElasticOut::create(scale,1.5f);
    next_level_button->runAction(scale_e);
    
}

void LevelCompleteLayer::show_claim_reward_button(){
    
    claim_reward_button = SPButton::createWithImage("gameover/claim.png");
    addChild(claim_reward_button);
    claim_reward_button->setScale(getContainer()->getContentSize().width*0.55f/claim_reward_button->getContentSize().width);
    claim_reward_button->setPosition(Vec2(getContentSize().width*0.5f, getContentSize().height*0.5f-(getContainer()->getContentSize().height*0.325f)));
    claim_reward_button->setVoidTouchDownCallback(CC_CALLBACK_0(LevelCompleteLayer::on_claim_reward_press, this));
    
    float btn_scale = claim_reward_button->getScale();
    
    auto scale = ScaleTo::create(0.5f, claim_reward_button->getScale());
    claim_reward_button->setScale(0);
    auto scale_e = EaseElasticOut::create(scale,1.5f);
    claim_reward_button->runAction(scale_e);
    
    auto call = CallFunc::create([this,btn_scale]{
        
        auto scale          = ScaleTo::create(0.35f, btn_scale*1.05f);
        auto scale2         = ScaleTo::create(0.35f, btn_scale);
        auto scale_seq      = Sequence::create(scale,scale2, NULL);
        auto scale_ease     = EaseInOut::create(scale_seq, 1.5f);
        claim_reward_button->runAction(RepeatForever::create(scale_ease));
        
    });
    auto seq = Sequence::create(DelayTime::create(0.5f),call, NULL);
    runAction(seq);
    
}

void LevelCompleteLayer::animate_show_objectives(){
    
    if (objectives) {
        objectives->animate_cells_appear();
    }
    
}

void LevelCompleteLayer::on_claim_reward_press(){
    

    
    claim_reward_button->setVisible(false);
    claim_reward_button->setActive(false);
    
    auto scale = ScaleTo::create(0.2f, 0);
    auto ease  = EaseIn::create(scale, 2.f);
    
    beamz->runAction(ease->clone());
    _effect->runAction(ease->clone());
    
    auto fade  = FadeTo::create(0.2f, 0);
    auto ease2  = EaseIn::create(fade, 2.f);
    
    field->runAction(ease2);
    level_label->runAction(ease2->clone());
    
    objective_indicator->setVisible(false);
    
    auto move = MoveTo::create(0.35f, Point(obj->getPositionX(), getHeaderUIDefaultPosY() - getContainer()->getContentSize().height * 0.125f));
    auto ease_move = EaseInOut::create(move, 2.3f);
    obj->runAction(ease_move);
    
    for (int x=0; x < obj->_cells.size(); x++) {
        Sprite * cell = obj->_cells.at(x);
        
        auto jump = JumpBy::create(0.35f, Vec2(0, 0), cell->getBoundingBox().size.height*0.5f, 1);
        auto d = DelayTime::create(x*0.1f);
        auto seq = Sequence::create(d,jump, NULL);
        cell->runAction(seq);
        
    }
    
    SoundDirector::playSound("fortunewheel/ev_fortune_wheel_appear");
    
    auto delay = DelayTime::create(0.35f);
    auto callf = CallFunc::create([this]{
        
        _fortuneWheelLayer->setVisible(true);
        _fortuneWheelLayer->animate_on_start();
        
        auto delay = DelayTime::create(0.4f);
        auto callf = CallFunc::create([this]{
            
            for (int i = 0; i < obj->_cells.size(); i++) {
                Sprite * cell = obj->_cells.at(i);
                
                WheelPart * part        = _fortuneWheelLayer->_fortune_wheel->get_part_by_index(i);
                
                
                Point world_pos = part->item_bg->getParent()->convertToWorldSpace(part->item_bg->getPosition());
                Point node_pos  = cell->getParent()->convertToNodeSpace(world_pos);
                
                auto delay  = DelayTime::create(0.15f * i);
                auto move   = MoveTo::create(0.2f, node_pos);
                auto scale  = ScaleTo::create(0.2f, cell->getScale() * 0.5f);
                auto rotate = RotateBy::create(0.2f, 360);
                auto spawn  = Spawn::create(move, scale, rotate, NULL);
                auto ease   = EaseInOut::create(spawn, 2.3f);
                auto callf  = CallFunc::create([this, part]{
                    part->show_all_content();
                    
                    PlatformManager::vibrate(3);
                    
                    SoundDirector::playSound("fortunewheel/ev_single_tile_to_wheel");
                    
                    std::string texture_name = WheelPart::getPartImage(part->_item.recipe_category);
                    part->fill_middle->setTexture(texture_name.c_str());
                    
                    if (_fortuneWheelLayer->_fortune_wheel->getActionByTag(122)) {
                        _fortuneWheelLayer->_fortune_wheel->stopActionByTag(122);
                    }
                    
                    _fortuneWheelLayer->_fortune_wheel->setScale(_fortuneWheelLayer->getContainer()->getContentSize().width * 0.58f / _fortuneWheelLayer->_fortune_wheel->getContentSize().width);
                    
                    auto scale = ScaleTo::create(0.1f, _fortuneWheelLayer->getContainer()->getContentSize().width * 0.7f / _fortuneWheelLayer->_fortune_wheel->getContentSize().width);
                    auto ease  = EaseElasticOut::create(scale, 0.6f);
                    ease->setTag(122);
                    _fortuneWheelLayer->_fortune_wheel->runAction(ease);
                    
                });
                auto remove = RemoveSelf::create();
                auto seq    = Sequence::create(delay, ease, callf, remove, NULL);
                cell->runAction(seq);
            }
            
            auto delay = DelayTime::create(1.0f);
            auto callf = CallFunc::create([this]{
                _fortuneWheelLayer->show_spin_button();
            });
            auto seq   = Sequence::create(delay, callf, NULL);
            runAction(seq);
            
        });
        auto seq   = Sequence::create(delay, callf, NULL);
        runAction(seq);
        
    });
    auto seq   = Sequence::create(delay, callf, NULL);
    runAction(seq);
    
}

