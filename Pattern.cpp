//
//  Pattern.cpp
//  99Ballz-mobile
//
//  Created by Marek on 13/11/2017.
//

#include "Pattern.h"

void Pattern::add_point(float x,float y){
    points.push_back(Vec2(x,y));
}

void Pattern::add_circle(float radius,int fruits_count){
    
    is_cicrcle          = true;
    circle_radius       = radius;
    circle_fruits_count = fruits_count;
    
}
