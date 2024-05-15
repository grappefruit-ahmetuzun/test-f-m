//
//  ExitLayer.hpp
//  TixGame
//
//  Created by Marek on 19/04/16.
//
//

#ifndef ExitLayer_h
#define ExitLayer_h

#include "cocos2d.h"
#include "SPButton.h"
#include "GameLayer.h"

USING_NS_CC;

class ExitLayer : public GameLayer{
    
public:
    ExitLayer();
    ~ExitLayer();
    
    CREATE_FUNC(ExitLayer);
    
    bool init() override;
    
    SPButton * _yesButton   = nullptr;
    SPButton * _noButton    = nullptr;
    Label * _titleLabel     = nullptr;
    
    void prepare(std::string txt);
    
private:
    
};

#endif /* ExitLayer_hpp */
