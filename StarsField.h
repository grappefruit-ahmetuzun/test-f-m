//
//  StarsField.h
//  FruitsKnife-mobile
//
//  Created by Slavik on 5/30/18.
//

#ifndef StarsField_h
#define StarsField_h

#include "cocos2d.h"

USING_NS_CC;

class StarsField : public Sprite {
    
public:
    
    CREATE_FUNC(StarsField);
    
    StarsField(){}
    ~StarsField(){}
    
    virtual bool init() override;
    
    void prepare(float height);
    
    void set_stars_count(int count);
    
    std::vector<Sprite *> stars;
    
    void hide();
};

#endif /* StarsField_h */
