//
//  CoinsAmmountSprite.cpp
//  SummerGames
//
//  Created by Marek on 7/17/16.
//
//

#include "CoinsAmmountSprite.h"
#include "Space.h"

CoinsAmmountSprite * CoinsAmmountSprite::createWithHeight(float height) {
    CoinsAmmountSprite *sprite = new (std::nothrow) CoinsAmmountSprite();
    sprite->addChild(sprite->getContentSprite());
    sprite->buttonSize = Size(height, height);

    if (sprite && sprite->init()){
        
        sprite->setTextureRect(Rect(0, 0, sprite->buttonSize.width, sprite->buttonSize.height));
        
        sprite->setOpacity(0);
        sprite->getContentSprite()->setOpacity(0);
        
        sprite->getContentSprite()->setPosition(Point(sprite->getBoundingBox().size.width/2,
                                                      sprite->getBoundingBox().size.height/2));
        
        sprite->getContentSprite()->setTextureRect(sprite->getTextureRect());
        
        sprite->epmty_area = sprite->getContentSize().height * 0.25f;
        
        sprite->autorelease();
        return sprite;
    }
    
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void CoinsAmmountSprite::fade_out(float duration,float delay){
    
    std::vector<Node *>a;
    a.push_back(getCoinsLabel());
    a.push_back(getCoinSprite());
    
    for (int x=0; x < a.size(); x++) {
        Node *n = a.at(x);
        auto fadeto = FadeTo::create(duration, 0);
        n->runAction(Sequence::create(DelayTime::create(delay),fadeto, NULL));
    }
    
}

void CoinsAmmountSprite::fade_in(float duration,float delay){
    std::vector<Node *>a;
    a.push_back(getCoinsLabel());
    a.push_back(getCoinSprite());
    
    for (int x=0; x < a.size(); x++) {
        Node *n = a.at(x);
        auto fadeto = FadeTo::create(duration, 255);
        n->runAction(Sequence::create(DelayTime::create(delay),fadeto, NULL));
    }

}

void CoinsAmmountSprite::animate_on_collect(){

    setScale(1.2f);
    stopAllActions();
    
    auto scale = ScaleTo::create(0.3f, 1.f);
    auto ease  = EaseElasticOut::create(scale, 0.4f);
    runAction(ease);
}

bool CoinsAmmountSprite::init() {
    if (SPButton::init()) {
        
        if (Director::getInstance()->getScheduler()->isScheduled(CC_SCHEDULE_SELECTOR(CoinsAmmountSprite::update_coins), this) == false) {
            Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(CoinsAmmountSprite::update_coins), this, 0.015f, false);
        }
        
        return true;
    }
    return false;
}

void CoinsAmmountSprite::setCoins(int coint, bool animated){
    
    if (animated == false) {
        coins_now = coint;
        next_coins = coint;
        
        setCurrentCoins(coins_now);
    }
    else{
        next_coins = coint;
    }
}

void CoinsAmmountSprite::setCurrentCoins(int coint){
    
    std::string str = StringUtils::format("%s%i",label_prefix.c_str(),coint);
    
    getCoinsLabel()->setString(str.c_str());
    
    float width =
    getCoinsLabel()->getBoundingBox().size.width+
    getCoinSprite()->getBoundingBox().size.width + epmty_area;
    
    setTextureRect(Rect(0, 0,
                        width,
                        getContentSize().height));
    getContentSprite()->setPosition(getBoundingBox().size*0.5f);
    getContentSprite()->setTextureRect(getTextureRect());
    
    if (_labelOnRight == true) {
        _coinSprite->setAnchorPoint(Vec2(0.f, 0.50f));
        _coinsLabel->setAnchorPoint(Vec2(1.f, 0.5f));
        getCoinsLabel()->  setPosition((getContentSize().width*0.5f)+(width/2),getContentSize().height*0.43f);
        getCoinSprite()->  setPosition((getContentSize().width*0.5f)-(width/2),getContentSize().height*0.5f);
    }
    else{
        _coinSprite->setAnchorPoint(Vec2(1.f, 0.50f));
        _coinsLabel->setAnchorPoint(Vec2(0, 0.5f));
        getCoinsLabel()->  setPosition((getContentSize().width*0.5f)-(width/2),getContentSize().height*0.43f);
        getCoinSprite()->  setPosition((getContentSize().width*0.5f)+(width/2),getContentSize().height*0.5f);
    }
}

void CoinsAmmountSprite::update_coins(float dt){
    
    if (coins_now != next_coins) {
        
        float diff     = next_coins - coins_now;
        
        float abs_diff = fabsf(diff);
        
        float offset = diff * 0.1f;
        
        if (abs_diff <= 10) {
            if (diff < 0) {
                offset = -1;
            }
            else{
                offset = 1;
            }
        }
        
        coins_now += offset;
        
        
        if (abs_diff <= 1) {
            coins_now = next_coins;
        }
        
        setCurrentCoins(coins_now);
    }
}

void CoinsAmmountSprite::color_white(){
    getCoinsLabel()->setColor(Color3B::WHITE);
}

void CoinsAmmountSprite::color_dark(){
    getCoinsLabel()->setColor(Color3B(140, 140, 140));
}

void CoinsAmmountSprite::color_black_n_white(){
    getCoinSprite()->setTexture("star_45_blacknwhite.png");
}

void CoinsAmmountSprite::color_colorfull(){
    getCoinSprite()->setTexture("circle_0.png");
}


#pragma mark lazy

Label * CoinsAmmountSprite::getCoinsLabel(){
    if (!_coinsLabel) {
        _coinsLabel = Label::createWithTTF("0", "fonts/Blogger_Sans-Bold.otf", getContentSize().height * 0.6f);
        _coinsLabel->setAnchorPoint(Vec2(0, 0.5f));
        _coinsLabel->setColor(Color3B(255, 255, 255));
        getContentSprite()->addChild(_coinsLabel, 2);
    }
    return _coinsLabel;
}

Sprite * CoinsAmmountSprite::getCoinSprite(){
    if (!_coinSprite) {
        _coinSprite = Sprite::create("hud/fake_coin.png");
        _coinSprite->setScale((getCoinHeight() * 0.6f)/_coinSprite->getContentSize().height);
        _coinSprite->setAnchorPoint(Vec2(1.f, 0.5f));
        getContentSprite()->addChild(_coinSprite, 2);
    }
    return _coinSprite;
}


float CoinsAmmountSprite::getCoinHeight(){
    return getContentSize().height * 1.f;
}
