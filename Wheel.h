//
//  Wheel.h
//  Dottz
//
//  Created by Slavik on 4/26/17.
//
//

#ifndef Wheel_h
#define Wheel_h

#include "cocos2d.h"
#include "WheelPart.h"

USING_NS_CC;

class Wheel : public Sprite {
    
public:
    
    
    Wheel(){
    }
    ~Wheel(){
    }
    
    CREATE_FUNC(Wheel);
    
    virtual bool init() override;
    
    std::vector<WheelPart *> _all_parts;
    
    void prepare();
    
    WheelPart * get_part_by_index(int index);
    WheelPart * get_winner_part(int spin_index);
    
    void remove_part(WheelPart * part);
    
    bool can_spin = true;
    
    bool freeze = false;

};

#endif /* Wheel_h */
