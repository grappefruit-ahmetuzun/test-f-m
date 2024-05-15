//
//  PathIndicator.hpp
//  DunkPath-mobile
//
//  Created by Marek Reichenbach on 16/02/2018.
//

#ifndef PathIndicator_hpp
#define PathIndicator_hpp

#include "cocos2d.h"
#include "SoundDirector.h"

USING_NS_CC;

class PathIndicator : public Sprite{
    
public:
    
    PathIndicator()
    {}
    
    CREATE_FUNC(PathIndicator);
    
    void prepare(Size size);
    
    float one_step_size_w;
    
    Sprite * steps_container;
    Sprite * pencil;
    
    void setMaxSteps(int max);
    void setAvailable(int available);
    
    std::vector<Sprite*>_steps;
    

};

#endif /* PathIndicator_hpp */
