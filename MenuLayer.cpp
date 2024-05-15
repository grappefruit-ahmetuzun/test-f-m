//
//  MenuLayer.cpp
//  FruitsKnife-mobile
//
//  Created by Marek on 16/05/2018.
//

#include "MenuLayer.h"
#include "Settings.h"
#include "SoundDirector.h"

void MenuLayer::prepare(){
    
    setTouchBlock(false);
    
    /*logo = Sprite::create("menu/full_logo.png");
    addChild(logo);
    logo->setScale(getContainer()->getContentSize().width * 1.25f / logo->getContentSize().width);
    logo->setPosition(Vec2(getContentSize().width*0.5f,
                           getContentSize().height*0.5f+getContainer()->getContentSize().height*0.25f));
    
*/
    
    SkeletonAnimation * _logo_spine = SPACE->get_spine_skeleton_animation("spine/logo/", "logo", true);
    _logo_spine->clearTracks();
    _logo_spine->update(0);
    _logo_spine->setScale(getContainer()->getContentSize().width * 1.25f / _logo_spine->getBoundingBox().size.width);
    _logo_spine->setPosition(Vec2(getContentSize().width*0.5f,
                                  getContentSize().height*0.5f+getContainer()->getContentSize().height*0.225f));
    addChild(_logo_spine);
    _logo_spine->setTimeScale(1.0f);
    
    if (Game::getInstance()->getLogo_animation_showed() == false) {
        Game::getInstance()->setLogo_animation_showed(true);
        
        _logo_spine->setAnimation(0, "start2", false);
        _logo_spine->addAnimation(0, "idle3", true);
        
        SoundDirector::playSound("ev_logo");
    }
    else{
        _logo_spine->setAnimation(0, "idle3", true);
    }
    
 
    
    tap_to_start_label = Label::createWithTTF(StringUtils::format("TAP TO PLAY"), "fonts/Blogger_Sans-Bold.otf", getContainer()->getContentSize().height*0.025f);
    tap_to_start_label->setPosition(getContentSize().width * 0.5f, getContentSize().height*0.5f - getContainer()->getContentSize().height*0.25f);
    //tap_to_start_label->setRotation(-10);
    //tap_to_start_label->setRotationSkewX(5);
    addChild(tap_to_start_label);
    tap_to_start_label->setColor(Color3B(0, 0, 0));
    
    auto scale          = ScaleTo::create(0.35f, 1.25f);
    auto scale2         = ScaleTo::create(0.35f, 1.0f);
    auto scale_seq      = Sequence::create(scale,scale2, NULL);
    auto scale_seq_e    = EaseInOut::create(scale_seq, 1.5f);
    auto scale_repeat   = RepeatForever::create(scale_seq_e);
    tap_to_start_label->runAction(scale_repeat);
    
    
    customzie_button = SPButton::createWithImage("menu/customize.png");
    addChild(customzie_button);
    customzie_button->setScale(getContainer()->getContentSize().width * 0.45f / customzie_button->getContentSize().width);
    customzie_button->setVisible(false);

}

void MenuLayer::animate_menu_start(){
    
    customzie_button->setVisible(true);
    customzie_button->setPosition(Point(getContentSize().width * 0.5f, -customzie_button->getBoundingBox().size.height * 1.5f));
    
    auto move = MoveTo::create(0.5f, Point(getContentSize().width * 0.5f, getContentSize().height * 0.5f - getContainer()->getContentSize().height * 0.33f));
    auto ease = EaseElasticOut::create(move, 0.7f);
    customzie_button->runAction(ease);

}

void MenuLayer::refrsh_dark_mode_button(){
    bool dark_mode_on = Settings::getStateOn(settings_darkmode);
    if (dark_mode_on == true) {
        if (tap_to_start_label) {
            tap_to_start_label->setColor(Color3B(106, 180, 173));
        }
    }
    else{
        if (tap_to_start_label) {
            tap_to_start_label->setColor(Color3B(0, 0, 0));
        }
    }
}
