//
//  LevelManager.cpp
//  FruitsKnife-mobile
//
//  Created by Marek on 30/05/2018.
//

#include "LevelManager.h"
#include "Patterns.h"

LevelManager::~LevelManager(){
    
}

std::shared_ptr< LevelManager > levelInstance;

std::shared_ptr< LevelManager > LevelManager::getInstance() {
    
    if (levelInstance){
        return levelInstance;
    }
    
    levelInstance = std::make_shared< LevelManager >();
    return levelInstance;
}

void LevelManager::preload(){
     _data_model = new LevelDataModel("lvlmanhrshgr");
}

bool LevelManager::is_level_available(){
    return _data_model->level_available();
}

level_info LevelManager::get_current_level_info(){

    if (is_level_available() == false) {
        Patterns::getInstance()->generate_new_level();
        Patterns::getInstance()->generate_new_coctails();
    }
    
    level_info l = Patterns::getInstance()->get_current_level();
    
    return l;
}
