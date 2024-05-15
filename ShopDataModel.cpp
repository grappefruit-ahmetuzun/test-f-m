//
//  ShopDataModel.cpp
//  SummerGames
//
//  Created by Marek on 18/07/16.
//
//

#include "ShopDataModel.h"

#define key_items_purchased         "puritems"
#define key_items_not_new           "purisnotnew"


ShopDataModel::ShopDataModel(std::string fileName){
    _fname = fileName;
    setEncryptData(true);
    preload();
}

void ShopDataModel::set_as_not_new(SHOP_ITEM item){
    
    if (is_not_new(item)) {
        return;
    }
    
    if (_data.HasMember(key_items_not_new)){
        rapidjson::Value &balls_array = _data[key_items_not_new];
        balls_array.PushBack(item, getAllocator());
        save();
    }
    
}

bool ShopDataModel::is_not_new(SHOP_ITEM item){
    if (_data.HasMember(key_items_not_new)){
        const rapidjson::Value &balls_array = _data[key_items_not_new];
        for (int x=0; x < balls_array.Size(); x++) {
            const rapidjson::Value &ball = balls_array[x];
            if (ball.IsInt()) {
                if (ball.GetInt() == item) {
                    return true;
                }
            }
        }
    }
    return false;
}

void ShopDataModel::purchase(SHOP_ITEM item){
    
    if (isPurchased(item)) {
        return;
    }
    
    
    if (_data.HasMember(key_items_purchased)){
        rapidjson::Value &balls_array = _data[key_items_purchased];
        balls_array.PushBack(item, getAllocator());
        save();
    }
    
}

bool ShopDataModel::isPurchased (SHOP_ITEM item){
    if (_data.HasMember(key_items_purchased)){
        const rapidjson::Value &balls_array = _data[key_items_purchased];
        for (int x=0; x < balls_array.Size(); x++) {
            const rapidjson::Value &ball = balls_array[x];
            if (ball.IsInt()) {
                if (ball.GetInt() == item) {
                    return true;
                }
            }
        }
    }
    return false;
}

std::vector<SHOP_ITEM>ShopDataModel::get_items(){
    std::vector<SHOP_ITEM> purchased;
    
    if (_data.HasMember(key_items_purchased)){
        const rapidjson::Value &balls_array = _data[key_items_purchased];
        for (int x=0; x < balls_array.Size(); x++) {
            const rapidjson::Value &ball = balls_array[x];
            if (ball.IsInt()) {
                purchased.push_back((SHOP_ITEM)ball.GetInt());
            }
        }
    }
    
    return purchased;
}

void ShopDataModel::preload(){
    SPFileModel::preload();
    
    bool save = false;
    
    if (_data.HasMember(key_items_purchased) == false){
        rapidjson::Value balls_array(rapidjson::kArrayType);
        _data.AddMember(key_items_purchased,balls_array,getAllocator());
        save = true;
    }

    if (_data.HasMember(key_items_not_new) == false){
        rapidjson::Value balls_array(rapidjson::kArrayType);
        _data.AddMember(key_items_not_new,balls_array,getAllocator());
        save = true;
    }

    if (save) {
        SPFileModel::save();
    }
    
    printData();
}
