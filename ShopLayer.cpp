//
//  ShopLayer.cpp
//  HotDog-mobile
//
//  Created by Marek on 7/16/17.
//

#include "ShopLayer.h"
#include "SoundDirector.h"
#include "AdManager.h"
#include "PlatformManager.h"
#include "ShopManager.h"
#include "Settings.h"

bool ShopLayer::init(){
    if (!GameLayer::init()){
        return false;
    }
    
    setTouchBlock(false);
    
    getBackButton()->setLocalZOrder(4);
    getBackButton()->setPositionY(getHeaderUIDefaultPosY()/*-getContentSize().height * 0.0075f*/);
    getBackButton()->getContentSprite()->setColor(Color3B(85, 160, 157));
    
    Sprite *_left_border = Sprite::create();
    _left_border->setTextureRect(Rect(0, 0, (getContentSize().width-(getContainer()->getContentSize().width))/2, getContentSize().height));
    _left_border->setPosition(Point(_left_border->getContentSize().width*0.5f, getContentSize().height*0.5f));
    _left_border->setColor(Color3B::BLACK);
    addChild(_left_border, 3);
    
    Sprite *_right_border = Sprite::create();
    _right_border->setTextureRect(Rect(0, 0, (getContentSize().width-(getContainer()->getContentSize().width))/2, getContentSize().height));
    _right_border->setPosition(Point(getContentSize().width - (_right_border->getContentSize().width*0.5f), getContentSize().height*0.5f));
    _right_border->setColor(Color3B::BLACK);
    addChild(_right_border, 3);

    Sprite * _background = Sprite::create();
    _background->setTextureRect(Rect(0, 0, getContentSize().width, getContentSize().height));
    _background->setPosition(getContentSize()/2);
    addChild(_background);
    
    Sprite * gradient_blick = Sprite::create("shop/grad.png");
    gradient_blick->setScale(getContainer()->getContentSize().width * 1.f / gradient_blick->getContentSize().width);
    addChild(gradient_blick);
    
    bool dark_mode_on = Settings::getStateOn(settings_darkmode);
    
    if (dark_mode_on == true) {
        _left_border->setColor(Color3B(0, 0, 0));
        _right_border->setColor(Color3B(0, 0, 0));
        
        _background->setColor(Color3B(12, 30, 35));
        
        gradient_blick->setColor(Color3B(2, 72, 79));
        gradient_blick->setOpacity(255);
    }
    else{
        _left_border->setColor(Color3B(117, 145, 157));
        _right_border->setColor(Color3B(117, 145, 157));
        
        _background->setColor(Color3B(225, 241, 241));
        gradient_blick->setOpacity(255 * 0.7f);
    }
    
    _background->setScale(getContentSize().height / _background->getContentSize().height);
    
    if (_background->getBoundingBox().size.width < getContentSize().width) {
        _background->setScaleX(getContentSize().width / _background->getContentSize().width);
    }
    
    
    _all_pages.push_back(SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_2);
    _all_pages.push_back(SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_1);
    _all_pages.push_back(SHOP_PAGE_TYPE_KNIVES_GEM_PAGE_1);
    _all_pages.push_back(SHOP_PAGE_TYPE_KNIVES_FORTUNE_WHLLE_PAGE_1);
    
    float scroll_w = getContainer()->getContentSize().width * 0.8f;
    
    Size s;
    s.width     = scroll_w;
    s.height    = scroll_w;
    
    _collectionView = SPCollectionView::createWithSize(s);
    addChild(_collectionView,2);
    _collectionView->setDirection(SPSCROLLVIEW::DIRECTION::HORIZONTAL);
    _collectionView->setOpacity(0);
    _collectionView->setClippingEnabled(false);
    _collectionView->setPaging(true);
    _collectionView->setTapBeginIgnoreContentsizeW(true);
    _collectionView->setAnchorPoint(Point(0.5f,0.5f));
    _collectionView->setPosition(Vec2(getContentSize().width*0.5f, (getContentSize().height * 0.5f) - getContainer()->getContentSize().height * 0.015f));
    _collectionView->setCollectionViewDelegate(this);
    _collectionView->setInteligentSpritesDelegate(this);
    _collectionView->setScaleCellonTouch(false);
    _collectionView->setCellsVisibilityControl(false);
    _collectionView->reloadData();
    
    // scroll seperators
    float separator_pos_y = 0;
    
    
    float offset_y      = _collectionView->getContentSize().height*0.5f;
    offset_y           += getContainer()->getContentSize().height*0.025f;
    
    offset_y *= -1.075f;
    separator_pos_y = _collectionView->getPositionY() + offset_y;
    
    
    _page_control = SPPageControl::create(getContainer()->getContentSize().height * 0.015f, getContainer()->getContentSize().height * 0.01f, (int)_all_pages.size(), Color3B(85, 160, 157), Color3B(255, 255, 255));
    _page_control->setPosition(Point(getContentSize().width * 0.5f, separator_pos_y + getContainer()->getContentSize().height * 0.02f));
    addChild(_page_control);
    
    
    for (int i = 0; i < _page_control->indicatorDots.size(); i++) {
        Sprite * dot = _page_control->indicatorDots.at(i);
        
        dot->setOpacity(0);
        
        auto fade = FadeTo::create(0.4f, 255);
        auto ease = EaseInOut::create(fade, 2.2f);
        auto delay = DelayTime::create(0.3f);
        auto seq   = Sequence::create(delay, ease, NULL);
        dot->runAction(seq);
    }
    
    
    SHOP_PAGE_TYPE _category_by_gun = SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_1;
    
    for (int i = 0; i < _collectionView->getCells().size(); i++) {
        ShopLayerCell * cell = (ShopLayerCell *)_collectionView->getCells().at(i);
        
        bool founded = false;
        
        for (int j = 0; j < cell->items.size(); j++) {
            CellItem item = cell->items.at(j);
            if (item._purchased && item._selected) {
                _category_by_gun = cell->_shop_category;
                founded = true;
                break;
            }
        }
        
        if (founded) {
            break;
        }
    }
    
//    if (can_buy_new_gun(SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_1)) {
//        _category_by_gun = SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_1;
//    }
//    else if (can_buy_new_gun(SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_2)) {
//        _category_by_gun = SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_2;
//    }
//    else if (can_buy_new_gun(SHOP_PAGE_TYPE_KNIVES_GEM_PAGE_1)) {
//        _category_by_gun = SHOP_PAGE_TYPE_KNIVES_GEM_PAGE_1;
//    }
    
    ShopLayerCell * cell_to_select = get_cell_by_type(_category_by_gun);
    
    _collectionView->set_next_page(cell_to_select, true);
    
    
    ShopLayerCell * cell_now = (ShopLayerCell *)_collectionView->getPageNow();
    
    _page_control->setActiveDot(cell_now->getSectionIndex(), false);
    
    _prev_bottom_items_category = _category_by_gun;
    
    
    _coin_knife_button = SPButton::createWithImage("shop/get_random.png");
    addChild(_coin_knife_button);
    _coin_knife_button->setScale(getContainer()->getContentSize().height * 0.078f / _coin_knife_button->getContentSize().height);
    _coin_knife_button->setPosition(Vec2(_collectionView->getPositionX(),
                                      _collectionView->getPositionY()-
                                      _collectionView->getContentSize().height * 0.5f -
                                      _coin_knife_button->getBoundingBox().size.height * 0.5f -
                                      getContainer()->getContentSize().height * 0.05f));
    
    _coin_knife_button->setVoidTouchDownCallback([this]{
        unlock_random_weapon();
    });
    
    
    {
        Sprite * _content = _coin_knife_button->getContentSprite();
        
        Label *_price_label = Label::createWithTTF("200", "fonts/Blogger_Sans-Bold.otf",
                                                   _content->getContentSize().height * 0.28f);
        _price_label->setPosition(_content->getContentSize().width * 0.84f,
                                  _content->getContentSize().height * 0.265f);
        _price_label->setColor(Color3B::BLACK);
        _price_label->setOpacity(255);
        _price_label->setTag(111);
        _price_label->setAlignment(TextHAlignment::CENTER);
        _price_label->setAnchorPoint(Vec2(0.5f, 0.5f));
        _content->addChild(_price_label);
        _price_label->setString(StringUtils::format("%i",Shop::getItemPrice()).c_str());
        
    }
    
    
    _gem_knife_button = SPButton::createWithImage("shop/get_random_gems.png");
    addChild(_gem_knife_button);
    _gem_knife_button->setScale(getContainer()->getContentSize().height * 0.078f / _gem_knife_button->getContentSize().height);
    _gem_knife_button->setPosition(Vec2(_collectionView->getPositionX(),
                                         _collectionView->getPositionY()-
                                         _collectionView->getContentSize().height * 0.5f -
                                         _gem_knife_button->getBoundingBox().size.height * 0.5f -
                                         getContainer()->getContentSize().height * 0.05f));
    
    _gem_knife_button->setVoidTouchDownCallback([this]{
        unlock_random_weapon();
    });

    {
        
        Sprite * _content = _gem_knife_button->getContentSprite();
        
        Label *_price_label = Label::createWithTTF("200", "fonts/Blogger_Sans-Bold.otf",
                                                   _content->getContentSize().height * 0.28f);
        _price_label->setPosition(_content->getContentSize().width * 0.84f,
                                  _content->getContentSize().height * 0.265f);
        _price_label->setColor(Color3B::BLACK);
        _price_label->setOpacity(255);
        _price_label->setTag(111);
        _price_label->setAlignment(TextHAlignment::CENTER);
        _price_label->setAnchorPoint(Vec2(0.5f, 0.5f));
        _content->addChild(_price_label);
        _price_label->setString(StringUtils::format("%i",Shop::getItemPrice(SHOP_PAGE_TYPE_KNIVES_GEM_PAGE_1)).c_str());
        
    }

    
    _video_button = SPButton::createWithImage("shop/+50.png");
    addChild(_video_button);
    _video_button->setScale(getContainer()->getContentSize().height * 0.078f / _video_button->getContentSize().height);
    _video_button->setPosition(Vec2(_collectionView->getPositionX(), _coin_knife_button->getPositionY()));
    _video_button->setVoidTouchDownCallback([this]{
        if (_video_button_callback) {
            _video_button_callback();
        }
    });
    
    {
        Sprite * _content = _video_button->getContentSprite();
        
        Label *_price_label = Label::createWithTTF("+20", "fonts/Blogger_Sans-Bold.otf",
                                                   _content->getContentSize().height * 0.42f);
        _price_label->setPosition(_content->getContentSize().width*0.51f,
                                  _content->getContentSize().height*0.44f);
        _price_label->setColor(Color3B::BLACK);
        _price_label->setAlignment(TextHAlignment::CENTER);
        _price_label->setAnchorPoint(Vec2(0.5f, 0.5f));
        _content->addChild(_price_label);
        _price_label->setString(StringUtils::format("+%i",k_VIDEO_REWARD_SHOP).c_str());
    }
    
    
    _fortune_page_info = Sprite::create("shop/spin.png");
    _fortune_page_info->setScale(getContainer()->getContentSize().height * 0.06f / _fortune_page_info->getContentSize().height);
    _fortune_page_info->setPosition(Point(getContentSize().width * 0.5f, _coin_knife_button->getPositionY()));
    addChild(_fortune_page_info);
    
    
    refresh_video_reward_button();
    
    Game::align_x_side_by_side(_coin_knife_button, _video_button, getContainer()->getContentSize().width * 0.02f);
    
    _page_name_label = Label::createWithTTF("CASUAL KNIVES", "fonts/Blogger_Sans-Bold.otf", getContainer()->getContentSize().height * 0.025f);
    _page_name_label->setPosition(getContentSize().width * 0.5f,  _collectionView->getPositionY() + _collectionView->getContentSize().height * 0.5f + getContainer()->getContentSize().height * 0.025f);
    _page_name_label->setColor(Color3B(85, 160, 157));
    // _page_name_label->setVisible(false);
    addChild(_page_name_label);
    
    refresh_bottom(_category_by_gun, false);
    
    _item_preview = ShopItemPreview::create();
    addChild(_item_preview);
//    _item_preview->setTextureRect(Rect(0, 0, getContainer()->getContentSize().width * 0.8f, getContainer()->getContentSize().height * 0.18f));
//    _item_preview->setColor(Color3B::RED);
    _item_preview->setContentSize(Size(getContainer()->getContentSize().width * 0.8f, getContainer()->getContentSize().height * 0.18f));
    _item_preview->setPosition(Point(getContentSize().width * 0.5f, (getContentSize().height * 0.5f) + getContainer()->getContentSize().height * 0.37f));
    _item_preview->setItem(ShopManager::getInstance()->get_item_selected(), false);
    
    
    gradient_blick->setPosition(_item_preview->getPosition());
    
    return true;
}

