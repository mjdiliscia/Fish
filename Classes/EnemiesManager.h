//
//  EnemiesManager.h
//  Fish
//
//  Created by Martin Javier Di Liscia on 25/7/18.
//

#ifndef Enemies_Manager_h
#define Enemies_Manager_h

#include <list>
#include "cocos2d.h"

USING_NS_CC;

class Enemy;

class EnemiesManager : public cocos2d::Node
{
public:
	virtual bool init();
	virtual void update(float delta);
    
    void poolEnemy(Enemy* enemy);

    // implement the "static create()" method manually
    CREATE_FUNC(EnemiesManager);
    
    ~EnemiesManager();
private:
	const float SPAWN_TIME = 1.0;
    const int POOL_SIZE = 15;
    const float SPAWN_OFFSET = 70.0;

	std::list<Enemy*> enemies;
	float nextSpawn;
};

#endif /* Enemies_Manager_h */
