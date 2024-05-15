//
//  Mixer.c
//  FruitsKnife-mobile
//
//  Created by Slavik on 5/22/18.
//

#include "Mixer.h"

void Mixer::prepare(Size size){
    
    setContentSize(size);
    
    _mixer_spine = SPACE->get_spine_skeleton_animation("spine/mixer/", "mxer", true);
    _mixer_spine->clearTracks();
    _mixer_spine->update(0);
    _mixer_spine->setScale(getContentSize().width / _mixer_spine->getBoundingBox().size.width);
    _mixer_spine->setPosition(Point(getContentSize().width * 0.5f, 0));
    addChild(_mixer_spine);
    _mixer_spine->setTimeScale(1.0f);
    _mixer_spine->setAnimation(0, "idle", true);
    
    _mixer_spine->setEventListener([this](spTrackEntry* entry, spEvent* event){
        
        if (Game::is_same_strings(event->data->name, "add")) {
           
        }
        else if (Game::is_same_strings(event->data->name, "empty")) {
            
    //        setSegmentsCount(0);
//            
//            if (get_coctail) {
//                get_coctail(_receipe_type);
//            }
        }
    });
    
    setSegmentsCount(0);
    
}

void Mixer::changeMixerFilledSegments(int segments, fruit_type _f_type) {
    
    _next_fruit_type  = _f_type;
    current_segment   = segments;
    
    setSegmentsCount(current_segment);
    
    if (_mixer_spine) {
        _mixer_spine->setAnimation(0, "take", false);
        _mixer_spine->addAnimation(0, "idle", true);
    }
}

void Mixer::mixNow(RECIPE_TYPES _receipe){
    
    _receipe_type = _receipe;
    
    current_segment = 0;
    
    if (_mixer_spine) {
        
        auto delay = DelayTime::create(0.3f);
        auto callf = CallFunc::create([this]{
            
            setSegmentsCount(current_segment);
            
            _mixer_spine->setAnimation(0, "take", false);
            _mixer_spine->addAnimation(0, "idle", true);
            
            
            if (get_coctail) {
                get_coctail(_receipe_type);
            }
        });
        auto seq   = Sequence::create(delay, callf, NULL);
        runAction(seq);
   
    }
}

void Mixer::setSegmentsCount(int count){
    
    Color3B color = Recipes::getColorByfruitType(_next_fruit_type);
    
    std::string skin_name = Recipes::get_spine_slot_name(_next_fruit_type);
    
    for (int i = 1; i <= 9; i++) {
        spSlot * color_slot = _mixer_spine->findSlot(StringUtils::format("collor_%i", i).c_str());
        
        std::string slot_name = StringUtils::format("icon_%i", i).c_str();
        
        if (color_slot) {
            
            if (i == count) {
                color_slot->color.r = color.r / 255.0f;
                color_slot->color.g = color.g / 255.0f;
                color_slot->color.b = color.b / 255.0f;
                
                _mixer_spine->setAttachment(slot_name, skin_name.c_str());
            }
            
            if (i <= count) {
                color_slot->color.a = 1;
            }
            else{
                color_slot->color.a = 0;
                
                _mixer_spine->setAttachment(slot_name, "off");
            }
        }
    }
}

