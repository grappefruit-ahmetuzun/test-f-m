//
//  ShopDataModel.hpp
//  SummerGames
//
//  Created by Marek on 18/07/16.
//
//

#ifndef ShopDataModel_hpp
#define ShopDataModel_hpp

#include "SPFileModel.h"
#include "Shop.h"

class ShopDataModel : public SPFileModel{
public:
    
    ShopDataModel()
    {};
    ShopDataModel(std::string fileName);
    virtual ~ShopDataModel(){};
    
    virtual void    preload() override;
    
    void    purchase        (SHOP_ITEM item);
    bool    isPurchased     (SHOP_ITEM item);
    
    void    set_as_not_new  (SHOP_ITEM item);
    bool    is_not_new      (SHOP_ITEM item);
    
    std::vector<SHOP_ITEM>get_items();
    
private:
    
};


#endif /* ShopDataModel_hpp */
