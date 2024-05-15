//
//  PathIndicator.cpp
//  DunkPath-mobile
//
//  Created by Marek Reichenbach on 16/02/2018.
//

#include "PathIndicator.h"
#include "Game.h"

void PathIndicator::prepare(Size size){
    
    setTextureRect(Rect(0, 0, size.width, size.height));
    setColor(Color3B(200, 200, 200));
    setOpacity(0);
    
    one_step_size_w = size.width/10;
    
    steps_container = Sprite::create();
    steps_container->setTextureRect(Rect(0, 0, one_step_size_w, 0));
    addChild(steps_container);
    steps_container->setPosition(getContentSize()*0.5f);
    
    pencil = Sprite::create("shuriken_icon.png");
    addChild(pencil);
    pencil->setScale(one_step_size_w*1.0f/pencil->getContentSize().width);
    pencil->setPosition(Vec2(0, getContentSize().height*0.5f));
    
}

void PathIndicator::setMaxSteps(int max){
    
    for (Sprite *step :_steps) {
        step->removeFromParentAndCleanup(true);
    }
    
    _steps.clear();
    
    steps_container->setTextureRect(Rect(0, 0, one_step_size_w*max, 0));
    
    Vec2 pos = Vec2(one_step_size_w*0.5f, 0);
    
    for (int x=0; x < max; x++) {
        
        Sprite *step = Sprite::create("shuriken_icon.png");
        steps_container->addChild(step);
        float w = one_step_size_w/step->getContentSize().width;
      //  w*=0.9f;
        step->setScale(one_step_size_w*0.75f/step->getContentSize().width);//(w);
        step->setPosition(pos);
        step->setColor(Color3B(59,161,158));
        _steps.push_back(step);
        pos.x+=one_step_size_w;
    }
    
    pencil->setVisible(false);
    steps_container->setPosition(getContentSize()*0.5f);
    
    setAvailable(max);
}

void PathIndicator::setAvailable(int available){
    
     for (int x=0; x < _steps.size(); x++) {
         
         Sprite * step = _steps.at(x);
         if (available <= x) {
             step->setColor(Color3B(46,92,91));
         }
         
     }
    
    if (available == 0){
        pencil->setColor(Color3B(46,92,91));
    }
    
}
