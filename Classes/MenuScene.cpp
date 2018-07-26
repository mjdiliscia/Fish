//
//  MenuScene.cpp
//  Fish
//
//  Created by Martin Javier Di Liscia on 26/7/18.
//

#include "MenuScene.h"
#include "GameScene.h"
#include "ui/UIButton.h"

cocos2d::Scene* MenuScene::createScene() {
    return MenuScene::create();
}

bool MenuScene::init() {
    if (!Scene::init()) {
        return false;
    }
    
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    
    auto playButton = cocos2d::ui::Button::create("CloseNormal.png", "CloseSelected.png");
    if (playButton) {
        cocos2d::Size buttonSize = cocos2d::Size(100,60);
        addChild(playButton);
        playButton->setTitleText("Play");
        playButton->setTitleFontSize(30);
        playButton->setScale9Enabled(true);
        playButton->setCapInsets(cocos2d::Rect(10,10,50,50));
        playButton->setContentSize(buttonSize);
        playButton->setPosition(cocos2d::Vec2(visibleSize/2));
        playButton->addClickEventListener(CC_CALLBACK_1(MenuScene::menuCloseCallback, this));
    } else {
        cocos2d::log("Problem loading 'CloseNormal.png' or 'CloseSelected.png'");
        return false;
    }
    
    auto label = cocos2d::Label::createWithTTF("Fish attack!", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr) {
        cocos2d::log("Problem loading 'fonts/Marker Felt.ttf'");
    } else {
        label->setPosition(cocos2d::Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - label->getContentSize().height));
        this->addChild(label, 1);
    }
    
    return true;
}

void MenuScene::menuCloseCallback(cocos2d::Ref* pSender) {
    cocos2d::Director::getInstance()->replaceScene(GameScene::create());
}
