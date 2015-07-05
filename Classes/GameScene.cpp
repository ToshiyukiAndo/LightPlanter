//
//  GameScene.cpp
//  LightPlanter
//
//  Created by ToshiyukiAndo on 2015/02/01.
//
//

#include "GameScene.h"
#include "SettingScene.h"
#include "getBrightness.h"
#include "SampleLive2DSprite.h"
#include "SaveData.h"
#include "LAppView.h"
#include "LAppLive2DManager.h"
#include "LAppDefine.h"
#include "Live2DFramework.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace live2d;

GameScene::GameScene()
{
    Live2D::init();
}

GameScene::~GameScene()
{
    Live2D::dispose();
}

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
//    初期化
    auto director = Director::getInstance();
    
    auto winSize = director->getWinSize();

//--------------------------時間取得-----------------------------//
    time_now = static_cast<long int>(time(NULL));
    time_now = time_now + 32400;
    //昼か夜かの判定
    if ((time_now % 86400) < 21600 || (time_now % 86400) > 64800) {
        flagDay = 1;
    }
    time_start = time_now;
    time_gomi = time_now;
//-------------------------------------------------------------//
    
//    Size visibleSize = Director::getInstance()->getVisibleSize();
    
//--------------------------背景の表示---------------------------//
    if (flagDay == 0) {//昼
        auto background = Sprite::create("images/GameScene/BG_day.png");
        background->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
        this->addChild(background);
    }else{//夜
        auto background = Sprite::create("images/GameScene/BG_night.png");
        background->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
        this->addChild(background);
    }
//--------------------------------------------------------------//
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    
    this->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 101);
    

    Menu2();//水、エサ
    Menu3();//話す
    Menu4();//掃除、設定
    Menu1();//Yes, No.
    SpriteSet();
    ShowCharactor();//Live2Dのキャラクター表示
//    auto* pLive2DSprite = LAppView::createDrawNode();
//    this->addChild(pLive2DSprite);
    
//1---------------------------実験領域---------------------------------------//
    
//1---------------------------ココマデ---------------------------------------//
    this->scheduleUpdate();//アップデート関数1fごと
    this->schedule(schedule_selector(GameScene::update_1), 1.0f);//アップデート一秒ごと
    
    
    return true;
}
//2-------------------------------------------------------------------------//

//2-------------------------------------------------------------------------//


void GameScene::update(float delta)
{
    double brightness = getBrightness();
//    log("%f", brightness);
    
    SkyControll(brightness);
    water_value = WaterChange(-0.002);
    
    //ゲームオーバー判定
    if (water_value < -100) {
        GameOver();
    }
    
}

void GameScene::update_1(float delta)
{
    time_now = static_cast<long int>(time(NULL));
    time_now = time_now + 32400;
    //昼か夜かの判定
    if ((time_now % 86400) < 21600 || (time_now % 86400) > 64800) {
        flagDay = 1;
    }
    Gomi_Add();
}

void GameScene::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/BGM_01.mp3", true);
}

bool GameScene::Menu1()
{
    //メニュー表示
    if (flagButton == 1) {
        //ボタンを押した時にメソッドを呼び出す
        auto mItem1 = MenuItemImage::create("images/GameScene/Yes_button.png","images/GameScene/Yes_button_pushed.png",[](Ref*sender){
            //ここが呼び出されます。
        });
        //ボタンを押した時にラムダ式を呼び出す
        auto mItem2 = MenuItemImage::create("images/GameScene/No_button.png","images/GameScene/No_button_pushed.png",[](Ref*sender){
            //ここが呼び出されます。
        });
        
        //メニューを作成
        auto _menu2 = Menu::create(mItem1,mItem2,NULL);
        _menu2->setPosition(Point(90, -290));
        _menu2->setAnchorPoint(Vec2(0.5, 0.5));
        _menu2->setScale(0.24);
        _menu2->alignItemsHorizontallyWithPadding(1600);
        this->addChild(_menu2);
    }else{
        //ボタンを押した時にメソッドを呼び出す
        auto mItem1 =
        MenuItemImage::create("images/GameScene/Tile_button.png","images/GameScene/Tile_button.png",[](Ref*sender){
        //ここが呼び出されます。
        });
        //ボタンを押した時にラムダ式を呼び出す
        auto mItem2 =
        MenuItemImage::create("images/GameScene/Tile_button.png","images/GameScene/Tile_button.png",[](Ref*sender){
        });
    
        //メニューを作成
        auto _menu2 = Menu::create(mItem1,mItem2,NULL);
        _menu2->setPosition(Point(90, -290));
        _menu2->setAnchorPoint(Vec2(0.5, 0.5));
        _menu2->setScale(0.24);
        _menu2->alignItemsHorizontallyWithPadding(1600);
        this->addChild(_menu2);
    }
    
    return true;
}

