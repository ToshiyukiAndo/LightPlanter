//
//  SplashScene.cpp
//  LightPlanter
//
//  Created by ToshiyukiAndo on 2015/02/01.
//
//

#include "SplashScene.h"
#include "GameScene.h"

USING_NS_CC;

SplashScene::SplashScene()
{
    
}

SplashScene::~SplashScene()
{
    
}

Scene* SplashScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SplashScene::create();
    scene->addChild(layer);
    return scene;
}

bool SplashScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    //初期化
    auto director = Director::getInstance();
    
    auto winSize = director->getWinSize();
    
    auto background = Sprite::create("images/SplashScene/LightPlanter.png");
    background->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(background);
    
    auto touch_to_start = Sprite::create("images/SplashScene/Touch_to_Start.png");
    touch_to_start->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    auto blink = Sequence::create(FadeTo::create(0.5, 127), FadeTo::create(0.5, 255), NULL);
    touch_to_start->runAction(RepeatForever::create(blink));
    this->addChild(touch_to_start);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* touch, Event* event){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/touch_to_start.mp3");
        this->getEventDispatcher()->removeAllEventListeners();
        auto delay = DelayTime::create(0.5);
        auto startGame = CallFunc::create([]{
            auto scene = GameScene::createScene();
            auto transition = TransitionFade::create(0.5, scene, Color3B::WHITE);
            Director::getInstance()->replaceScene(transition);
        });
        this->runAction(Sequence::create(delay,startGame, NULL));
        return true;
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}