bool ShopLayer::unlock_random_weapon(){
    
    
    std::vector<SHOP_ITEM>items_locked = ShopManager::getInstance()->get_items_locked();
    std::vector<SHOP_ITEM>items_locked_final;
    std::vector<SHOP_ITEM>coins_guns   = Shop::get_knives(SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_1);
    
    if (_prev_bottom_items_category == SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_2) {
        coins_guns   = Shop::get_knives(SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_2);
    }
    else if (_prev_bottom_items_category == SHOP_PAGE_TYPE_KNIVES_GEM_PAGE_1) {
        coins_guns   = Shop::get_knives(SHOP_PAGE_TYPE_KNIVES_GEM_PAGE_1);
    }
    
    int items_purchased_size    = 0;
    
    for (int i = 0; i < coins_guns.size(); i++) {
        
        SHOP_ITEM _coins_gun = coins_guns.at(i);
        
        if (ShopManager::getInstance()->is_item_purchased(_coins_gun) == false) {
            items_locked_final.push_back(_coins_gun);
        }
        else{
            items_purchased_size++;
        }
        
    }
    
    int coins = Game::getCoins();
    
    std::string info_text = "NOT ENOUGH COINS";
    Vec2 world_pos = _coin_knife_button->getParent()->convertToWorldSpace(_coin_knife_button->getPosition());
    world_pos.y+= _coin_knife_button->getBoundingBox().size.height*0.5f;
    
    if (_prev_bottom_items_category == SHOP_PAGE_TYPE_KNIVES_GEM_PAGE_1) {
        coins = Game::getGems();
        info_text = "NOT ENOUGH GEMS";
        
        world_pos = _gem_knife_button->getParent()->convertToWorldSpace(_gem_knife_button->getPosition());
        world_pos.y+= _gem_knife_button->getBoundingBox().size.height*0.5f;
    }
    
    
    if (items_locked_final.size() == 0) {
        
        Game::getInstance()->show_text_label_info(world_pos, "ALL UNLOCKED");
        
        return false;
    }
    
    int price = Shop::getItemPrice(_prev_bottom_items_category);
    
    if (coins < price) {
        
        Game::getInstance()->show_text_label_info(world_pos, info_text.c_str());
        
        return false;
    }
    
    

    
    //
    
    int index      = random(0, (int)items_locked_final.size()-1);
    SHOP_ITEM item = items_locked_final.at(index);
    
    std::vector<SHOP_ITEM> locked_items = ShopManager::getInstance()->get_items_locked();
    
    if (coins >= price && locked_items.size() > 0) {
        
        is_now_runnig_random_unlock = true;
        
        
        
        ShopLayerCell * cell_now = (ShopLayerCell *)_collectionView->getPageNow();
        
        std::vector<ShopLayerCellItem *> all_items = cell_now->_all_items;
        std::vector<ShopLayerCellItem *> items;
        
        for (int i = 0; i < all_items.size(); i++) {
            ShopLayerCellItem * cell_item = all_items.at(i);
            
            cell_item->setSelected(false);
            cell_item->updateContent();
            
            for (int j = 0; j < locked_items.size(); j++) {
                SHOP_ITEM _shop_item = locked_items.at(j);
                if (cell_item->_item._id == _shop_item) {
                    items.push_back(cell_item);
                    break;
                }
            }
        }
        
        int seed = (int)std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(items.begin(), items.end(), std::default_random_engine(seed));
        
        ShopLayerCellItem * winner_cell = nullptr;
        
        for (int i = 0; i < items.size(); i++) {
            ShopLayerCellItem * cell_item = items.at(i);
            if (cell_item->_item._id == item) {
                winner_cell = cell_item;
                break;
            }
        }
        
        bool must_add_last_item = true;
        
        if (items.size() == 1) {
            must_add_last_item = false;
        }
        
        
        int items_limit = 20;
        
        if (items.size() < items_limit && items.size() > 1) {
            
            for (int i = 0; i < items_limit; i++) {
                items.push_back(items.at(i));
                
                if (items.size() >= items_limit) {
                    break;
                }
            }
        }
        
        if (winner_cell && must_add_last_item) {
            items.push_back(winner_cell);
        }
        
        if (winner_cell == nullptr) {
            return false;
        }
        
        if (_prev_bottom_items_category == SHOP_PAGE_TYPE_KNIVES_GEM_PAGE_1) {
            Game::addGems(-price);
        }
        else{
            Game::addCoins(-price);
        }
        
        
        
        if (_refresh_coins) {
            _refresh_coins();
        }
        
        Director::getInstance()->getEventDispatcher()->setEnabled(false);
        
        ShopManager::getInstance()->set_item_purchase(winner_cell->_item._id);
        
        refresh_coin_button_animation();
        refresh_gem_button_animation();
        
        float delay_value = 0.1f;
        
        auto get_rewarder_cell = [this](ShopLayerCellItem * cell_item, SPCollectionView * _collection_view){
            
            for (int x = 0; x < _collection_view->getInteligentSprites().size(); x++) {
                ShopLayerCellItem * list_cell = (ShopLayerCellItem*)_collection_view->getInteligentSprites().at(x);
                if (list_cell->isSelected()) {
                    list_cell->setSelected(false);
                    list_cell->updateContent();
                }
            }
            
            cell_item->setIsPurchased(true);
            cell_item->setSelected(true);
            cell_item->updateContent();
            cell_item->setSelected(true, true, NULL);
            
            
            _item_preview->setItem(cell_item->_item._id, true);
            
            ShopManager::getInstance()->set_item_selected(cell_item->_item._id);
            
            SoundDirector::playSound("shop/ev_shop_unlock");
            
            if (_refresh_weapon_callback) {
                _refresh_weapon_callback();
            }
            
            
            auto tint  = TintTo::create(0.1f, Shop::getPageColor(_prev_bottom_items_category, true));
            auto ease  = EaseInOut::create(tint, 2.2f);
            auto tint1 = TintTo::create(0.1f, 255,234,55);
            auto ease2 = EaseInOut::create(tint1, 2.2f);
            auto seq   = Sequence::create(ease, ease2, NULL);
            auto repaet = Repeat::create(seq, 5);
            cell_item->_selected_frame->runAction(repaet);
            
            {
                auto tint  = TintTo::create(0.1f, Shop::getPageColor(_prev_bottom_items_category, true));
                auto ease  = EaseInOut::create(tint, 2.2f);
                auto tint1 = TintTo::create(0.1f, 255,255,255);
                auto ease2 = EaseInOut::create(tint1, 2.2f);
                auto seq   = Sequence::create(ease, ease2, NULL);
                auto repaet = Repeat::create(seq, 5);
                cell_item->_content->runAction(repaet);
            }
            
            //SoundDirector::playSound("ev_shop_bought");
            
            if (Settings::getStateOn(settings_vibration)) {
                PlatformManager::vibrate(2);
            }
            
            
            is_now_runnig_random_unlock = false;
            
            Director::getInstance()->getEventDispatcher()->setEnabled(true);
        };
        
        if (items.size() == 1) {
            get_rewarder_cell(winner_cell, _collectionView);
        }
        else{
            
            for (int i = 0; i < items.size(); i++) {
                ShopLayerCellItem * cell_item = items.at(i);
                
                bool must_opened = false;
                
                if (i == items.size() - 1) {
                    must_opened = true;
                }
                
                float scale_ = cell_item->_content->getScale();
                
                auto delay   = DelayTime::create(delay_value * i);
                auto scale   = ScaleTo::create(0.15f, scale_ * 1.1f);
                auto spawn   = Spawn::create(scale, NULL);
                auto ease    = EaseOut::create(spawn, 2.2f);
                auto scale2  = ScaleTo::create(0.1f, scale_);
                auto spawn2  = Spawn::create(scale2, NULL);
                auto ease2   = EaseIn::create(spawn2, 2.2f);
                auto sound   = CallFunc::create([this]{
                    
                    if (Settings::getStateOn(settings_vibration)) {
                        PlatformManager::vibrate(1);
                    }
                    
                     SoundDirector::playSound("shop/ev_shop_random");
                    
                });
                auto reset   = CallFunc::create([this, cell_item, scale_]{
                    
                    if (cell_item->_content->getActionByTag(333)) {
                        cell_item->_content->stopActionByTag(333);
                    }
                    if (cell_item->_content->getActionByTag(444)) {
                        cell_item->_content->stopActionByTag(444);
                    }
                    
                    cell_item->_content->setScale(scale_);
                });
                auto callf   = CallFunc::create([this, must_opened, cell_item, get_rewarder_cell]{
                    if (must_opened) {
                        get_rewarder_cell(cell_item, _collectionView);
                    }
                });
                auto seq1    = Sequence::create(sound, ease, ease2, callf, NULL);
                seq1->setTag(444);
                auto seq     = Sequence::create(delay, seq1, NULL);
                cell_item->_content->runAction(seq);
                
                
                auto tint     = FadeTo::create(0.1f, 100);
                auto ease3    = EaseOut::create(tint, 2.2f);
                auto tint1    = FadeTo::create(0.05f, 255);
                auto ease4    = EaseIn::create(tint1, 2.2f);
                auto seq3     = Sequence::create(ease3, ease4, NULL);
                seq3->setTag(333);
                auto seq4     = Sequence::create(reset, seq3, NULL);
                auto seq44    = Sequence::create(delay, seq4, NULL);
                cell_item->_content->runAction(seq44);
                
                delay_value += 0.005f;
                if (delay_value > 0.8f) {
                    delay_value = 0.8f;
                }
            }
        }
        return true;
    }
    return false;
}

