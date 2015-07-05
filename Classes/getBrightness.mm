//
//  getBrightness.m
//  HelloCocos
//
//  Created by 植木華織 on 2015/01/29.
//
//

#import "getBrightness.h"
#import "cocos2d.h"

float brightness;
int count=1;

double getBrightness()
{
    
    if(count == 1){ //初期設定値
        [[UIScreen mainScreen] setBrightness:0.300000]; //0~1の間(0.5が室内蛍光灯の光量と同程度)
        brightness = [UIScreen mainScreen].brightness;
    }else{  //その他の場合
        brightness = [UIScreen mainScreen].brightness;
    }
    ++count;
    
    
    return brightness;
}
