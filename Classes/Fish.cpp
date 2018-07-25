//
//  Fish.cpp
//  Gun-mobile
//
//  Created by Martin Javier Di Liscia on 25/7/18.
//

#include <Fish.h>

Fish* Fish::createWithSprite(cocos2d::Sprite* sprite) {
    auto newFish = Fish::create();
    newFish->sprite = sprite;
    newFish->addChild(sprite);
    sprite->setPosition(cocos2d::Vec2::ZERO);
    
    return newFish;
}

bool Fish::init() {
    auto eventDispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
    touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(Fish::OnTouchBool, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(Fish::OnTouch, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Fish::OnTouch, this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

void Fish::OnTouch(cocos2d::Touch* touch, cocos2d::Event* event) {
    cocos2d::Vec2 direction = touch->getLocation() - this->getPosition();
    this->setRotation(CC_RADIANS_TO_DEGREES(-direction.getAngle()));
}

bool Fish::OnTouchBool(cocos2d::Touch* touch, cocos2d::Event* event) {
    OnTouch(touch, event);
    return true;
}

void Fish::update(float delta) {
    
}