void ShopLayer::refresh_bottom(SHOP_PAGE_TYPE _category, bool animated){
    
    SHOP_PAGE_TYPE _category_prev = _prev_bottom_items_category;
    _prev_bottom_items_category = _category;
    
    if (_category_prev != _category || animated == false) {
        
        if (animated) {
            
            _coin_knife_button->setVisible(false);
            _gem_knife_button->setVisible(false);
            _video_button->setVisible(false);
            _fortune_page_info->setVisible(false);
            
            
            
            if (_category == SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_1 || _category == SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_2) {
                
                _coin_knife_button->setVisible(true);
                _video_button->setVisible(true);
                
                bool animate = true;
                
                if ((_category == SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_1 && _category_prev == SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_2) ||
                    (_category == SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_2 && _category_prev == SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_1)) {
                    animate = false;
                    
                    refresh_coin_button_animation();
                }
                
                if (animate) {
                    
                    if (_coin_knife_button->getActionByTag(44)) {
                        _coin_knife_button->stopActionByTag(44);
                    }
                    
                    if (_video_button->getActionByTag(44)) {
                        _video_button->stopActionByTag(44);
                    }
                    
                    _coin_knife_button->setScale(getContainer()->getContentSize().height * 0.02f / _coin_knife_button->getContentSize().height);
                    _video_button->setScale(getContainer()->getContentSize().height * 0.02f / _video_button->getContentSize().height);
                    
                    auto scale1 = ScaleTo::create(0.1f, getContainer()->getContentSize().height * 0.078f / _coin_knife_button->getContentSize().height);
                    auto ease1  = EaseOut::create(scale1, 2.6f);
                    ease1->setTag(44);
                    _coin_knife_button->runAction(ease1);
                    
                    auto scale2 = ScaleTo::create(0.1f, getContainer()->getContentSize().height * 0.078f / _video_button->getContentSize().height);
                    auto ease2  = EaseOut::create(scale2, 2.6f);
                    ease2->setTag(44);
                    _video_button->runAction(ease2);
                    
                    refresh_coin_button_animation();
                    
                    //                if (_category_prev == SHOP_PAGE_TYPE_BLACKLIST_GUNS_PAGE_1) {
                    //
                    //                    if (_estoty_social_layer) {
                    //                        _estoty_social_layer->stopAllActions();
                    //                        auto scale1 = ScaleTo::create(0.1f, 0);
                    //                        auto ease1  = EaseOut::create(scale1, 2.6f);
                    //                        _estoty_social_layer->runAction(ease1);
                    //
                    //
                    //                        for (SPButton * button : _social_buttons) {
                    //                            button->setActive(false);
                    //                        }
                    //                    }
                    //                }
                    
                    
                    if (_page_name_label->getActionByTag(44)) {
                        _page_name_label->stopActionByTag(44);
                    }
                    
                    
                    _page_name_label->setScale(0);
                    
                    Color3B tint_color = Shop::getPageColor(_category, true);
                    
                    auto tint   = TintTo::create(0.2f, tint_color);
                    auto scale  = ScaleTo::create(0.2f, 1.0f);
                    auto spawn  = Spawn::create(tint, scale, NULL);
                    auto ease3  = EaseOut::create(spawn, 2.6f);
                    ease3->setTag(44);
                    _page_name_label->runAction(ease3);
                    
                    _page_name_label->setString(Shop::get_page_name(_category));
                }
                
                
                
                Label * price_label = (Label *) _coin_knife_button->getContentSprite()->getChildByTag(111);
                
                int price = Shop::getItemPrice(_category);
                
                if (price_label) {
                    price_label->setString(StringUtils::format("%i", price));
                }
            }
            else if(_category == SHOP_PAGE_TYPE_KNIVES_GEM_PAGE_1){
                
                _gem_knife_button->setVisible(true);
                
                if (_gem_knife_button->getActionByTag(44)) {
                    _gem_knife_button->stopActionByTag(44);
                }
                
                _gem_knife_button->setScale(getContainer()->getContentSize().height * 0.02f / _gem_knife_button->getContentSize().height);
                
                auto scale1 = ScaleTo::create(0.1f, getContainer()->getContentSize().height * 0.078f / _gem_knife_button->getContentSize().height);
                auto ease1  = EaseOut::create(scale1, 2.6f);
                ease1->setTag(44);
                _gem_knife_button->runAction(ease1);
                
          
                
                refresh_gem_button_animation();
                
                //                if (_category_prev == SHOP_PAGE_TYPE_BLACKLIST_GUNS_PAGE_1) {
                //
                //                    if (_estoty_social_layer) {
                //                        _estoty_social_layer->stopAllActions();
                //                        auto scale1 = ScaleTo::create(0.1f, 0);
                //                        auto ease1  = EaseOut::create(scale1, 2.6f);
                //                        _estoty_social_layer->runAction(ease1);
                //
                //
                //                        for (SPButton * button : _social_buttons) {
                //                            button->setActive(false);
                //                        }
                //                    }
                //                }
                
                Label * price_label = (Label *) _gem_knife_button->getContentSprite()->getChildByTag(111);
                
                int price = Shop::getItemPrice(_category);
                
                if (price_label) {
                    price_label->setString(StringUtils::format("%i", price));
                }
                
                
                if (_page_name_label->getActionByTag(44)) {
                    _page_name_label->stopActionByTag(44);
                }
                
                
                _page_name_label->setScale(0);
                
                Color3B tint_color = Shop::getPageColor(_category, true);
                
                auto tint   = TintTo::create(0.2f, tint_color);
                auto scale  = ScaleTo::create(0.2f, 1.0f);
                auto spawn  = Spawn::create(tint, scale, NULL);
                auto ease3  = EaseOut::create(spawn, 2.6f);
                ease3->setTag(44);
                _page_name_label->runAction(ease3);
                
                _page_name_label->setString(Shop::get_page_name(_category));
            }
            else if (_category == SHOP_PAGE_TYPE_KNIVES_FORTUNE_WHLLE_PAGE_1){
                
                if (_page_name_label->getActionByTag(44)) {
                    _page_name_label->stopActionByTag(44);
                }
                
                
                _page_name_label->setScale(0);
                
                Color3B tint_color = Shop::getPageColor(_category, true);
                
                auto tint   = TintTo::create(0.2f, tint_color);
                auto scale  = ScaleTo::create(0.2f, 1.0f);
                auto spawn  = Spawn::create(tint, scale, NULL);
                auto ease3  = EaseOut::create(spawn, 2.6f);
                ease3->setTag(44);
                _page_name_label->runAction(ease3);
                
                _page_name_label->setString(Shop::get_page_name(_category));
                
                
                {
                    
                    _fortune_page_info->setVisible(true);
                    _fortune_page_info->setScale(0);
                    
                    if (_fortune_page_info->getActionByTag(44)) {
                        _fortune_page_info->stopActionByTag(44);
                    }
                    
                    auto scale = ScaleTo::create(0.2f, getContainer()->getContentSize().height * 0.06f / _fortune_page_info->getContentSize().height);
                    auto ease3  = EaseOut::create(scale, 2.6f);
                    ease3->setTag(44);
                    _fortune_page_info->runAction(ease3);
                }
            }
        }
        else{

            _gem_knife_button->setVisible(false);
            _coin_knife_button->setVisible(false);
            _video_button->setVisible(false);
            _fortune_page_info->setVisible(false);
           
            _page_name_label->setColor(Shop::getPageColor(_category, true));
            _page_name_label->setString(Shop::get_page_name(_category));
            
            
            if (_category == SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_1 || _category == SHOP_PAGE_TYPE_KNIVES_COINS_PAGE_2) {
                
                _coin_knife_button->setVisible(true);
                _video_button->setVisible(true);
        
                refresh_coin_button_animation();
                
//                if (_estoty_social_layer) {
//                    _estoty_social_layer->stopAllActions();
//
//                    _estoty_social_layer->setScale(0);
//
//
//                    for (SPButton * button : _social_buttons) {
//                        button->setActive(false);
//                    }
//                }
                
                Label * price_label = (Label *) _coin_knife_button->getContentSprite()->getChildByTag(111);
                
                int price = Shop::getItemPrice(_category);
                
                if (price_label) {
                    price_label->setString(StringUtils::format("%i", price));
                }
                
            }
            else if(_category == SHOP_PAGE_TYPE_KNIVES_GEM_PAGE_1){
                
                _gem_knife_button->setVisible(true);
                
                refresh_gem_button_animation();
                
                Label * price_label = (Label *) _gem_knife_button->getContentSprite()->getChildByTag(111);
                
                int price = Shop::getItemPrice(_category);
                
                if (price_label) {
                    price_label->setString(StringUtils::format("%i", price));
                }
            }
            else if(_category == SHOP_PAGE_TYPE_KNIVES_FORTUNE_WHLLE_PAGE_1){
                
                _fortune_page_info->stopAllActions();
                _fortune_page_info->setVisible(true);
                _fortune_page_info->setScale(getContainer()->getContentSize().height * 0.06f / _fortune_page_info->getContentSize().height);
            }
        }
    }
}

