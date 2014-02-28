//
//  ObjectiveBitcoinTests.m
//  ObjectiveBitcoinTests
//
//  Created by Eric Nelson on 2/1/14.
//  Copyright (c) 2014 Sandalsoft. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <OHHTTPStubs/OHHTTPStubs.h>
#import "ObjectiveBitcoin.h"

#define TestNeedsToWaitForBlock() __block BOOL blockFinished = NO
#define BlockFinished() blockFinished = YES
#define WaitForBlock() while (CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0, true) && !blockFinished)

@interface ObjectiveBitcoinTests : XCTestCase

@property (strong, nonatomic) ObjectiveBitcoin *client;

@property (strong, nonatomic) NSString *OHTTPStubHostString;

@property (strong, nonatomic) NSString *host;
@property (strong, nonatomic) NSString *port;
@property (strong, nonatomic) NSString *username;
@property (strong, nonatomic) NSString *password;
@property (strong, nonatomic) NSString *block;
@property (strong, nonatomic) NSString *accountName;
@property (strong, nonatomic) NSString *bitcoinAddress;



@end

@implementation ObjectiveBitcoinTests

- (void)setUp {
    [super setUp];

    
    // Setup properties of bitcoind RPC Client and params to send methods for testing.  These params should be valid -testnet values.
    self.OHTTPStubHostString = @"dev.sndl.io";
    self.host = @"http://dev.sndl.io";
    self.port = @"18332";
    self.username = @"u";
    self.password = @"p";
    self.block = @"00000000f275c4a72eb44e2385d4ac0acb5760b111fc335c5c400945cbc3bba5";
    self.accountName = @"test";
    self.bitcoinAddress = @"moFizF4tnNgaGRtwfV3uxvB4VfWzsv5rvU";
    
    
    // Instantiate the client singleton
    self.client = [[ObjectiveBitcoin alloc] initWithHost:self.host port:self.port username:self.username password:self.password];
    
}

- (void)tearDown {
    [super tearDown];
    
    // Remove stubs after each test method.  Failure to do this can cause stubs to hang around and get mixed with other tests yielding unpredictable results
    [OHHTTPStubs removeAllStubs];
    
}


- (void)testGetBalance {
    NSString *stubDataFileName = @"getbalance.json";
    
    [OHHTTPStubs stubRequestsPassingTest:^BOOL(NSURLRequest *request) {
        return [request.URL.host isEqualToString:self.OHTTPStubHostString];
    } withStubResponse:^OHHTTPStubsResponse*(NSURLRequest *request) {
        return [OHHTTPStubsResponse responseWithFileAtPath:OHPathForFileInBundle(stubDataFileName, nil) statusCode:200 headers:nil];
    }].name = [NSString stringWithFormat:@"Stub for %@", NSStringFromSelector(_cmd)];
    
    TestNeedsToWaitForBlock();
    
    [self.client getBalanceForAccount:@"test" success:^(NSNumber *balance) {
        XCTAssertTrue([balance isEqualToNumber:@3.09890000], @"Balance should equal 3.09890000");
        BlockFinished();
    } failure:^(NSError *error) {
        XCTAssertNil(@"bewbz", @"In failure block :(");
        BlockFinished();
    }];
    
    WaitForBlock();
}

- (void)testGetBlock {
    NSString *stubDataFileName = @"getblock.json";
    
    [OHHTTPStubs stubRequestsPassingTest:^BOOL(NSURLRequest *request) {
        return [request.URL.host isEqualToString:self.OHTTPStubHostString];
    } withStubResponse:^OHHTTPStubsResponse*(NSURLRequest *request) {
        return [OHHTTPStubsResponse responseWithFileAtPath:OHPathForFileInBundle(stubDataFileName, nil) statusCode:200 headers:nil];
    }].name = [NSString stringWithFormat:@"Stub for %@", NSStringFromSelector(_cmd)];
    
    TestNeedsToWaitForBlock();
    
    [self.client getBlock:@"00000000f275c4a72eb44e2385d4ac0acb5760b111fc335c5c400945cbc3bba5" success:^(BitcoinBlock *block) {
        XCTAssertTrue([block.height isEqualToNumber:@193346], @"Block Height should equal 193346");
        BlockFinished();
    } failure:^(NSError *error) {
        XCTAssertNil(@"bewbz", @"In failure block :(");
        BlockFinished();
    }];
    
    WaitForBlock();
}

- (void)testGetInfo {
    NSString *stubDataFileName = @"getinfo.json";
    
    [OHHTTPStubs stubRequestsPassingTest:^BOOL(NSURLRequest *request) {
        return [request.URL.host isEqualToString:self.OHTTPStubHostString];
    } withStubResponse:^OHHTTPStubsResponse*(NSURLRequest *request) {
        return [OHHTTPStubsResponse responseWithFileAtPath:OHPathForFileInBundle(stubDataFileName, nil) statusCode:200 headers:nil];
    }].name = [NSString stringWithFormat:@"Stub for %@", NSStringFromSelector(_cmd)];
    
    TestNeedsToWaitForBlock();
    
    [self.client getInfo:^(BitcoindInfo *info) {
        XCTAssertTrue([info.blocks isEqualToNumber:@666666], @"getInfo.Blocks should be 666666");
        BlockFinished();
    } failure:^(NSError *error) {
        XCTAssertNil(@"bewbz", @"In failure block :(");
        BlockFinished();
    }];
    
    WaitForBlock();
}

- (void)testGetReceivedByAccount {
    NSString *stubDataFileName = @"getreceivedbyaccount.json";
    
    [OHHTTPStubs stubRequestsPassingTest:^BOOL(NSURLRequest *request) {
        return [request.URL.host isEqualToString:self.OHTTPStubHostString];
    } withStubResponse:^OHHTTPStubsResponse*(NSURLRequest *request) {
        return [OHHTTPStubsResponse responseWithFileAtPath:OHPathForFileInBundle(stubDataFileName, nil) statusCode:200 headers:nil];
    }].name = [NSString stringWithFormat:@"Stub for %@", NSStringFromSelector(_cmd)];
    
    TestNeedsToWaitForBlock();
    
    [self.client getReceivedByAccount:@"test" success:^(NSNumber *balance) {
        XCTAssertTrue([balance isEqualToNumber:@1.60000000], @"%@ should be 1.60000000", balance);
        BlockFinished();
    } failure:^(NSError *error) {
        XCTAssertNil(@"bewbz", @"In failure block :(");
        BlockFinished();
    }];
    
    WaitForBlock();
}



@end
