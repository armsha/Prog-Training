/**
 * Testing the tt_test tool.
 * Trying to teach this through template tests:  
 */

#include "tt_test.h"

/**
 * Build test methods doing what is neccessary for setup,
 * and then making the desired asserts.
 */

void testFail(){
	TT_Fail;
}

void testSuccess(){
	TT_Success;
}

void testTrue1(){
	TT_assert_True(true);
}

void testTrue2(){
	TT_assert_True(1==1);
}

void testTrue3(){
	TT_assert_True(1);
	TT_assert_True(1==(2-1));
	char a = 'a';
	TT_assert_True(a=='a'); 
	TT_assert_True(a!='b'); 
}

void testTrueF(){
	TT_assert_True(false); 
}

void testFalse1(){
	TT_assert_False(false);
}

void testFalse2(){
	TT_assert_False(1==2); 
	TT_assert_False(1!=1); 
	TT_assert_False(1==(1+1));
}

void testFalseF(){
	TT_assert_False(true);
}

void testEQ(){
	TT_assert_EQ(1,1);
	TT_assert_EQ(1-1,0);
	TT_assert_EQ('a','a');
}

void testEQF(){
	TT_assert_EQ('a','b');
}

void testNEQ(){
	TT_assert_NotEQ(1,2);
	TT_assert_NotEQ(1-1,3);
	TT_assert_NotEQ('a','b');
}

void testNEQF(){
	TT_assert_NotEQ('a','a');
}

void testSTREQ1(){
	TT_assert_STREQ("abc","abc");
}

void testSTREQ2(){
	TT_assert_STREQ( "", "" );
	TT_assert_STREQ( "a", "a" );
	TT_assert_STREQ( "abcd", "abcd" );
}

void testSTREQF(){
	TT_assert_STREQ( "abcd","abce" );
}

void testNotNull(){
	int a = 5;
	TT_assert_NotNull( &a );
}

void testNotNullF(){
	TT_assert_NotNull( NULL );
}

void testFF1(){
	TT_assert_True( FLOAT_EQ(1.0, 1.0, 0.0000001) );
	TT_assert_True( FLOAT_EQ(1.5, 1.5, 0.0000001) );
	TT_assert_True( FLOAT_EQ(3.0, 3.0, 0.0000001) );
	TT_assert_True( FLOAT_EQ(-11234.13210, -11234.13210, 0.0000001) );


	TT_assert_False( FLOAT_EQ(1.0, 2.0, 0.0000001) );
	TT_assert_False( FLOAT_EQ(1.5, 2.5, 0.0000001) );
	TT_assert_False( FLOAT_EQ(3.0, 2.0, 0.0000001) );
	TT_assert_False( FLOAT_EQ(-11234.13210, -11234.13212, 0.0000001) );
}


void testFF2(){
	
	TT_assert_True( FLOAT_EQ(1.0, 1.0, 0.0000000000001) );
	TT_assert_True( FLOAT_EQ(1.5, 1.51, 0.1) );
	TT_assert_True( FLOAT_EQ(3.001, 3.0, 0.001) );
	TT_assert_True( FLOAT_EQ(-11234.13210, -11233.13210, 1.1) );


	TT_assert_False( FLOAT_EQ(1.0, 1.01, 0.0000001) );
	TT_assert_False( FLOAT_EQ(1.5, 1.500011, 0.00001) );
	TT_assert_False( FLOAT_EQ(3.0, 2.0, 0.1) );
}

/**
 * Then run the test methods by calling as follows:
 * TT_SETUP; To reset counters.
 * TT_TEST( <testMethodName> ); to perform test of the method.
 * ...
 * TT_FINAL; To print results.
 */

int main(void){

	TT_SETUP;
	TT_TEST(testFail);
	TT_TEST(testSuccess);
	TT_TEST(testTrue1);
	TT_FINAL;


	TT_SETUP;
	TT_TEST(testTrue1);
	TT_TEST(testTrue2);
	TT_TEST(testTrue3);
	TT_TEST(testTrueF);
	TT_TEST(testFalse1);
	TT_TEST(testFalse2);
	TT_TEST(testFalseF);
	TT_TEST(testEQ);
	TT_TEST(testEQF);
	TT_TEST(testNEQ);
	TT_TEST(testNEQF);
	TT_TEST(testSTREQ1);
	TT_TEST(testSTREQ2);
	TT_TEST(testSTREQF);
	TT_TEST(testFF1);
	TT_TEST(testFF2);
	TT_TEST(testNotNull);
	TT_TEST(testNotNullF);
	TT_FINAL;

	TT_SETUP;
	TT_TEST(testSuccess);
	TT_TEST(testTrue3);
	TT_TEST(testEQ);
	TT_FINAL;

	TT_SETUP;
	TT_TEST(testEQF);
	TT_TEST(testNEQF);
	TT_FINAL;

	TT_SETUP;
	TT_TEST(testTrueF);
	TT_TEST(testFalseF);
	TT_FINAL;

	return 0;
}