ShopLayerCell * ShopLayer::get_cell_by_type(SHOP_PAGE_TYPE _category){
    
    for (int i = 0; i < _collectionView->getCells().size(); i++) {
        
        ShopLayerCell * cell = (ShopLayerCell *)_collectionView->getCells().at(i);
        if (cell->_shop_category == _category) {
            return cell;
        }
        
    }
    return nullptr;
}

void ShopLayer::update_video_button(float dt){
    
    refresh_video_reward_button();
    
}

void ShopLayer::refresh_video_reward_button(int force_state){
    
    if (_video_button == nullptr) {
        return;
    }
    
    bool video_available = AdManager::getInstance()->is_available_VideoAd();
    
    if ((video_available && force_state == -1) || force_state == 1) {
        _video_button->setActive(true);
        _video_button->getContentSprite()->setOpacity(255);
    }
    else if((video_available == false && force_state == -1 )|| force_state == 0){
        _video_button->setActive(false);
       // _video_button->getContentSprite()->setOpacity(100);
    }
}

void ShopLayer::refresh_coin_button_animation(){
    
    bool animate = can_buy_new_gun(_prev_bottom_items_category);
    

    float scale_normal = getContainer()->getContentSize().height * 0.078f / _coin_knife_button->getContentSize().height;
    
    if (animate) {
        
        if (_coin_knife_button->getActionByTag(1) == nullptr) {
            
            auto a_bar_scale     = ScaleTo::create(0.35f, scale_normal*1.1f);
            auto a_bar_scale_2   = ScaleTo::create(0.35f, scale_normal);
            auto a_bar_scale_seq = Sequence::create(a_bar_scale,a_bar_scale_2, NULL);
            auto a_bar_scale_rep = RepeatForever::create(EaseInOut::create(a_bar_scale_seq, 2.3f));
            a_bar_scale_rep->setTag(1);
            _coin_knife_button->runAction(a_bar_scale_rep);
            
        }
        
        _coin_knife_button->getContentSprite()->setOpacity(255);
    }
    else{
        
        if (_coin_knife_button->getActionByTag(1)) {
            _coin_knife_button->stopActionByTag(1);
            _coin_knife_button->setScale(scale_normal);
        }
        
        //_coin_knife_button->getContentSprite()->setOpacity(100);
    }
}

