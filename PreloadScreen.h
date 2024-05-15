//
//  PreloadScreen.hpp
//  TixGame
//
//  Created by Marek on 04/05/16.
//
//

#ifndef PreloadScreen_hpp
#define PreloadScreen_hpp

#include "cocos2d.h"

USING_NS_CC;

class PreloadScreen : public Layer{
    
public:
    PreloadScreen()
    {};
    ~PreloadScreen(){};
    
    CREATE_FUNC(PreloadScreen);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;
    
    bool init() override;

private:
    
    Sprite      *_content           = nullptr;
    
};

#endif /* PreloadScreen_hpp */
