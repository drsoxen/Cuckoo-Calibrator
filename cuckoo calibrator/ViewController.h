//
//  ViewController.h
//  cuckoo calibrator
//
//  Created by Chris Ziraldo on 12-06-18.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreAudio/CoreAudioTypes.h>

#import "Timer.h"
@interface ViewController : UIViewController
{
    Timer *timer;
    bool tickTock;
    
    AVAudioRecorder *recorder;
	NSTimer *levelTimer;
	double lowPassResults;
}

- (void)levelTimerCallback:(NSTimer *)time;
-(IBAction)Time;

@property(nonatomic,retain)IBOutlet UILabel *TimeLabel;
@property(nonatomic,retain)IBOutlet UILabel *MoveLabel;
@property(nonatomic,retain)IBOutlet UIButton *Button;

@end