void ShopLayer::refresh_gem_button_animation(){
    
    bool animate = can_buy_new_gun(SHOP_PAGE_TYPE_KNIVES_GEM_PAGE_1);
    
    float scale_normal = getContainer()->getContentSize().height * 0.078f / _gem_knife_button->getContentSize().height;
    
    if (animate) {
        
        if (_gem_knife_button->getActionByTag(1) == nullptr) {
            
            auto a_bar_scale     = ScaleTo::create(0.35f, scale_normal*1.1f);
            auto a_bar_scale_2   = ScaleTo::create(0.35f, scale_normal);
            auto a_bar_scale_seq = Sequence::create(a_bar_scale,a_bar_scale_2, NULL);
            auto a_bar_scale_rep = RepeatForever::create(EaseInOut::create(a_bar_scale_seq, 2.3f));
            a_bar_scale_rep->setTag(1);
            _gem_knife_button->runAction(a_bar_scale_rep);
            
        }
        
        _gem_knife_button->getContentSprite()->setOpacity(255);
    }
    else{
        
        if (_gem_knife_button->getActionByTag(1)) {
            _gem_knife_button->stopActionByTag(1);
            _gem_knife_button->setScale(scale_normal);
        }
        
       // _gem_knife_button->getContentSprite()->setOpacity(100);
    }
}

