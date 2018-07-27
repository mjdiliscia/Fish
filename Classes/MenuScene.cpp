//
//  MenuScene.cpp
//  Fish
//
//  Created by Martin Javier Di Liscia on 26/7/18.
//

#include "MenuScene.h"
#include "GameScene.h"
#include "ui/UIButton.h"

USING_NS_CC;

Scene* MenuScene::createScene() {
    return MenuScene::create();
}

bool MenuScene::init() {
    if (!Scene::init()) {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    auto background = Sprite::create("menuBackground.png");
    if (background == nullptr) {
        log("Problem loading 'menuBackground.png'");
    } else {
        background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        this->addChild(background, 0);
    }
    
    auto playButton = ui::Button::create("buttonRed.png", "buttonRedPressed.png");
    if (playButton) {
        Size buttonSize = Size(100,60);
        addChild(playButton);
        playButton->setTitleText("Play");
        playButton->setTitleFontSize(30);
        playButton->setScale9Enabled(true);
        playButton->setCapInsets(Rect(10,10,50,50));
        playButton->setContentSize(buttonSize);
        playButton->setPosition(Vec2(visibleSize/2));
        playButton->addClickEventListener(CC_CALLBACK_1(MenuScene::menuCloseCallback, this));
    } else {
        log("Problem loading 'buttonRed.png' or 'buttonRedPressed.png'");
        return false;
    }
    
    auto label = Label::createWithTTF("Fish attack!", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr) {
        log("Problem loading 'fonts/Marker Felt.ttf'");
    } else {
        label->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - label->getContentSize().height));
        this->addChild(label, 1);
    }
    
    return true;
}

void MenuScene::menuCloseCallback(Ref* pSender) {
    Director::getInstance()->replaceScene(GameScene::create());
}
