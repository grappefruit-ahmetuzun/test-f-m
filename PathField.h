//
//  PathField.hpp
//  99Ballz-mobile
//
//  Created by Marek on 13/11/2017.
//

#ifndef PathField_hpp
#define PathField_hpp

#include "cocos2d.h"
#include "Game.h"
#include "Space.h"
#include "Pattern.h"
#include "PathFieldObject.h"

USING_NS_CC;

class PathField : public Sprite{
    
public:
    
    PathField():
    _moveSpeed(1),
    _createSubPoints(false),
    _checkForSlotAvailable(false),
    _timeWhenLastAddedObject(0),
    _lerpOnMove(0)
    {}
    
    CREATE_FUNC(PathField);
    
    void prepare(Size field_size,Pattern * pattern);
    
    Pattern * _pattern = nullptr;
    
    // update
    
    void update_movable_objects(float dt);
    
    // add
    
    void add_line       (Vec2 pt_start, Vec2 pt_finish, float line_height);
    void add_object     (PathFieldObject * new_object,int index);
    void remove_object  (PathFieldObject * remove_object);
    
    // objects
    
    std::vector<Vec2>               _pattern_main_dot_positions;
    std::vector<Sprite*>            _pattern_main_dots;
    std::vector<Sprite*>            _pattern_other_objects;
    std::vector<PathFieldObject *>  _pattern_movable_objects;
    
    // variables
    
    CC_SYNTHESIZE(float, _moveSpeed,         MoveSpeed);
    CC_SYNTHESIZE(bool, _createSubPoints,    CreateSubPoints);
    CC_SYNTHESIZE(bool, _checkForSlotAvailable, CheckForSlotAvailable);
    CC_SYNTHESIZE(float, _timeWhenLastAddedObject, TimeWhenLastAddedObject);
    CC_SYNTHESIZE(float,  _lerpOnMove,               LerpOnMove);
    
private:
    
    bool slotAvailable(int slot);
    
    void add_points_ui(std::vector<Vec2>points);
    void add_circle(float radius, int points);
    
};

#endif /* PathField_hpp */
