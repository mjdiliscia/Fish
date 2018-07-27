//
//  MenuScene.h
//  Fish
//
//  Created by Martin Javier Di Liscia on 26/7/18.
//

#ifndef MenuScene_h
#define MenuScene_h

#include "cocos2d.h"

USING_NS_CC;

class MenuScene : public Scene {
public:
    static Scene* createScene();
    
    virtual bool init();
    
    void menuCloseCallback(Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
};

#endif /* MenuScene_h */
