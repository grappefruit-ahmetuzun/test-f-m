//
//  PathFieldObject.cpp
//  99Ballz-mobile
//
//  Created by Marek on 13/11/2017.
//

#include "PathFieldObject.h"

bool PathFieldObject::init(){
    if (SPPhysicsSprite::init()) {
        return true;
    }
    return false;
}
