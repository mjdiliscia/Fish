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
    
    virtual bool init();
    virtual void update(float delta);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Fish);

private:
    bool OnTouchBool(cocos2d::Touch* touch, cocos2d::Event* event);
    void OnTouch(cocos2d::Touch* touch, cocos2d::Event* event);

    cocos2d::EventListenerTouchOneByOne* touchListener;
    cocos2d::Sprite* sprite;
};

#endif /* Fish_h */
