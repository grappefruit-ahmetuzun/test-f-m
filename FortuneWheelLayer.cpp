//
//  FortuneWheelLayer.cpp
//  FruitsKnife-mobile
//
//  Created by Slavik on 6/6/18.
//

#include "FortuneWheelLayer.h"
#include "AdManager.h"
#include "Patterns.h"
#include "Settings.h"
#include "AdManager.h"
#include "GameScene.h"
#include "FortuneWheelLayer.h"

bool FortuneWheelLayer::init(){
    if (!GameLayer::init()){
        return false;
    }
    
    _background = Sprite::create();
    _background->setTextureRect(Rect(0, 0, getContentSize().width, getContentSize().height));
    _background->setPosition(getContentSize()/2);
    addChild(_background);
    
    bool dark_mode_on = Settings::getStateOn(settings_darkmode);
    
    if (dark_mode_on == true) {
        _background->setColor(Color3B(2, 72, 79));
    }
    else{
        _background->setColor(Color3B(225, 241, 241));
    }
    
    _background->setScale(getContentSize().height / _background->getContentSize().height);
    
    if (_background->getBoundingBox().size.width < getContentSize().width) {
        _background->setScaleX(getContentSize().width / _background->getContentSize().width);
    }
    
    _background->setVisible(false);
    
    
    
    _fortune_wheel = Wheel::create();
    addChild(_fortune_wheel);
    _fortune_wheel->prepare();
    _fortune_wheel->setScale(getContainer()->getContentSize().width * 0.7f / _fortune_wheel->getContentSize().width);
    _fortune_wheel->setPosition(Point(getContentSize().width * 0.5f, getContentSize().height * 0.5f + getContainer()->getContentSize().height * 0.05f));
    
    _black_arrow = Sprite::create("fortune_wheel/arrow.png");
    _black_arrow->setAnchorPoint(Point(0.5f, 0.8f));
    _black_arrow->setScale(getContainer()->getContentSize().width * 0.08f / _black_arrow->getContentSize().width);
    _black_arrow->setPosition(Point(getContentSize().width * 0.5f, _fortune_wheel->getPositionY() + getContainer()->getContentSize().height * 0.25f));
    addChild(_black_arrow);
    _black_arrow->setVisible(false);
    
    //if (dark_mode_on == false) {
        _black_arrow->setColor(Color3B::BLACK);
   // }
    
    _spin_button = SPButton::createWithImage("fortune_wheel/spin.png");
    addChild(_spin_button);
    _spin_button->setScale(getContainer()->getContentSize().height * 0.1f / _spin_button->getContentSize().height);
    _spin_button->setPosition(Point(getContentSize().width * 0.5f, getContentSize().height * 0.5f - getContainer()->getContentSize().height * 0.25f));
    _spin_button->setVoidTouchDownCallback(CC_CALLBACK_0(FortuneWheelLayer::spin, this));

    
    _spin_again_button = SPButton::createWithImage("fortune_wheel/again.png");
    addChild(_spin_again_button);
    _spin_again_button->setScale(getContainer()->getContentSize().height * 0.1f / _spin_again_button->getContentSize().height);
    _spin_again_button->setPosition(Point(getContentSize().width * 0.5f, getContentSize().height * 0.5f - getContainer()->getContentSize().height * 0.25f));
    _spin_again_button->setVoidTouchDownCallback(CC_CALLBACK_0(FortuneWheelLayer::spin_again, this));
    
    
    {
        float continue_scale_val = _spin_again_button->getScale();
        
        auto scale_1   = ScaleTo::create(0.15f, continue_scale_val * 1.065f);
        auto ease1     = EaseInOut::create(scale_1, 2.2f);
        auto scale_2   = ScaleTo::create(0.15f, continue_scale_val * 1.f);
        auto ease2     = EaseInOut::create(scale_2, 2.2f);
        auto scale_seq = Sequence::create(ease1,ease2, NULL);
        auto repeat    = Repeat::create(scale_seq,2);
        auto seq       = Sequence::create(repeat,DelayTime::create(0.35f), NULL);
        auto rep_fore  = RepeatForever::create(seq);
        rep_fore->setTag(10);
        _spin_again_button->runAction(rep_fore);
    }

    
    
    Size button_size = Size(getContainer()->getContentSize().width*0.5f,getContainer()->getContentSize().height*0.0275f);
    
    _nothanks_button = SPButton::createWithTTF(button_size, "NO THANKS", "fonts/Blogger_Sans-Bold.otf", button_size.height);
    addChild(_nothanks_button);
    _nothanks_button->setPosition(Vec2(getContentSize().width*0.5f, getContentSize().height * 0.5f - (getContainer()->getContentSize().height * 0.35f)));
    _nothanks_button->getLabel()->setColor(Color3B(160, 160, 160));
    _nothanks_button->setTouchAreaScale(2.0f);
    _nothanks_button->setVoidTouchDownCallback([this]{
        restart_scene();
    });
    _nothanks_button->setScale(0);
    
    
    _nothanks_button->setActive(false);
    _nothanks_button->setVisible(false);
    _spin_again_button->setVisible(false);
    _spin_again_button->setActive(false);
    _spin_button->setVisible(false);
    _spin_button->setActive(false);
    
    
    
    
    scheduleUpdate();
    
    return true;
}

