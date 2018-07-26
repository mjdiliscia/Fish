//
//  Bullet.h
//  Fish
//
//  Created by Martin Javier Di Liscia on 26/7/18.
//

#ifndef Bullet_h
#define Bullet_h

#include "cocos2d.h"

class Fish;

class Bullet : public cocos2d::Node {
public:
    static Bullet* createWithSprite(cocos2d::Sprite* sprite);
    
    bool initWithSprite(cocos2d::Sprite* sprite);
    virtual void update(float delta);

    void goTowards(cocos2d::Vec2 direction, Fish* manager);
    
private:
    const float SPEED = 80.0;
    const float PLAY_AREA_OFFSET = 70.0;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Bullet);
    
    bool onEnemyContact(Node* node);
    
    static cocos2d::Rect playArea;
    
    Fish* manager;
    cocos2d::Sprite* sprite;
    cocos2d::Vec2 direction;
};

#endif /* Bullet_h */
