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
#include <cmath>

USING_NS_CC;

Fish::~Fish() {
    Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);
    
    for (auto bullet : bullets)
        bullet->release();
}

Fish* Fish::createWithSprites(std::string idle, std::string shooting) {
    auto idleSprite = Sprite::create(idle);
    auto shootingSprite = Sprite::create(shooting);
    auto newFish = Fish::create();
    if (idleSprite && shootingSprite && newFish && newFish->initWithSprites(idleSprite, shootingSprite)) {
        return newFish;
    }
    CC_SAFE_DELETE(newFish);
    return nullptr;
}

bool Fish::initWithSprites(Sprite* idle, Sprite* shooting) {
    auto eventDispatcher = Director::getInstance()->getEventDispatcher();
    touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(Fish::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(Fish::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Fish::onTouchEnded, this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto body = PhysicsBody::createCircle(idle->getContentSize().width / 2.0 * SCALE);
    body->setDynamic(false);
    body->setContactTestBitmask(0x2);
	addComponent(body);

    GameScene::getInstance()->addContactListener(this, CC_CALLBACK_1(Fish::onEnemyContact, this));
    
    this->idle = idle;
    addChild(idle);
    idle->setPosition(Vec2::ZERO);
    idle->setScale(SCALE);
    
    this->shooting = shooting;
    addChild(shooting);
    shooting->setPosition(Vec2::ZERO);
    shooting->setScale(SCALE);
    shooting->setVisible(false);

    while (bullets.size() < POOL_SIZE) {
        auto newBullet = Bullet::createWithSprite("bubble.png");
        if (!newBullet) {
            log("bubble.png not found");
            return false;
        }
        
        newBullet->retain();
        newBullet->unscheduleUpdate();
        bullets.push_back(newBullet);
    }
    
    return true;
}

void Fish::update(float delta) {
    time += (long)(delta*1000);

    if (touching) {
        direction = (touchPos - this->getPosition()).getNormalized();
        float angleDiff = CC_RADIANS_TO_DEGREES(-direction.getAngle()) - (getRotation()+90);
        if (std::abs(angleDiff) > 180)
            angleDiff = (360 - std::abs(angleDiff)) * (angleDiff > 0.0 ? -1.0 : 1.0);
        float rotationAngle = angleDiff;
        if (std::abs(rotationAngle) > ROTATION_SPEED * delta)
            rotationAngle = ROTATION_SPEED * delta * (rotationAngle > 0.0 ? 1.0 : -1.0);
        setRotation(getRotation() + rotationAngle);
        
        if (std::abs(rotationAngle - angleDiff) <= SHOOT_ANGLE)
            Director::getInstance()->getRunningScene()->getPhysicsWorld()->queryPoint(CC_CALLBACK_3(Fish::onEnemyTouched, this), touchPos, nullptr);
    }
    
    if (lastBulletTimestamp + SHOOT_DURATION < time && (!idle->isVisible() || shooting->isVisible())) {
        shooting->setVisible(false);
        idle->setVisible(true);
    }
}

void Fish::onTouchMoved(Touch* touch, Event* event) {
    touchPos = touch->getLocation();
}

bool Fish::onTouchBegan(Touch* touch, Event* event) {
    touching = true;
    touchPos = touch->getLocation();
    
    return true;
}

void Fish::onTouchEnded(Touch* touch, Event* event) {
    touching = false;
}

bool Fish::onEnemyTouched(PhysicsWorld& world, PhysicsShape& shape, void* data) {
    Enemy* enemy = dynamic_cast<Enemy*> (shape.getBody()->getNode());
    if (enemy) {
        if (lastBulletTimestamp + BULLET_CADENCY < time) {
            fireBullet();
            lastBulletTimestamp = time;
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
        Vec2 rotatedOffset = BULLET_OFFSET;
        rotatedOffset.rotate(Vec2::ZERO, CC_DEGREES_TO_RADIANS(-getRotation()-90));
        bullet->setPosition(getPosition() + rotatedOffset);
        bullet->goTowards(direction, this);
        bullet->scheduleUpdate();
        bullet->release();
        
        shooting->setVisible(true);
        idle->setVisible(false);
    }
}

void Fish::poolBullet(Bullet* bullet) {
    bullet->retain();
    bullet->removeFromParent();
    bullets.push_back(bullet);
}

