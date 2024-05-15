//
//  ExitLayer.cpp
//  TixGame
//
//  Created by Marek on 19/04/16.
//
//

#include "ExitLayer.h"
#include "Space.h"
#include "Game.h"

ExitLayer::ExitLayer(){
    
}

ExitLayer::~ExitLayer(){

}

bool ExitLayer::init() {
    if (GameLayer::init()) {
        
        setTouchBlock(true);
        return true;
    }
    return false;
}

void ExitLayer::prepare(std::string txt){
    
    getBg()->setOpacity(150);
    getBg()->setColor(Color3B::BLACK);
    
    Sprite * popup = Sprite::create("exit/popup.png");
    addChild(popup);
    popup->setPosition(Point(getContentSize().width * 0.5f, getContentSize().height * 0.52f));
    popup->setScale(getContainer()->getContentSize().width * 0.7f / popup->getContentSize().width);
    
    _yesButton = SPButton::createWithImage("exit/yes.png");
    popup->addChild(_yesButton);
    _yesButton->setScale(popup->getContentSize().width * 0.375f / _yesButton->getContentSize().width);
    _yesButton->setPosition(Vec2(popup->getContentSize().width * 0.3f, popup->getContentSize().height*0.315f));
    
    _noButton = SPButton::createWithImage("exit/no.png");
    popup->addChild(_noButton);
    _noButton->setScale(popup->getContentSize().width * 0.375f / _noButton->getContentSize().width);
    _noButton->setPosition(Vec2(popup->getContentSize().width * 0.7f, popup->getContentSize().height*0.315f));
    
    _titleLabel = Label::createWithTTF(txt.c_str(), "fonts/Triomphe-Regular-autoinstr.ttf", popup->getContentSize().height * 0.15f);
    popup->addChild(_titleLabel);
    _titleLabel->setPosition(Vec2(popup->getContentSize().width*0.5f, popup->getContentSize().height*0.8f));
    
    Game::align_x_side_by_side(_yesButton, _noButton, popup->getContentSize().width*0.05f);
    
}
