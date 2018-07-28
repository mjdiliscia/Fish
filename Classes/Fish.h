//
//  Fish.h
//  Gun
//
//  Created by Martin Javier Di Liscia on 25/7/18.
//

#ifndef Fish_h
#define Fish_h

#include "cocos2d.h"
#include <string>

USING_NS_CC;

class Bullet;

class Fish : public Node
{
public:
    static Fish* createWithSprites(std::string idle, std::string shooting);
    
    bool initWithSprites(Sprite* idle, Sprite* shooting);
    void poolBullet(Bullet* bullet);
    virtual void update(float delta);

    ~Fish();
private:
    // implement the "static create()" method manually
    CREATE_FUNC(Fish);
    
    const float SCALE = 0.2;
    const long BULLET_CADENCY = 500;
    const long SHOOT_DURATION = 300;
    const float SHOOT_ANGLE = 5;
    const int POOL_SIZE = 15;
    const float ROTATION_SPEED = 180;
    const Vec2 BULLET_OFFSET = Vec2(30,0);
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    bool onEnemyTouched(PhysicsWorld& world, PhysicsShape& shape, void* data);
    bool onEnemyContact(Node* node);
    
    void fireBullet();

    std::list<Bullet*> bullets;
    EventListenerTouchOneByOne* touchListener;
    Sprite* idle;
    Sprite* shooting;
    Vec2 direction;
    long lastBulletTimestamp;
    bool touching;
    Vec2 touchPos;
};

#endif /* Fish_h */
