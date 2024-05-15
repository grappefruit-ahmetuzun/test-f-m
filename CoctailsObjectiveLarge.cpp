//
//  CoctailsObjectiveLarge.cpp
//  FruitsKnife-mobile
//
//  Created by Marek on 05/06/2018.
//

#include "CoctailsObjectiveLarge.h"
#include "Game.h"
#include "PlatformManager.h"

void CoctailsObjectiveLarge::prepare(Size size){
    
    std::vector<objetive_recipe_info> fortune_wheel_objects = Recipes::get_objective_recipes();
    
    int cells = (int)fortune_wheel_objects.size();   //Game::getCoctailsCollectObjective();
    
    setTextureRect(Rect(0, 0, size.height*cells, size.height));
    setOpacity(0);
    
    Size cell_size = Size(size.height, size.height);
    Vec2 cell_pos  = Vec2(cell_size.width*0.5f, getContentSize().height*0.5f);
    int collected  = Game::getCoctailsCollected();
    
    for (int x=0; x < cells; x++) {
        
        objetive_recipe_info recipe_info = fortune_wheel_objects.at(x);
        
        RECIPE_TYPES coctail_type        = recipe_info.recipe_type;         // (RECIPE_TYPES)Game::getCotailAdded(x);
        RECIPE_CATEGORY coctail_category = recipe_info.recipe_category;     // Recipes::get_recipe_category(coctail_type);
        
        std::string bg_img = "coctail_objective/slot_empty.png";
        
        bool is_completed   = false;
        bool is_winner_cell = false;
        Color3B box_color = Color3B::WHITE;
        
        if (collected > x) {
            bg_img = "coctail_objective/box.png";
            is_completed = true;
            box_color = Recipes::get_recipe_color(coctail_category);
        }
        
        if (collected == x+1){
            is_winner_cell = true;
            bg_img = "coctail_objective/slot_empty.png";
            box_color = Color3B::WHITE;
        }
        
        Sprite * cell_bg = Sprite::create(bg_img);
        addChild(cell_bg);
        cell_bg->setScale(cell_size.width*0.9f/cell_bg->getContentSize().width);
        cell_bg->setPosition(cell_pos);
        cell_bg->setColor(box_color);
        
        Sprite * frame = Sprite::create("coctail_objective/box_frame.png");
        cell_bg->addChild(frame);
        frame->setScale(cell_bg->getContentSize().width*1.05f/frame->getContentSize().width);
        frame->setPosition(cell_bg->getContentSize()*0.5f);
        frame->setTag(1);
        frame->setVisible(is_completed);
        frame->setColor(Color3B(254, 223, 55));

        Coctail * coctail = Coctail::create();
        cell_bg->addChild(coctail);
        coctail->prepare(cell_bg->getContentSize(),coctail_type);
        coctail->coctail_spr->setAnchorPoint(Vec2(0.5f, 0));
        coctail->coctail_spr->setScale(coctail->getContentSize().height*0.75f/coctail->coctail_spr->getContentSize().height);
        coctail->coctail_spr->setPosition(Vec2(coctail->coctail_spr->getPositionX(),
                                               coctail->getContentSize().height*0.115f));
        coctail->setPosition(Vec2(cell_bg->getContentSize().width*0.5f,
                                  cell_bg->getContentSize().height*0.5f));
        
        if (is_completed == false || is_winner_cell == true){
            coctail->setVisible(false);
            frame->setVisible(false);
        }
        
        _cells.push_back(cell_bg);
        _coctails.push_back(coctail);
        
        cell_pos.x+=cell_size.width;
       // cell_pos.y+=cell_size.height*0.2f;
        
    }
    
}

void CoctailsObjectiveLarge::hide_all(){
    
    for (Sprite *cell : _cells) {
        cell->setVisible(false);
    }
    
}

void CoctailsObjectiveLarge::animate_winner_cell(){
    
    SoundDirector::playSound("ev_new_coctail_tile");
    PlatformManager::vibrate(2);
    
    int win_index =  Game::getCoctailsCollected();
    win_index-=1;
    if (win_index < 0) {
        win_index = 0;
    }
    if (win_index >= _cells.size()) {
        win_index = (int)_cells.size()-1;
    }
    
    Sprite   * cell    = _cells.at(win_index);
    Coctail  * coctail = _coctails.at(win_index);
    
    cell->setTexture("coctail_objective/box.png");
    cell->setLocalZOrder(1);
    RECIPE_CATEGORY category = Recipes::get_recipe_category(coctail->_coctail_type);
    
    cell->setColor(Recipes::get_recipe_color(category));
    
    if (cell->getChildByTag(1)) {
        
        Sprite * frame = (Sprite*)cell->getChildByTag(1);
        frame->setScale(cell->getContentSize().width*1.05f/frame->getContentSize().width);
        frame->setPosition(cell->getContentSize()*0.5f);
        frame->setVisible(true);
        
        Color3B color_from = frame->getColor();
        Color3B color_to   = Color3B::WHITE;
        auto f1 = TintTo::create(0.25f, color_to.r, color_to.g, color_to.b);
        auto f2 = TintTo::create(0.25f, color_from.r, color_from.g, color_from.b);
        auto f = Sequence::create(f1,f2, NULL);
        frame->runAction(Repeat::create(f, 3));
        
    }
    
    float cell_scale = cell->getScale();
    
    coctail->setVisible(true);
    coctail->setOpacity(0);
    coctail->runAction(FadeTo::create(0.15f, 255));
    
    auto scale     = ScaleTo::create(1.5f, cell->getScale());
    auto scale_e   = EaseElasticOut::create(scale,0.5f);
    auto scale_seq = Sequence::create(ScaleTo::create(0.125f, cell->getScale()*1.5f),scale_e, NULL);
    cell->runAction(scale_seq);
    
    if (win_index == Game::getCoctailsCollectObjective()-1) {
  
        auto d = DelayTime::create(0.5f);
        auto call = CallFunc::create([this,cell_scale]{
            
            for (int x=0; x < _cells.size(); x++) {
                
                Sprite *coc = _cells.at(x);
                
                auto scale          = ScaleTo::create(0.15f, cell_scale*1.05f);
                auto scale2         = ScaleTo::create(0.15f, cell_scale);
                auto scale_seq      = Sequence::create(scale,scale2, NULL);
                auto scale_ease     = EaseInOut::create(scale_seq, 1.5f);
                coc->runAction(RepeatForever::create(scale_ease));
                
            }
            
        });
        auto seq = Sequence::create(d,call, NULL);
        runAction(seq);
    
    }

}

void CoctailsObjectiveLarge::animate_cells_appear(){
    
   // SoundDirector::playSound("ev_coctail_tiles_grid_appear");
    
    for (int x=0; x < _cells.size(); x++) {
        Sprite * cell = _cells.at(x);
        cell->setVisible(true);
        auto d          = DelayTime::create(0.05f*x);
        auto scale      = ScaleTo::create(0.25f, cell->getScale());
        cell->setScale(0);
        auto scale_e    = EaseElasticOut::create(scale,1.5f);
        auto seq        = Sequence::create(d,scale_e, NULL);
        cell->runAction(seq);
    }
    
}
