//
//  EnemiesManager.cpp
//  Fish
//
//  Created by Martin Javier Di Liscia on 25/7/18.
//

#include "EnemiesManager.h"
#include "Enemy.h"

bool EnemiesManager::init() {
	while (enemies.size() < POOL_SIZE) {
		auto enemySprite = cocos2d::Sprite::create("Enemy.png");
        if (!enemySprite) {
            cocos2d::log("Enemy.png not found");
            return false;
        }
		auto enemy = Enemy::createWithSprite(enemySprite);
		enemy->retain();
		enemies.push_back(enemy);
	}

	nextSpawn = SPAWN_TIME;
	scheduleUpdate();

	return true;
}

void EnemiesManager::update(float delta) {
	nextSpawn -= delta;
	if (nextSpawn < 0.0) {
		nextSpawn += SPAWN_TIME;

		if (enemies.size() > 0) {
			Enemy* enemy = enemies.front();
			enemies.pop_front();

			cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
			float x, y;
			if (cocos2d::rand_0_1() > 0.5) {
				x = cocos2d::random() > RAND_MAX / 2 ? -SPAWN_OFFSET : visibleSize.width + SPAWN_OFFSET;
				y = cocos2d::rand_0_1() * visibleSize.height;
			} else {
				x = cocos2d::rand_0_1() * visibleSize.width;
				y = cocos2d::random() > RAND_MAX / 2 ? -SPAWN_OFFSET : visibleSize.height + SPAWN_OFFSET;
			}
			cocos2d::Vec2 position = cocos2d::Vec2(x, y);
			cocos2d::Vec2 center = visibleSize / 2.0;

			addChild(enemy);
            enemy->scheduleUpdate();
			enemy->setPosition(position);
			enemy->goTowards((center - position).getNormalized(), this);
            enemy->release();
		}
	}
}

void EnemiesManager::poolEnemy(Enemy* enemy) {
    enemy->retain();
    enemy->removeFromParent();
    enemies.push_back(enemy);
}