bool GameScene::Menu2()
{
    //メニュー表示
    //ボタンを押した時にメソッドを呼び出す
    Water_button =
    MenuItemImage::create("images/GameScene/water_button2.png", "images/GameScene/water_button_pushed2.png", CC_CALLBACK_1(GameScene::JoroControll, this));
    //ボタンを押した時にラムダ式を呼び出す
    Food_button =
    MenuItemImage::create("images/GameScene/food_button2.png","images/GameScene/food_button_pushed2.png",[&](Ref*sender){
        flagEsa = 1;
        esa0->setPosition(Vec2(600, 450));
        esa0->setOpacity(255);
        esa0->setVisible(true);
        
    });
    
    //メニューを作成
    auto _menu2 = Menu::create(Water_button, Food_button, NULL);
    _menu2->setPosition(Point(386, 377));
    _menu2->setAnchorPoint(Vec2(0.5, 0.5));
    _menu2->setScale(1.02);
    _menu2->alignItemsHorizontallyWithPadding(10);
    this->addChild(_menu2);
    
    
    return true;
    
    
}

bool GameScene::Menu3()
{
    //メニュー表示
    //ボタンを押した時にメソッドを呼び出す
    Talk_button = MenuItemImage::create("images/GameScene/talk_button.png","images/GameScene/talk_button_pushed.png",[](Ref*sender){
    });
    
    //メニューを作成
    auto _menu2 = Menu::create(Talk_button, NULL);
    _menu2->setPosition(Point(90, -290));
    _menu2->setAnchorPoint(Vec2(0.5, 0.5));
    _menu2->setScale(0.24);
    this->addChild(_menu2);
    
    return true;
}

bool GameScene::Menu4()
{
    //メニュー表示
    //ボタンを押した時にメソッドを呼び出す
    Clean_button =
    MenuItemImage::create("images/GameScene/clean_button.png","images/GameScene/clean_button_pushed.png",[&](Ref*sender){
        if (flagGomi == 0) {
            flagGomi = 1;
            Water_button->setEnabled(false);
            Talk_button->setEnabled(false);
            Food_button->setEnabled(false);
            Setting_button->setEnabled(false);
            houki->setVisible(true);
        }else{
            flagGomi = 0;
            houki->setVisible(false);
            Water_button->setEnabled(true);
            Talk_button->setEnabled(true);
            Food_button->setEnabled(true);
            Setting_button->setEnabled(true);
        }
    });
    
    //ボタンを押した時にラムダ式を呼び出す
    Setting_button =
    MenuItemImage::create("images/GameScene/setting_button.png","images/GameScene/setting_button_pushed.png",[&](Ref*sender){
        
        if (flagSetting == 0) {
            CustomLayer *layer = CustomLayer::create();
            this->addChild(layer, 4);
            layer->setTag(200);
            flagSetting = 1;
        }else{
            auto target = (CustomLayer*)this->getChildByTag(200);
            target->removeFromParentAndCleanup(true);
            flagSetting = 0;
        }
    });
    
    //メニューを作成
    auto _menu2 = Menu::create( Clean_button, Setting_button, NULL);
    _menu2->setPosition(Point(90, -435));
    _menu2->setAnchorPoint(Vec2(0.5, 0.5));
    _menu2->setScale(0.240);
    _menu2->alignItemsHorizontallyWithPadding(50);
    this->addChild(_menu2);
    
    return true;
}

