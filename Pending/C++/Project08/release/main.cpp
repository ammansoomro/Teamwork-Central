#include <iostream>
#include "gtest/gtest.h"

using namespace std;

TEST(testing, test01)
{
	ASSERT_TRUE( 2 == 3 );
}

TEST(testing, test02)
{
	ASSERT_TRUE( 2 == 2 );
}

int main()
{
    ::testing::InitGoogleTest();

    //
    // run all the tests, returns 0 if they
    // all pass and 1 if any fail:
    //
    int result = RUN_ALL_TESTS();

    return result;
}

