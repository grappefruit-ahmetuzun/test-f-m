//
//  LevelDataModel.cpp
//  FruitsKnife-mobile
//
//  Created by Marek on 30/05/2018.
//

#include "LevelDataModel.h"

#define key_level "level_object"
#define key_coctails "cocktails_object"

LevelDataModel::LevelDataModel(std::string fileName){
    _fname = fileName;
    setEncryptData(true);
    preload();
}

bool LevelDataModel::level_available(){
    if (_data.HasMember(key_level)){
        return true;
    }
    return false;
}

void LevelDataModel::preload(){
    SPFileModel::preload();
    
    bool save = false;
    
    if (save) {
        SPFileModel::save();
    }
    
    printData();
}

std::vector<objetive_recipe_info> LevelDataModel::get_saved_cocktails_objectives(){
    
    std::vector<objetive_recipe_info>array;
    
    if (_data.HasMember(key_coctails)){
        
        rapidjson::Value &cocktails_arary    = _data[key_coctails];
        
        for (int x=0; x < cocktails_arary.Size(); x++) {
            
            rapidjson::Value &cocktail_obj = cocktails_arary[x];
            objetive_recipe_info info;
            
            info.recipe_category   = (RECIPE_CATEGORY)cocktail_obj["recipe_category"].GetInt();
            info.recipe_type       = (RECIPE_TYPES)cocktail_obj["recipe_type"].GetInt();
            info.coins_give        = cocktail_obj["coins"].GetInt();
            info.gems_give         = cocktail_obj["gems"].GetInt();
            info.knife_id          = cocktail_obj["knife"].GetInt();
            info.is_winner_1       = cocktail_obj["is_winner_1"].GetBool();
            info.is_winner_2       = cocktail_obj["is_winner_2"].GetBool();
            
            array.push_back(info);
        }
        
    }
    
    return array;
}

level_info LevelDataModel::getSavedLevel(){
    
    level_info l;
    
    if (_data.HasMember(key_level)){
        
        rapidjson::Value &level_object    = _data[key_level];
        rapidjson::Value &patterns_array  = level_object["patterns"];
        
        for (int x=0; x < patterns_array.Size(); x++) {
            
            pattern_info pattern;
            
            rapidjson::Value &pattern_obj = patterns_array[x];
            
            rapidjson::Value &positions_array = pattern_obj["positions"];
            rapidjson::Value &fruits_array    = pattern_obj["fruits"];
            rapidjson::Value &actions_array   = pattern_obj["actions"];
            
            for (int p = 0; p < positions_array.Size(); p++) {
                
                rapidjson::Value &position_object = positions_array[p];
                
                Vec2 position;
                position.x = position_object["x"].GetFloat();
                position.y = position_object["y"].GetFloat();
                
                pattern._path_points.push_back(position);

            }
            
            for (int p = 0; p < fruits_array.Size(); p++) {
                
                rapidjson::Value &fruits_object = fruits_array[p];
                fruit_info fruit;
                fruit.type = (fruit_type)(fruits_object["type"].GetInt());
                
                pattern._fruits.push_back(fruit);
                
            }
            
            for (int p = 0; p < actions_array.Size(); p++) {
                
                rapidjson::Value &action_object = actions_array[p];
                
                action_info action;
                
                action.duration = action_object["duration"].GetFloat();
                action.angle    = action_object["angle"].GetFloat();
                action.rate     = action_object["rate"].GetFloat();
                action.ease     = (ACTION_EASE_TYPE)(action_object["ease"].GetInt());
                
                // loose count duration changes
                
                int loose_count    = Game::getLooseCount(x);
                float percent_add  = loose_count*0.01f;
                float duration_new = action.duration+percent_add;
                //log("lost: %i dur: %f",loose_count,percent_add);
                action.duration = duration_new;

                pattern._actions.push_back(action);
            }
            
            pattern.circle_radius =  pattern_obj["circle_radius"].GetInt();

            l._patterns.push_back(pattern);
        }
        
    }
    
    
   // rapidjson::Value &patterns_array = _data[key_black_list_items];
    
    return l;
    
}

