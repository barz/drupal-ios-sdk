//
//  DIOSNode.h
//
// ***** BEGIN LICENSE BLOCK *****
// Version: MPL 1.1/GPL 2.0
//
// The contents of this file are subject to the Mozilla Public License Version
// 1.1 (the "License"); you may not use this file except in compliance with
// the License. You may obtain a copy of the License at
// http://www.mozilla.org/MPL/
//
// Software distributed under the License is distributed on an "AS IS" basis,
// WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
// for the specific language governing rights and limitations under the
// License.
//
// The Original Code is Kyle Browning, released June 27, 2010.
//
// The Initial Developer of the Original Code is
// Kyle Browning
// Portions created by the Initial Developer are Copyright (C) 2010
// the Initial Developer. All Rights Reserved.
//
// Contributor(s):
//
// Alternatively, the contents of this file may be used under the terms of
// the GNU General Public License Version 2 or later (the "GPL"), in which
// case the provisions of the GPL are applicable instead of those above. If
// you wish to allow use of your version of this file only under the terms of
// the GPL and not to allow others to use your version of this file under the
// MPL, indicate your decision by deleting the provisions above and replacing
// them with the notice and other provisions required by the GPL. If you do
// not delete the provisions above, a recipient may use your version of this
// file under either the MPL or the GPL.
//
// ***** END LICENSE BLOCK *****

#import <Foundation/Foundation.h>
#import "AFHTTPClient.h"
#import "Settings.h"

@interface DIOSSession : AFHTTPClient {
  NSDictionary *user;
  NSMutableDictionary *accessTokens;
  NSString *consumerKey;
  NSString *consumerSecret;
  NSString *tokenIdentifier;
  NSString *tokenSecret;
}

@property (readwrite, nonatomic, strong) NSURL *baseURL;    // Hsoi 2013-04-18 - This is not right nor good, but Kyle's code is violating the readonly nature of things in all of his "shared session" class methods. Maybe in the past 'baseURL' was a readwrite attribute in AFHTTPClient and so this all worked. But now? Not so much. Frankly, that it's violating this really isn't good given how AFHTTPClient works. But... it's a HUGE beast that I'm unwilling to tackle to fix. It seems workable for now, so we'll just do this to keep the compiler quiet. *sigh*

@property (strong, nonatomic) NSDictionary *user;
@property (nonatomic, retain) NSMutableDictionary *accessTokens;
@property (nonatomic) BOOL signRequests;
@property (nonatomic) BOOL threeLegged;
@property (nonatomic, copy) NSString *realm;
@property (nonatomic, retain) NSString *consumerKey;
@property (nonatomic, retain) NSString *consumerSecret;
@property (nonatomic, retain) NSString *tokenIdentifier;
@property (nonatomic, retain) NSString *tokenSecret;
@property (readwrite, nonatomic, retain) NSURL *baseURL;
+ (DIOSSession *)sharedSession;
+ (DIOSSession *)sharedSessionWithURL:(NSString*)url;
+ (DIOSSession *)sharedOauthSessionWithURL:(NSString*)url consumerKey:(NSString *)aConsumerKey secret:(NSString *)aConsumerSecret;
+ (void) getRequestTokensWithSuccess:(void (^)(AFHTTPRequestOperation *operation, id responseObject))success
                             failure:(void (^)(AFHTTPRequestOperation *operation, NSError *error)) failure;
+ (void) getAccessTokensWithRequestTokens:(NSDictionary *)requesTokens
                                  success:(void (^)(AFHTTPRequestOperation *operation, id responseObject))success
                                  failure:(void (^)(AFHTTPRequestOperation *operation, NSError *error)) failure;

- (void) sendSignedRequestWithPath:(NSString*)path
                      method:(NSString*)method
                      params:(NSDictionary*)params
                     success:(void (^)(AFHTTPRequestOperation *operation, id responseObject))success
                     failure:(void (^)(AFHTTPRequestOperation *operation, NSError *error)) failure;

- (void) addHeaderValue:(NSString*)value forKey:(NSString*)key;
- (NSURLRequest *) signedRequestWithMethod:(NSString *)method
                                      path:(NSString *)path
                                parameters:(NSDictionary *)parameters;
- (id) initWithBaseURL:(NSURL *)url consumerKey:(NSString *)consumerKey secret:(NSString *)consumerSecret;

- (void) setAccessToken:(NSString *)accessToken secret:(NSString *)secret;
- (void) setConsumerKey:(NSString *)consumerKey secret:(NSString *)secret;
@end

