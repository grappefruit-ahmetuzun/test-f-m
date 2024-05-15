//
//  Game.cpp
//  bottlechallenge
//
//  Created by Marek on 22/09/2016.
//
//

#include "Game.h"
#include "PlatformManager.h"
#include "GameScene.h"

std::shared_ptr< Game > gameInstance;

std::shared_ptr< Game > Game::getInstance(){
    if (gameInstance) return gameInstance;
    gameInstance = std::make_shared< Game >();
    return gameInstance;
}

void Game::addCoins(int c){
    
    int now = SPUserDefault::getInstance()->getIntegerForKey("coins");
    int after = now+c;
    if (after<0) {
        after = 0;
    }
    SPUserDefault::getInstance()->setIntegerForKey("coins", after);
    
}

void Game::addGems(int c){
    
    
    int now = SPUserDefault::getInstance()->getIntegerForKey("gems");
    int after = now+c;
    if (after<0) {
        after = 0;
    }
    SPUserDefault::getInstance()->setIntegerForKey("gems", after);
    
}

float Game::getRotationWorld(Node* node){
    Vec2 vForward = node->convertToWorldSpace(Vec2::UNIT_X);
    Vec2 vZero = node->convertToWorldSpace(Vec2::ZERO);
    Vec2 vRot = vForward - vZero;
    return -CC_RADIANS_TO_DEGREES(vRot.getAngle());
}

float Game::getRotationNode(Node* node, float worldRotationDegrees){
    Vec2 vZero = node->convertToWorldSpace(Vec2::ZERO);
    Vec2 vForward = Vec2::forAngle(-CC_DEGREES_TO_RADIANS(worldRotationDegrees)) + vZero;
    Vec2 vLocal = node->convertToNodeSpace(vForward);
    float rDelta = -CC_RADIANS_TO_DEGREES(vLocal.getAngle());
    //if (rDelta == 0)return 0;
    float tRot = rDelta + node->getRotation();
    return tRot;
}


#pragma mark promotions

void Game::setPromotionsSequence(){
    
    std::vector<promo_type>promotions;
    
    promotions.push_back(promo_type_knife_hit);
    promotions.push_back(promo_type_dunk_shot);
    promotions.push_back(promo_type_dunk_line);

    for (int x=0; x < promotions.size(); x++) {
        SPUserDefault::getInstance()->setIntegerForKey(StringUtils::format("promo_seq_%i",x).c_str(), promotions.at(x));
    }
    
}

promo_type Game::get_next_promotion(){
    
    int index              = SPUserDefault::getInstance()->getIntegerForKey("promo_seq_index");
    promo_type promo       = (promo_type)SPUserDefault::getInstance()->getIntegerForKey(StringUtils::format("promo_seq_%i",index).c_str());
    
    
    index++;
    if (index > 2) {
        index = 0;
    }
    
    SPUserDefault::getInstance()->setIntegerForKey("promo_seq_index", index);
    
    return promo;
}

#pragma mark

void Game::runRecursiveAction(Node *node,ActionInterval *action){
    node->runAction(action->clone());
    
    for (Node *n : node->getChildren()) {
        runRecursiveAction(n, action->clone());
    }
}

void Game::align_x_side_by_side(Node *left,Node *right,float offset){
    
    float width =
    left->getBoundingBox().size.width+
    right->getBoundingBox().size.width+(offset);
    
    right->  setPosition((right->getParent()->getContentSize().width*0.5f)-(right->getBoundingBox().size.width*0.5f)+(width/2), right->getPositionY());
    left->   setPosition((left->getParent()->getContentSize().width*0.5f) +(left-> getBoundingBox().size.width*0.5f)-(width/2), left->getPositionY());
    
}

float Game::pointPairToBearingDegrees(const cocos2d::Point &startingPoint, const cocos2d::Point &endingPoint) {
    
    cocos2d::Point originPoint = cocos2d::Point(endingPoint.x - startingPoint.x, endingPoint.y - startingPoint.y);
    float bearingRadians = atan2f(originPoint.y, originPoint.x);
    float bearingDegrees = bearingRadians * (180.0 / M_PI);
    bearingDegrees = (bearingDegrees > 0.0 ? bearingDegrees : (360.0 + bearingDegrees));
    return bearingDegrees;
}


Label * Game::show_text_label_info(Vec2 world_pos,std::string text,float scale_by){
    
    Scene * scene = Director::getInstance()->getRunningScene();
    if (scene) {
        
        GameScene * game_scene = (GameScene *)scene->getChildByTag(GAMESCENE_TAG);
        
        if (game_scene) {
            
            Label * label = Label::createWithTTF(text.c_str(), "fonts/Triomphe-Regular-autoinstr.ttf", game_scene->getContainer()->getContentSize().height * 0.025f * scale_by);
            label->setAlignment(TextHAlignment::CENTER);
            game_scene->addChild(label, 999999999);
            label->setPosition(world_pos);
            
            bool dark_mode_on = Settings::getStateOn(settings_darkmode);
            
            if (dark_mode_on == true) {
                label->setColor(Color3B::WHITE);
            }
            else{
                label->setColor(Color3B::BLACK);
            }
            
            auto move_by = MoveBy::create(1.0f, Vec2(0, game_scene->getContentSize().height*0.05f));
            auto fade = FadeTo::create(0.35f, 0);
            auto seq = Sequence::create(Spawn::create(move_by,Sequence::create(DelayTime::create(0.25f),fade, NULL), NULL),RemoveSelf::create(), NULL);
            label->runAction(seq);
            
            return label;
        }
    }
    return nullptr;
}
