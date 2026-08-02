//
//  SlackTextViewController
//  https://github.com/slackhq/SlackTextViewController
//
//  Copyright 2014-2016 Slack Technologies, Inc.
//  Licence: MIT-Licence
//

#import "UIScrollView+SLKAdditions.h"

@implementation UIScrollView (SLKAdditions)

- (void)slk_scrollToTopAnimated:(BOOL)animated
{
    if ([self slk_canScroll]) {
        [self setContentOffset:CGPointZero animated:animated];
    }
}

- (void)slk_scrollToBottomAnimated:(BOOL)animated
{
    if ([self slk_canScroll]) {
        [self setContentOffset:[self slk_bottomRect].origin animated:animated];
    }
}

- (BOOL)slk_canScroll
{
    if (self.contentSize.height + [self slk_bottomInset] > CGRectGetHeight(self.frame)) {
        return YES;
    }
    return NO;
}

- (CGFloat)slk_bottomInset
{
    // Content covered by e.g. a translucent text input bar is reserved using the bottom content inset,
    // so it needs to be taken into account when scrolling to (or detecting) the bottom
    if (@available(iOS 11.0, *)) {
        return self.adjustedContentInset.bottom;
    }

    return self.contentInset.bottom;
}

- (BOOL)slk_isAtTop
{
    return CGRectGetMinY([self slk_visibleRect]) <= CGRectGetMinY(self.bounds);
}

- (BOOL)slk_isAtBottom
{
    return CGRectGetMaxY([self slk_visibleRect]) >= CGRectGetMaxY([self slk_bottomRect]);
}

- (CGRect)slk_visibleRect
{
    CGRect visibleRect;
    visibleRect.origin = self.contentOffset;
    visibleRect.size = self.frame.size;
    return visibleRect;
}

- (CGRect)slk_bottomRect
{
    return CGRectMake(0.0, self.contentSize.height + [self slk_bottomInset] - CGRectGetHeight(self.bounds), CGRectGetWidth(self.bounds), CGRectGetHeight(self.bounds));
}

- (void)slk_stopScrolling
{
    if (!self.isDragging) {
        return;
    }
    
    CGPoint offset = self.contentOffset;
    offset.y -= 1.0;
    [self setContentOffset:offset];
    
    offset.y += 1.0;
    [self setContentOffset:offset];
}

@end
