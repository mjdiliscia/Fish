//
//  Enemy.h
//  Fish
//
//  Created by Martin Javier Di Liscia on 25/7/18.
//

#ifndef Enemy_h
#define Enemy_h

#include "cocos2d.h"

class Enemy : public cocos2d::Node
{
public:
    static Enemy* createWithSprite(cocos2d::Sprite* sprite);
    
    bool initWithSprite(cocos2d::Sprite* sprite);
    virtual void update(float delta);
    
    void goTowards(cocos2d::Vec2 direction);
    void receiveHit();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Enemy);
    
private:
    constexpr static float SPEED = 2.0;
    
    cocos2d::Vec2 direction;
    cocos2d::Sprite* sprite;
};

#endif /* Enemy_h */
