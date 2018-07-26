//
//  Enemy.cpp
//  Fish
//
//  Created by Martin Javier Di Liscia on 25/7/18.
//

#include "Enemy.h"

Enemy* Enemy::createWithSprite(cocos2d::Sprite* sprite) {
    auto newEnemy = Enemy::create();
    if (sprite && newEnemy && newEnemy->initWithSprite(sprite)) {
        return newEnemy;
    }
    
    CC_SAFE_DELETE(newEnemy);
    return nullptr;
}

bool Enemy::initWithSprite(cocos2d::Sprite* sprite) {
    direction = cocos2d::Vec2::ZERO;
    auto body = cocos2d::PhysicsBody::createCircle(sprite->getContentSize().width / 2.0);
    body->setDynamic(false);
    addComponent(body);
    
    this->sprite = sprite;
    addChild(sprite);
    sprite->setPosition(cocos2d::Vec2::ZERO);
    
	scheduleUpdate();

    return true;
}

void Enemy::update(float delta) {
    auto position = getPosition();
    position += direction * SPEED * delta;
	setPosition(position);
}

void Enemy::goTowards(cocos2d::Vec2 direction) {
    this->direction = direction;
	setRotation(CC_RADIANS_TO_DEGREES(-direction.getAngle())+90);
}

void Enemy::receiveHit() {
    
}