bool ShopLayer::can_buy_new_gun(SHOP_PAGE_TYPE page){
    
    std::vector<SHOP_ITEM>items_locked = ShopManager::getInstance()->get_items_locked();
    std::vector<SHOP_ITEM>items_locked_final;
    
    std::vector<SHOP_ITEM>coins_guns = Shop::get_knives(page);
    
    for (int i = 0; i < coins_guns.size(); i++) {
        
        SHOP_ITEM _coins_gun = coins_guns.at(i);
        
        for (int j = 0; j < items_locked.size(); j++) {
            SHOP_ITEM _locked_gun = items_locked.at(j);
            if (_coins_gun == _locked_gun) {
                items_locked_final.push_back(_locked_gun);
                break;
            }
        }
    }
    
    int coins = Game::getCoins();
    
    if (page == SHOP_PAGE_TYPE_KNIVES_GEM_PAGE_1) {
        coins = Game::getGems();
    }
    
    int price = Shop::getItemPrice(page);
    
    if (coins >= price) {
        if (items_locked_final.size() > 0) {
              return true;
        }
    }
    return false;
}

bool ShopLayer::onTouchBegan(Touch *touch, Event *event){
    if (is_deleting) {
        return true;
    }
    
    if (_collectionView) {
        if (touch->getLocation().y > _collectionView->getPosition().y + _collectionView->getContentSize().height*0.55f) {
            if (getBackButton()->voidTouchDownCallback) {
                is_deleting = true;
                auto d = DelayTime::create(0.1f);
                auto call = CallFunc::create([this]{
//                    if (_did_touch_player_shop) {
//                        _did_touch_player_shop();
//                    }
                    if (_double_selected_item) {
                        _double_selected_item();
                    }
                });
                auto seq = Sequence::create(d,call, NULL);
                runAction(seq);
            }
        }
    }
    
    return true;
}

