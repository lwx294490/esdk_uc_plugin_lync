//
//  EGORefreshTableHeaderView.m
//  Demo
//
//  Created by Devin Doty on 10/14/09October14.
//  Copyright 2009 enormego. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#import "EGORefreshTableHeaderView.h"


#define TIME_TEXT_COLOR	 [UIColor colorWithRed:153.0/255.0 green:153.0/255.0 blue:153.0/255.0 alpha:1.0]
#define TEXT_COLOR	 [UIColor colorWithRed:103.0/255.0 green:103.0/255.0 blue:103.0/255.0 alpha:1.0]
#define FLIP_ANIMATION_DURATION 0.18f
#define LOADMOREVIEW_HEIGHT 65


@interface EGORefreshTableHeaderView (Private)
- (void)setState:(EGOPullRefreshState)aState;
@end

@implementation EGORefreshTableHeaderView

@synthesize delegate=_delegate;


- (id)initWithFrame:(CGRect)frame {
	//默认下拉
	return [self initWithFrame:frame pullType:PULLTYPE_PULLDOWN];
}

-(id)initWithFrame:(CGRect)frame pullType:(PULLTYPE)pullType delegate:(id<EGORefreshTableHeaderDelegate>)d {
	if (self = [super initWithFrame:frame]) {
		
		_pullType = pullType;
		CGFloat lblUpdateTime_y = 0.0f;
		CGFloat lblStatus_y = 0.0f;
		CGFloat loadingIndicator_y = 0.0f;
		CGFloat arrow_y = 0.0f;
		
		switch (_pullType) {
			case PULLTYPE_PULLUP:
				lblUpdateTime_y = 45.0f;
				lblStatus_y = 20.0f;
				arrow_y = 5.0f;
				loadingIndicator_y = 12.0f;
				break;
			case PULLTYPE_PULLDOWN: //默认下拉
			default:
				lblUpdateTime_y = frame.size.height - 13.0f;
				lblStatus_y = frame.size.height - 27.0f;
				arrow_y = frame.size.height - 53.0f;
				loadingIndicator_y = frame.size.height - 44.0f;
				break;
		}
		
		_delegate = d;
		
		self.autoresizingMask = UIViewAutoresizingFlexibleWidth;
		if ([_delegate respondsToSelector:@selector(egoRefreshTableHeaderViewBackgroundColor:)]) {
			self.backgroundColor = [_delegate egoRefreshTableHeaderViewBackgroundColor:self];
		}else {
			self.backgroundColor = [UIColor colorWithRed:230.0/255.0 green:230.0/255.0 blue:230.0/255.0 alpha:1.0];
		}
		
		UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0.0f, lblUpdateTime_y, self.frame.size.width, 9.0f)];
		label.autoresizingMask = UIViewAutoresizingFlexibleWidth;
		label.font = [UIFont systemFontOfSize:9.0f];
		label.textColor = TIME_TEXT_COLOR;
		//		label.shadowColor = [UIColor colorWithWhite:0.9f alpha:1.0f];
		//		label.shadowOffset = CGSizeMake(0.0f, 1.0f);
		label.backgroundColor = [UIColor clearColor];
		label.textAlignment = UITextAlignmentCenter;
		[self addSubview:label];
		_lastUpdatedLabel=label;
		[label release];
		
		label = [[UILabel alloc] initWithFrame:CGRectMake(0.0f, lblStatus_y, self.frame.size.width, 11.0f)];
		label.autoresizingMask = UIViewAutoresizingFlexibleWidth;
		label.font = [UIFont boldSystemFontOfSize:11.0f];
		label.textColor = TEXT_COLOR;
		//		label.shadowColor = [UIColor colorWithWhite:0.9f alpha:1.0f];
		//		label.shadowOffset = CGSizeMake(0.0f, 1.0f);
		label.backgroundColor = [UIColor clearColor];
		label.textAlignment = UITextAlignmentCenter;
		[self addSubview:label];
		_statusLabel=label;
		[label release];
		
		CALayer *layer = [CALayer layer];
		layer.frame = CGRectMake(21.0f, arrow_y, 35.0f, 35.0f);
		layer.contentsGravity = kCAGravityResizeAspect;
		if (_pullType == PULLTYPE_PULLUP) {
			layer.contents = (id)[UIImage imageNamed:@"pullup_arrow.png"].CGImage;
		}else {
			layer.contents = (id)[UIImage imageNamed:@"pulldown_arrow.png"].CGImage;
		}
		
		
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 40000
		if ([[UIScreen mainScreen] respondsToSelector:@selector(scale)]) {
			layer.contentsScale = [[UIScreen mainScreen] scale];
		}
