//
//  Fish.h
//  Gun
//
//  Created by Martin Javier Di Liscia on 25/7/18.
//

#ifndef Fish_h
#define Fish_h

#include "cocos2d.h"

class Bullet;

class Fish : public cocos2d::Node
{
public:
    static Fish* createWithSprites(cocos2d::Sprite* idle, cocos2d::Sprite* shooting);
    
    bool initWithSprites(cocos2d::Sprite* idle, cocos2d::Sprite* shooting);
    void poolBullet(Bullet* bullet);
    virtual void update(float delta);

    ~Fish();
private:
    // implement the "static create()" method manually
    CREATE_FUNC(Fish);
    
    const long BULLET_CADENCY = 500;
    const long SHOOT_DURATION = 300;
    const float SHOOT_ANGLE = 5;
    const int POOL_SIZE = 5;
    const float ROTATION_SPEED = 180;
    const cocos2d::Vec2 BULLET_OFFSET = cocos2d::Vec2(30,0);
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    bool onEnemyTouched(cocos2d::PhysicsWorld& world, cocos2d::PhysicsShape& shape, void* data);
    bool onEnemyContact(Node* node);
    
    void fireBullet();

    std::list<Bullet*> bullets;
    cocos2d::EventListenerTouchOneByOne* touchListener;
    cocos2d::Sprite* idle;
    cocos2d::Sprite* shooting;
    cocos2d::Vec2 direction;
    long lastBulletTimestamp;
    bool touching;
    cocos2d::Vec2 touchPos;
};

#endif /* Fish_h */