#pragma mark
#pragma mark SPInteligentSpritesDelegate

bool ShopLayer::inteligentSpriteEnableTouch(SPCollectionView *collectionView, Sprite *sprite, SPCollectionViewCell *cell) {
    return true;
}

void ShopLayer::inteligentSpriteStateOnFocus(SPCollectionView *collectionView, Sprite *sprite, SPCollectionViewCell *cell) {
    sprite->setScale(0.925f);
}

void ShopLayer::inteligentSpriteStateLooseFocus(SPCollectionView *collectionView, Sprite *sprite, SPCollectionViewCell *cell) {
     sprite->setScale(1.0f);
}

void ShopLayer::inteligentSpriteStateOnDidSelect(SPCollectionView *collectionView, Sprite *sprite, SPCollectionViewCell *cell) {
    
    ShopLayerCellItem * cell_item = (ShopLayerCellItem *)sprite;
    
    if (cell_item) {
        
        SHOP_ITEM item = cell_item->_item._id;
        
        if (cell_item->_selected == false && cell_item->_purchased) {
            
            for (int x = 0; x < collectionView->getInteligentSprites().size(); x++) {
                ShopLayerCellItem * list_cell = (ShopLayerCellItem*)collectionView->getInteligentSprites().at(x);
                if (list_cell->isSelected()) {
                    list_cell->setSelected(false);
                    list_cell->updateContent();
                }
            }
            
            if (cell_item->_purchased) {
                ShopManager::getInstance()->set_item_selected(item);
                
                SoundDirector::playSound("shop/ev_shop_select");
                
                if (_refresh_weapon_callback) {
                    _refresh_weapon_callback();
                }
            
                if (Settings::getStateOn(settings_vibration)) {
                    PlatformManager::vibrate(1);
                }
            }
            
            cell_item->setSelected(true);
            cell_item->updateContent();
            cell_item->setSelected(true, true, NULL);
            
            if (_item_preview) {
                _item_preview->setItem(cell_item->_item._id, true);
            }
            
        }
        else if (cell_item->_purchased == false){
            
             SoundDirector::playSound("shop/ev_shop_select_negative");
            
        }
        else if (cell_item->_purchased && cell_item->_selected){
            if (_double_selected_item) {
                SoundDirector::playSound("ev_shop_select");
                _double_selected_item();
            }
        }
    }
}