void FortuneWheelLayer::spin(){
    
    if (_fortune_wheel->can_spin) {
        
        Director::getInstance()->getEventDispatcher()->setEnabled(false);
        
        _fortune_wheel->can_spin = false;
        
        spinning = true;
        
        spin_count++;
        
        if (spin_count == 1) {
            if (_spin_button) {
                _spin_button->setVisible(false);
                _spin_button->setActive(false);
            }
            
            Patterns::getInstance()->generate_new_coctails();
        }
        else if (spin_count == 2){
            
            _rotation_for_sound                 = 0;
            _previous_wheel_rotation_for_sounds = 0;
            
            if (_spin_again_button) {
                _spin_again_button->setVisible(false);
                _spin_again_button->setActive(false);
            }
        }
        
        int segments_count = (int)_fortune_wheel->_all_parts.size();
        
        float radius_of_one_segment  = (360.0f / segments_count);
        
        WheelPart * part     = _fortune_wheel->get_winner_part(spin_count);
        
        if (part) {
            //int index_of_reward  = (int)part->index;
            
            //CCLOG("REWARD: %i", part->_item._count_of_tokens);
            
            float rot            = part->getRotation();
            float offset         = (radius_of_one_segment - (360.0f / segments_count)) / 2;
            float segment_offset = radius_of_one_segment * random(0.05f, 0.95f);
            float angle          = 2520 + (360.0f - (rot - radius_of_one_segment/2)) - (_fortune_wheel->getRotation() + ((360.0f / segments_count)/2)) - offset - segment_offset;
            
            auto rotate     = RotateBy::create(6.f, angle);
            auto ease       = EaseQuarticActionOut::create(rotate);
            auto after_spin = CallFunc::create([this, part]{
                
                if (part->_item.recipe_category == RECIPE_CATEGORY_KNIFE) {
                    if (part->item_sprite) {
                        part->item_sprite->setColor(Color3B::WHITE);
                        part->item_sprite->setOpacity(255);
                    }
                }
                
                spinning = false;
                
                PlatformManager::vibrate(5);
                
                if (_did_win_callback){
                    Vec2 position = part->item_bg->getParent()->convertToWorldSpace(part->item_bg->getPosition());
                    _did_win_callback(part->_item,position);
                }
                
                Director::getInstance()->getEventDispatcher()->setEnabled(true);
                
                _fortune_wheel->remove_part(part);
            
                
                int segments_count  = (int)_fortune_wheel->_all_parts.size();
                float angle_of_part = (360.0f / segments_count);
                
                
                auto delay_   = DelayTime::create(0.3f);
                auto rotate   = RotateTo::create(0.6f, -angle_of_part/2);
                auto ease_rot = EaseInOut::create(rotate, 2.65f);
                auto seq      = Sequence::create(delay_, ease_rot, NULL);
                _fortune_wheel->runAction(seq);
         
                
                if (spin_count == 1) {
                    if (AdManager::getInstance()->is_available_VideoAd()) {
                        _spin_again_button->setVisible(true);
                        _spin_again_button->setActive(true);
                        
                        _spin_again_button->setScale(0);
                        
                        auto scale = ScaleTo::create(0.4f, getContainer()->getContentSize().height * 0.1f / _spin_again_button->getContentSize().height);
                        auto ease  = EaseElasticOut::create(scale, 0.65f);
                        _spin_again_button->runAction(ease);
                        
                        
                        auto delay_for_not = DelayTime::create(1.f);
                        auto callf         = CallFunc::create([this]{
                            auto scale = ScaleTo::create(0.4f, 1.0f);
                            auto ease  = EaseElasticOut::create(scale, 0.6f);
                            _nothanks_button->runAction(ease);
                            _nothanks_button->setActive(true);
                            _nothanks_button->setVisible(true);
                        });
                        auto seq_for_not   = Sequence::create(delay_for_not, callf, NULL);
                        seq_for_not->setTag(2233);
                        runAction(seq_for_not);
                    }
                    else{
                        
                        if (this->getActionByTag(2233)) {
                            this->stopActionByTag(2233);
                        }
                        
                        _nothanks_button->stopAllActions();
                        _nothanks_button->setActive(false);
                        _nothanks_button->setVisible(false);
                        
                        show_next_level_button();
                    }
                }
                else if (spin_count == 2){
                    auto delay = DelayTime::create(1.f);
                    auto callf = CallFunc::create([this]{
                        show_next_level_button();
                    });
                    auto seq   = Sequence::create(delay, callf, NULL);
                    runAction(seq);
                }
            });
            auto seq    = Sequence::create(ease, after_spin, NULL);
            _fortune_wheel->runAction(seq);
        }
    }
}

