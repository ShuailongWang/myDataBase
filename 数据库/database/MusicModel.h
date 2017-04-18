//
//  MusicModel.h
//  02
//
//  Created by admin on 17/4/7.
//  Copyright © 2017年 北京奥泰瑞格科技有限公司. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MusicModel : NSObject

@property (nonatomic, copy) NSString *playUrl64;
@property (nonatomic, copy) NSString *title;
@property (nonatomic, copy) NSString *coverSmall;
@property (nonatomic, copy) NSString *coverMiddle;
@property (nonatomic, copy) NSString *coverLarge;
@property (nonatomic, copy) NSString *nickname;
@property (nonatomic, copy) NSString *smallLogo;

+(NSArray*)MusicModelWithData;

@end
