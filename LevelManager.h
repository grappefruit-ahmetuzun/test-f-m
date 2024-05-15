//
//  LevelManager.hpp
//  FruitsKnife-mobile
//
//  Created by Marek on 30/05/2018.
//

#ifndef LevelManager_hpp
#define LevelManager_hpp

#include "cocos2d.h"
#include "SPUserDefault.h"
#include "LevelDataModel.h"
#include "Game.h"

USING_NS_CC;

class LevelManager{
    
public:
    
    static std::shared_ptr< LevelManager > getInstance();
    
    LevelManager()
    {
        preload();
    };
    virtual ~LevelManager();
    
    static int get_level_number(){
        return SPUserDefault::getInstance()->getIntegerForKey("level_id");
    }
    
    static void set_level_number(int number){
        return SPUserDefault::getInstance()->setIntegerForKey("level_id", number);
    }
    
    level_info get_current_level_info();
    bool is_level_available();
    
    LevelDataModel * _data_model = nullptr;

private:
    
    void preload();

};

#endif /* LevelManager_hpp */
