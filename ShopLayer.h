//
//  ShopLayer.hpp
//  HotDog-mobile
//
//  Created by Marek on 7/16/17.
//

#ifndef ShopLayer_h
#define ShopLayer_h

#include "GameLayer.h"
#include "Shop.h"
#include "SPCollectionView.h"
#include "ShopLayerCell.h"
#include "SPPageControl.h"
#include "Game.h"
#include "ShopItemPreview.h"

USING_NS_CC;

enum reward_info_type{
    
    reward_info_type_daily = 0,
    reward_info_type_blacklist = 1
    
};

class ShopLayer : public GameLayer,
public SPCollectionViewDelegate,
public SPInteligentSpritesDelegate

{
    
public:
    CREATE_FUNC(ShopLayer);
    
     ShopLayer(){}
    ~ShopLayer(){}
    
    virtual bool init() override;
    
    SPCollectionView    * _collectionView          = nullptr;
    SPPageControl       * _page_control            = nullptr;
    SPButton            * _coin_knife_button       = nullptr;
    SPButton            * _gem_knife_button        = nullptr;
    SPButton            * _video_button            = nullptr;
    ShopItemPreview     * _item_preview            = nullptr;
    Label               * _page_name_label         = nullptr;
    Sprite              * _fortune_page_info       = nullptr;
    
    
    std::function<void()> _double_selected_item     = nullptr;
    std::function<void()> _refresh_coins            = nullptr;
    std::function<void()> _video_button_callback    = nullptr;
    std::function<void()> _refresh_weapon_callback  = nullptr;
    
    ShopLayerCell * get_cell_by_type(SHOP_PAGE_TYPE _category);
    
    SHOP_PAGE_TYPE _prev_bottom_items_category = SHOP_PAGE_TYPE_UNKNOWN;
    
    void refresh_bottom(SHOP_PAGE_TYPE _category, bool animated);

    std::vector<SHOP_PAGE_TYPE> _all_pages;
    std::vector<SPButton *> _social_buttons;
    
    void update_video_button(float dt);
    void refresh_video_reward_button(int force_state = -1 );
    void refresh_coin_button_animation();
    void refresh_gem_button_animation();
    
    bool is_now_runnig_random_unlock = false;
    bool is_deleting = false;
    
    bool can_buy_new_gun(SHOP_PAGE_TYPE page);
    
    bool unlock_random_weapon();
    
    virtual bool onTouchBegan(Touch *touch, Event *event)      override;
    
private:
    
    std::vector<CellItem> get_items(SHOP_PAGE_TYPE page);
    
    // SPCollectionViewDelegate
    
    virtual int                     getNumberOfSections             (SPCollectionView *colectionView) override;
    virtual int                     getNumberOfItems                (SPCollectionView *colectionView,int section) override;
    virtual Size                    getCellSize                     (SPCollectionView *colectionView,int section,int item) override;
    virtual SPCollectionViewCell*   getCellItem                     (SPCollectionView *colectionView,int section,int item) override;
    virtual void                    didSelectCell                   (SPCollectionView *collectionView,SPCollectionViewCell *cell) override;
    virtual float                   getSeperatorAfter               (SPCollectionView *collectionView,int section) override;
    virtual float                   getSeperatorBefore              (SPCollectionView *collectionView,int section) override;
    virtual Sprite *                getSectionBefore                (SPCollectionView *collectionView,int section) override;
    
    virtual void                    didPageStop                     (SPCollectionView *collectionView, SPCollectionViewCell *cell, int item) override;
    virtual void                    willPageStop                    (SPCollectionView *collectionView, SPCollectionViewCell *cell, int item) override;
    
    // SPInteligentSpritesDelegate
    
    virtual bool inteligentSpriteEnableTouch        (SPCollectionView *collectionView, Sprite *sprite, SPCollectionViewCell *cell) override;
    virtual void inteligentSpriteStateOnFocus       (SPCollectionView *collectionView, Sprite *sprite, SPCollectionViewCell *cell) override;
    virtual void inteligentSpriteStateLooseFocus    (SPCollectionView *collectionView, Sprite *sprite, SPCollectionViewCell *cell) override;
    virtual void inteligentSpriteStateOnDidSelect   (SPCollectionView *collectionView, Sprite *sprite, SPCollectionViewCell *cell) override;
};

#endif /* ShopLayer_hpp */
