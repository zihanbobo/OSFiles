//
//  OSDownloader.h
//  DownloaderManager
//
//  Created by Ossey on 2017/6/4.
//  Copyright © 2017年 Ossey. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "OSDownloadProgress.h"
#import "OSDownloadProtocol.h"

NS_ASSUME_NONNULL_BEGIN

#ifdef DEBUG
#define DLog(fmt, ...) NSLog((@"<%s : %d> %s  " fmt), [[[NSString stringWithUTF8String:__FILE__] lastPathComponent]   UTF8String], __LINE__, __PRETTY_FUNCTION__,  ##__VA_ARGS__);
#else
#define DLog(...)
#endif


FOUNDATION_EXTERN NSString * const OSDownloaderFolderNameKey;

@interface OSDownloader : NSObject

@property (nonatomic, assign) NSInteger maxConcurrentDownloads;
/// 完成一个后台任务时回调
@property (nonatomic, copy) void (^backgroundSessionCompletionHandler)();
/// 下载的任务(包括正在下载的、暂停的) key 为 taskIdentifier， value 为 OSDownloadOperation, 下载完成后会从此集合中移除
@property (nonatomic, strong) NSMutableDictionary<NSNumber *, id<OSDownloadOperationProtocol>> *activeDownloadsDictionary;
/// 等待下载的任务数组 每个元素 字典 为一个等待的任务
@property (nonatomic, strong) NSMutableArray<NSDictionary <NSString *, NSObject *> *> *waitingDownloadArray;
@property (nonatomic, weak) id<OSDownloaderDelegate> downloadDelegate;

- (id<OSDownloadOperationProtocol>)getDownloadItemByTask:(NSURLSessionDataTask *)task;
- (id<OSDownloadOperationProtocol>)getDownloadItemByURL:(nonnull NSString *)urlPath;
- (long long)getCacheFileSizeWithPath:(NSString *)url;
/// 执行开始下载任务
/// @param urlPath 下载任务的remote url path
- (id<OSDownloadOperationProtocol>)downloadWithURL:(NSString *)urlPath;

- (NSURLSessionDataTask *)downloadTaskWithURLPath:(NSString *)urlPath
                                             progress:(nullable void (^)(NSProgress *downloadProgress))downloadProgressBlock
                                    completionHandler:(nullable void (^)(NSURLResponse *response, NSURL * _Nullable filePath, NSError * _Nullable error))completionHandler;
- (NSURLSessionDataTask *)downloadTaskWithRequest:(NSURLRequest *)request
                                         progress:(nullable void (^)(NSProgress *downloadProgress))downloadProgressBlock
                                completionHandler:(nullable void (^)(NSURLResponse *response, NSURL * _Nullable filePath, NSError * _Nullable error))completionHandler;

/// 取消下载, 取消下载后任务不可恢复
/// @param urlPath 下载任务
- (void)cancelWithURL:(NSString *)urlPath;

/// 暂停下载，暂停后任务可恢复
/// @param urlPath 暂停下载任务的urlPath
- (void)pauseWithURL:(NSString *)urlPath;

/// 根据是否urlPath判断正在下载中
/// @param urlPath 下载任务的url
- (BOOL)isDownloading:(NSString *)urlPath;

/// 根据是否urlPath判断在等待中
/// @param urlPath 下载任务的url
- (BOOL)isWaiting:(NSString *)urlPath;

/// 判断该文件是否下载完成
- (BOOL)isCompletionByRemoteUrlPath:(NSString *)url;

/// 当前是否有任务下载
- (BOOL)hasActiveDownloads;

/// 获取下载进度
/// urlPath 当前下载任务的唯一标识符
/// @return 下载进度的信息
- (OSDownloadProgress *)getDownloadProgressByURL:(NSString *)urlPath;

/// 检查当前同时下载的任务数量是否超出最大值maxConcurrentDownloadCount
/// @mark 当当前正在下载的activeDownloadsDictionary任务中小于最大同时下载数量时，
/// @mark 则从等待的waitingDownloadArray中取出第一个开始下载，添加到activeDownloadsDictionary，并从waitingDownloadArray中移除
- (void)checkMaxConcurrentDownloadCountThenDownloadWaitingQueueIfExceeded;

/// 如果当前没有正在下载中的就重置进度
- (void)resetProgressIfNoActiveDownloadsRunning;


@end

NS_ASSUME_NONNULL_END
