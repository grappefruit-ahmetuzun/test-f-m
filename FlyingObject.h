//
//  FlyingObject.hpp
//  hiball
//
//  Created by Viaceslav Adamovic on 22/02/2017.
//
//

#ifndef FlyingObject_h
#define FlyingObject_h

#include "cocos2d.h"
#include "Game.h"
#include "CustomMotionStreak.h"

USING_NS_CC;

enum FLYING_OBJECT_TYPE{

    FLYING_OBJECT_TYPE_UNKNOWN                      = -1,
    FLYING_OBJECT_TYPE_COIN                         = 1,
    FLYING_OBJECT_TYPE_GEM                          = 2
};

class FlyingObject : public Sprite {
    
public:
    
    FlyingObject():
    _object_type(FLYING_OBJECT_TYPE_UNKNOWN),
    _texture_title(""),
    _tile_color(Color3B::WHITE)
    {}
    virtual ~FlyingObject(){}
    
    CREATE_FUNC(FlyingObject);
    
    static FlyingObject * createWithType(FLYING_OBJECT_TYPE t);
    
    virtual bool init() override;
    
    bool _must_be_deleted = false;
    
    CustomMotionStreak * tail = nullptr;

    void prepare(bool add_trail);
    
    void updatePosition();
    
    CC_SYNTHESIZE(FLYING_OBJECT_TYPE,   _object_type,       Object_type);
    CC_SYNTHESIZE(std::string,          _texture_title,     Texture_title);
    CC_SYNTHESIZE(Color3B,              _tile_color,        Tile_color);
    
private:
    

};

#endif /* FlyingObject_h */