bool GameScene::SpriteSet()
{
    auto director = Director::getInstance();
    auto winSize = director->getWinSize();

    
    //太陽の位置変更
    sun1->setPosition(Vec2(600,1200));
    sun1->setScale(0.24, 0.24);
    sun2->setPosition(Vec2(555,1155));
    sun2->setScale(0.24, 0.24);
    sun3->setPosition(Vec2(538,1138));
    sun3->setScale(0.24, 0.24);
    
    //月の位置変更
    moon1->setPosition(Vec2(600, 1200));
    moon2->setPosition(Vec2(arc4random()%100 + 450, arc4random()%100 + 1050));
    moon3->setPosition(Vec2(arc4random()%100 + 600, arc4random()%100 + 1000));
    moon4->setPosition(Vec2(arc4random()%100 + 400, arc4random()%50 + 1150));
    moon2->setScale(0.7, 0.7);
    moon3->setScale(0.6, 0.6);
    moon4->setScale(0.6, 0.6);
    
    //雲の初期位置設定
    for (int i = 0; i < 3; i++) {
        clouds[i] = cocos2d::Sprite::create("images/GameScene/cloud.png");
        int randomNum0 = arc4random()%600;//x
        int randomNum1 = arc4random()%200;//y
        clouds[i]->setPosition(Vec2(randomNum0, randomNum1 + 1000));
        this->addChild(clouds[i]);
        clouds[i]->setOpacity(0);
    }
    
    //水のスライダーの位置設定
    Water_Slider = ControlSlider::create("images/GameScene/water_.png","images/GameScene/water__.png" ,"images/GameScene/water___.png");
    Water_Slider->setAnchorPoint(Vec2(0.5f, 1.0f));
    Water_Slider->setMinimumValue(0.0f); // Sets the min value of range
    Water_Slider->setMaximumValue(51.0f); // Sets the max value of range
    Water_Slider->setPosition(Vec2(winSize.width * .5f, winSize.height * .345f));
    Water_Slider->setScale(1.05, 0.8);
    addChild(Water_Slider);
    
    
    
    //addChild
    this->addChild(sun1);
    this->addChild(sun2);
    this->addChild(sun3);
    this->addChild(moon1);
    this->addChild(moon2);
    this->addChild(moon3);
    this->addChild(moon4);
    sun1->setOpacity(0);
    sun2->setOpacity(0);
    sun3->setOpacity(0);
    moon1->setOpacity(0);
    moon2->setOpacity(0);
    moon3->setOpacity(0);
    moon4->setOpacity(0);
    
    if (flagDay == 1) {
        sun1->setVisible(false);
        sun2->setVisible(false);
        sun3->setVisible(false);
        moon1->setVisible(true);
        moon2->setVisible(true);
        moon3->setVisible(true);
        moon4->setVisible(true);

    }else{
        moon1->setVisible(false);
        moon2->setVisible(false);
        moon3->setVisible(false);
        moon4->setVisible(false);
        sun1->setVisible(true);
        sun2->setVisible(true);
        sun3->setVisible(true);
    }
    
    Joro_Sprite0 = cocos2d::Sprite::create("images/GameScene/joro1.png");
    Joro_Sprite1 = cocos2d::Sprite::create("images/GameScene/joro2.png");
    Joro_Sprite0->setScale(1.2);
    Joro_Sprite1->setScale(1.2);
    this->addChild(Joro_Sprite0, 3);//ジョウロの優先度3
    this->addChild(Joro_Sprite1, 3);
    Joro_Sprite0->setVisible(false);
    Joro_Sprite1->setVisible(false);
    
    esa0 = cocos2d::Sprite::create("images/GameScene/esa0.png");
    this->addChild(esa0, 3);
    esa0->setVisible(false);
    
    Gomi_SpriteSet();
    
    return true;
}

//空の変化全般
bool GameScene::SkyControll(double status)
{
    auto director = Director::getInstance();
    auto winSize = director->getWinSize();
    
    double status0 = status;
    double status1 = status;
    if (status < 0.4) {
    }else if(0.4 <= status && status <= 0.6){
        status = status-0.4;
        status = status * 5 * 255;
        sun1->setOpacity(status);
        sun2->setOpacity(0);
        sun3->setOpacity(0);
        moon1->setOpacity(status);
    }else if(0.6 < status && status <= 0.8){
        status = status-0.6;
        status = status * 5 * 255;
        sun1->setOpacity(255);
        sun2->setOpacity(0);
        sun3->setOpacity(status);
        moon2->setOpacity(status);
    }else if (0.8 < status){
        status = status-0.8;
        status = status * 5 * 255;
        sun1->setOpacity(255);
        sun2->setOpacity(status);
        sun3->setOpacity(255);
        moon3->setOpacity(status);
        moon4->setOpacity(status);
    }
    
    if (0.2 <= status0 && status0 <= 0.5) {
        status0 = status0-0.2;
        status0 = status0 * 3.33;
        status0 = 1 - status0;
        status0 = status0 * 255;
        clouds[0]->setOpacity(status0);
        clouds[1]->setOpacity(status0 * 0.7);
        clouds[2]->setOpacity(status0 * 0.3);
        
        //雲の移動
        for (int i = 0; i < 3; i++) {
            int randomNum1 = arc4random()%300 + 1000;
            clouds[i]->setPosition(Point(clouds[i]->getPositionX() - (1 + i * 0.5 - status1), clouds[i]->getPositionY()));
            if (clouds[i]->getPositionX() < -160) {
                clouds[i]->setPosition(Point( 1000, randomNum1));
            }
        }
        
    }
    
    return true;
}

