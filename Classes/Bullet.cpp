//
//  Bullet.cpp
//  Fish
//
//  Created by Martin Javier Di Liscia on 26/7/18.
//

#include "Bullet.h"
#include "Enemy.h"
#include "Fish.h"
#include "GameScene.h"

cocos2d::Rect Bullet::playArea;

Bullet* Bullet::createWithSprite(cocos2d::Sprite* sprite) {
    auto newBullet = Bullet::create();
    if (sprite && newBullet && newBullet->initWithSprite(sprite)) {
        return newBullet;
    }
    
    CC_SAFE_DELETE(newBullet);
    return nullptr;
}

bool Bullet::initWithSprite(cocos2d::Sprite* sprite) {
    if (playArea.equals(cocos2d::Rect::ZERO)) {
        playArea = cocos2d::Rect(cocos2d::Vec2::ONE*(-PLAY_AREA_OFFSET), cocos2d::Director::getInstance()->getVisibleSize() + cocos2d::Size(PLAY_AREA_OFFSET*2, PLAY_AREA_OFFSET*2));
    }
    
    direction = cocos2d::Vec2::ZERO;
    
    auto body = cocos2d::PhysicsBody::createCircle(sprite->getContentSize().width / 2.0);
    body->setDynamic(false);
    body->setContactTestBitmask(0x1);
    addComponent(body);
    
    GameScene::getInstance()->addContactListener(this, CC_CALLBACK_1(Bullet::onEnemyContact, this));
    
    this->sprite = sprite;
    addChild(sprite);
    sprite->setPosition(cocos2d::Vec2::ZERO);
    
    return true;
}

void Bullet::update(float delta) {
    auto position = getPosition();
    position += direction * SPEED * delta;
    setPosition(position);
    
    if (!playArea.containsPoint(position))
        manager->poolBullet(this);
}

void Bullet::goTowards(cocos2d::Vec2 direction, Fish* manager) {
    this->manager = manager;
    this->direction = direction;
    setRotation(CC_RADIANS_TO_DEGREES(-direction.getAngle())+90);
}

bool Bullet::onEnemyContact(Node* node) {
    Enemy* enemy = dynamic_cast<Enemy*>(node);
    
    if (enemy) {
        enemy->receiveHit();
        manager->poolBullet(this);
    }
    return true;
}
