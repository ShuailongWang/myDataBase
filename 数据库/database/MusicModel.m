//
//  MusicModel.m
//  02
//
//  Created by admin on 17/4/7.
//  Copyright © 2017年 北京奥泰瑞格科技有限公司. All rights reserved.
//

#import "MusicModel.h"
#import "YYModel.h"

@implementation MusicModel

+(NSArray*)MusicModelWithData{
    NSString *path = [[NSBundle mainBundle] pathForResource:@"Type" ofType:@"json"];
    NSData *data = [NSData dataWithContentsOfFile:path];
    NSArray *array = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingAllowFragments error:nil];
    
    NSMutableArray *arrayM = [NSMutableArray array];
    for (NSDictionary *dict in array) {
        MusicModel *model = [MusicModel yy_modelWithDictionary:dict];
        
        [arrayM addObject:model];
    }
    
    return arrayM.copy;
}

@end
