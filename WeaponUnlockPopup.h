//
//  WeaponUnlockPopup.h
//  FruitsKnife-mobile
//
//  Created by Slavik on 6/12/18.
//

#ifndef WeaponUnlockPopup_h
#define WeaponUnlockPopup_h

#include "GameLayer.h"
#include "SPButton.h"
#include "Shop.h"

USING_NS_CC;

class WeaponUnlockPopup : public GameLayer{
    
public:
    CREATE_FUNC(WeaponUnlockPopup);
    
    virtual bool init() override;
    
    WeaponUnlockPopup(){}
    ~WeaponUnlockPopup(){}
    
    void prepare(SHOP_ITEM item);
    
    virtual bool onTouchBegan(Touch *touch, Event *event) override;
    
    SPButton * equip_button = nullptr;
    SPButton * close_button = nullptr;
    
    SHOP_ITEM _item = item_unknown;
    
};

#endif /* WeaponUnlockPopup_h */
