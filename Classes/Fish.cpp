//
//  Fish.cpp
//  Gun-mobile
//
//  Created by Martin Javier Di Liscia on 25/7/18.
//

#include "Fish.h"
#include "Enemy.h"
#include "Bullet.h"
#include "GameScene.h"

Fish::~Fish() {
    cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);
    
    for (auto bullet : bullets)
        bullet->release();
}

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
    touchListener->onTouchBegan = CC_CALLBACK_2(Fish::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(Fish::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Fish::onTouchEnded, this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto body = cocos2d::PhysicsBody::createCircle(sprite->getContentSize().width / 2.0);
    body->setDynamic(false);
    body->setContactTestBitmask(0x2);
	addComponent(body);

    GameScene::getInstance()->addContactListener(this, CC_CALLBACK_1(Fish::onEnemyContact, this));
    
    this->sprite = sprite;
    addChild(sprite);
    sprite->setPosition(cocos2d::Vec2::ZERO);
    
    while (bullets.size() < POOL_SIZE) {
        auto sprite = cocos2d::Sprite::create("Bullet.png");
        if (!sprite) {
            cocos2d::log("Bullet.png not found");
            return false;
        }
        
        auto newBullet = Bullet::createWithSprite(sprite);
        newBullet->retain();
        newBullet->unscheduleUpdate();
        bullets.push_back(newBullet);
    }
    
    return true;
}

void Fish::update(float delta) {
    if (touching) {
        direction = (touchPos - this->getPosition()).getNormalized();
        this->setRotation(CC_RADIANS_TO_DEGREES(-direction.getAngle()));
        
        cocos2d::Director::getInstance()->getRunningScene()->getPhysicsWorld()->queryPoint(CC_CALLBACK_3(Fish::onEnemyTouched, this), touchPos, nullptr);
    }
}

void Fish::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
    touchPos = touch->getLocation();
}

bool Fish::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    touching = true;
    touchPos = touch->getLocation();
    
    return true;
}

void Fish::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    touching = false;
}

bool Fish::onEnemyTouched(cocos2d::PhysicsWorld& world, cocos2d::PhysicsShape& shape, void* data) {
    Enemy* enemy = dynamic_cast<Enemy*> (shape.getBody()->getNode());
    if (enemy) {
        long timestamp = cocos2d::utils::getTimeInMilliseconds();
        if (lastBulletTimestamp + BULLET_CADENCY < timestamp) {
            fireBullet();
            lastBulletTimestamp = timestamp;
        }
    }
    
    return true;
}

bool Fish::onEnemyContact(Node* node) {
    Enemy* enemy = dynamic_cast<Enemy*>(node);
    
	if (enemy)
        GameScene::getInstance()->end();

    return false;
}

void Fish::fireBullet() {
    if (bullets.size() > 0) {
        auto bullet = bullets.front();
        bullets.pop_front();
    
        getParent()->addChild(bullet);
        bullet->setPosition(getPosition());
        bullet->goTowards(direction, this);
        bullet->scheduleUpdate();
        bullet->release();
    }
}

void Fish::poolBullet(Bullet* bullet) {
    bullet->retain();
    bullet->removeFromParent();
    bullets.push_back(bullet);
}