#pragma mark
#pragma mark SPCollectionViewDelegate

void ShopLayer::didPageStop(SPCollectionView *collectionView, SPCollectionViewCell *cell, int item){

}

void ShopLayer::willPageStop(SPCollectionView *collectionView, SPCollectionViewCell *cell, int item){
    
    if (_page_control == NULL) {
        return;
    }
    
    _page_control->setActiveDot(item, true);
    refresh_bottom(((ShopLayerCell *)cell)->_shop_category, true);
    
    if (Settings::getStateOn(settings_vibration)) {
        PlatformManager::vibrate(1);
    }
    
}

Sprite * ShopLayer::getSectionBefore(SPCollectionView *collectionView,int section){
    
    if (section > 0) {
        Sprite * separator = Sprite::create();
        separator->setTextureRect(Rect(0, 0, getContainer()->getContentSize().width * 0.05f, collectionView->getContentSize().height));
        separator->setOpacity(0);
        return separator;
    }
    
    return nullptr;
}

float ShopLayer::getSeperatorAfter(SPCollectionView *collectionView,int section) {
    return 0;
}

float ShopLayer::getSeperatorBefore(SPCollectionView *collectionView,int section) {
    return 0;
}

void ShopLayer::didSelectCell                  (SPCollectionView *collectionView,SPCollectionViewCell *cell){
    
}

int ShopLayer::getNumberOfSections             (SPCollectionView *colectionView){
    return (int)_all_pages.size();
}

std::vector<CellItem> ShopLayer::get_items(SHOP_PAGE_TYPE page){
    std::vector<CellItem> items;
    
    for (SHOP_ITEM _item : Shop::get_knives(page)) {
        
        CellItem cell_item;
        
        ShopItem it;
        it._id      = _item;
        it._imgPath = Shop::get_knife_image(_item);
        
        cell_item._item      = it;
        cell_item._purchased = ShopManager::getInstance()->is_item_purchased(_item);
        cell_item._selected  = _item == ShopManager::getInstance()->get_item_selected();
        
        items.push_back(cell_item);
    }
    
    return items;
}

int ShopLayer::getNumberOfItems                (SPCollectionView *colectionView,int section){
    return 1;
}

Size ShopLayer::getCellSize                    (SPCollectionView *colectionView,int section,int item){
    Size s = Size(colectionView->getContentSize().width, colectionView->getContentSize().height);
    return s;
    
}

SPCollectionViewCell * ShopLayer::getCellItem                     (SPCollectionView *colectionView,int section,int item){

    ShopLayerCell *cell = (ShopLayerCell *)colectionView->dequeCellItem(section, item);
    
    if (!cell) {
        cell = ShopLayerCell::create();
        cell->items_count = Vec2(4, 4);
        colectionView->addCell(cell, section, item);
    }

    cell->_shop_category = _all_pages.at(section);
    
    std::vector<CellItem>items    = get_items(cell->_shop_category);
    cell->items                   = items;
    cell->_collection_view        = colectionView;

    return cell;
}