void LevelDataModel::save_coctail_objective(std::vector<objetive_recipe_info>cocktails){
    
    if (_data.HasMember(key_coctails)){
        _data.RemoveMember(key_coctails);
    }
    
    rapidjson::Value cocktails_array(rapidjson::kArrayType);
    
    for (int x=0; x < cocktails.size(); x++) {
        
        objetive_recipe_info info = cocktails.at(x);
        
        rapidjson::Value cocktail_object (rapidjson::kObjectType);
        
        cocktail_object.AddMember("recipe_category",    info.recipe_category,        getAllocator());
        cocktail_object.AddMember("recipe_type",        info.recipe_type,            getAllocator());
        cocktail_object.AddMember("coins",              info.coins_give,             getAllocator());
        cocktail_object.AddMember("gems",               info.gems_give,              getAllocator());
        cocktail_object.AddMember("knife",              info.knife_id,               getAllocator());
        cocktail_object.AddMember("is_winner_1",        info.is_winner_1,            getAllocator());
        cocktail_object.AddMember("is_winner_2",        info.is_winner_2,            getAllocator());
        
        cocktails_array.PushBack(cocktail_object, getAllocator());
    }
    
    _data.AddMember(key_coctails,cocktails_array,getAllocator());
    
    save();
  //  printData();
    
}

void LevelDataModel::save_level(level_info level){
    
    if (_data.HasMember(key_level)){
        _data.RemoveMember(key_level);
    }
    
    rapidjson::Value level_object(rapidjson::kObjectType);
    rapidjson::Value patterns_array (rapidjson::kArrayType);
    
    for (int x=0; x < level._patterns.size(); x++) {
        
        rapidjson::Value pattern_object (rapidjson::kObjectType);
        
        rapidjson::Value positions_array (rapidjson::kArrayType);
        rapidjson::Value fruits_array    (rapidjson::kArrayType);
        rapidjson::Value actions_array   (rapidjson::kArrayType);
        
        pattern_info pattern_info = level._patterns.at(x);
        
        // position
        
        for (int p = 0; p < pattern_info._path_points.size(); p++) {
            
            Vec2 position = pattern_info._path_points.at(p);
            
            rapidjson::Value position_object (rapidjson::kObjectType);
            position_object.AddMember("x",position.x,getAllocator());
            position_object.AddMember("y",position.y,getAllocator());
            
            positions_array.PushBack(position_object, getAllocator());
        }
        
        // fruits
        
        for (int p = 0; p < pattern_info._fruits.size(); p++) {

            fruit_info fruit = pattern_info._fruits.at(p);

            rapidjson::Value fruit_object (rapidjson::kObjectType);
            fruit_object.AddMember("type",fruit.type,getAllocator());

            fruits_array.PushBack(fruit_object, getAllocator());
        }
        
        // actions
        
        for (int p = 0; p < pattern_info._actions.size(); p++) {
            
            action_info action = pattern_info._actions.at(p);
            
            rapidjson::Value action_object (rapidjson::kObjectType);
            
            action_object.AddMember("duration", action.duration,    getAllocator());
            action_object.AddMember("angle",    action.angle,       getAllocator());
            action_object.AddMember("rate",     action.rate,        getAllocator());
            action_object.AddMember("ease",     action.ease,        getAllocator());
            
            actions_array.PushBack(action_object, getAllocator());
        }

        pattern_object.AddMember("actions",      actions_array,      getAllocator());
        pattern_object.AddMember("fruits",       fruits_array,       getAllocator());
        pattern_object.AddMember("positions",    positions_array,    getAllocator());
        
        //
        
        pattern_object.AddMember("circle_radius",       pattern_info.circle_radius, getAllocator());
        
        patterns_array.PushBack(pattern_object,getAllocator());
    }
    
     level_object.AddMember("patterns",patterns_array,getAllocator());
    
    _data.AddMember(key_level,level_object,getAllocator());
    
    save();
    printData();
    
}
