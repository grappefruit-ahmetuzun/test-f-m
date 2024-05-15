//
//  ContinueLayer.cpp
//  BasketDunk
//
//  Created by Marek on 23/10/2017.
//
//

#include "ContinueLayer.h"
#include "SoundDirector.h"
#include "PlatformManager.h"

void ContinueLayer::prepare(){
    
    std::string bg_name = "continue/abc.png";
    
    Sprite *_background = Sprite::create(bg_name.c_str());
    _background->setPosition(getContentSize()/2);
    _background->setScale(getContentSize().height / _background->getContentSize().height);
    _background->setOpacity(255*0.975f);
    
    if (_background->getBoundingBox().size.width < getContentSize().width) {
        _background->setScaleX(getContentSize().width / _background->getContentSize().width);
    }
    
    addChild(_background);

    Label * _continue_label = Label::createWithTTF("CONTINUE?", "fonts/Blogger_Sans-Bold.otf", getContainer()->getContentSize().height * 0.065f);
    _continue_label->setPosition(getContentSize().width * 0.5f, getContentSize().height * 0.5f + (getContainer()->getContentSize().height * 0.375f));
    _continue_label->setColor(Color3B(254,205,49));
    addChild(_continue_label);
    
    Sprite * glass = Sprite::create("continue/glass.png");
    addChild(glass);
    glass->setScale(getContainer()->getContentSize().width*0.35f/glass->getContentSize().width);
    glass->setPosition(Vec2(getContentSize().width*0.5f, getContentSize().height*0.5f + getContainer()->getContentSize().height*0.085f));
    
    Sprite * beams = Sprite::create("continue/beamz_01.png");
    addChild(beams);
    beams->setScale(getContainer()->getContentSize().width*1.0f/beams->getContentSize().width);
    beams->setPosition(glass->getPosition());
    beams->setOpacity(175);
    
    beams->runAction(RepeatForever::create(RotateBy::create(3.0f, 360)));
    
    Sprite * continue_progress_sprite = Sprite::create("continue/drink.png");
    
    _progress = ProgressTimer::create(continue_progress_sprite);
    _progress->setScale(glass->getBoundingBox().size.width*1.0f / _progress->getContentSize().width);
    _progress->setType(cocos2d::ProgressTimer::Type::BAR);
    //_progress->setMidpoint(Point(0, continue_progress_sprite->getContentSize().height/2));
    _progress->setMidpoint(Point(continue_progress_sprite->getContentSize().height/2,0));
    _progress->setBarChangeRate(Point(0,1));
    _progress->setReverseDirection(false);
    _progress->setPercentage(100);
    _progress->setPosition(glass->getPosition());
    addChild(_progress);
    
    auto progress1        = ProgressFromTo::create(8.0f, 65, 0);
    auto progressFinished = CallFunc::create(CC_CALLBACK_0(ContinueLayer::progress_animation_did_finish, this));
    auto progress_seq     = Sequence::create(progress1,progressFinished, NULL);
    _progress->runAction(progress_seq);
    
    Sprite * reflection = Sprite::create("continue/ice_and_reflection.png");
    addChild(reflection);
    reflection->setScale(glass->getBoundingBox().size.width*1.0f /reflection->getContentSize().width);
    reflection->setPosition(glass->getPosition());
    
    
    _continue_button = SPButton::createWithImage("continue/continue.png");
    addChild(_continue_button);
    _continue_button->setScale(getContainer()->getContentSize().width * 0.5f / _continue_button->getContentSize().width);
    _continue_button->setPosition(Vec2(getContentSize().width * 0.5f,
                                       getContentSize().height * 0.5f - (getContainer()->getContentSize().height * 0.225f)));
    
    float continue_scale_val = _continue_button->getScale();

    auto scale_1   = ScaleTo::create(0.15f, continue_scale_val * 1.065f);
    auto ease1     = EaseInOut::create(scale_1, 2.2f);
    auto scale_2   = ScaleTo::create(0.15f, continue_scale_val * 1.f);
    auto ease2     = EaseInOut::create(scale_2, 2.2f);
    auto scale_seq = Sequence::create(ease1,ease2, NULL);
    auto repeat    = Repeat::create(scale_seq,2);
    auto seq       = Sequence::create(repeat,DelayTime::create(0.35f), NULL);
    auto rep_fore  = RepeatForever::create(seq);
    rep_fore->setTag(10);
    _continue_button->runAction(rep_fore);

    Size button_size = Size(getContainer()->getContentSize().width*0.5f,getContainer()->getContentSize().height*0.0275f);

    _nothanks_button = SPButton::createWithTTF(button_size, "NO THANKS", "fonts/Blogger_Sans-Bold.otf", button_size.height);
    addChild(_nothanks_button);
    _nothanks_button->setPosition(Vec2(getContentSize().width*0.5f, getContentSize().height * 0.5f - (getContainer()->getContentSize().height * 0.35f)));
    _nothanks_button->getLabel()->setColor(Color3B(160, 160, 160));
    _nothanks_button->setTouchAreaScale(2.0f);
    _nothanks_button->setScale(0);
    _nothanks_button->setActive(false);


    auto delay_for_not = DelayTime::create(1.f);
    auto callf         = CallFunc::create([this]{
        auto scale = ScaleTo::create(0.4f, 1.0f);
        auto ease  = EaseElasticOut::create(scale, 0.6f);
        _nothanks_button->runAction(ease);
        _nothanks_button->setActive(true);
    });
    auto seq_for_not   = Sequence::create(delay_for_not, callf, NULL);
    runAction(seq_for_not);

    
    SoundDirector::getInstance()->playContinueSound();
}

void ContinueLayer::stop_sound(){

    SoundDirector::getInstance()->stopContinueSound();
    
    if (getActionByTag(12)) {
        stopActionByTag(12);
    }
    
    _progress->stopAllActions();
    _continue_button->stopAllActions();
}

void ContinueLayer::onExit(){
    Layer::onExit();
}

void ContinueLayer::progress_animation_did_finish(){
    
    stop_sound();
    
    if (_animation_did_finish_callback) {
        _animation_did_finish_callback();
    }
    
}
