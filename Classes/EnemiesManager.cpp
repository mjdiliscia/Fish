//
//  EnemiesManager.cpp
//  Fish
//
//  Created by Martin Javier Di Liscia on 25/7/18.
//

#include "EnemiesManager.h"

bool EnemiesManager::init() {
	while (enemies.size() < 20) {
		auto enemySprite = cocos2d::Sprite::create("Enemy.png");
		auto enemy = Enemy::createWithSprite(enemySprite);
		if (!enemy) {
			cocos2d::log("Enemy.png not found");
			return false;
		}
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
				x = cocos2d::random() > RAND_MAX / 2 ? -70 : visibleSize.width + 70;
				y = cocos2d::rand_0_1() * visibleSize.height;
			} else {
				x = cocos2d::rand_0_1() * visibleSize.width;
				y = cocos2d::random() > RAND_MAX / 2 ? -70 : visibleSize.height + 70;
			}
			cocos2d::Vec2 position = cocos2d::Vec2(x, y);
			cocos2d::Vec2 center = visibleSize / 2.0;

			addChild(enemy);
			enemy->setPosition(position);
			enemy->goTowards((center - position).getNormalized());
		}
	}
}