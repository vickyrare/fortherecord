#include <gtest/gtest.h>
#include "NumberFrequencyManager.h"

TEST(ForTheRecord, testFibonacci)
{
	NumberFrequencyManager nfm;
    EXPECT_EQ (nfm.isFibonacci(0), true);
    EXPECT_EQ (nfm.isFibonacci(1), true);
    EXPECT_EQ (nfm.isFibonacci(2), true);
    EXPECT_EQ (nfm.isFibonacci(3), true);
    EXPECT_EQ (nfm.isFibonacci(5), true);
    EXPECT_EQ (nfm.isFibonacci(8), true);
}

TEST(ForTheRecord, testNotFibonacci)
{
    NumberFrequencyManager nfm;
    EXPECT_EQ (nfm.isFibonacci(4), false);
    EXPECT_EQ (nfm.isFibonacci(6), false);
    EXPECT_EQ (nfm.isFibonacci(7), false);
    EXPECT_EQ (nfm.isFibonacci(9), false);
    EXPECT_EQ (nfm.isFibonacci(10), false);
}

TEST(ForTheRecord, testInsert)
{
    NumberFrequencyManager nfm;
    nfm.insertDatatable(10);
    nfm.insertDatatable(10);
    nfm.insertDatatable(10);
    nfm.insertDatatable(9);
    nfm.insertDatatable(9);
    nfm.insertDatatable(8);
    nfm.insertDatatable(5);
    nfm.insertDatatable(5);

    std::map<int, int> m = nfm.getDatatable();
    EXPECT_EQ (m[10], 3);
    EXPECT_EQ (m[5], 2);
    EXPECT_EQ (m[9], 2);
    EXPECT_EQ (m[8], 1);
}

TEST(ForTheRecord, testSort)
{
    NumberFrequencyManager nfm;
    nfm.insertDatatable(10);
    nfm.insertDatatable(8);
    nfm.insertDatatable(10);
    nfm.insertDatatable(9);
    nfm.insertDatatable(5);
    nfm.insertDatatable(5);
    nfm.insertDatatable(9);
    nfm.insertDatatable(10);

    std::vector<pair<int, int>> vec = nfm.getSortedDatatable();
    EXPECT_EQ (vec[0].first, 10);
    EXPECT_EQ (vec[0].second, 3);

    EXPECT_EQ (vec[1].first, 5);
    EXPECT_EQ (vec[1].second, 2);

    EXPECT_EQ (vec[2].first,9);
    EXPECT_EQ (vec[2].second, 2);

    EXPECT_EQ (vec[3].first, 8);
    EXPECT_EQ (vec[3].second, 1);
}

int main(int argc, char** argv) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}