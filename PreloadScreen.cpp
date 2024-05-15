//
//  PreloadScreen.cpp
//  TixGame
//
//  Created by Marek on 04/05/16.
//
//

#include "PreloadScreen.h"
#include "Space.h"

bool PreloadScreen::init() {
    if (Layer::init()) {
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = CC_CALLBACK_2(PreloadScreen::onTouchBegan, this);
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
        
        Sprite * bg = Sprite::create();
        addChild(bg);
        bg->setTextureRect(Rect(0, 0, getContentSize().width, getContentSize().height));
        bg->setColor(Color3B(213, 1, 1));
        bg->setPosition(getContentSize()*0.5f);
        
        _content = Sprite::create();
        _content->setTextureRect(Rect(0, 0, SPACE->getFHDAspectSize().width, SPACE->getFHDAspectSize().height));
        _content->setPosition(getContentSize()*0.5f);
        _content->setOpacity(0);
        _content->setColor(Color3B::RED);
        addChild(_content);
        
        Sprite * top_logo = Sprite::create("splash_ketchapp/splash_ketchapp_title.png");
        _content->addChild(top_logo);
        top_logo->setScale(_content->getContentSize().width*0.65f/top_logo->getContentSize().width);
        top_logo->setPosition(_content->getContentSize().width*0.5f, _content->getContentSize().height*0.6f);
        
        Sprite * bottom_logo = Sprite::create("splash_ketchapp/splash_estoty_title.png");
        _content->addChild(bottom_logo);
        bottom_logo->setScale(_content->getContentSize().width*0.65f/bottom_logo->getContentSize().width);
        bottom_logo->setPosition(_content->getContentSize().width*0.5f, _content->getContentSize().height*0.4f);
        
        return true;
    }
    
    return false;
}

bool PreloadScreen::onTouchBegan(Touch *touch, Event *unused_event){
    return true;
}
