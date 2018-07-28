//
//  Bullet.h
//  Fish
//
//  Created by Martin Javier Di Liscia on 26/7/18.
//

#ifndef Bullet_h
#define Bullet_h

#include "cocos2d.h"
#include <string>

USING_NS_CC;

class Fish;

class Bullet : public Node {
public:
    static Bullet* createWithSprite(std::string spriteFile);
    
    bool initWithSprite(Sprite* sprite);
    virtual void update(float delta);

    void goTowards(Vec2 direction, Fish* manager);
    
private:
    const float SCALE = 0.2;
    const float SPEED = 80.0;
    const float PLAY_AREA_OFFSET = 70.0;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Bullet);
    
    bool onEnemyContact(Node* node);
    
    static Rect playArea;
    
    Fish* manager;
    Sprite* sprite;
    Vec2 direction;
};

#endif /* Bullet_h */
