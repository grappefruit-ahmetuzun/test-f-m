//
//  PathField.cpp
//  99Ballz-mobile
//
//  Created by Marek on 13/11/2017.
//

#include "PathField.h"

void PathField::prepare(Size field_size,Pattern * pattern){
    
    setTextureRect(Rect(0, 0, field_size.width, field_size.height));
    setColor(Color3B::RED);
    setOpacity(0);
    
    _pattern = pattern;
    
    if (_pattern->is_cicrcle) {
        add_circle(_pattern->circle_radius,_pattern->circle_fruits_count);
    }
    else{
       add_points_ui(_pattern->points);
    }

}

#pragma mark
#pragma mark Update

void PathField::update_movable_objects(float dt){
    
    _timeWhenLastAddedObject+=dt;
    
    for (int x=0; x < _pattern_movable_objects.size(); x++) {
        
        PathFieldObject * object_move = _pattern_movable_objects.at(x);
        
        // position update
        
        std::vector<Point> points = _pattern_main_dot_positions;
        
        float speed        = _moveSpeed;
        Point aimPoint     = points.at(object_move->_pathStepIndex);
        aimPoint          += object_move->getMovingPosOffset();
        
        if (_lerpOnMove > 0) {
            aimPoint = object_move->getPosition().lerp(aimPoint, _lerpOnMove);
        }
        
        object_move->updateMove(dt, aimPoint, speed);
        
        if (aimPoint.getDistance(object_move->getPosition()) <= 3){
            
            // go up
            
            if (object_move->_pathStepUp) {
                
                if (object_move->_pathStepIndex < points.size()-1) {
                    int next_slot = object_move->_pathStepIndex+1;
                    
                    if (_checkForSlotAvailable) {
                        if (slotAvailable(next_slot)) {
                            object_move->_pathStepIndex++;
                        }
                    }
                    else{
                         object_move->_pathStepIndex++;
                    }
               
                }
                
            }
            
        }
    
        Point object_position = object_move->getPosition() - object_move->getMovingPosOffset();
        
        if (object_position.getDistance(points.at(_pattern_main_dot_positions.size()-1)) <= 3) {
            object_move->setIsOnLastPathPoint(true);
        }
        
    }
    
}

bool PathField::slotAvailable(int slot){
    
    for (int x=0; x < _pattern_movable_objects.size(); x++) {
        PathFieldObject * object = _pattern_movable_objects.at(x);
        if (object->_pathStepIndex == slot) {
            return false;
        }
    }
    
    return true;
}

#pragma mark
#pragma mark Add

void PathField::add_circle(float radius, int points){
    
    radius               =  ((getContentSize().width/2)*(radius*0.01f));
    float angleStep      = (float)360/points;
    angleStep            = ceilf(angleStep);
    float angle          = 0;

    for (int p = 0; p < points; p++) {
        
        if (angle >=360) {
            continue;
        }
        
        Point endPoint;
        endPoint.x      = sinf(CC_DEGREES_TO_RADIANS(angle)) * radius;
        endPoint.y      = cosf(CC_DEGREES_TO_RADIANS(angle)) * radius;
        Point center    = getContentSize()/2;
        endPoint        = Vec2(center+endPoint);
        
        Sprite *dot = Sprite::create("circle_0.png");
        float scale = getContentSize().width*0.0275f/dot->getContentSize().width;
        dot->setScale(scale);
        dot->setColor(_pattern->_line_color);
        addChild(dot);
        dot->setPosition(endPoint);
        
        Vec2 world_pos = dot->getParent()->convertToWorldSpace(dot->getPosition());
        
        if (_pattern->_line_type == PATTERN_LINE_DOTS) {
            dot->setOpacity(0);
        }
        
        _pattern_main_dots.push_back(dot);
        _pattern_main_dot_positions.push_back(world_pos);
        
        angle+=angleStep;
    }
    
}

