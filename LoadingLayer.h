//
//  LoadingLayer.hpp
//  mannequin
//
//  Created by Marek on 22/11/2016.
//
//

#ifndef LoadingLayer_hpp
#define LoadingLayer_hpp

#include "GameLayer.h"
#include "SPButton.h"

USING_NS_CC;

class LoadingLayer : public GameLayer
{
public:
    
    LoadingLayer()
    {}
    virtual ~LoadingLayer(){}
    
    virtual bool init() override;
    
    CREATE_FUNC(LoadingLayer);
    
    void hide_all();
    
    Sprite * bg = nullptr;
    Sprite * _logo = nullptr;
    ProgressTimer * _icon_progress = nullptr;
    Sprite * _icon_bottom = nullptr;
    Sprite * _game_logo = nullptr;
    
    void animate(std::function<void> on_finish);
};

#endif /* LoadingLayer_hpp */
