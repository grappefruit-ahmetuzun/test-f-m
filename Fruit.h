//
//  Fruit.hpp
//  FruitsKnife-mobile
//
//  Created by Marek on 11/05/2018.
//

#ifndef Fruit_hpp
#define Fruit_hpp

#include "SPPhysicsSprite.h"
#include "Game.h"
#include "Space.h"
#include "Patterns.h"
#include "PathFieldObject.h"

USING_NS_CC;

class Fruit : public PathFieldObject{
    
public:
    
    Fruit()
    {}
    
    CREATE_FUNC(Fruit);
    
    void prepare(fruit_info info,Size container,b2World * world);
    
    Size _container  = Size(0,0);
    
    fruit_info _info;
    
    bool can_switch_side = false;
    
    SkeletonAnimation * _spine_fruit = nullptr;
    
    void updateFruit();
    
private:
    
    std::string getTexturePath(fruit_type type);
    float getSize(fruit_type type);
    
};

#endif /* Fruit_hpp */
