//
//  SlackTextViewController
//  https://github.com/slackhq/SlackTextViewController
//
//  Copyright 2014-2016 Slack Technologies, Inc.
//  Licence: MIT-Licence
//

// TODO: Modernization - SLK_IS_LANDSCAPE reads [UIScreen mainScreen].bounds, so it reports the shape of the whole
// display rather than of the window the text view actually lives in. Under Split View, Slide Over, Stage Manager and
// iPhone Mirroring that is the wrong answer. It cannot be fixed in the macro itself: a macro has no `self`, and the
// replacement differs per call site - a view should compare its own bounds (or read
// self.traitCollection.verticalSizeClass), a view controller self.view.bounds. Migrate each call site to a local check
// and delete this macro. Live call sites: SLKTextView.m -maxNumberOfLines and SLKTextViewController.m
// -slk_topBarsHeight; the third (SLKTextViewController.m -slk_didPostSLKKeyboardNotification:) sits behind
// !SLK_IS_IOS8_AND_HIGHER and is unreachable on any supported OS, so it can be dropped along with the macro.
#define SLK_IS_LANDSCAPE         ([UIScreen mainScreen].bounds.size.width > [UIScreen mainScreen].bounds.size.height)
#define SLK_IS_IPAD              ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad)
#define SLK_IS_IPHONE            ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone)
#define SLK_IS_IOS8_AND_HIGHER   ([[UIDevice currentDevice].systemVersion floatValue] >= 8.0)
#define SLK_IS_IOS9_AND_HIGHER   ([[UIDevice currentDevice].systemVersion floatValue] >= 9.0)

#define SLK_KEYBOARD_NOTIFICATION_DEBUG     DEBUG && 0  // Logs every keyboard notification being sent

static NSString *SLKTextViewControllerDomain = @"com.slack.TextViewController";

/**
 Returns a constant font size difference reflecting the current accessibility settings.
 
 @param category A content size category constant string.
 @returns A float constant font size difference.
 */
__unused static CGFloat SLKPointSizeDifferenceForCategory(NSString *category)
{
    if ([category isEqualToString:UIContentSizeCategoryExtraSmall])                         return -3.0;
    if ([category isEqualToString:UIContentSizeCategorySmall])                              return -2.0;
    if ([category isEqualToString:UIContentSizeCategoryMedium])                             return -1.0;
    if ([category isEqualToString:UIContentSizeCategoryLarge])                              return 0.0;
    if ([category isEqualToString:UIContentSizeCategoryExtraLarge])                         return 2.0;
    if ([category isEqualToString:UIContentSizeCategoryExtraExtraLarge])                    return 4.0;
    if ([category isEqualToString:UIContentSizeCategoryExtraExtraExtraLarge])               return 6.0;
    if ([category isEqualToString:UIContentSizeCategoryAccessibilityMedium])                return 8.0;
    if ([category isEqualToString:UIContentSizeCategoryAccessibilityLarge])                 return 10.0;
    if ([category isEqualToString:UIContentSizeCategoryAccessibilityExtraLarge])            return 11.0;
    if ([category isEqualToString:UIContentSizeCategoryAccessibilityExtraExtraLarge])       return 12.0;
    if ([category isEqualToString:UIContentSizeCategoryAccessibilityExtraExtraExtraLarge])  return 13.0;
    return 0;
}

__unused static CGRect SLKRectInvert(CGRect rect)
{
    CGRect invert = CGRectZero;
    
    invert.origin.x = rect.origin.y;
    invert.origin.y = rect.origin.x;
    invert.size.width = rect.size.height;
    invert.size.height = rect.size.width;
    
    return invert;
}
