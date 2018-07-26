//
//  Fish.cpp
//  Gun-mobile
//
//  Created by Martin Javier Di Liscia on 25/7/18.
//

#include "Fish.h"
#include "Enemy.h"

Fish* Fish::createWithSprite(cocos2d::Sprite* sprite) {
    auto newFish = Fish::create();
    if (sprite && newFish && newFish->initWithSprite(sprite)) {
        return newFish;
    }
    CC_SAFE_DELETE(newFish);
    return nullptr;
}

bool Fish::initWithSprite(cocos2d::Sprite* sprite) {
    auto eventDispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
    touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(Fish::onTouchBool, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(Fish::onTouch, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Fish::onTouch, this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto body = cocos2d::PhysicsBody::createCircle(sprite->getContentSize().width / 2.0);
    body->setDynamic(false);
	addComponent(body);

    contactListener = cocos2d::EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Fish::onEnemyContact, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    this->sprite = sprite;
    addChild(sprite);
    sprite->setPosition(cocos2d::Vec2::ZERO);
    
    return true;
}

void Fish::onTouch(cocos2d::Touch* touch, cocos2d::Event* event) {
    cocos2d::Vec2 direction = touch->getLocation() - this->getPosition();
    this->setRotation(CC_RADIANS_TO_DEGREES(-direction.getAngle()));
    
    cocos2d::Director::getInstance()->getRunningScene()->getPhysicsWorld()->queryPoint(CC_CALLBACK_3(Fish::onEnemyTouched, this), touch->getLocation(), nullptr);
}

bool Fish::onTouchBool(cocos2d::Touch* touch, cocos2d::Event* event) {
    onTouch(touch, event);
    return true;
}

bool Fish::onEnemyTouched(cocos2d::PhysicsWorld& world, cocos2d::PhysicsShape& shape, void* data) {
    Enemy* enemy = dynamic_cast<Enemy*> (shape.getBody()->getNode());
    return true;
}

bool Fish::onEnemyContact(cocos2d::PhysicsContact& contact) {
    Enemy* enemy = nullptr;
    if (contact.getShapeA()->getBody()->getNode() == this) {
        enemy = dynamic_cast<Enemy*>(contact.getShapeB()->getBody()->getNode());
    } else {
        enemy = dynamic_cast<Enemy*>(contact.getShapeA()->getBody()->getNode());
    }
    
	if (enemy) {
		cocos2d::Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
	}

    return false;
}
