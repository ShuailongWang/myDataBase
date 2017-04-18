//
//  DataBaseTool.h
//  database
//
//  Created by admin on 17/4/17.
//  Copyright © 2017年 北京奥泰瑞格科技有限公司. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DataBaseTool : NSObject


/**
 单例方法创建数据库, 
 如果使用shareDatabase创建,则默认在NSDocumentDirectory下创建JQFMDB.sqlite, 
 但只要使用这三个方法任意一个创建成功, 之后即可使用三个中任意一个方法获得同一个实例,参数可随意或nil
 
 dbName 数据库的名称 如: @"Users.sqlite", 如果dbName = nil,则默认dbName=@"DataBaseTool.sqlite"
 dbPath 数据库的路径, 如果dbPath = nil, 则路径默认为NSDocumentDirectory
 */
+ (instancetype)shareDatabase;
+ (instancetype)shareDatabase:(NSString *)dbName;
+ (instancetype)shareDatabase:(NSString *)dbName path:(NSString *)dbPath;


/**
 非单例方法创建数据库
 
 @param dbName 数据库的名称 如: @"DataBaseTool.sqlite"
 dbPath 数据库的路径, 如果dbPath = nil, 则路径默认为NSDocumentDirectory
 */
- (instancetype)initWithDBName:(NSString *)dbName;
- (instancetype)initWithDBName:(NSString *)dbName path:(NSString *)dbPath;

/**
 创建表 通过传入的model或dictionary(如果是字典注意类型要写对),虽然都可以,不过还是推荐以下都用model
 
 @param tableName 表的名称
 @param parameters 设置表的字段,可以传model(runtime自动生成字段)或字典(格式:@{@"name":@"TEXT"})
 @return 是否创建成功
 
 //
 [db createTable:@"user" dicOrModel:[Person class]];
 */
- (BOOL)createTable:(NSString *)tableName dicOrModel:(id)parameters;

/**
 创建表
 
 @param tableName 表的名称
 @param parameters 设置表的字段,可以传model(runtime自动生成字段)或字典(格式:@{@"name":@"TEXT"})
 @param nameArr 不允许model或dic里的属性/key生成表的字段,如:nameArr = @[@"name"],则不允许名为name的属性/key 生成表的字段
 */
- (BOOL)createTable:(NSString *)tableName dicOrModel:(id)parameters excludeName:(NSArray *)nameArr;


/**
 增加: 向表中插入数据
 
 @param tableName 表的名称
 @param parameters 要插入的数据,可以是model或dictionary(格式:@{@"name":@"小李"})
 @return 是否插入成功
 */
- (BOOL)insertTable:(NSString *)tableName dicOrModel:(id)parameters;


/**
 删除: 根据条件删除表中数据
 
 @param tableName 表的名称
 @param format 条件语句, 如:@"where name = '小李'"
 @return 是否删除成功
 
 //删除最后一条数据
 [db deleteTable:@"user" whereFormat:@"WHERE rowid = (SELECT max(rowid) FROM user)"];
 */
- (BOOL)deleteTable:(NSString *)tableName whereFormat:(NSString *)format, ...;

/**
 更改: 根据条件更改表中数据
 
 @param tableName 表的名称
 @param parameters 要更改的数据,可以是model或dictionary(格式:@{@"name":@"张三"})
 @param format 条件语句, 如:@"where name = '小李'"
 @return 是否更改成功
 
 //更新最后一条数据 name=testName , dicOrModel的参数也可以是name为testName的person
 [db updateTable:@"user" dicOrModel:@{@"name":@"testName"} whereFormat:@"WHERE rowid = (SELECT max(rowid) FROM user)"];
 //把表中所有的name改成godlike
 [db updateTable:@"user" dicOrModel:@{@"name":@"godlike"} whereFormat:nil];
 */
- (BOOL)updateTable:(NSString *)tableName dicOrModel:(id)parameters whereFormat:(NSString *)format, ...;

/**
 查找: 根据条件查找表中数据
 
 @param tableName 表的名称
 @param parameters 每条查找结果放入model(可以是[Person class] or @"Person" or Person实例)或dictionary中
 @param format 条件语句, 如:@"where name = '小李'", nil为全部,
 @return 将结果存入array,数组中的元素的类型为parameters的类型
 
 //查找name=cleanmonkey的数据
 [db lookupTable:@"user" dicOrModel:[Person class] whereFormat:@"where name = 'cleanmonkey'"];
 //查找所有数据
 [db lookupTable:@"user" dicOrModel:[Person class] whereFormat:nil];
 */
- (NSArray *)lookupTable:(NSString *)tableName dicOrModel:(id)parameters whereFormat:(NSString *)format, ...;

/**
 批量插入或更改
 
 @param dicOrModelArray 要insert/update数据的数组,也可以将model和dictionary混合装入array
 @return 返回的数组存储未插入成功的下标,数组中元素类型为NSNumber
 */
- (NSArray *)insertTable:(NSString *)tableName dicOrModelArray:(NSArray *)dicOrModelArray;

/** 删除表 */
- (BOOL)deleteTable:(NSString *)tableName;
/** 清空表 */
- (BOOL)deleteAllDataFromTable:(NSString *)tableName;
/** 是否存在表 */
- (BOOL)isExistTable:(NSString *)tableName;
/** 表中共有多少条数据 */
- (int)tableItemCount:(NSString *)tableName;
/** 返回表中的字段名 */
- (NSArray *)columnNameArray:(NSString *)tableName;






@end
