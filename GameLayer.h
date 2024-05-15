//
//  GameLayer.hpp
//  bottlechallenge
//
//  Created by Marek on 22/09/2016.
//
//

#ifndef GameLayer_hpp
#define GameLayer_hpp

#include "cocos2d.h"
#include "SPButton.h"

USING_NS_CC;

class GameLayer : public cocos2d::Layer
{
public:
    
    virtual bool init() override;
    virtual void animateOnEnter();
    virtual void animateOnExit(std::function<void()> onFinish);
    virtual void update(float delta) override;
    
    CREATE_FUNC(GameLayer);
    
    Sprite          * getContainer();
    Sprite          * getBg();
    SPButton        * getBackButton();
    Label           * getTitleLabel();
    Sprite          * getHeader();
    float             getHeaderUIDefaultPosY();

    
    CC_SYNTHESIZE(bool, _touchBlock, TouchBlock);
    
    SPButton            * _backButton       = nullptr;
    Label               * _titleLabel       = nullptr;
    Sprite              * _container        = nullptr;
    Sprite              * _bg               = nullptr;
    Sprite              * _header           = nullptr;
    Sprite              * _dark_bg          = nullptr;
    
    virtual bool onTouchBegan(Touch *touch, Event *event)      override;
    virtual void onTouchMoved(Touch *touch, Event *event)      override;
    virtual void onTouchEnded(Touch *touch, Event *event)      override;
    
    Vec2 ContainerPoint(Vec2 point);
    
private:
    
};

#endif /* GameLayer_hpp */
