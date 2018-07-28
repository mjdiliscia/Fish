//
//  Enemy.h
//  Fish
//
//  Created by Martin Javier Di Liscia on 25/7/18.
//

#ifndef Enemy_h
#define Enemy_h

#include "cocos2d.h"
#include <string>

USING_NS_CC;

class EnemiesManager;

class Enemy : public Node
{
public:
    static Enemy* createWithSprite(std::string spriteFile);
    
    bool initWithSprite(Sprite* sprite);
    virtual void update(float delta);
    
    void goTowards(Vec2 direction, EnemiesManager* manager);
    void receiveHit();
    
private:
    const float SCALE = 0.2;
    const float SPEED = 40.0;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Enemy);
    
    EnemiesManager* manager;
    Vec2 direction;
    Sprite* sprite;
};

#endif /* Enemy_h */
