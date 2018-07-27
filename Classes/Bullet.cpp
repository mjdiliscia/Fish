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

USING_NS_CC;

Rect Bullet::playArea;

Bullet* Bullet::createWithSprite(Sprite* sprite) {
    auto newBullet = Bullet::create();
    if (sprite && newBullet && newBullet->initWithSprite(sprite)) {
        return newBullet;
    }
    
    CC_SAFE_DELETE(newBullet);
    return nullptr;
}

bool Bullet::initWithSprite(Sprite* sprite) {
    if (playArea.equals(Rect::ZERO)) {
        playArea = Rect(Vec2::ONE*(-PLAY_AREA_OFFSET), Director::getInstance()->getVisibleSize() + Size(PLAY_AREA_OFFSET*2, PLAY_AREA_OFFSET*2));
    }
    
    direction = Vec2::ZERO;
    
    auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2.0);
    body->setDynamic(false);
    body->setContactTestBitmask(0x1);
    addComponent(body);
    
    GameScene::getInstance()->addContactListener(this, CC_CALLBACK_1(Bullet::onEnemyContact, this));
    
    this->sprite = sprite;
    addChild(sprite);
    sprite->setPosition(Vec2::ZERO);
    
    return true;
}

void Bullet::update(float delta) {
    auto position = getPosition();
    position += direction * SPEED * delta;
    setPosition(position);
    
    if (!playArea.containsPoint(position))
        manager->poolBullet(this);
}

void Bullet::goTowards(Vec2 direction, Fish* manager) {
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
