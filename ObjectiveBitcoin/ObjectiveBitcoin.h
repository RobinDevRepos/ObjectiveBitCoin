//
//  ObjectiveBitcoin.h
//  ObjectiveBitcoin
//
//  Created by Eric Nelson on 2/1/14.
//  Copyright (c) 2014 Sandalsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "Contstants.h"
#import "BitcoinTransaction.h"
#import "BitcoinRawTransaction.h"
#import "BitcoinBlock.h"
#import "BitcoindInfo.h"
#import "BitcoindJSONRPCClient.h"
#import "BitcoinAddress.h"
#import "Account.h"



@interface ObjectiveBitcoin : NSObject

@property BitcoindJSONRPCClient *bitcoindClient;


/**
 *  Instantiates BitcoindJSONRPCClient singleton.  Accepts parameters needed to setup the shared BitcoindJSONRPCClient client that can be resused.
 *
 *  @param host     Host running bitcoind
 *  @param port     The port bitcoind is listening on.  8332 for production, 18332 for testnet
 *  @param username The username to bitcoind is configured to allow access
 *  @param password The password for the username
 *
 *  @return a BitcoindJSONRPCClient singleton
 */
-(id)initWithHost:(NSString *)host
         port:(NSString *)port
     username:(NSString *)username
     password:(NSString *)password;

#pragma mark - bitcoind methods

/**
 *  Returns current bitcoin address for receiving payments to this account.  Bitcoind method: getaccountaddress
 *
 *  @param account The account string to get address for
 *  @param success Success block returning BitcoinAddress object
 *  @param failure Failure block returning NSError
 */
-(void)getAccountAddress:(NSString *)account
                 success:(void (^)(BitcoinAddress *address))success
                 failure:(void (^)(NSError *error))failure;

/**
 *  Returns the balance for the given account name with a minimum number of confirmations (default is 1 confirmation)
 *
 *  @param account Name of the account
 *  @param minconf Minimum number of confirmations
 *  @param success Success block returning the balance for the account specified
 *  @param failure Failure block returning NSError
 */
-(void)getBalanceForAccount:(NSString *)account
withMinimumConfirmations:(NSNumber *)minconf
          success:(void (^)(NSNumber *balance))success
          failure:(void (^)(NSError *error))failure;



-(void)getBalanceForAccount:(NSString *)account
                    success:(void (^)(NSNumber *balance))success
                    failure:(void (^)(NSError *error))failure;


/**
 *  Returns details of the block of the hash input
 *
 *  @param blockHash Hash of block to get details of
 *  @param success   Success block returning details of block in BitcoinBlock object
 *  @param failure   Failure block returning NSError
 */
-(void)getBlock:(NSString *)blockHash
        success:(void (^)(BitcoinBlock *block))success
        failure:(void (^)(NSError *error))failure;

/**
 *  Returns info about running bitcoind instance.  Bitcoind method: getinfo
 *
 *  @param success Success block returning BitcoindInfo object
 *  @param failure Failure block returning NSError
 */
-(void)getInfo:(void (^)(BitcoindInfo *info))success
       failure:(void (^)(NSError *error))failure;

/**
 *  Returns a new bitcoin address for receiving payments. If [account] is specified payments received with the address will be credited to [account].
 *
 *  @param account Account associated with new address.  All payments to the returned address will be credited to this account
 *  @param success Success block returning BitcoinAddress
 *  @param failure Failure block returning NSError
 */
-(void)getNewAddress:(NSString *)account
             success:(void (^)(BitcoinAddress *address))success
             failure:(void (^)(NSError *error))failure;

-(void)getNewAddress:(void (^)(BitcoinAddress *address))success
             failure:(void (^)(NSError *error))failure;

/**
 *  Returns the total amount received by addresses in the specified account in transactions with at least 1 confirmation. If account not provided return will include all transactions to all accounts.
 *
 *  @param account Account name
 *  @param success Success block returning the amount
 *  @param failure Failure block returning NSError
 */
-(void)getReceivedByAccount:(NSString *)account
                    success:(void (^)(NSNumber *amount))success
                    failure:(void (^)(NSError *error))failure;

/**
 *  eturns the total amount received by addresses in the specified account in transactions with at least x confirmations. If account not provided return will include all transactions to all accounts.
 *
 *  @param account Account name
 *  @param minconf Number of minimum confirmations
 *  @param success Success block returning the amount
 *  @param failure Failure block returning NSError
 */
