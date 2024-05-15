//
//  LoadingLayer.cpp
//  mannequin
//
//  Created by Marek on 22/11/2016.
//
//

#include "LoadingLayer.h"
#include "Settings.h"

bool LoadingLayer::init(){
    
    if (!GameLayer::init()){
        return false;
    }
    
    Color3B bg_color = Color3B(222,242,242);//Color3B(36,73,89);
    
    bool dark_mode_on = Settings::getStateOn(settings_darkmode);
    
    if (dark_mode_on) {
        bg_color = Color3B(7,32,44);
    }
    
    bg = Sprite::create();
    bg->setTextureRect(Rect(0, 0, getContentSize().width, getContentSize().height));
    bg->setColor(bg_color);
    bg->setPosition(getContentSize()*0.5f);
    addChild(bg,0);
    
    _game_logo = Sprite::create("loading/logo.png");
    addChild(_game_logo);
    _game_logo->setScale(getContainer()->getContentSize().width*0.5f/_game_logo->getContentSize().width);
    float y = getHeaderUIDefaultPosY() - (getContainer()->getContentSize().height * 0.065f);
    _game_logo->setPosition(Vec2(getContentSize().width*0.5f, y - _game_logo->getBoundingBox().size.height * 0.95f));

//    _logo = Sprite::create("loading/man.png");
//    addChild(_logo,2);
//    _logo->setScale(getContainer()->getContentSize().width*0.175f/_logo->getContentSize().width);
//

    _game_logo->setPosition(Vec2(getContentSize().width * 0.5f, getContentSize().height * 0.5f + (getContainer()->getContentSize().height * 0.05f)));

    _icon_bottom = Sprite::create("loading/bar_white.png");
    addChild(_icon_bottom);
    _icon_bottom->setScale(getContainer()->getContentSize().width*0.28f/_icon_bottom->getContentSize().width);
    _icon_bottom->setPosition(Vec2(getContentSize().width*0.5f,
                                   getContentSize().height * 0.5f - (getContainer()->getContentSize().height * 0.1f)));
    _icon_bottom->setColor(Color3B(76,117,119));

    Sprite * fill = Sprite::create("loading/bar_coloured.png");
    //fill->setColor(Color3B(245, 189, 65));
    
    _icon_progress = ProgressTimer::create(fill);
    _icon_progress->setScale(_icon_bottom->getBoundingBox().size.width / _icon_progress->getContentSize().width);
    _icon_progress->setType(cocos2d::ProgressTimer::Type::BAR);
    _icon_progress->setPosition(_icon_bottom->getPosition());
    _icon_progress->setMidpoint(Point(0,fill->getContentSize().height/2));
    _icon_progress->setBarChangeRate(Point(1, 0));
    _icon_progress->setPercentage(0);
    addChild(_icon_progress);
    
    auto progress1 = ProgressFromTo::create(2.25f, 0, 100);
    _icon_progress->runAction(progress1);
    
    getBg()->setLocalZOrder(1111);
    getBg()->setColor(bg_color);//Color3B::BLACK);
    getBg()->setOpacity(0);
    
    auto call = CallFunc::create([this]{
        this->hide_all();
    });
    auto seq = Sequence::create(DelayTime::create(2.25),FadeTo::create(0.25f, 255),call,FadeTo::create(0.25f, 0), NULL);
    getBg()->runAction(seq);
    
    return true;
}

void LoadingLayer::hide_all(){
    _icon_bottom->setVisible(false);
    _icon_progress->setVisible(false);
 //   _logo->setVisible(false);
    _game_logo->setVisible(false);
    bg->setVisible(false);
}
