//
//  ViewController.m
//  cuckoo calibrator
//
//  Created by Chris Ziraldo on 12-06-18.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ViewController.h"

@implementation ViewController
@synthesize TimeLabel;
@synthesize Button;
@synthesize MoveLabel;

-(id)init
{
    if (self = [super init])
    {
        timer = [[Timer alloc] init];
        tickTock = true;
    }
    return self;
}

-(IBAction)Time
{
        
    if(tickTock)
    {    
    [timer startTimer];
        [Button setTitle:@"Tock" forState:UIControlStateNormal];
    }
    else 
    {
    [timer stopTimer];  
        [Button setTitle:@"Tick" forState:UIControlStateNormal];
        double SecondDelta = [timer timeElapsedInSeconds];
        TimeLabel.text = [NSString stringWithFormat:@"%f", SecondDelta];
        if(SecondDelta > 1)
            MoveLabel.text = @"Move Down";
        else 
            MoveLabel.text = @"Move Up";
        
    }   
    
    tickTock = !tickTock;
    
//    NSLog(@"Total time was: %lf milliseconds", [timer timeElapsedInMilliseconds]);  
//    NSLog(@"Total time was: %lf seconds", [timer timeElapsedInSeconds]);
//    NSLog(@"Total time was: %lf minutes", [timer timeElapsedInMinutes]);
    

}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    NSURL *url = [NSURL fileURLWithPath:@"/dev/null"];
    
	NSDictionary *settings = [NSDictionary dictionaryWithObjectsAndKeys:
							  [NSNumber numberWithFloat: 44100.0],                 AVSampleRateKey,
							  [NSNumber numberWithInt: kAudioFormatAppleLossless], AVFormatIDKey,
							  [NSNumber numberWithInt: 1],                         AVNumberOfChannelsKey,
							  [NSNumber numberWithInt: AVAudioQualityMax],         AVEncoderAudioQualityKey,
							  nil];
    
	NSError *error;
    
	recorder = [[AVAudioRecorder alloc] initWithURL:url settings:settings error:&error];
    
	if (recorder) {
		[recorder prepareToRecord];
		recorder.meteringEnabled = YES;
		[recorder record];
		levelTimer = [NSTimer scheduledTimerWithTimeInterval: 0.03 target: self selector: @selector(levelTimerCallback:) userInfo: nil repeats: YES];
	} else
		NSLog(@"%@",[error description]);	
}

static int count = 0;
- (void)levelTimerCallback:(NSTimer *)time {
	[recorder updateMeters];
    
//    float level = [recorder peakPowerForChannel:0];
//    NSLog(@"Vol: %f", level);
    
	const double ALPHA = 0.05;
	double peakPowerForChannel = pow(10, (0.05 * [recorder peakPowerForChannel:0]));
	lowPassResults = ALPHA * peakPowerForChannel + (1.0 - ALPHA) * lowPassResults;	
	
	if (lowPassResults > 0.7)
    {
        if(count == 30)            
        {
            count = 0;
        NSLog(@"DETECTED");
        if(tickTock)
        {    
            [timer startTimer];
            [Button setTitle:@"Tock" forState:UIControlStateNormal];
        }
        else 
        {
            [timer stopTimer];  
            [Button setTitle:@"Tick" forState:UIControlStateNormal];
            double SecondDelta = [timer timeElapsedInSeconds];
            TimeLabel.text = [NSString stringWithFormat:@"%f", SecondDelta];
            if(SecondDelta > 1)
                MoveLabel.text = @"Move Down";
            else 
                MoveLabel.text = @"Move Up";
            
        }   
        
        tickTock = !tickTock;
        }
        else
            count ++;
    }
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

- (void)dealloc {
	[levelTimer release];
	[recorder release];
    [super dealloc];
}

@end
