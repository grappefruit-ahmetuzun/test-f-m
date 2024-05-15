//
//  SettingsCell.hpp
//  hiball
//
//  Created by Marek on 1/7/17.
//
//

#ifndef SettingsCell_hpp
#define SettingsCell_hpp

#include "SPCollectionViewCell.h"
#include "CoinsAmmountSprite.h"
#include "Settings.h"
#include "spine/spine.h"
#include <spine/spine-cocos2dx.h>

class SettingsCell : public SPCollectionViewCell {
    
public:
    
    SettingsCell():
    _type(settings_none)
    {};
    ~SettingsCell(){};
    
    CREATE_FUNC(SettingsCell);
    
    virtual void updateContent() override;
    
    Label * _title          = nullptr;
    
    spine::SkeletonAnimation * _toggle_spine_animation  = nullptr;
    
    CC_SYNTHESIZE(settings_type, _type, Type);
    
    void changeState(bool animated);
    
private:
    
};

#endif /* SettingsCell_hpp */
