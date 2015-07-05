//
//  GameScene.h
//  LightPlanter
//
//  Created by ToshiyukiAndo on 2015/02/01.
//
//

#ifndef __LightPlanter__GameScene__
#define __LightPlanter__GameScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SampleLive2DSprite.h"
#include "LAppView.h"
#include "LAppLive2DManager.h"
#include "LAppDefine.h"
#include "Live2DFramework.h"
#include "time.h"


#define ABC "abc"

class GameScene :public cocos2d::Layer
{
protected:
    virtual ~GameScene();
    bool init() override;
//-----------画面の設定---------------//
    bool Menu1();//○×のメニュー
    bool Menu2();
    bool Menu3();
    bool Menu4();
    bool SkyControll(double);//空の変化の管理
    bool SpriteSet();//画像の初期設定
    int flagDay = 0;//昼0, 夜1
    int flagButton = 0;//0でタイル 1でまるばつ
//-----------更新系の関数---------------//
    void update(float delta);//更新1フレームごと
    void update_1(float delta);//更新一秒ごと
    
//-----------音関数---------------------//
    void onEnterTransitionDidFinish() override;//BGM用関数
    
//------------ジョウロ関数---------------//
    int flagJoro = 0;
    float water_value = 50;
    void Joro_Action();
    void JoroControll(Ref* sender);
//------------ゴミ関数------------------//
    int flagGomi = 0;
    int Gomi_num = 0;
    void Gomi_Add();
    void Gomi_SpriteSet();
    void Gomi_Remove(int target);
    long int time_gomi;//ゴミ時間
//-------------エサ関数------------------//
    int flagEsa = 0;
    void Esa_Action();
    
//------------キャラクター関数-----------//
    void ShowCharactor();
    void DeleteCharactor();
//------------ゲームオーバー関数----------//
    void GameOver();
    
//-----------------------------------------------------------//
    int flagSetting = 0;
//-----------------------------------------------------------//
    
    cocos2d::MenuItemImage* Water_button;
    cocos2d::MenuItemImage* Clean_button;
    cocos2d::MenuItemImage* Food_button;
    cocos2d::MenuItemImage* Talk_button;
    cocos2d::MenuItemImage* Setting_button;
    
    cocos2d::Sprite* sun1 = cocos2d::Sprite::create("images/GameScene/sun1.png");
    cocos2d::Sprite* sun2 = cocos2d::Sprite::create("images/GameScene/sun2.png");
    cocos2d::Sprite* sun3 = cocos2d::Sprite::create("images/GameScene/sun3.png");
    cocos2d::Sprite* moon1 = cocos2d::Sprite::create("images/GameScene/moon1.png");
    cocos2d::Sprite* moon2 = cocos2d::Sprite::create("images/GameScene/moon2.png");
    cocos2d::Sprite* moon3 = cocos2d::Sprite::create("images/GameScene/moon2.png");
    cocos2d::Sprite* moon4 = cocos2d::Sprite::create("images/GameScene/moon2.png");
    
    
    cocos2d::Sprite* clouds[3];
    cocos2d::Sprite* Joro_Sprite0;
    cocos2d::Sprite* Joro_Sprite1;
    cocos2d::Sprite* gomi[100];
    cocos2d::Sprite* esa0;
    cocos2d::Sprite* houki;
    
    cocos2d::extension::ControlSlider *Water_Slider;
    
    SampleLive2DSprite *pLive2DSprite;
    
//-----------------時間---------------------------------------------//
    long int time_start;//始めた時間
    long int time_now;//現在の時間
    
public:
    GameScene();
    static cocos2d::Scene* createScene();
    CREATE_FUNC(GameScene);
    
    //flagとかの管理
//    int flagDay = 0;//昼0, 夜1

//---------------Touch関数------------------------------------------//
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
//-----------------------------------------------------------------//
    

    float WaterChange(float w_value);

    
    cocos2d::EventListenerTouchOneByOne *EventListener;

    
};

class CustomLayer : public cocos2d::Layer{
    
public:
    virtual bool init();
    
    CREATE_FUNC(CustomLayer);
};

#endif /* defined(__LightPlanter__GameScene__) */
