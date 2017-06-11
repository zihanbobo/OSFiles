//
//  BaseViewController.h
//  FileDownloader
//
//  Created by Ossey on 2017/6/10.
//  Copyright © 2017年 Ossey. All rights reserved.
//

#import "UITableView+NoDataPlaceholderExtend.h"

@interface BaseViewController : UIViewController

@property (nonatomic, strong) UITableView *tableView;

- (BOOL)shouldShowNoDataPlaceholder;

- (UIImage *)noDataPlaceholderImageWithIsLoading:(BOOL)isLoading;
- (NSAttributedString *)reloadbuttonTitleAttributedStringForNoDataPlaceholder;
- (NSAttributedString *)detailAttributedStringForNoDataPlaceholder;
- (NSAttributedString *)titleAttributedStringForNoDataPlaceholder;
@end
