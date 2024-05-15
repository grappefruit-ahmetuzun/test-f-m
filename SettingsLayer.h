//
//  SettingsLayer.hpp
//  BasketDunk
//
//  Created by Marek on 23/10/2017.
//
//

#ifndef SettingsLayer_hpp
#define SettingsLayer_hpp

#include "GameLayer.h"
#include "Space.h"
#include "SPButton.h"
#include "SettingsCell.h"
#include "Settings.h"
#include "SPCollectionView.h"

USING_NS_CC;


class SettingsLayer : public GameLayer,public SPCollectionViewDelegate{
    
public:
    CREATE_FUNC(SettingsLayer);
    
    SettingsLayer()
    {}
    ~SettingsLayer(){}
    
    void refresh_noads_buttons();
    
    SPButton * noads_button                           = nullptr;
    SPButton * restore_button                         = nullptr;
    SPButton * gdpr_button                            = nullptr;
    
    CC_SYNTHESIZE(SettingsDelegate *, _delegate, Delegate)
    
    //
    
    SPCollectionView        * _list_chars           = nullptr;
    
    // SPCollectionViewDelegate
    
    virtual int                     getNumberOfSections             (SPCollectionView *colectionView) override;
    virtual int                     getNumberOfItems                (SPCollectionView *colectionView,int section) override;
    virtual Size                    getCellSize                     (SPCollectionView *colectionView,int section,int item) override;
    virtual SPCollectionViewCell*   getCellItem                     (SPCollectionView *colectionView,int section,int item) override;
    virtual void                    didSelectCell                   (SPCollectionView *collectionView,SPCollectionViewCell *cell) override;
    virtual float                   getSeperatorAfter               (SPCollectionView *collectionView,int section) override;
    virtual float                   getSeperatorBefore              (SPCollectionView *collectionView,int section) override;
    
    //
    
    std::function<void(int, float, Vec2)> _coins_give_callback = nullptr;

    void animateOnEnter(bool show_estoty_social);
    
    
public:

    
};

#endif /* SettingsLayer_hpp */