#endif
		[[self layer] addSublayer:layer];
		_arrowImage=layer;
		if (_pullType == PULLTYPE_PULLDOWN) {
			_arrowImage.hidden = NO;
			UIImageView *imgvLogo = [[UIImageView alloc] initWithFrame:CGRectMake(140, self.frame.size.height - 68.0f, 40.0f, 40.0f)];
			imgvLogo.image = [UIImage imageNamed:@"pulldown_logo.png"];
			[self addSubview:imgvLogo];
			[imgvLogo release];
			
		}else {
			_arrowImage.hidden = YES;
		}
		
		UIActivityIndicatorView *view = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
		view.frame = CGRectMake(30.0f, loadingIndicator_y, 20.0f, 20.0f);
		[self addSubview:view];
		_activityView = view;
		[view release];
		
		
		[self setState:EGOOPullRefreshNormal];
		
    }
	
    return self;
	
}
-(id)initWithFrame:(CGRect)frame pullType:(PULLTYPE)pullType {
	return [self initWithFrame:frame pullType:pullType delegate:nil];
}



#pragma mark -
#pragma mark Setters

- (void)refreshLastUpdatedDate {
	
	if ([_delegate respondsToSelector:@selector(egoRefreshTableHeaderDataSourceLastUpdated:)]) {
		
		if (_pullType == PULLTYPE_PULLUP) {
			_lastUpdatedLabel.text = nil;
		}else {
			NSDate *date = [_delegate egoRefreshTableHeaderDataSourceLastUpdated:self];
			
			NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
			[formatter setDateFormat:@"yyyy/MM/dd HH:mm"];
			_lastUpdatedLabel.text = [NSString stringWithFormat:@"%@ %@",NSLocalizedString(@"last_updated",@"last update"), [formatter stringFromDate:date]];
			[[NSUserDefaults standardUserDefaults] setObject:_lastUpdatedLabel.text forKey:@"EGORefreshTableView_LastRefresh"];
			[[NSUserDefaults standardUserDefaults] synchronize];
			[formatter release];
		}

		
		
	} else {
		
		_lastUpdatedLabel.text = nil;
		
	}

}

- (void)setState:(EGOPullRefreshState)aState{
	
	switch (aState) {
		case EGOOPullRefreshPulling:
			
			_statusLabel.text = NSLocalizedString(@"release_refresh", @"Release to refresh status");
			[CATransaction begin];
			[CATransaction setAnimationDuration:FLIP_ANIMATION_DURATION];
			_arrowImage.transform = CATransform3DMakeRotation((M_PI / 180.0) * 180.0f, 0.0f, 0.0f, 1.0f);
			[CATransaction commit];
			
			break;
		case EGOOPullRefreshNormal:
			
			if (_state == EGOOPullRefreshPulling) {
				[CATransaction begin];
				[CATransaction setAnimationDuration:FLIP_ANIMATION_DURATION];
				_arrowImage.transform = CATransform3DIdentity;
				[CATransaction commit];
			}
			if (_pullType == PULLTYPE_PULLUP) {
				_statusLabel.text = NSLocalizedString(@"pull_up_to_load_more", @"Pull up to refresh status");
			}else {
				_statusLabel.text = NSLocalizedString(@"down_refresh", @"Pull down to refresh status");
			}

			
			[_activityView stopAnimating];
			[CATransaction begin];
			[CATransaction setValue:(id)kCFBooleanTrue forKey:kCATransactionDisableActions]; 
			_arrowImage.hidden = NO;
			_arrowImage.transform = CATransform3DIdentity;
			[CATransaction commit];
			
			break;
		case EGOOPullRefreshLoading:
			
			_statusLabel.text = NSLocalizedString(@"loding", @"Loading Status");
			[_activityView startAnimating];
			[CATransaction begin];
			[CATransaction setValue:(id)kCFBooleanTrue forKey:kCATransactionDisableActions]; 
			_arrowImage.hidden = YES;
			[CATransaction commit];
			
			break;
		default:
			break;
	}
	if ([_delegate respondsToSelector:@selector(egoRefreshTableHeaderDataSourceViewTitle:state:)]) {
		_statusLabel.text = [_delegate egoRefreshTableHeaderDataSourceViewTitle:self state:aState];
	}
	
	_state = aState;
}


#pragma mark -
#pragma mark ScrollView Methods

