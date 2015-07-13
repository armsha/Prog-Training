/**
 * The terribly tiny testing tool.
 * Thanks to O.O
 */

#ifndef __TTTEST_H__
#define __TTTEST_H__

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

/** Counters and variables for testing. */
static unsigned int 	testCount   = 0;
static unsigned int 	successCount= 0;
static unsigned int 	failCount   = 0;
static bool 			testStatus  = true;

/** File to use for logging, stderr default. */
FILE * 					TT_logFile  = NULL; 


/** Macro for allowing macros to call code. */
#define _DO( expr ) do { expr } while(0)


/** Setup the tester, resetting counters. */
#define TT_SETUP _DO( testCount = 0; successCount = 0; \
		failCount = 0; testStatus = true; )

/** Print count and result. */
#define TT_FINAL _DO(   \
		TT_LOG( "TT:\t%u/%u\tTests successful!\n"     \
			"TT:\t%s\n\n", successCount, testCount, \
			((failCount!=0)?("Failure!"):("All Passed!")) ); )

/** Result quiet, checking the number of failures. */
#define TT_FINAL_Q ( failCount==0 )


/** Log the given message using fprintf to TT_logFile (stderr if null). */
#define TT_LOG( msg... ) _DO(  \
		if ( TT_logFile == NULL ) TT_logFile = stderr; \
		fprintf( TT_logFile, msg ); )


/** Setup a test on the given function, and print the result. */
#define TT_TEST( func ) _DO( \
		testStatus = true; \
		func(); \
		testCount++; \
		if ( !testStatus ){  \
		    TT_LOG( "TT:\t%-15s Failed!\n", #func ); \
		    failCount++; \
		}else{  \
		    TT_LOG( "TT:\t%-15s Passed!\n", #func ); \
		    successCount++; \
		} )

/** Only test the given function, don't print */
#define TT_TEST_Q( func ) _DO( \
		testStatus = true; \
		func(); \
		testCount++; \
		if ( !testStatus ){  \
		    failCount++; \
		}else{  \
		    successCount++; \
		} )

/** Asserts to use, determines if tests fail or not. */
#define TT_assert_True( expr )    _DO( if( (expr)!=true ) TT_Fail; )
#define TT_assert_False( expr )   _DO( if( (expr)!=false ) TT_Fail; )
#define TT_assert_EQ( a, b )      _DO( if( (a)!=(b) ) TT_Fail; )
#define TT_assert_NotEQ( a, b )   _DO( if( (a)==(b) ) TT_Fail; )
#define TT_assert_STREQ( a, b )   _DO( if( !STR_EQ( (a), (b) ) ) TT_Fail; )
#define TT_assert_NotNull( expr ) _DO( if( (expr)==NULL ) TT_Fail; )

/** Fail or pass a test. Success will overwrite fails! */
#define TT_Fail            testStatus=false 
#define TT_Success         testStatus=true 

/** Match a char * with strcmp */
#define STR_EQ( str1, str2 ) ( strcmp( (str1), (str2) ) == 0 ) 

/** Chec if a float is equal to another, using a given epsilon */
#define FLOAT_EQ( f1, f2, eps ) ( ( f1 >= (f2-eps) ) && ( f1 <= (f2+eps) ) ) 

#endif

/**
 * Example usage and sanity check found at tt_test.c!
 */
