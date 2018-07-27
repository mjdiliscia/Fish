//
//  Enemy.cpp
//  Fish
//
//  Created by Martin Javier Di Liscia on 25/7/18.
//

#include "Enemy.h"
#include "EnemiesManager.h"

USING_NS_CC;

Enemy* Enemy::createWithSprite(Sprite* sprite) {
    auto newEnemy = Enemy::create();
    if (sprite && newEnemy && newEnemy->initWithSprite(sprite)) {
        return newEnemy;
    }
    
    CC_SAFE_DELETE(newEnemy);
    return nullptr;
}

bool Enemy::initWithSprite(Sprite* sprite) {
    direction = Vec2::ZERO;
    
    auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2.0);
    body->setDynamic(false);
    body->setContactTestBitmask(0x3);
    addComponent(body);

    this->sprite = sprite;
    addChild(sprite);
    sprite->setPosition(Vec2::ZERO);

    return true;
}

void Enemy::update(float delta) {
    auto position = getPosition();
    position += direction * SPEED * delta;
	setPosition(position);
}

void Enemy::goTowards(Vec2 direction, EnemiesManager* manager) {
    this->manager = manager;
    this->direction = direction;
	setRotation(CC_RADIANS_TO_DEGREES(-direction.getAngle())+90);
}

void Enemy::receiveHit() {
    manager->poolEnemy(this);
}
