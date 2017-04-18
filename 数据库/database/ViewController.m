//
//  ViewController.m
//  database
//
//  Created by admin on 17/4/17.
//  Copyright © 2017年 北京奥泰瑞格科技有限公司. All rights reserved.
//

#import "ViewController.h"
#import "RGPlayManager.h"
#import "DataBaseTool.h"
#import "MusicModel.h"

@interface ViewController ()<RGPlayManagerDelegate, UITableViewDelegate, UITableViewDataSource>

@property (nonatomic, strong) RGPlayManager *playManager;
@property (nonatomic, strong) DataBaseTool *dataTool;
@property (nonatomic, strong) UITableView *myTableView;
@property (nonatomic, strong) NSArray *musicArr;


@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    [self setupUI];
}

-(void)setupUI{
    self.playManager = [RGPlayManager sharedPlayManager];
    self.playManager.delegate = self;

    self.dataTool = [DataBaseTool shareDatabase];
    
    //创建表
    if (![self.dataTool isExistTable:@"music"]) {
        [self.dataTool createTable:@"music" dicOrModel:[MusicModel class]];
    }
    
    //清空表
    [self.dataTool deleteAllDataFromTable:@"music"];
    //插入
    [self.dataTool insertTable:@"music" dicOrModelArray:[MusicModel MusicModelWithData]];
    
    //搜索
    self.musicArr = [self.dataTool lookupTable:@"music" dicOrModel:[MusicModel class] whereFormat:nil];
    
    if (nil == _myTableView) {
        _myTableView = [[UITableView alloc]initWithFrame:self.view.bounds style:UITableViewStylePlain];
        _myTableView.delegate = self;
        _myTableView.dataSource = self;
        [self.view addSubview:_myTableView];
    }
}
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return self.musicArr.count;
}
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cellID"];
    if (nil == cell) {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"cellID"];
    }
    MusicModel *model = self.musicArr[indexPath.row];
    cell.textLabel.text = model.title;
    
    return cell;
}
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    MusicModel *model = self.musicArr[indexPath.row];
    
    [self.playManager musicPrePlay:model.playUrl64 isOnline:YES];
}




#pragma mark - RGPlayManagerDelegate
-(void)getCurTiem:(NSString *)curTime Totle:(NSString *)totleTime Progress:(CGFloat)progress netValue:(NSTimeInterval)netValue{
    NSLog(@"%f", progress);
}

/**
 播放结束之后, 如何操作由外部决定.
 */
-(void)endOfPlayAction{

}



@end
