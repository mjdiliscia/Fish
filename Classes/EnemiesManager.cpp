//
//  EnemiesManager.cpp
//  Fish
//
//  Created by Martin Javier Di Liscia on 25/7/18.
//

#include "EnemiesManager.h"
#include "Enemy.h"

USING_NS_CC;

EnemiesManager::~EnemiesManager() {
    for (auto enemy : enemies)
        enemy->release();
}

bool EnemiesManager::init() {
	while (enemies.size() < POOL_SIZE) {
		auto enemySprite = Sprite::create("badFish.png");
        if (!enemySprite) {
            log("badFish.png not found");
            return false;
        }
		auto enemy = Enemy::createWithSprite(enemySprite);
		enemy->retain();
        enemy->unscheduleUpdate();
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

			Size visibleSize = Director::getInstance()->getVisibleSize();
			float x, y;
			if (rand_0_1() > 0.5) {
                x = cocos2d::random() > RAND_MAX / 2 ? -SPAWN_OFFSET : visibleSize.width + SPAWN_OFFSET;
				y = rand_0_1() * visibleSize.height;
			} else {
				x = rand_0_1() * visibleSize.width;
				y = cocos2d::random() > RAND_MAX / 2 ? -SPAWN_OFFSET : visibleSize.height + SPAWN_OFFSET;
			}
			Vec2 position = Vec2(x, y);
			Vec2 center = visibleSize / 2.0;

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
