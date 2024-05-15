//
//  Patterns.hpp
//  FruitsKnife-mobile
//
//  Created by Marek on 15/05/2018.
//

#ifndef Patterns_hpp
#define Patterns_hpp

#include "SPUserDefault.h"
#include "Game.h"
#include "PlatformManager.h"
#include "Pattern.h"
#include "Shop.h"

USING_NS_CC;

#define PATTERN_DEBUG_ENABLED   0
#define PATTERN_DEBUG_NUMBER    3
#define PATTERN_DEBUG_WAVES     8
#define PATTERN_DEBUG_ROTATION  0

struct gameplay_info{
    
    int level           = 0;
    int stage           = 0;
    int wave            = 0;
    int score           = 0;
    int highscore       = 0;
    int fruits_in_mixer = 0;
    int recipes_unlocked= 0;
    int fruit_type_roll = 0;
    
};

class Patterns{
    
public:
    
    static std::shared_ptr< Patterns > getInstance();
    
    Patterns()
    {};
    virtual ~Patterns();
    
    void         generate_new_coctails();
    void         generate_new_level();
    level_info   get_current_level();
    level_info   get_new_level      (int level_number);
    pattern_info get_pattern_info   (int stage,int wave);
    Pattern *    get_pattern(pattern_info p_info);
    
    std::vector<SHOP_ITEM> is_current_level_have_knife();
    
    fruit_type              get_random_fruit    (gameplay_info gameplay);
    std::vector<fruit_type> get_fruits          (int max_size,gameplay_info gameplay);
    
};

#endif /* Patterns_hpp */
