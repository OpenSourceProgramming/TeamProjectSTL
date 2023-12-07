// 라이선스

#include "set_avl.h"

#include <gtest/gtest.h>
#include <iostream>

class SetAVLTestFixture : public testing::Test 
{
public:
    SetAVLTestFixture() {}
    virtual ~SetAVLTestFixture() {}
    void SetUp() override { std::cout << "Test Start\n"; }
    void TearDown() override {}
protected:
    SetAVL set_;
};

// 테스트케이스 1
TEST_F(SetAVLTestFixture, SetAVLTest1)
{
    ASSERT_EQ(0, set_.Insert(38));
    ASSERT_EQ(1, set_.Insert(58));
    ASSERT_EQ(1, set_.Insert(31));
    ASSERT_EQ(2, set_.Insert(27));
    ASSERT_EQ(2, set_.Insert(68));
    ASSERT_EQ(2, set_.Insert(81));
    ASSERT_EQ(2, set_.Insert(14));
    ASSERT_EQ(3, set_.Insert(76));
    ASSERT_EQ(2, set_.Insert(78));
    ASSERT_EQ(3, set_.Insert(37));
    ASSERT_EQ(2, set_.Insert(34));
}

// 테스트케이스 2
TEST_F(SetAVLTestFixture, SetAVLTest2)
{
    ASSERT_EQ(0, set_.Insert(1));
    ASSERT_EQ(1, set_.Insert(2));
    ASSERT_EQ(1, set_.Insert(3));
}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}