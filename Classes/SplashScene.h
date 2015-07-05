//
//  SplashScene.h
//  LightPlanter
//
//  Created by ToshiyukiAndo on 2015/02/01.
//
//

#ifndef __LightPlanter__SplashScene__
#define __LightPlanter__SplashScene__

#include <stdio.h>
#include "cocos2d.h"

class SplashScene :public cocos2d::Layer
{
protected:
    SplashScene();
    virtual ~SplashScene();
    bool init() override;
    
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(SplashScene);
    void myCallback(cocos2d::Ref* pSender);
};

#endif /* defined(__LightPlanter__SplashScene__) */
