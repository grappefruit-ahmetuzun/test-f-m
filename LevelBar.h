//
//  LevelBar.h
//  CastleShooter-mobile
//
//  Created by Viaceslav Adamovic on 01/03/2018.
//

#ifndef LevelBar_h
#define LevelBar_h

#include "cocos2d.h"

USING_NS_CC;

class LevelBar : public Sprite {
    
public:
    
    CREATE_FUNC(LevelBar);
    
    LevelBar(){}
    ~LevelBar(){}
    
    ProgressTimer * _progress    = nullptr;
    Label         * _level_label = nullptr;

    void setPercentage(float percents, bool animated, std::function<void()> on_finish);
    
    virtual bool init() override;
    
    void refresh_color();
    
};

#endif /* LevelBar_h */
