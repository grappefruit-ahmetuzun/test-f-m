//
//  LevelBar.cpp
//  CastleShooter-mobile
//
//  Created by Viaceslav Adamovic on 01/03/2018.
//

#include "LevelBar.h"
#include "Game.h"
#include "LevelManager.h"
#include "Settings.h"

bool LevelBar::init(){
    if (Sprite::initWithFile("ui/bar.png")) {
    
        setColor(Color3B(47, 77, 92));
        
        Sprite * fill_bar_top = Sprite::create("ui/bar.png");
        fill_bar_top->setColor(Color3B(247, 207, 70));
        
        
        _progress = ProgressTimer::create(fill_bar_top);
        _progress->setScale(getContentSize().height / _progress->getContentSize().height);
        _progress->setType(cocos2d::ProgressTimer::Type::BAR);
        _progress->setPosition(Point(getContentSize().width * 0.5f, getContentSize().height * 0.5f));
        _progress->setMidpoint(Point(0, getContentSize().height/2));
        _progress->setBarChangeRate(Point(1, 0));
        _progress->setPercentage(0);
        addChild(_progress,1);
        
        _level_label = Label::createWithTTF("LEVEL 1", "fonts/Blogger_Sans-Bold.otf", getContentSize().height * 0.7f);
        _level_label->setPosition(getContentSize().width * 0.5f, getContentSize().height * 0.43f);
        _level_label->setColor(Color3B(255, 255, 255));
        addChild(_level_label,2);
        
        return true;
    }
    return false;
}

void LevelBar::setPercentage(float percents, bool animated, std::function<void()> on_finish){
    
    if (animated) {
        auto pr   = ProgressTo::create(0.2f, percents);
        auto ease = EaseInOut::create(pr, 2.2f);
        auto callf = CallFunc::create([this, on_finish, percents]{
            if (on_finish) {
                on_finish();
            }
        });
        auto seq  = Sequence::create(ease, callf, NULL);
        _progress->runAction(seq);
    }
    else{
        _progress->setPercentage(percents);
        
        if (on_finish) {
            on_finish();
        }
    }
    
    _level_label->setString(StringUtils::format("LEVEL %i", LevelManager::get_level_number()));
}

void LevelBar::refresh_color(){
    
    bool is_dark_mode = Settings::getStateOn(settings_darkmode);
    
    if (is_dark_mode) {
        setColor(Color3B(47/1.5f, 77/1.5f, 92/1.5f));
    }
    else{
        setColor(Color3B(47, 77, 92));
    }
    
}