void PathField::add_points_ui(std::vector<Vec2>points){
    
    // add dots
    
    for (int x=0; x < points.size(); x++) {
        Vec2 point = points.at(x);
        
        float pos_x = (getContentSize().width*point.x)/100;
        float pos_y = (getContentSize().height*point.y)/100;
        
        Sprite *dot = Sprite::create("circle_0.png");
        addChild(dot,1);
        dot->setScale(getContentSize().width*0.0275f/dot->getContentSize().width);
        dot->setPosition(Vec2(pos_x, pos_y));
        
        dot->setColor(_pattern->_line_color);
        
        Vec2 world_pos = dot->getParent()->convertToWorldSpace(dot->getPosition());
        
        if (_pattern->_line_type == PATTERN_LINE_DOTS) {
            dot->setOpacity(0);
        }
        
        _pattern_main_dots.push_back(dot);
        _pattern_main_dot_positions.push_back(world_pos);
        
    }
    
    // Add lines/dots between dots
    
    if (_pattern->_line_type == PATTERN_LINE_LINE) {
        
        for (int x=0; x < _pattern_main_dots.size(); x++) {
            Sprite * dot_current = _pattern_main_dots.at(x);
            if (x+1 < _pattern_main_dots.size()) {
                Sprite * dot_next = _pattern_main_dots.at(x+1);
                add_line(dot_current->getPosition(), dot_next->getPosition(), dot_current->getBoundingBox().size.width);
            }
//            if (x == _pattern_main_dots.size()-1) {
//                dot_current->setVisible(false);
//            }
        }
        
    }
    else if (_pattern->_line_type == PATTERN_LINE_DOTS) {
        
        float one_ball_height = (getContentSize().width*0.035f);
        
        for (int x=0; x < _pattern_main_dots.size(); x++) {
            
            Sprite * dot_current = _pattern_main_dots.at(x);
            
            if (x+1 < _pattern_main_dots.size()) {
                
                Sprite * dot_next = _pattern_main_dots.at(x+1);
               
                Vec2 point_from         = dot_current->getPosition();
                Vec2 point_to           = dot_next->getPosition();
                
                float distance_from_previous               = point_from.getDistance(point_to);
                float steps_done_size                      = distance_from_previous/one_ball_height;
                float steps_done                           = steps_done_size;
                
                float lerp_step         = 1/steps_done;
                float lerp_increaser    = lerp_step;
                
                Point last_point = point_to;
                
                while (lerp_increaser < 1) {
                    
                    Vec2 point_lerp_middle = point_from.lerp(point_to,lerp_increaser);

                    lerp_increaser+=lerp_step;

                    Sprite *dot = Sprite::create("circle_0.png");
                    addChild(dot);
                    dot->setScale(getContentSize().width*0.0135f/dot->getContentSize().width);
                    dot->setPosition(point_lerp_middle);
                    
                    dot->setColor(_pattern->_line_color);
                    last_point = point_lerp_middle;
                }
                
                dot_next->setPosition(last_point);
                Vec2 world_pos                   = dot_next->getParent()->convertToWorldSpace(dot_next->getPosition());
                _pattern_main_dot_positions[x+1] = world_pos;
                
            }
            
        }
        
    }
    
}

void PathField::add_line(Vec2 pt_start, Vec2 pt_finish, float line_height){
    
    Sprite * line = Sprite::create();
    line->setTextureRect(Rect(0, 0, line_height, 1));
    line->setAnchorPoint(Point(0.5f, 0.0f));
    line->setPosition(pt_start);
    line->setColor(_pattern->_line_color);
    addChild(line);
    
    Point originPoint       = pt_finish - pt_start;
    float radians           = atan2f(originPoint.y, originPoint.x);
    float degrees           = radians * (180.0 / M_PI);
    degrees = -degrees;
    degrees += 90;
    
    line->setRotation(degrees);
    line->setScaleY(pt_start.distance(pt_finish) / line->getContentSize().height);
    _pattern_other_objects.push_back(line);
}

void PathField::remove_object  (PathFieldObject * remove_object){
    
    for (int x=0; x < _pattern_movable_objects.size(); x++) {
        
        PathFieldObject * object = _pattern_movable_objects.at(x);
        if (object == remove_object) {
            _pattern_movable_objects.erase(_pattern_movable_objects.begin()+x);
            break;
        }
        
    }

}

void PathField::add_object(PathFieldObject * new_object,int index){
    
//    if (force_add == false || _checkForSlotAvailable == true) {
//        
//        if (_pattern_movable_objects.size() > 0) {
//            if (_pattern_movable_objects.size() == _pattern_main_dot_positions.size()) {
//                // tunnel full
//                return;
//            }
//        }
//        
//        for (int x=0; x < _pattern_movable_objects.size(); x++) {
//            PathFieldObject * ball_in_tunnel = _pattern_movable_objects.at(x);
//            if (ball_in_tunnel->_pathStepIndex < 1) {
//                // tunnel top is full
//                return;
//            }
//        }
//        
//    }
    
    _timeWhenLastAddedObject = 0;
    
    _pattern_movable_objects.push_back(new_object);
    
    new_object->setIsMovingInPath(true);
    new_object->setIsOnLastPathPoint(false);
    new_object->_pathStepIndex = index;
    new_object->_pathStepUp    = true;
    new_object->_pathStepDown  = false;
    
    if (new_object->body != nullptr) {
        new_object->bodyFallowSprite = true;
    }
    
    Vec2 first_pos                  = _pattern_main_dots.at(index)->getPosition();  //_pattern_main_dot_positions.at(index);
    new_object->setPosition(first_pos);
    
}