- (void)egoRefreshScrollViewDidScroll:(UIScrollView *)scrollView {	
	
	
	if (_state == EGOOPullRefreshLoading) {
		
		if (_pullType == PULLTYPE_PULLUP) {
			CGFloat footerOffset = scrollView.frame.size.height + scrollView.contentOffset.y - scrollView.contentSize.height;
			
			CGFloat offset = MAX(footerOffset * -1, 0);
			offset = MIN(offset, 60);
			scrollView.contentInset = UIEdgeInsetsMake(0.0f, 0.0f, offset, 0.0f);
			
		}else {
			CGFloat offset = MAX(scrollView.contentOffset.y * -1, 0);
			offset = MIN(offset, 60);
			scrollView.contentInset = UIEdgeInsetsMake(offset, 0.0f, 0.0f, 0.0f);
		}

		
		
	} else if (scrollView.isDragging) {
		
		BOOL _loading = NO;
		if ([_delegate respondsToSelector:@selector(egoRefreshTableHeaderDataSourceIsLoading:)]) {
			_loading = [_delegate egoRefreshTableHeaderDataSourceIsLoading:self];
		}
		
		if (_pullType == PULLTYPE_PULLUP) {
			CGFloat footerOffset = scrollView.frame.size.height + scrollView.contentOffset.y - scrollView.contentSize.height;
			if (_state == EGOOPullRefreshPulling && footerOffset > 0.0f && footerOffset < LOADMOREVIEW_HEIGHT && !_loading) {
				[self setState:EGOOPullRefreshNormal];
			} else if (_state == EGOOPullRefreshNormal && footerOffset>LOADMOREVIEW_HEIGHT && !_loading) {
				[self setState:EGOOPullRefreshPulling];
			}
		}else {
			if (_state == EGOOPullRefreshPulling && scrollView.contentOffset.y > -65.0f && scrollView.contentOffset.y < 0.0f && !_loading) {
				[self setState:EGOOPullRefreshNormal];
			} else if (_state == EGOOPullRefreshNormal && scrollView.contentOffset.y < -65.0f && !_loading) {
				[self setState:EGOOPullRefreshPulling];
			}
		}

		if (_pullType == PULLTYPE_PULLUP) {
			if (scrollView.contentInset.bottom != 0) {
				scrollView.contentInset = UIEdgeInsetsZero;
			}
		}else {
			if (scrollView.contentInset.top != 0) {
				scrollView.contentInset = UIEdgeInsetsZero;
			}
		}		
		
	}
	
}

- (void)egoRefreshScrollViewDidEndDragging:(UIScrollView *)scrollView {
	
	BOOL _loading = NO;
	if ([_delegate respondsToSelector:@selector(egoRefreshTableHeaderDataSourceIsLoading:)]) {
		_loading = [_delegate egoRefreshTableHeaderDataSourceIsLoading:self];
	}
	
	if (_pullType == PULLTYPE_PULLUP) {
		//上拉加载更多
		CGFloat footerOffset = scrollView.frame.size.height + scrollView.contentOffset.y - scrollView.contentSize.height;
		if (footerOffset >= LOADMOREVIEW_HEIGHT && _loading == NO) {
			
			[self setState:EGOOPullRefreshLoading];
			
			[UIView beginAnimations:nil context:NULL];
			[UIView setAnimationDuration:0.2];
			scrollView.contentInset = UIEdgeInsetsMake(0.0f, 0.0f, 0.0f, 0.0f);
			[UIView commitAnimations];
			if ([_delegate respondsToSelector:@selector(egoRefreshTableHeaderDidTriggerRefresh:)]) {
				[_delegate egoRefreshTableHeaderDidTriggerRefresh:self];
			}
		}
		
	}else {
		if (scrollView.contentOffset.y <= - 65.0f && !_loading) {
			
			[self setState:EGOOPullRefreshLoading];
			[UIView beginAnimations:nil context:NULL];
			[UIView setAnimationDuration:0.2];
			scrollView.contentInset = UIEdgeInsetsMake(60.0f, 0.0f, 0.0f, 0.0f);
			[UIView commitAnimations];
			
			if ([_delegate respondsToSelector:@selector(egoRefreshTableHeaderDidTriggerRefresh:)]) {
				[_delegate egoRefreshTableHeaderDidTriggerRefresh:self];
			}
			
		}
	}

	

	
}

- (void)egoRefreshScrollViewDataSourceDidFinishedLoading:(UIScrollView *)scrollView {	
	
	[UIView beginAnimations:nil context:NULL];
	[UIView setAnimationDuration:.3];
	[scrollView setContentInset:UIEdgeInsetsMake(0.0f, 0.0f, 0.0f, 0.0f)];
	[UIView commitAnimations];
	
	[self setState:EGOOPullRefreshNormal];
	[self refreshLastUpdatedDate];

}


#pragma mark -
#pragma mark Dealloc

- (void)dealloc {
	
	_delegate=nil;
	_activityView = nil;
	_statusLabel = nil;
	_arrowImage = nil;
	_lastUpdatedLabel = nil;
    [super dealloc];
}


@end