//---------------------------Live2Dキャラクター-----------------------------//
//Live2Dのキャラクター表示
void GameScene::ShowCharactor()
{
    auto* pLive2DSprite = LAppView::createDrawNode();
    this->addChild(pLive2DSprite, 1, 0);
}


void GameScene::DeleteCharactor()
{
    LAppLive2DManager::releaseInstance();
    live2d::Live2D::dispose();
}


//----------------------------ジョウロ--------------------------------------//

void GameScene::JoroControll(Ref* sender)
{
    //ジョウロボタンを押した時のコールバック関数
    flagJoro = 1;
    Water_button->setEnabled(false);
    Joro_Sprite0->setPosition(Point(165, 400));
    Joro_Sprite1->setPosition(Point(165, 400));
    Joro_Sprite0->setVisible(true);
    
}

//引数に水の量、この中でスライダーの変化、水の量の変化を記録する。
float GameScene::WaterChange(float w_value_change)
{
    float w_value_local;
    w_value_local = water_value + w_value_change;
    
    Water_Slider->setValue(w_value_local);
    
    return w_value_local;
}

void GameScene::Joro_Action()
{
    //ジョウロの移動、アクション
    ActionInterval *action1, *action2, *action3;
    action1 = CCRotateTo::create(1.0f, 30);
    action2 = CCRotateTo::create(3.0f, 30);
    action3 = CCRotateTo::create(0.5f, 0);

    cocos2d::CallFunc *compCallFunc00 = CallFunc::create([this](){
        flagJoro = 2;
    });
    
    cocos2d::CallFunc *compCallFunc0 = CallFunc::create([this](){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/water_01.mp3");
        Joro_Sprite0->setVisible(false);
        Joro_Sprite1->setVisible(true);
    });
        
    cocos2d::CallFunc *compCallFunc1 = CallFunc::create([this](){
        Joro_Sprite1->setVisible(false);
        Joro_Sprite0->setVisible(true);
        
        water_value += 20;
    });
    
    cocos2d::CallFunc *compCallFunc2 = CallFunc::create([this](){
        Joro_Sprite0->setVisible(false);
        Water_button->setEnabled(true);
        flagJoro = 0;
    });
        
    Sequence* Joro_Rotate = Sequence::create( compCallFunc00, action1, compCallFunc0, action2, compCallFunc1, action3, compCallFunc2, NULL);
    Joro_Sprite1->setRotation(30);
    Joro_Sprite0->runAction(Joro_Rotate);
    

}
//-------------------------------エサ------------------------------------------------------//
void GameScene::Esa_Action()
{
    //エサの移動、アクション
    ActionInterval *action1, *action2, *action3;
    action1 = CCScaleBy::create(0.5f, 0.7);
    action2 = CCDelayTime::create(0.8f);
    action3 = CCFadeOut::create(0.5);
    
    cocos2d::CallFunc *compCallFunc00 = CallFunc::create([this](){
        
    });

    cocos2d::CallFunc *compCallFunc01 = CallFunc::create([this](){
        flagEsa = 0;
        esa0->setVisible(false);
        esa0->setScale(1.0);
    });
    
    Sequence* Esa_Eat = Sequence::create( compCallFunc00, action1, action2, action1, action2, action3, compCallFunc01,NULL);
    esa0->runAction(Esa_Eat);
}

//--------------------------------ゴミ------------------------------------------------------//

void GameScene::Gomi_SpriteSet()
{
    for (int i = 0; i < 100; i++ ) {
        int n = arc4random()%4;
        if (n == 0) {
            gomi[i] = cocos2d::Sprite::create("images/GameScene/gomi/gomi0.png");
        }else if (n == 1){
            gomi[i] = cocos2d::Sprite::create("images/GameScene/gomi/gomi1.png");
        }else if (n == 2){
            gomi[i] = cocos2d::Sprite::create("images/GameScene/gomi/gomi2.png");
        }else{
            gomi[i] = cocos2d::Sprite::create("images/GameScene/gomi/gomi3.png");
        }
        
        gomi[i]->setPosition(Vec2(arc4random()%751, arc4random()%150+460));
        int a = arc4random()%3;
        addChild(gomi[i], a);
        gomi[i]->setTag(i);
        gomi[i]->setVisible(false);
    }
    
    houki = cocos2d::Sprite::create("houki.png");
    this->addChild(houki, 3);
    houki->setVisible(false);
    houki->setPosition(100, 100);
    houki->setScale(.4, .4);
    
}

