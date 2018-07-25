//
//  Fish.h
//  Gun
//
//  Created by Martin Javier Di Liscia on 25/7/18.
//

#ifndef Fish_h
#define Fish_h

#include "cocos2d.h"

class Fish : public cocos2d::Node
{
public:
    static Fish* createWithSprite(cocos2d::Sprite* sprite);
    
    bool initWithSprite(cocos2d::Sprite* sprite);

private:
    // implement the "static create()" method manually
    CREATE_FUNC(Fish);
                        
    bool onTouchBool(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouch(cocos2d::Touch* touch, cocos2d::Event* event);
    bool onEnemyTouched(cocos2d::PhysicsWorld& world, cocos2d::PhysicsShape& shape, void* data);
    bool onEnemyContact(cocos2d::PhysicsContact& contact);

    cocos2d::EventListenerPhysicsContact* contactListener;
    cocos2d::EventListenerTouchOneByOne* touchListener;
    cocos2d::Sprite* sprite;
};

#endif /* Fish_h */
