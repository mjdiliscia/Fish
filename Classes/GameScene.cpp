//
//  GameScene.cpp
//  Fish
//
//  Created by Martin Javier Di Liscia on 25/7/18.
//

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Fish.h"
#include "EnemiesManager.h"
#include "MenuScene.h"

USING_NS_CC;

GameScene* GameScene::instance = nullptr;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

GameScene* GameScene::getInstance() {
    return instance;
}

bool GameScene::init()
{
    if (!Scene::init())
        return false;

	if (!Scene::initWithPhysics())
		return false;

    if (instance == nullptr)
        instance = this;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto sprite = Sprite::create("Fish.png");
    if (sprite == nullptr)
    {
        cocos2d::log("Problem loading 'Fish.png'");
    }
    else
    {
        auto fish = Fish::createWithSprite(sprite);
        fish->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        this->addChild(fish, 0);
    }

	auto enemiesManager = EnemiesManager::create();
	if (enemiesManager) {
		addChild(enemiesManager);
	}

    auto eventDispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
    contactListener = cocos2d::EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContact, this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;
}

GameScene::~GameScene() {
    if (instance == this)
        instance = nullptr;
    
    cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(contactListener);
}

bool GameScene::onContact(cocos2d::PhysicsContact& contact) {
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    for (auto& kv : contactListeners) {
        if (kv.first == nodeA)
            kv.second(nodeB);
        if (kv.first == nodeB)
            kv.second(nodeA);
    }
    
    return false;
}

void GameScene::addContactListener(Node* node, std::function<void(cocos2d::Node* node)> fnc) {
    contactListeners[node] = fnc;
}

void GameScene::removeContactListener(Node* node) {
    contactListeners.erase(node);
}

void GameScene::end() {
    cocos2d::Director::getInstance()->replaceScene(MenuScene::create());
}
