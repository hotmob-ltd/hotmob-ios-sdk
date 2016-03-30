//
//  HotmobManager.h
//  HotmobSDKDemo
//
//  Created by Hotmob Ltd. on 23/7/15.
//  Copyright (c) 2015 Hotmob Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

// Define settings string constants
extern NSString * const HotmobBannerSetFadeoutDirection;
extern NSString * const HotmobBannerSetFadeoutDelay;
extern NSString * const HotmobBannerSetEnableFadeinAnimation;
extern NSString * const HotmobBannerSetFadeinDirection;
extern NSString * const HotmobBannerSetAutoRefreshDelay;

extern NSString * const HotmobBannerSetExternalMessagePrompt;
extern NSString * const HotmobBannerSetDialMessagePrompt;
extern NSString * const HotmobBannerSetSMSMessagePrompt;
extern NSString * const HotmobBannerSetEmailMessagePrompt;
extern NSString * const HotmobBannerSetiCalMessagePrompt;
extern NSString * const HotmobBannerSetMessageConfirmPrompt;
extern NSString * const HotmobBannerSetMessageCancelPrompt;


enum
{
    HotmobBannerFadeoutDirectionNone = 0,
    HotmobBannerFadeoutDirectionToTop = 1,
    HotmobBannerFadeoutDirectionToBottom = 2,
};
typedef NSInteger HotmobBannerFadeoutDirection;

enum
{
    HotmobBannerFadeinDirectionNone = 0,
    HotmobBannerFadeinDirectionFromTop = 1,
    HotmobBannerFadeinDirectionFromBottom = 2,
};
typedef NSInteger HotmobBannerFadeinDirection;

@class HotmobBanner;

@protocol HotmobManagerDelegate <NSObject>
@optional
/**
 * Calls if there is an advertisement return.
 *
 * @param obj The banner or popup object.
 **/
- (void)didLoadBanner:(id)obj;

/**
 * Calls before the advertisement content shown on the banner.
 *
 * @param obj The banner or popup object.
 **/
- (void)willShowBanner:(id)obj;

/**
 * Calls after the advertisement content shown on the banner.
 *
 * @param obj The banner or popup object.
 **/
- (void)didShowBanner:(id)obj;

/**
 * Calls when the advertisement is ready to hide.
 *
 * @param obj The banner or popup object.
 **/
- (void)willHideBanner:(id)obj;

/**
 * Calls when the advertisement is hidden
 *
 * @param obj The banner or popup object.
 **/
- (void)didHideBanner:(id)obj;

/**
 * Calls if there is no advertisement return, or the advertisement content cannot be loaded.
 *
 * @param obj The banner or popup object.
 **/
- (void)openNoAdCallback:(id)obj;

/**
 * Calls if user tap on the advertisement.
 *
 * @param obj The banner or popup object.
 **/
- (void)didClick:(id)obj;

/**
 * Calls if the advertisement content cannot load successfully.
 *
 * @param obj The banner or popup object.
 **/
- (void)didLoadFailed:(id)obj;

/**
 * Calls if "Click to Interal" action detected.
 *
 * @param obj The banner or popup object.
 **/
- (void)openInternalCallback:(id)obj url:(NSString*)url;

/**
 * Calls if In-App browser will be shown.
 *
 * @param obj The banner or popup object.
 **/
- (void)willShowInAppBrowser:(id)obj;

/**
 * Calls if In-App browser was shown.
 *
 * @param obj The banner or popup object.
 **/
- (void)didShowInAppBrowser:(id)obj;

/**
 * Calls if In-App browser ready to close.
 *
 * @param obj The banner or popup object.
 **/
- (void)willCloseInAppBrowser:(id)obj;

/**
 * Calls if In-App browser was closed.
 *
 * @param obj The banner or popup object.
 **/
- (void)didCloseInAppBrowser:(id)obj;

/**
 * Calls if Hotmob SDK need to change sound settings.
 *
 * @param
 * obj The banner or popup object.
 * isSoundEnable Indicates whether the sound will be on or off for the Hotmob Banner action
 **/