void GameScene::Gomi_Add()
{
    if ((time_now - time_gomi) > arc4random()%3600) {
        if (Gomi_num == 99) {
            GameOver();
        }
        for (int i = 0; i < 100;  i++) {
            int n = arc4random()%100;
            if (gomi[n]->isVisible() == false) {
                gomi[n]->setVisible(true);
                break;
            }
        }
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/gomi_02.mp3");
        Gomi_num++;
        time_gomi = time_now;
        log("Gomi_num = %d", Gomi_num);
    }
}

void GameScene::Gomi_Remove(int target)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/gomi_01.mp3");
    auto sprite = this->getChildByTag(target);
    sprite->setVisible(false);
    Gomi_num--;
}

//------------------------------------Touch関連の関数--------------------------------------------//

bool GameScene::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    Point location =pTouch->getLocation();
    log("Touch Started location(%f, %f)", location.x, location.y);
    
    //タッチしたゴミのタグの取得
    if (flagGomi == 1) {
        for (int i = 0; i < 100; i++) {
            Rect targetBox = gomi[i]->getBoundingBox();
            if (targetBox.containsPoint(location)) {
                if (gomi[i]->isVisible()) {
                    log("Sprite's tag is %d", gomi[i]->getTag());
                    Gomi_Remove(i);
                }
            }
        }
    }
    
    if(flagJoro == 1){
        Joro_Sprite0->setPosition(Point(location.x, location.y));
        Joro_Sprite1->setPosition(Point(location.x, location.y));
    }
    if (flagEsa == 1) {
        esa0->setPosition(Point(location.x, location.y));
    }
    if (flagGomi == 1) {
        houki->setPosition(Point(location.x, location.y));
    }
    
    return true;
}

void GameScene::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    if (flagJoro == 1) {
        Joro_Action();
    }
    if (flagEsa == 1) {
        Esa_Action();
    }
    if (flagGomi == 1){
    }
}

void GameScene::onTouchMoved(Touch* pTouch, Event* pEvent)
{
    Point location =pTouch->getLocation();
    if(flagJoro == 1){
        Joro_Sprite0->setPosition(Point(location.x, location.y));
        Joro_Sprite1->setPosition(Point(location.x, location.y));
    }
    if (flagEsa == 1) {
        esa0->setPosition(Point(location.x, location.y));
    }
    if (flagGomi == 1) {
        houki->setPosition(Point(location.x, location.y));
    }
}

//------------------------------------Touch関連ここまで------------------------------------------//

//------------------------------------ゲームオーバーの定義----------------------------------------//
void GameScene::GameOver()
{
    log("GameOver!");
}


//---------------------------------------------------------------------------------------------//

//------------------------------------設定レイヤーの作成------------------------------------------//
bool CustomLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
 
    //    初期化
    auto director = Director::getInstance();
    
    auto winSize = director->getWinSize();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    
    //    this->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 255);
    
    auto Talk_button = MenuItemImage::create("images/SettingScene/BG_setting.png","images/SettingScene/BG_setting.png",[](Ref*sender){
        //ここが呼び出されます。
    });
    //メニューを作成
    auto _menu2 = Menu::create(Talk_button, NULL);
    _menu2->setPosition(Point(winSize.width / 2 - 80, winSize.height / 2-100));
    _menu2->setScale(0.8);
    this->addChild(_menu2);
    
    auto A_Slider = ControlSlider::create("extensions/sliderTrack.png","extensions/sliderProgress.png" ,"extensions/sliderThumb.png");
    A_Slider->setMinimumValue(0.0f); // Sets the min value of range
    A_Slider->setMaximumValue(50.0f); // Sets the max value of range
    A_Slider->setPosition(Vec2(winSize.width * .5f, winSize.height * 0.77f));
    A_Slider->setScale(1.5);
    A_Slider->setValue(25);
    addChild(A_Slider);
    
    auto B_Slider = ControlSlider::create("extensions/sliderTrack.png","extensions/sliderProgress.png" ,"extensions/sliderThumb.png");
    B_Slider->setMinimumValue(0.0f); // Sets the min value of range
    B_Slider->setMaximumValue(50.0f); // Sets the max value of range
    B_Slider->setPosition(Vec2(winSize.width * .5f, winSize.height * 0.6f));
    B_Slider->setScale(1.5);
    B_Slider->setValue(25);
    addChild(B_Slider);
    
    
    return true;
}