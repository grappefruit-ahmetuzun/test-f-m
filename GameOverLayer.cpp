//
//  GameOverLayer.cpp
//  FruitsKnife-mobile
//
//  Created by Marek on 17/05/2018.
//

#include "GameOverLayer.h"
#include "Game.h"
#include "PlatformManager.h"

void GameOverLayer::animateOnEnter (GameOverInfo info, float delay){
    
    _info = info;
    
    getBg()->setOpacity(0);
    getBg()->setColor(Color3B::BLACK);
    getBg()->runAction(FadeTo::create(0.1f, 255 * 0.75f));
    
    Sprite *stamp = Sprite::create("gameover/splash.png");
    addChild(stamp);
    stamp->setScale(getContainer()->getContentSize().width*0.8f/stamp->getContentSize().width);
    stamp->setPosition(Vec2(getContentSize().width*0.5f, getContentSize().height*0.5f+(getContainer()->getContentSize().height*0.285f)));
    
    Label *score_label = Label::createWithTTF(StringUtils::format("%i",info.score), "fonts/Blogger_Sans-Bold.otf", stamp->getContentSize().height*0.25f);
    score_label->setPosition(stamp->getContentSize().width * 0.5f,
                             stamp->getContentSize().height*0.6f);
    score_label->setRotation(-10);
    score_label->setColor(Color3B(6, 41, 48));
    score_label->setRotationSkewX(5);
    stamp->addChild(score_label);

    Label *wave_label = Label::createWithTTF(StringUtils::format("LEVEL %i",info.level), "fonts/Blogger_Sans-Bold.otf", stamp->getContentSize().height*0.125f);
    wave_label->setPosition(stamp->getContentSize().width * 0.5f,
                             stamp->getContentSize().height*0.4f);
    wave_label->setRotation(-10);
    wave_label->setColor(Color3B(6, 41, 48));
    wave_label->setRotationSkewX(5);
    stamp->addChild(wave_label);
    
    
    home_button = SPButton::createWithImage("gameover/home.png");
    addChild(home_button);
    home_button->setScale(getContainer()->getContentSize().width * 0.18f / home_button->getContentSize().width);
    home_button->setTouchAreaScale(2.0f);
    
    int game_tag = 1;
    
    std::string game_button_texture = "gameover/knifemdpi.png";
    
    if (random(0, 1) == 1) {
        game_tag = 2;
        game_button_texture = "gameover/mrmdpi.png";
    }
    
    game_promo_button     = SPButton::createWithImage(game_button_texture);
    addChild(game_promo_button);
    game_promo_button->setTag(game_tag);
    game_promo_button->setScale(getContainer()->getContentSize().height * 0.15f / game_promo_button->getContentSize().height);
    game_promo_button->setVoidTouchDownCallback([this]{
        if (game_promo_button->getTag() == 1) {
            PlatformManager::open_game(promo_type_knife_hit);
        }
        else if (game_promo_button->getTag() == 2){
            PlatformManager::open_game(promo_type_mr_gun);
        }
    });
    
    
    coins_video_button    = SPButton::createWithImage("gameover/coins.png");
    addChild(coins_video_button);
    coins_video_button->setScale(getContainer()->getContentSize().height * 0.08f / coins_video_button->getContentSize().height);
    
    {
        Label * count_label = Label::createWithTTF(StringUtils::format("+%i", k_VIDEO_REWARD_COINS_GAMEOVER), "fonts/Blogger_Sans-Bold.otf", coins_video_button->getContentSprite()->getContentSize().height * 0.45f);
        count_label->setPosition(coins_video_button->getContentSprite()->getContentSize().width * 0.55f, coins_video_button->getContentSprite()->getContentSize().height * 0.45f);
        coins_video_button->getContentSprite()->addChild(count_label);
        count_label->setColor(Color3B::BLACK);
    }
    
    gems_video_button    = SPButton::createWithImage("gameover/gems.png");
    addChild(gems_video_button);
    gems_video_button->setScale(getContainer()->getContentSize().height * 0.08f / gems_video_button->getContentSize().height);
    
    {
        Label * count_label = Label::createWithTTF(StringUtils::format("+%i", k_VIDEO_REWARD_GEMS_GAMEOVER), "fonts/Blogger_Sans-Bold.otf", gems_video_button->getContentSprite()->getContentSize().height * 0.45f);
        count_label->setPosition(gems_video_button->getContentSprite()->getContentSize().width * 0.55f, gems_video_button->getContentSprite()->getContentSize().height * 0.45f);
        gems_video_button->getContentSprite()->addChild(count_label);
        count_label->setColor(Color3B::BLACK);
    }
    
    
    customize_button       = SPButton::createWithImage("menu/customize.png");
    addChild(customize_button);
    customize_button->setScale(getContainer()->getContentSize().height * 0.08f / customize_button->getContentSize().height);
    
    no_ads_button          = SPButton::createWithImage("gameover/no_ads.png");
    addChild(no_ads_button);
    no_ads_button->setScale(getContainer()->getContentSize().width*0.18f/no_ads_button->getContentSize().width);
    
    int social_tag = 1;
    
    std::string button_texture = "gameover/facebook.png";
    
    if (random(0, 1) == 1) {
        social_tag = 2;
        button_texture = "gameover/instagram.png";
    }
    
    social_button          = SPButton::createWithImage(button_texture);
    addChild(social_button);
    social_button->setTag(social_tag);
    social_button->setScale(getContainer()->getContentSize().width*0.18f/social_button->getContentSize().width);
    social_button->setVoidTouchDownCallback([this]{
        if (social_button->getTag() == 1) {
            PlatformManager::open_facebook();
        }
        else if (social_button->getTag() == 2){
            PlatformManager::open_instagram();
        }
    });
    
    restart_button          = SPButton::createWithImage("gameover/restart.png");
    addChild(restart_button);
    restart_button->setScale(getContainer()->getContentSize().width*0.25f/restart_button->getContentSize().width);
    
    leaderboards_button     = SPButton::createWithImage("gameover/leader.png");
    addChild(leaderboards_button);
    leaderboards_button->setScale(getContainer()->getContentSize().width*0.18f/leaderboards_button->getContentSize().width);
    
    
    if (info.is_highscore_now) {
        
        Label * best_score = Label::createWithTTF("NEW BEST!", "fonts/Blogger_Sans-Bold.otf", stamp->getContentSize().height*0.165f);
        best_score->setPosition(getContentSize().width * 0.5f, stamp->getPositionY() - stamp->getBoundingBox().size.height * 0.6f);
        best_score->setRotation(-10);
        best_score->setColor(Color3B(246, 206, 72));
        best_score->setRotationSkewX(5);
        addChild(best_score);
        
    }
    else{
        
        Label * best_score = Label::createWithTTF(StringUtils::format("BEST SCORE %i",info.high_score), "fonts/Blogger_Sans-Bold.otf", stamp->getContentSize().height*0.12f);
        best_score->setPosition(getContentSize().width * 0.5f, stamp->getPositionY() - stamp->getBoundingBox().size.height * 0.6f);
        best_score->setRotation(-10);
        best_score->setColor(Color3B(107, 182, 175));
        best_score->setRotationSkewX(5);
        addChild(best_score);
    }
    
    
    

    float start_pos_x = getContentSize().width*0.5f;

   // rate_button->setPosition(Vec2(start_pos_x-(getContainer()->getContentSize().width*0.25f),
   //                               getContentSize().height*0.5f-(getContainer()->getContentSize().height*0.4f)));

    home_button->setPosition(Vec2(getContentSize().width * 0.5f - getContainer()->getContentSize().width * 0.38f, getHeaderUIDefaultPosY()));
    
    game_promo_button->setPosition(Vec2(start_pos_x, getContentSize().height * 0.5f - (getContainer()->getContentSize().height * 0.125f)));
    
    coins_video_button->setPosition(Vec2(start_pos_x, getContentSize().height * 0.5f - (getContainer()->getContentSize().height * 0.15f)));
    gems_video_button->setPosition(Vec2(start_pos_x, getContentSize().height * 0.5f - (getContainer()->getContentSize().height * 0.15f)));
    
    customize_button->setPosition(Vec2(start_pos_x, getContentSize().height * 0.5f - (getContainer()->getContentSize().height * 0.15f)));
    
    no_ads_button->setPosition(Vec2(start_pos_x - (getContainer()->getContentSize().width*0.265f), getContentSize().height * 0.5f - (getContainer()->getContentSize().height * 0.32f)));
    
    social_button->setPosition(Vec2(start_pos_x - (getContainer()->getContentSize().width*0.265f), getContentSize().height * 0.5f - (getContainer()->getContentSize().height * 0.32f)));
    
    restart_button->setPosition(Vec2(start_pos_x, getContentSize().height*0.5f - (getContainer()->getContentSize().height * 0.32f)));

    leaderboards_button->setPosition(Vec2(start_pos_x + (getContainer()->getContentSize().width*0.265f), getContentSize().height*0.5f - (getContainer()->getContentSize().height * 0.32f)));
    
    std::vector<Node *>buttons;
   // buttons.push_back(rate_button);
    
    buttons.push_back(home_button);
    buttons.push_back(coins_video_button);
    buttons.push_back(gems_video_button);
    buttons.push_back(customize_button);
    buttons.push_back(game_promo_button);
    
    buttons.push_back(social_button);
    buttons.push_back(no_ads_button);
    buttons.push_back(leaderboards_button);
    buttons.push_back(restart_button);
    
    float delay_time = 0;
    
    for (int x=0; x < buttons.size(); x++) {
        
        Node * button = buttons.at(x);
        auto scale    = ScaleTo::create(0.4f, button->getScale());
        auto scale_e  = EaseElasticOut::create(scale, 0.75f);
        button->setScale(0);
        
        if (button == social_button) {
            delay_time+=0.25f;
        }
        else{
            delay_time+=0.035f;
        }
        
        if (button == game_promo_button) {
            auto callf = CallFunc::create([this]{
                auto scale1 = ScaleTo::create(0.4f, getContainer()->getContentSize().height * 0.14f / game_promo_button->getContentSize().height);
                auto ease1  = EaseInOut::create(scale1, 2.2f);
                auto scale2 = ScaleTo::create(0.4f, getContainer()->getContentSize().height * 0.15f / game_promo_button->getContentSize().height);
                auto ease2  = EaseInOut::create(scale2, 2.2f);
                auto seq    = Sequence::create(ease1, ease2, NULL);
                auto repeat = RepeatForever::create(seq);
                game_promo_button->runAction(repeat);
            });
            auto seq = Sequence::create(DelayTime::create(delay_time),scale_e, callf, NULL);
            button->runAction(seq);
        }
        else{
            auto seq = Sequence::create(DelayTime::create(delay_time),scale_e, NULL);
            button->runAction(seq);
        }
        
    }
    
    
    auto scale = ScaleTo::create(0.5f, stamp->getScale());
    auto scale_e = EaseElasticOut::create(scale,1.5f);
    stamp->setScale(0);
    stamp->runAction(scale_e);
    
}
