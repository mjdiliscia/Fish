//
//  Enemy.h
//  Fish
//
//  Created by Martin Javier Di Liscia on 25/7/18.
//

#ifndef Enemy_h
#define Enemy_h

#include "cocos2d.h"

class EnemiesManager;

class Enemy : public cocos2d::Node
{
public:
    static Enemy* createWithSprite(cocos2d::Sprite* sprite);
    
    bool initWithSprite(cocos2d::Sprite* sprite);
    virtual void update(float delta);
    
    void goTowards(cocos2d::Vec2 direction, EnemiesManager* manager);
    void receiveHit();
    
private:
    const float SPEED = 40.0;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Enemy);
    
    EnemiesManager* manager;
    cocos2d::Vec2 direction;
    cocos2d::Sprite* sprite;
};

#endif /* Enemy_h */
