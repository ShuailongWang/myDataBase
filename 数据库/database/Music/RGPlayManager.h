//
//  RGPlayManager.h
//  RGPsyCloud
//
//  Created by admin on 17/4/12.
//  Copyright © 2017年 北京奥泰瑞格科技有限公司. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

@protocol RGPlayManagerDelegate <NSObject>

/**
 获取播放信息

 @param curTime   当前时间
 @param totleTime 总时间
 @param progress  当前播放进度
 @param netValue  缓冲进度百分比
 */
-(void)getCurTiem:(NSString *)curTime Totle:(NSString *)totleTime Progress:(CGFloat)progress netValue:(NSTimeInterval)netValue;

/**
 播放结束之后, 如何操作由外部决定.
 */
-(void)endOfPlayAction;

@end

@interface RGPlayManager : NSObject

@property (nonatomic, strong) AVPlayer *player;
@property (weak, nonatomic)   id<RGPlayManagerDelegate> delegate;


+(instancetype)sharedPlayManager;

/**播放音乐*/
-(void)musicPlay;

/**暂停音乐*/
-(void)musicPause;


/**
 准备播放
 
 @param urlStr 音乐地址
 @param isOnline 是在线, 否本地
 */
-(void)musicPrePlay:(NSString*)urlStr isOnline:(BOOL)isOnline;

/**
 前进或者后退

 @param value silder的值
 */
-(void)seekToTimeWithValue:(CGFloat)value;

/**
 设置音量

 @param value silder的值
 */
- (void)setupCurrentVolume:(CGFloat)value;

@end
