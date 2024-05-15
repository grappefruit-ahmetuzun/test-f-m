//
//  PathFieldObject.hpp
//  99Ballz-mobile
//
//  Created by Marek on 13/11/2017.
//

#ifndef PathFieldObject_hpp
#define PathFieldObject_hpp

#include "SPPhysicsSprite.h"
#include "Game.h"
#include "Space.h"

USING_NS_CC;

class PathFieldObject : public SPPhysicsSprite{
    
public:
    
    PathFieldObject():
    _isOnLastPathPoint(false),
    _movingPosOffset(0,0),
    _isMovingInPath(false),
    _canMoveInPath(false)
    {}
    
    CREATE_FUNC(PathFieldObject);
    
    virtual bool init() override;
    
    CC_SYNTHESIZE(bool, _isOnLastPathPoint, IsOnLastPathPoint);
    CC_SYNTHESIZE(Vec2, _movingPosOffset,   MovingPosOffset);
    CC_SYNTHESIZE(bool, _isMovingInPath,    IsMovingInPath);
    CC_SYNTHESIZE(bool, _canMoveInPath,     CanMoveInPath);
    
    bool         _pathStepDown = false;
    bool         _pathStepUp    = false;
    int          _pathStepIndex = 0;
    
private:
    
};

#endif /* PathFieldObject_hpp */
