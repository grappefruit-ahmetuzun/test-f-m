//
//  Pattern.hpp
//  99Ballz-mobile
//
//  Created by Marek on 13/11/2017.
//

#ifndef Pattern_hpp
#define Pattern_hpp

#include "cocos2d.h"
#include "Game.h"
#include "Space.h"

USING_NS_CC;

enum PATTERN_LINE_TYPE{
    
    PATTERN_LINE_UNKNOWN                     = -1,
    PATTERN_LINE_DOTS                        = 0,
    PATTERN_LINE_LINE                        = 1
    
};

class Pattern : public Node{
    
public:
    
    Pattern()
    {}
    
    CREATE_FUNC(Pattern);
    
    void add_point(float x,float y);
    void add_circle(float radius,int fruits_count);
    
    bool is_cicrcle = false;
    float circle_radius = 0;
    float circle_fruits_count = 0;

    std::vector<Vec2>points;
    std::vector<fruit_type>fruits;
    std::vector<ActionInterval*>actions;
    
    int lifes_count = 1;
    
    PATTERN_LINE_TYPE _line_type    = PATTERN_LINE_UNKNOWN;
    Color3B           _line_color   = Color3B(96,141,162);
    
private:
    
};

#endif /* Pattern_hpp */
