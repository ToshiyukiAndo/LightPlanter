/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#include "SampleLive2DSprite.h"
#include "base/CCDirector.h"
#include "../include/util/UtSystem.h"

#include "../include/graphics/DrawProfileCocos2D.h"
#include "platform/CCFileUtils.h"

#include "../cocos2d/cocos/base/ccMacros.h"

using namespace live2d;
USING_NS_CC;
const char* TEXTURES[] ={
    "texture_00.png" ,
    NULL
} ;
SampleLive2DSprite::SampleLive2DSprite()
{
    //Live2D Sample
    const char* MODEL = "model.moc" ;
    
    unsigned char* buf;
    ssize_t bufSize;
    buf = FileUtils::getInstance()->getFileData(MODEL,"rb", &bufSize);
    
    live2DModel = Live2DModelOpenGL::loadModel( buf, bufSize ) ;
    free(buf);
    
    
    for( int i = 0 ; TEXTURES[i] != NULL ; i++ ){
        auto texture =Director::getInstance()->getTextureCache()->addImage(std::string(TEXTURES[i]));
        Texture2D::TexParams texParams = { GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };
        texture->setTexParameters(texParams);
        texture->generateMipmap();
        
        int glTexNo = texture->getName() ;
        
        live2DModel->setTexture( i , glTexNo ) ;// テクスチャとモデルを結びつける
        textures.push_back( texture ) ;
    }
    
    // Live2Dモデルはローカル座標で左上を原点にして(CanvasWidth、CanvasWidth)
    // のサイズになるため、以下のようにして調整してください。
    float w = Director::getInstance()->getWinSize().width;
    float h = Director::getInstance()->getWinSize().height;
    float scx = 1.8 / live2DModel->getCanvasWidth() ; //1.8
    float scy = -1.8 / live2DModel->getCanvasWidth() * (w/h); //1.8
    float x = -1 ;
    float y = 0.65 ;
    float matrix []= {
        scx , 0 , 0 , 0 ,
        0 , scy ,0 , 0 ,
        0 , 0 , 1 , 0 ,
        x , y , 0 , 1
    } ;
    
    live2DModel->setMatrix(matrix) ;// 位置を設定
    
    live2DModel->setPremultipliedAlpha( true );
}

SampleLive2DSprite::~SampleLive2DSprite()
{
    delete live2DModel;
    // テクスチャを解放
    Director::getInstance()->getTextureCache()->removeTextureForKey(std::string(TEXTURES[0]));
    Director::getInstance()->getTextureCache()->removeTextureForKey(std::string(TEXTURES[1]));
    Director::getInstance()->getTextureCache()->removeTextureForKey(std::string(TEXTURES[2]));
    
}


void SampleLive2DSprite::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    DrawNode::draw(renderer, transform, flags);
    
    
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(SampleLive2DSprite::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void SampleLive2DSprite::onDraw(const cocos2d::Mat4 &transform, uint32_t flags)
{
    kmGLPushMatrix();
    kmGLLoadMatrix(&transform);
    
    
    // モデルのパラメータを変更。動作確認用です。
    double t = (UtSystem::getUserTimeMSec()/1.0) * 2 * M_PI  ;// 1秒ごとに2π(1周期)増える
    double cycle=0.3;// パラメータが一周する時間(秒)
    double value=sin( t/cycle );// -1から1の間を周期ごとに変化する
    live2DModel->setParamFloat( "PARAM_ANGLE_X" , (float) (30 * value) ) ;// PARAM_ANGLE_Xのパラメータが[cycle]秒ごとに-30から30まで変化する
    
    
    // Live2Dの描画前と描画後に以下の関数を呼んでください
    // live2d::DrawProfileCocos2D::preDraw() ;
    // live2d::DrawProfileCocos2D::postDraw() ;
    // これはOpenGLの状態をもとに戻すための処理です。
    // これを行わない場合、Cocos2DかLive2Dどちらかで状態の不整合が起こります。
    live2d::DrawProfileCocos2D::preDraw();
    
    live2DModel->update() ;
    live2DModel->draw() ;
    
    live2d::DrawProfileCocos2D::postDraw() ;
    
    kmGLPopMatrix();
}

SampleLive2DSprite* SampleLive2DSprite::createDrawNode()
{
    SampleLive2DSprite *ret = new SampleLive2DSprite();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    
    
}