-(void)getReceivedByAccount:(NSString *)account
   withMinimumConfirmations:(NSNumber *)minconf
                    success:(void (^)(NSNumber *amount))success
                    failure:(void (^)(NSError *error))failure;



/**
 *  Returns raw transaction for given transaction ID.  The transaction input need to have been performed on your bitcoind instance OR bitcoind needs to be started with the -reindex -txindex flags set.  Otherwise you'll get an error about an unknown transaction.  See http://bitcoin.stackexchange.com/a/9152/10996 for details.
 *
 *  @param transactionId Valid transaction ID.
 *  @param success       Success block returning details of the raw transaction
 *  @param failure       Failure block returning NSError
 */
-(void)getRawTransaction:(NSString *)transactionId
                 success:(void (^)(BitcoinRawTransaction *rawTransaction))success
                 failure:(void (^)(NSError *error))failure;



/**
 *  Returns transaction details for given transaction ID.  The transaction input need to have been performed on your bitcoind instance.  For non-wallet transactions use getRawTransaction
 *
 *  @param transactionId ID of transaction performed on your wallet
 *  @param transactionId Valid transaction ID.
 *  @param success       Success block returning details of the transaction
 *  @param failure       Failure block returning NSError
 */
-(void)getTransaction:(NSString *)transactionId
              success:(void (^)(BitcoinTransaction *transaction))success
              failure:(void (^)(NSError *error))failure;

/**
 *  Determines if an address is valid and if it is owned by this wallet.  Returns details of the address
 *
 *  @param addressString Bitcoin address string
 *  @param success       Success block returning details of the address
 *  @param failure       Failure block with NSError
 */
-(void)validateAddress:(NSString *)addressString
               success:(void (^)(BitcoinAddress *address))success
               failure:(void (^)(NSError *error))failure;

/**
 *  Lists all accounts balances for each account
 *
 *  @param success Success block returning array of Account objects
 *  @param failure Faulure block with NSError
 */
-(void)listAccounts:(void (^)(NSArray *accounts))success
            failure:(void (^)(NSError *error))failure;

#pragma mark - unimplemented


// Has stub
-(void)getBalanceForAddress:(NSString *)address
   withMinimumConfirmations:(NSNumber *)minconf
                    success:(void (^)(NSNumber *balance))success
                    failure:(void (^)(NSError *error))failure;

// Has stub
-(void)getReceivedByAddress:(NSString *)address
                    success:(void (^)(NSNumber *balance))success
                    failure:(void (^)(NSError *error))failure;

// Has stub
-(void)getReceivedByAddress:(NSString *)address
   withMinimumConfirmations:(NSNumber *)minconf
                    success:(void (^)(NSNumber *balance))success
                    failure:(void (^)(NSError *error))failure;

// Has stub
-(void)getPeerInfo:(void (^)(NSArray *peerList))success
                  failure:(void (^)(NSError *error))failure;

-(void)getAddedNodeInfo:(Boolean)useDNS
                    success:(void (^)(NSString *blockHash))success
                    failure:(void (^)(NSError *error))failure;

-(void)getAddedNodeInfo:(Boolean)useDNS
                   node:(NSString *)nodeString
                success:(void (^)(NSString *blockHash))success
                failure:(void (^)(NSError *error))failure;



-(void)getBlockHashForIndex:(NSNumber *)blockNumber
            success:(void (^)(NSString *blockHash))success
            failure:(void (^)(NSError *error))failure;

-(void)getBlockCount:(void (^)(NSNumber *blockCount))success
                  failure:(void (^)(NSError *error))failure;

-(void)getConnectionCount:(void (^)(NSNumber *connections))success
             failure:(void (^)(NSError *error))failure;

-(void)getDifficulty:(void (^)(NSNumber *difficulty))success
               failure:(void (^)(NSError *error))failure;

-(void)getHashesPerSec:(void (^)(NSNumber *hashesPerSecond))success
             failure:(void (^)(NSError *error))failure;

-(void)getRawMemPool:(void (^)(NSArray *poolList))success
             failure:(void (^)(NSError *error))failure;

-(void)getGenerate:(void (^)(Boolean *isGeneratingHashes))success
             failure:(void (^)(NSError *error))failure;

-(void)getMiningInfo:(void (^)(NSDictionary *miningInfoDict))success
       failure:(void (^)(NSError *error))failure;





@end
