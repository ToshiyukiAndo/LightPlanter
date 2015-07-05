//
//  SettinghScene.h
//  LightPlanter
//
//  Created by ToshiyukiAndo on 2015/02/01.
//
//

#ifndef __SettingScene__SplashScene__
#define __SettingScene__SplashScene__

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace ui;

class SettingScene :public cocos2d::Layer
{
protected:
    SettingScene();
    virtual ~SettingScene();
    bool init() override;
    
    
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(SettingScene);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    
    
};


#endif /* defined(__LightPlanter__SettingScene__) */