- (void)hotmobBanner:(id)obj isReadyChangeSoundSettings:(BOOL)isSoundEnable;
@end

@interface HotmobManager : NSObject

@property (nonatomic, weak) id <HotmobManagerDelegate> bannerDelegate;
@property (nonatomic, weak) id <HotmobManagerDelegate> popupDelegate;

/**
 Set whether enabling debug mode or not.
 **/
+ (void)setDebug:(BOOL)isDebug;

/**
 Get the HotmobBanner object, and enable auto refresh at default.
 */
+ (UIView *)getBanner:(UIViewController *)rootViewController delegate:(id<HotmobManagerDelegate>)delegate identifier:(NSString *)identifier adCode:(NSString *)adCode size:(CGRect)rect;

/**
 Get the HotmobBanner object.
 */
+ (UIView *)getBanner:(UIViewController *)rootViewController delegate:(id<HotmobManagerDelegate>)delegate identifier:(NSString *)identifier adCode:(NSString *)adCode size:(CGRect)rect autoRefresh:(BOOL)shouldAutoRefresh;

/**
 Get the HotmobPopup object, and enable auto refresh at default.
 */
+ (void)getPopup:(UIViewController *)rootViewController delegate:(id<HotmobManagerDelegate>)delegate identifier:identifier adCode:(NSString *)adCode showWhenResume:(BOOL)shouldShowWhenResume;

/**
 Get the HotmobPopup object.
 */
+ (void)getPopup:(UIViewController *)rootViewController delegate:(id<HotmobManagerDelegate>)delegate identifier:identifier adCode:(NSString *)adCode showWhenResume:(BOOL)shouldShowWhenResume autoRefresh:(BOOL)shouldAutoRefresh;

/**
 Set additional parameters to target object
 */
+ (void)set:(id)param withValue:(id)value withObject:(id)object;

/**
 Set additional paramrters to target object (where value is a double number.)
 */
+ (void)set:(id)param withDoubleValue:(double)value withObject:(id)object;

/**
 set additional paramrters to target object (where value is a boolean.)
 */
+ (void)set:(id)param withBooleanValue:(BOOL)value withObject:(id)object;

/**
 set additional paramrters to target object (where value is a integer or enum.)
 */
+ (void)set:(id)param withIntegerValue:(NSInteger)value withObject:(id)object;

/**
 Manually refresh the banner
 */
+ (void)refreshBanner:(UIView *)banner;

/**
 Enable refesh popup
 */
+ (void)enablePopupRefresh:(BOOL)shouldEnablePopupRefresh;

/**
 Return the ad code of input banner
 */
+ (NSString *)getAdCode:(UIView *)bannerView;

/**
 Return the identifier of the banner
 */
+ (NSString *)getIdentifier:(UIView *)bannerView;

/**
 Check the banner view position in tableview and do the actions for video ads. (For only one items)
 */
+ (void)calculateBannerPositionWithView:(UIScrollView *)view cellItems:(NSArray *)cellItems forVideoAdsBannerCell:(UIView *)bannerCell andBanner:(UIView *)banner;

/**
 Transit the banner into given UITableViewCell or UICollectionViewCell
 */
+ (void)transitBanner:(UIView*)bannerView toCell:(id)cell;

/**
 Get The Banner View from a UITableViewCell or UICollectionViewCell
 
 The method will return nil if the given cell is neither UITableViewCell nor UICollectionViewCell.
 */
+ (UIView *)bannerViewFromCell:(id)cell;

/**
 * Set the current visible view controller
 **/
+ (void)setCurrentViewController:(UIViewController *)viewController;

/** 
 * Set banner delegate
 **/
+ (void)setHotmobBannerDelegate:(id <HotmobManagerDelegate>) delegate;

/**
 * Reload all banners in the array provided.
 **/
+ (void)reloadBannersWithArray:(NSArray *)array;

/**
 * Set the banner width (for mediation use)
 **/
+ (void)setBannerWidth:(float)width;
@end
