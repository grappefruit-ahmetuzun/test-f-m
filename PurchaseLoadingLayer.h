//
//  PurchaseLoadingLayer.h
//  TixGame
//
//  Created by Slavik on 19/04/16.
//
//

#ifndef PurchaseLoadingLayer_h
#define PurchaseLoadingLayer_h

#include "GameLayer.h"

USING_NS_CC;

enum LOADING_TYPE{

    LOADING_TYPE_UNKNOWN    = 0,
    LOADING_TYPE_VIDEO_AD   = 1,
    LOADING_TYPE_PURCHASE   = 2
};

class PurchaseLoadingLayer : public GameLayer{
    
public:
    
    PurchaseLoadingLayer();
    ~PurchaseLoadingLayer();
    
    static PurchaseLoadingLayer * createWithType(LOADING_TYPE _type);
    
    CREATE_FUNC(PurchaseLoadingLayer);
    
    bool init() override;
    
    virtual void onEnter() override;
    virtual void onExit() override;
    

private:
    
    LOADING_TYPE type = LOADING_TYPE_UNKNOWN;

    virtual bool onTouchBegan(Touch *touch, Event *event)      override;

};
#endif /* LoadingLayer_h */
