//
//  GameLayer.cpp
//  bottlechallenge
//
//  Created by Marek on 22/09/2016.
//
//

#include "GameLayer.h"
#include "Space.h"
#include "Game.h"
#include "PlatformManager.h"

#define FLY_ANIMATION_TAG 12234

bool GameLayer::init(){
    if (!Layer::init()){
        return false;
    }
    
    _touchBlock = true;
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void GameLayer::update(float delta){
    
}

void GameLayer::animateOnEnter(){
    
    
}

float GameLayer::getHeaderUIDefaultPosY(){
    if (PlatformManager::isIphoneX()) {
        return getContentSize().height*0.935f;
    }
    return getContentSize().height*0.965f;
}

void GameLayer::animateOnExit(std::function<void()> onFinish){
    
    
}

bool GameLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    if (_touchBlock == false) {
        return false;
    }
    return true;
}

void GameLayer::onTouchMoved(Touch *touch, Event *event) {

}

void GameLayer::onTouchEnded(Touch *touch, Event *event) {

}

Sprite * GameLayer::getHeader(){
    if (!_header) {
        _header = Sprite::create();
        _header->setTextureRect(Rect(0, 0, getContentSize().width, getContentSize().height*0.1f));
        _header->setColor(Color3B(223, 75, 82));
        addChild(_header,1);
        _header->setPosition(getContentSize().width/2, getContentSize().height - _header->getBoundingBox().size.height/2);
    }
    return _header;
}

Sprite * GameLayer::getBg(){
    if (!_bg) {
        _bg = Sprite::create();
        _bg->setTextureRect(Rect(0, 0, getContentSize().width, getContentSize().height));
        _bg->setPosition(getContentSize()*0.5f);
        addChild(_bg);
        
        if (SPPHYSICS_DEBUG == 1) {
            _bg->setOpacity(0);
        }
    }
    return _bg;
}

Label * GameLayer::getTitleLabel(){
    if (!_titleLabel) {
        _titleLabel = Label::createWithTTF("TITLE X", "fonts/Blogger_Sans-Bold.otf", getBoundingBox().size.height * 0.025f);
        _titleLabel->setAnchorPoint(Vec2(0.5f,0.6f));
        _titleLabel->setPosition(getContentSize().width/2, /*getContentSize().height * 0.965f*/getHeaderUIDefaultPosY());
        _titleLabel->setColor(Color3B(255, 255, 255));
        _titleLabel->setOpacity(255);
        addChild(_titleLabel,2);
    }
    return _titleLabel;
}

SPButton * GameLayer::getBackButton(){
    if (!_backButton) {
        _backButton = SPButton::createWithImage("back.png");
        float offset = getContainer()->getContentSize().width * 0.055f;
        _backButton->setTouchAreaScale(4.5f);
        _backButton->setScale(getContainer()->getContentSize().width * 0.05f / _backButton->getContentSize().width);
        _backButton->setPosition(getContentSize().width * 0.5f - (getContainer()->getContentSize().width * 0.5f) + offset + (_backButton->getBoundingBox().size.width * 0.5f), getHeaderUIDefaultPosY());
        _backButton->getContentSprite()->setColor(Color3B(140, 140, 140));
        addChild(_backButton,2);
    }
    return _backButton;
}

Sprite * GameLayer::getContainer(){
    if (!_container) {
        _container = Sprite::create();
        _container->setColor(Color3B::WHITE);
        _container->setOpacity(0);
        
        float w = getContentSize().width;
        float h = getContentSize().height;
        
        Size _container_size = Size(w, w * 1.77f);
    
        if (_container_size.height > getContentSize().height) {
            _container_size = Size(h * 0.5625f, h);
        }
        
        _container->setContentSize(_container_size);
        _container->setAnchorPoint(Vec2(0.5f, 0.5f));
        _container->setPosition(getContentSize()*0.5f);
        addChild(_container,1);
    }
    return _container;
}

Vec2 GameLayer::ContainerPoint(Vec2 point) {
    Vec2 point_to_return = Vec2((getContentSize().width * 0.5f) - (getContainer()->getContentSize().width * 0.5f) + point.x,
                                (getContentSize().height * 0.5f) - (getContainer()->getContentSize().height * 0.5f) + point.y);
    return point_to_return;
}
