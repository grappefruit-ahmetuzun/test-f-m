//
//  LevelDataModel.hpp
//  FruitsKnife-mobile
//
//  Created by Marek on 30/05/2018.
//

#ifndef LevelDataModel_hpp
#define LevelDataModel_hpp

#include "SPFileModel.h"
#include "Game.h"

class LevelDataModel : public SPFileModel{
public:
    
    LevelDataModel()
    {};
    LevelDataModel(std::string fileName);
    virtual ~LevelDataModel(){};
    
    virtual void    preload() override;
    
    std::vector<objetive_recipe_info> get_saved_cocktails_objectives();
    level_info getSavedLevel();
    void save_level(level_info level);
    bool level_available();
    
    void save_coctail_objective(std::vector<objetive_recipe_info>cocktails);
    
private:
    
};

#endif /* LevelDataModel_hpp */
