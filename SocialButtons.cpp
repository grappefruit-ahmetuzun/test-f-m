//
//  SocialButtons.cpp
//  FruitsKnife-mobile
//
//  Created by Slavik on 6/6/18.
//

#include "SocialButtons.h"
#include "SPButton.h"

void SocialButtons::prepare(float width){
    
    setContentSize(Size(width, width * 0.4f));
    
    Sprite * _estoty_logo = Sprite::create("splash_ketchapp/splash_estoty_title.png");
    addChild(_estoty_logo, 6);
    _estoty_logo->setScale(getContentSize().width * 0.12f / _estoty_logo->getContentSize().height);
    _estoty_logo->setPosition(Vec2(getContentSize().width * 0.75f, getContentSize().height * 0.5f + getContentSize().height * 0.3f));
    
    Sprite * _ketchapp_logo = Sprite::create("splash_ketchapp/splash_ketchapp_title.png");
    addChild(_ketchapp_logo, 6);
    _ketchapp_logo->setScale(getContentSize().width * 0.085f / _ketchapp_logo->getContentSize().height);
    _ketchapp_logo->setPosition(Vec2(getContentSize().width * 0.25f, getContentSize().height * 0.5f + getContentSize().height * 0.28f));
    
    
    
    
    {
        SPButton * _estoty_facebook_button = SPButton::createWithImage("settings/f_2.png");
        addChild(_estoty_facebook_button, 7);
        _estoty_facebook_button->setScale(getContentSize().width * 0.1f / _estoty_facebook_button->getContentSize().height);
        _estoty_facebook_button->setPosition(Vec2(_estoty_logo->getPositionX() - (_estoty_facebook_button->getBoundingBox().size.width * 0.65f), getContentSize().height * 0.5f - getContentSize().height * 0.04f));
        _estoty_facebook_button->setTouchAreaScale(1.25f);
        _estoty_facebook_button->setVoidTouchDownCallback([this, _estoty_facebook_button]{
            PlatformManager::open_facebook_estoty();
            
            if (get_social_reward(1) == false) {
                set_social_reward(1);
                
                float after_delay = 0.4f;
                
                Vec2 pos = _estoty_facebook_button->getParent()->convertToWorldSpace(_estoty_facebook_button->getPosition());
                
                if (_social_reward_give_callback) {
                    _social_reward_give_callback(25, after_delay,pos);
                }
                
                auto delay = DelayTime::create(after_delay);
                auto callf = CallFunc::create([this, _estoty_facebook_button]{
                    if (_estoty_facebook_button->getContentSprite()->getChildByTag(11)) {
                        _estoty_facebook_button->getContentSprite()->removeChildByTag(11);
                    }
                });
                auto seq   = Sequence::create(delay, callf, NULL);
                runAction(seq);
            }
        });
        
        if (get_social_reward(1) == false) {
            Sprite * apples_image = Sprite::create("settings/yellow.png");
            _estoty_facebook_button->getContentSprite()->addChild(apples_image, -1);
            apples_image->setScale(_estoty_facebook_button->getContentSprite()->getContentSize().width / apples_image->getContentSize().width);
            apples_image->setPosition(Point(_estoty_facebook_button->getContentSprite()->getContentSize().width * 0.5f, 0));
            apples_image->setTag(11);
        }
        
        
        
        
        SPButton * _estoty_instagram_button = SPButton::createWithImage("settings/f_3.png");
        addChild(_estoty_instagram_button, 7);
        _estoty_instagram_button->setScale(getContentSize().width * 0.1f / _estoty_instagram_button->getContentSize().height);
        _estoty_instagram_button->setPosition(Vec2(_estoty_logo->getPositionX() + (_estoty_instagram_button->getBoundingBox().size.width * 0.65f), getContentSize().height * 0.5f - getContentSize().height * 0.04f));
        _estoty_instagram_button->setTouchAreaScale(1.25f);
        _estoty_instagram_button->setVoidTouchDownCallback([this, _estoty_instagram_button]{
            PlatformManager::open_instagram_estoty();
            
            if (get_social_reward(2) == false) {
                set_social_reward(2);
                
                
                float after_delay = 0.4f;
                
                Vec2 pos = _estoty_instagram_button->getParent()->convertToWorldSpace(_estoty_instagram_button->getPosition());
                
                if (_social_reward_give_callback) {
                    _social_reward_give_callback(25, after_delay,pos);
                }
                
                auto delay = DelayTime::create(after_delay);
                auto callf = CallFunc::create([this, _estoty_instagram_button]{
                    if (_estoty_instagram_button->getContentSprite()->getChildByTag(11)) {
                        _estoty_instagram_button->getContentSprite()->removeChildByTag(11);
                    }
                });
                auto seq   = Sequence::create(delay, callf, NULL);
                runAction(seq);
            }
        });
        
        if (get_social_reward(2) == false) {
            Sprite * apples_image = Sprite::create("settings/yellow.png");
            _estoty_instagram_button->getContentSprite()->addChild(apples_image, -1);
            apples_image->setScale(_estoty_instagram_button->getContentSprite()->getContentSize().width / apples_image->getContentSize().width);
            apples_image->setPosition(Point(_estoty_instagram_button->getContentSprite()->getContentSize().width * 0.5f, 0));
            apples_image->setTag(11);
        }
    }
    
    
    
    
    
    {
        SPButton * _ketchapp_facebook_button = SPButton::createWithImage("settings/f_1.png");
        addChild(_ketchapp_facebook_button, 7);
        _ketchapp_facebook_button->setScale(getContentSize().width * 0.1f / _ketchapp_facebook_button->getContentSize().height);
        _ketchapp_facebook_button->setPosition(Vec2(_ketchapp_logo->getPositionX() - (_ketchapp_facebook_button->getBoundingBox().size.width * 0.65f),
                                                    getContentSize().height * 0.5f - getContentSize().height * 0.04f));
        _ketchapp_facebook_button->setTouchAreaScale(1.25f);
        _ketchapp_facebook_button->setVoidTouchDownCallback([this, _ketchapp_facebook_button]{
            PlatformManager::open_facebook();
            
            if (get_social_reward(3) == false) {
                set_social_reward(3);
                
                float after_delay = 0.4f;
                
                Vec2 pos = _ketchapp_facebook_button->getParent()->convertToWorldSpace(_ketchapp_facebook_button->getPosition());
                
                if (_social_reward_give_callback) {
                    _social_reward_give_callback(25, after_delay,pos);
                }
                
                
                auto delay = DelayTime::create(after_delay);
                auto callf = CallFunc::create([this, _ketchapp_facebook_button]{
                    if (_ketchapp_facebook_button->getContentSprite()->getChildByTag(11)) {
                        _ketchapp_facebook_button->getContentSprite()->removeChildByTag(11);
                    }
                });
                auto seq   = Sequence::create(delay, callf, NULL);
                runAction(seq);
                
            }
        });
        
        if (get_social_reward(3) == false) {
            Sprite * apples_image = Sprite::create("settings/yellow.png");
            _ketchapp_facebook_button->getContentSprite()->addChild(apples_image, -1);
            apples_image->setScale(_ketchapp_facebook_button->getContentSprite()->getContentSize().width / apples_image->getContentSize().width);
            apples_image->setPosition(Point(_ketchapp_facebook_button->getContentSprite()->getContentSize().width * 0.5f, 0));
            apples_image->setTag(11);
        }
        
        
        
        SPButton * _ketchapp_instagram_button = SPButton::createWithImage("settings/i_1.png");
        addChild(_ketchapp_instagram_button, 7);
        _ketchapp_instagram_button->setScale(getContentSize().width * 0.1f / _ketchapp_instagram_button->getContentSize().height);
        _ketchapp_instagram_button->setPosition(Vec2(_ketchapp_logo->getPositionX() + (_ketchapp_instagram_button->getBoundingBox().size.width * 0.65f), getContentSize().height * 0.5f - getContentSize().height * 0.04f));
        _ketchapp_instagram_button->setTouchAreaScale(1.25f);
        _ketchapp_instagram_button->setVoidTouchDownCallback([this, _ketchapp_instagram_button]{
            PlatformManager::open_instagram();
            
            if (get_social_reward(4) == false) {
                set_social_reward(4);
                
                float after_delay = 0.4f;
                
                Vec2 pos = _ketchapp_instagram_button->getParent()->convertToWorldSpace(_ketchapp_instagram_button->getPosition());
                
                if (_social_reward_give_callback) {
                    _social_reward_give_callback(25, after_delay,pos);
                }
                
                auto delay = DelayTime::create(after_delay);
                auto callf = CallFunc::create([this, _ketchapp_instagram_button]{
                    if (_ketchapp_instagram_button->getContentSprite()->getChildByTag(11)) {
                        _ketchapp_instagram_button->getContentSprite()->removeChildByTag(11);
                    }
                });
                auto seq   = Sequence::create(delay, callf, NULL);
                runAction(seq);
                
                
            }
        });
        
        if (get_social_reward(4) == false) {
            Sprite * apples_image = Sprite::create("settings/yellow.png");
            _ketchapp_instagram_button->getContentSprite()->addChild(apples_image, -1);
            apples_image->setScale(_ketchapp_instagram_button->getContentSprite()->getContentSize().width / apples_image->getContentSize().width);
            apples_image->setPosition(Point(_ketchapp_instagram_button->getContentSprite()->getContentSize().width * 0.5f, 0));
            apples_image->setTag(11);
        }
    }
    
}
