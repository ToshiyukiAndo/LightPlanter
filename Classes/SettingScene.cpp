//
//  SettingScene.cpp
//  LightPlanter
//
//  Created by ToshiyukiAndo on 2015/02/01.
//
//

#include "SettingScene.h"
#include "GameScene.h"
//#include "Live2D.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
//using namespace live2d;

SettingScene::SettingScene()
{
    init();
}

SettingScene::~SettingScene()
{
    
}

Scene* SettingScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SettingScene::create();
    scene->addChild(layer);
    return scene;
}

bool SettingScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    //    初期化
    auto director = Director::getInstance();
    
    auto winSize = director->getWinSize();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(SettingScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(SettingScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(SettingScene::onTouchEnded, this);
    
    //    this->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 255);
    
    auto Talk_button = MenuItemImage::create("images/SettingScene/BG_setting.png","images/SettingScene/BG_setting.png",[](Ref*sender){
        //ここが呼び出されます。
    });
    //メニューを作成
    auto _menu2 = Menu::create(Talk_button, NULL);
    _menu2->setPosition(Point(winSize.width / 2, winSize.height / 2));
    _menu2->setScale(1);
    this->addChild(_menu2);
    
    auto A_Slider = ControlSlider::create("extensions/sliderTrack.png","extensions/sliderProgress.png" ,"extensions/sliderThumb.png");
    A_Slider->setMinimumValue(0.0f); // Sets the min value of range
    A_Slider->setMaximumValue(50.0f); // Sets the max value of range
    A_Slider->setPosition(Vec2(winSize.width * .5f, winSize.height * 0.8f));
    A_Slider->setScale(2.0);
    A_Slider->setValue(25);
    addChild(A_Slider);
    
    auto B_Slider = ControlSlider::create("extensions/sliderTrack.png","extensions/sliderProgress.png" ,"extensions/sliderThumb.png");
    B_Slider->setMinimumValue(0.0f); // Sets the min value of range
    B_Slider->setMaximumValue(50.0f); // Sets the max value of range
    B_Slider->setPosition(Vec2(winSize.width * .5f, winSize.height * 0.6f));
    B_Slider->setScale(2.0);
    B_Slider->setValue(25);
    addChild(B_Slider);
    
    auto Back_button = MenuItemImage::create("images/SettingScene/back_button.png","images/SettingScene/back_setting.png",[](Ref*sender){
        auto scene = GameScene::createScene();
        auto transition = TransitionFade::create(0.5, scene, Color3B::WHITE);
        Director::getInstance()->replaceScene(transition);
    });
    //メニューを作成
    auto _menu = Menu::create(Back_button, NULL);
    _menu->setPosition(Point(winSize.width * 0.3, winSize.height * 0.1));
    _menu->setScale(0.24);
    this->addChild(_menu);
    
    
    return true;
    
    
    
    // モーダルレイヤ ここから
//    auto listener = EventListenerTouchOneByOne::create();
//    listener->setSwallowTouches(true);
//    listener->onTouchBegan = [](Touch *touch,Event*event)->bool{
//        return true;
//    };
//    auto dip = layer->getEventDispatcher();
//    dip->addEventListenerWithSceneGraphPriority(listener, this);
//    dip->setPriority(listener, kModalLayerPriority);
    // モーダルレイヤ ここまで
    
//    auto size = Director::getInstance()->getVisibleSize();
//    ui::ScrollView* sc = ui::ScrollView::create();
//    sc->setContentSize(Size(Vec2(size.width, size.height)));//たての長さ2倍
//    auto background = Sprite::create("images/SettingScene/BG_setting@2.png");
//    background->setPosition(Vec2(size.width/2, size.height/2));
//    sc->addChild(background);
//    sc->setBounceEnabled(true);
//    sc->setDirection(ui::ScrollView::Direction::VERTICAL);
//    sc->setInnerContainerSize(Size(size.width, sc->getContentSize().height));
//    
//    sc->setPosition(Vec2(0, 0));
//    
//    //メニュー表示
//    //ボタンを押した時にメソッドを呼び出す
//    auto a = MenuItemImage::create("button.png", "button.png", [](Ref*sender){});
//    //ボタンを押した時にラムダ式を呼び出す
//    auto b = MenuItemImage::create("button.png", "button.png", [](Ref*sender){});
//    
//    //メニューを作成
//    auto c = Menu::create(a, b,NULL);
//    c->setPosition(Point(size.width /2, size.height /2));
//    sc->addChild(c);
    //layer->addChild();
}


//--------------------------------Touch関連の関数----------------------------------------------//

bool SettingScene::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    Point location =pTouch->getLocation();
    log("Touch Started location(%f, %f)", location.x, location.y);
    
    return true;
}


void SettingScene::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    

}

void SettingScene::onTouchMoved(Touch* pTouch, Event* pEvent)
{

}
//------------------------------Touch関連ここまで------------------------------------------------//
















