//
//  MenuScene.h
//  Fish
//
//  Created by Martin Javier Di Liscia on 26/7/18.
//

#ifndef MenuScene_h
#define MenuScene_h

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
};

#endif /* MenuScene_h */
