/*
    Reusable find panel functionality (find, replace).
    Need one shared instance of TextFinder to which the menu items and widgets in the find panel are connected.
    Loads UI lazily.
    Works on first responder, assumed to be an NSTextView.
*/

#import <Cocoa/Cocoa.h>

@class ChatWindowController;

#define Forward YES
#define Backward NO

@interface TextFinder : NSObject {
    NSString *findString;
    id findTextField;
    id replaceTextField;
    id ignoreCaseButton;
    id findNextButton;
    id replaceAllScopeMatrix;
    id statusField;
    BOOL lastFindWasSuccessful;
    IBOutlet ChatWindowController *chatWindowController;
}

/* Common way to get a text finder. One instance of TextFinder per app is good enough. */
+ (id)sharedInstance;

/* Main method for external users; does a find in the first responder. Selects found range or beeps. */
- (BOOL)find:(BOOL)direction;

/* Loads UI lazily */
- (NSPanel *)findPanel;

/* Gets the first responder and returns it if it's an NSTextView */
- (NSTextView *)textObjectToSearchIn;

/* Get/set the current find string. Will update UI if UI is loaded */
- (NSString *)findString;
- (void)setFindString:(NSString *)string;
- (void)setFindString:(NSString *)string writeToPasteboard:(BOOL)flag;

/* Misc internal methods */
- (void)appDidActivate:(NSNotification *)notification;
- (void)loadFindStringFromPasteboard;
- (void)loadFindStringToPasteboard;

/* Action methods, sent from the find panel UI; can also be connected to menu items */
- (void)findNext:(id)sender;
- (void)findPrevious:(id)sender;
- (void)findNextAndOrderFindPanelOut:(id)sender;
- (void)replace:(id)sender;
- (void)replaceAndFind:(id)sender;
- (void)replaceAll:(id)sender;
- (void)orderFrontFindPanel:(id)sender;
- (void)takeFindStringFromSelection:(id)sender;
- (void)jumpToSelection:(id)sender;

@end

