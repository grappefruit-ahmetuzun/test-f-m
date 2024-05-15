//
//  PurchaseLoadingLayer.cpp
//  TixGame
//
//  Created by Slavik on 19/04/16.
//
//

#include "PurchaseLoadingLayer.h"
#include "Space.h"

PurchaseLoadingLayer::PurchaseLoadingLayer(){
    
}

PurchaseLoadingLayer::~PurchaseLoadingLayer(){

}

PurchaseLoadingLayer * PurchaseLoadingLayer::createWithType(LOADING_TYPE _type){
    
    PurchaseLoadingLayer * layer = new (std::nothrow) PurchaseLoadingLayer();
    layer->type = _type;
    
    if( layer && layer->init()){
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

void PurchaseLoadingLayer::onEnter() {
    Layer::onEnter();
}

void PurchaseLoadingLayer::onExit() {
    Layer::onExit();
}

bool PurchaseLoadingLayer::init() {
    if (Layer::init()) {
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = CC_CALLBACK_2(PurchaseLoadingLayer::onTouchBegan, this);
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
        
        LayerColor * bg = LayerColor::create(Color4B(0, 0, 0, 175));
        addChild(bg);

        
        Sprite * whiteBG = Sprite::create("inapploading/spinner_field.png");
        whiteBG->setPosition(getContentSize()/2);
        whiteBG->setScale(getContainer()->getContentSize().width * 0.6f / whiteBG->getContentSize().width);
        addChild(whiteBG);
        whiteBG->setColor(Color3B(36,66,106));
        
        
        Sprite * orange = Sprite::create("inapploading/star_loading.png");
        orange->setScale(whiteBG->getContentSize().width * 0.15f / orange->getContentSize().width);
        orange->setPosition(whiteBG->getContentSize().width/2, whiteBG->getContentSize().height * 0.35f);
        whiteBG->addChild(orange);
        //orange->setColor(Color3B(253,185,44));
        
        std::string text = "PROCESSING...";
        
        if (type == LOADING_TYPE_VIDEO_AD) {
         //   text = "PREPARING GIFT...";
        }
        
        Label * loadingLabel = Label::createWithTTF(text.c_str(), "fonts/Blogger_Sans-Bold.otf", whiteBG->getContentSize().height * 0.4f);
        loadingLabel->setColor(Color3B(255, 255, 255));
        loadingLabel->setScale(whiteBG->getContentSize().width * 0.45f / loadingLabel->getBoundingBox().size.width);
        loadingLabel->setPosition(whiteBG->getContentSize().width/2, whiteBG->getContentSize().height * 0.75f);
        whiteBG->addChild(loadingLabel);
        
        auto rotate = RotateBy::create(0.1f, 40);
        auto repeat = RepeatForever::create(rotate);
        
        orange->runAction(repeat);
        
        return true;
    }
    return false;
}

bool PurchaseLoadingLayer::onTouchBegan(Touch *touch, Event *unused_event){
    return true;
}