void FortuneWheelLayer::show_next_level_button(){
    
    if (!_next_level_button) {
        _next_level_button = SPButton::createWithImage("gameover/next.png");
        addChild(_next_level_button);
        _next_level_button->setScale(getContainer()->getContentSize().height * 0.1f / _next_level_button->getContentSize().height);
        _next_level_button->setPosition(Point(getContentSize().width * 0.5f, getContentSize().height * 0.5f - getContainer()->getContentSize().height * 0.25f));
        _next_level_button->setVoidTouchDownCallback(CC_CALLBACK_0(FortuneWheelLayer::restart_scene, this));
        
        _next_level_button->setScale(0);
        
        auto scale = ScaleTo::create(0.4f, getContainer()->getContentSize().height * 0.1f / _next_level_button->getContentSize().height);
        auto ease  = EaseElasticOut::create(scale, 0.65f);
        _next_level_button->runAction(ease);
    }
}

void FortuneWheelLayer::restart_scene(){
    Game::getInstance()->setDidSeeMenu(false);
    Director::getInstance()->replaceScene(TransitionFade::create(0.3f, GameScene::createScene(), Color3B::BLACK));
}

void FortuneWheelLayer::spin_again(){
    if (AdManager::getInstance()->is_available_VideoAd()) {
        AdManager::getInstance()->show_VideoAd(WATCH_VIDEO_TYPE_REWARD_SPIN_AGAIN);
    }
}

void FortuneWheelLayer::animate_on_start(){
    
    _fortune_wheel->setScale(0);
    
    auto scale = ScaleTo::create(0.5f, getContainer()->getContentSize().width * 0.7f / _fortune_wheel->getContentSize().width);
    auto ease  = EaseElasticOut::create(scale, 0.55f);
    _fortune_wheel->runAction(ease);
    
    
    _background->setVisible(true);
    _background->setOpacity(0);
    
    auto fade  = FadeTo::create(0.3f, 255 * 0.7f);
    auto ease2 = EaseInOut::create(fade, 2.2f);
    _background->runAction(ease2);
    
    auto delay = DelayTime::create(1.f);
    auto callf = CallFunc::create([this]{
        _black_arrow->setVisible(true);
        _black_arrow->setScale(0);
        _black_arrow->setRotation(90);
        
        auto scale  = ScaleTo::create(0.4f, getContainer()->getContentSize().width * 0.08f / _black_arrow->getContentSize().width);
        auto rotate = RotateTo::create(0.4f, 0);
        auto spawn  = Spawn::create(scale, rotate, NULL);
        auto ease   = EaseElasticOut::create(spawn, 0.6f);
        _black_arrow->runAction(ease);
        
    });
    auto seq   = Sequence::create(delay, callf, NULL);
    runAction(seq);
}

void FortuneWheelLayer::update(float delta){
    
    if (_fortune_wheel && spinning) {
        
        float rot = _fortune_wheel->getRotation();
        
        float _diff_between_rotations = fabsf(rot - _previous_wheel_rotation_for_sounds);
        _previous_wheel_rotation_for_sounds = rot;
        
        _rotation_for_sound += _diff_between_rotations;
        
        float radius_of_one_segment = ((float)360.0f / _fortune_wheel->_all_parts.size());
        
        if (_rotation_for_sound >= radius_of_one_segment) {
            _rotation_for_sound = (_rotation_for_sound - radius_of_one_segment);
            
            SoundDirector::playSound("fortunewheel/ev_fortune_wheel_tick");
            
            PlatformManager::vibrate(2);
            
            if (_black_arrow->getActionByTag(222)) {
                _black_arrow->stopActionByTag(222);
                _black_arrow->setRotation(0);
            }
            
            if (_black_arrow->getActionByTag(333)) {
                _black_arrow->stopActionByTag(333);
            }
            
            auto rotate  = RotateTo::create(0.02f, -15);
            auto rotate2 = RotateTo::create(0.065f, 0);
            auto seq     = Sequence::create(rotate, rotate2, NULL);
            seq->setTag(333);
            _black_arrow->runAction(seq);
        }
    }
}

void FortuneWheelLayer::show_spin_button(){
    
    SoundDirector::playSound("fortunewheel/ev_spin_button_appear");
    
    _spin_button->setVisible(true);
    _spin_button->setActive(true);
    
    _spin_button->setScale(0);
    
    auto scale = ScaleTo::create(0.4f, getContainer()->getContentSize().height * 0.1f / _spin_button->getContentSize().height);
    auto ease  = EaseElasticOut::create(scale, 0.65f);
    auto callf = CallFunc::create([this]{
        float continue_scale_val = _spin_button->getScale();
        
        auto scale_1   = ScaleTo::create(0.4f, continue_scale_val * 1.065f);
        auto ease1     = EaseInOut::create(scale_1, 2.2f);
        auto scale_2   = ScaleTo::create(0.4f, continue_scale_val * 1.f);
        auto ease2     = EaseInOut::create(scale_2, 2.2f);
        auto scale_seq = Sequence::create(ease1,ease2, NULL);
        auto rep_fore  = RepeatForever::create(scale_seq);
        rep_fore->setTag(10);
        _spin_button->runAction(rep_fore);
    });
    auto seq = Sequence::create(ease, callf, NULL);
    _spin_button->runAction(seq);
}

bool FortuneWheelLayer::onTouchBegan(Touch *touch, Event *event){
    return false;
}
