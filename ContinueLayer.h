//
//  ContinueLayer.h
//  BasketDunk
//
//  Created by Marek on 23/10/2017.
//
//

#ifndef ContinueLayer_h
#define ContinueLayer_h

#include "GameLayer.h"
#include "Space.h"
#include "SPButton.h"

USING_NS_CC;

class ContinueLayer : public GameLayer{
    
public:
    CREATE_FUNC(ContinueLayer);
    
    ContinueLayer()
    {}
    ~ContinueLayer(){}
    
    virtual void onExit() override;

    void prepare();
    
    SPButton * _continue_button = nullptr;
    SPButton * _nothanks_button = nullptr;
    
    void progress_animation_did_finish();
    void stop_sound();
    
    std::function<void()> _animation_did_finish_callback = nullptr;
    
    std::vector<Sprite *> _bullets;
    
    bool bullet_flag = false;
    
private:
    
    ProgressTimer * _progress = nullptr;
    
    unsigned int sound_id = 0;
    
};

#endif /* ContinueLayer_hpp */
