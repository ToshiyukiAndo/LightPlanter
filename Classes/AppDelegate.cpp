#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SplashScene.h"
#include "GameScene.h"
//-----------------------------------//
//#include "../include/Live2D.h"
#include "LAppLive2DManager.h"
#ifdef L2D_TARGET_ANDROID_ES2
#include "graphics/DrawParam_OpenGLES2.h"
#endif

using namespace live2d;
//-----------------------------------//

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
    //--------------------------------------//
//    Live2D::dispose();
    LAppLive2DManager* Live2DMgr=LAppLive2DManager::getInstance();
    Live2DMgr->releaseInstance();
    //--------------------------------------//
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        
        //--------------------------------------//
        glview = GLView::create("Live2D Simple");
        //--------------------------------------//
        
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    //画面サイズの変更
    glview->setDesignResolutionSize(751, 1335, ResolutionPolicy::SHOW_ALL);
    
    //--------------------------------------//
//    Live2D::init();
    
//	LAppLive2DManager* Live2DMgr=LAppLive2DManager::getInstance();
    #ifdef L2D_TARGET_ANDROID_ES2
        char *exts = (char*)glGetString(GL_EXTENSIONS);
        if(strstr(exts, "GL_NV_shader_framebuffer_fetch ")){
            live2d::DrawParam_OpenGLES2::setExtShaderMode( true , true );
        }
    #endif
    //--------------------------------------//

    // create a scene. it's an autorelease object
    auto scene = SplashScene::createScene();

    
    //探索ファイルの追加
    FileUtils::getInstance()->addSearchPath("images");
    FileUtils::getInstance()->addSearchPath("images/SpliteScene");
    FileUtils::getInstance()->addSearchPath("images/GameScene");
    FileUtils::getInstance()->addSearchPath("images/hana2");
    FileUtils::getInstance()->addSearchPath("sounds");
    FileUtils::getInstance()->addSearchPath("extensions");
    
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
//     SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
//     SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
