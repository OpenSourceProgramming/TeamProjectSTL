/**************************************************
 * Copyright INHA_OSAP_004_Froyo
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 *
 * Contributors: Lee Seung-Bin
 * Latest Updated on 2023-12-15
**************************************************/

#include "set_avl.h"

#include <gtest/gtest.h>
#include <iostream>
#include <tuple>
#include <vector>

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

enum class TestOperations { INSERT, FIND, ERASE };

class SetAVLParameterizedFixture 
: public testing::TestWithParam<std::vector<std::tuple<TestOperations, int, int>>>
{
public:
protected:
    SetAVL set_;
};

TEST_P(SetAVLParameterizedFixture, SetAVLTest) {
    std::vector<std::tuple<TestOperations, int, int>> param = GetParam();

    for (auto& tuple: param)
    {
        TestOperations operation = std::get<0>(tuple);
        int value = std::get<1>(tuple);
        int expected_value = std::get<2>(tuple);

        switch (operation)
        {
        case TestOperations::INSERT:
            ASSERT_EQ(expected_value, set_.Insert(value));
            break;
        case TestOperations::FIND:
            ASSERT_EQ(expected_value, set_.Find(value));
            break;
        case TestOperations::ERASE:
            ASSERT_EQ(expected_value, set_.Erase(value));
            break;
        }
    }
}

// 테스트케이스 1
INSTANTIATE_TEST_CASE_P(
    InsertionTest1, SetAVLParameterizedFixture,
    testing::Values(std::vector<std::tuple<TestOperations, int, int>> {
        std::make_tuple(TestOperations::INSERT, 38, 0),
        std::make_tuple(TestOperations::INSERT, 58, 1),
        std::make_tuple(TestOperations::INSERT, 31, 1),
        std::make_tuple(TestOperations::INSERT, 27, 2),
        std::make_tuple(TestOperations::INSERT, 68, 2),
        std::make_tuple(TestOperations::INSERT, 81, 2),
        std::make_tuple(TestOperations::INSERT, 14, 2),
        std::make_tuple(TestOperations::INSERT, 76, 3),
        std::make_tuple(TestOperations::INSERT, 78, 2),
        std::make_tuple(TestOperations::INSERT, 37, 3),
        std::make_tuple(TestOperations::INSERT, 34, 2)
    })
);

// 테스트케이스 2
INSTANTIATE_TEST_CASE_P(
    InsertionTest2, SetAVLParameterizedFixture,
    testing::Values(std::vector<std::tuple<TestOperations, int, int>> {
        std::make_tuple(TestOperations::INSERT, 1, 0),
        std::make_tuple(TestOperations::INSERT, 2, 1),
        std::make_tuple(TestOperations::INSERT, 3, 1)
    })
);

// 테스트케이스 3
INSTANTIATE_TEST_CASE_P(
    AdvancedTest1, SetAVLParameterizedFixture,
    testing::Values(std::vector<std::tuple<TestOperations, int, int>> {
        std::make_tuple(TestOperations::INSERT, 10, 0),
        std::make_tuple(TestOperations::INSERT, 5, 1),
        std::make_tuple(TestOperations::INSERT, 15, 1),
        std::make_tuple(TestOperations::ERASE, 10, 0),
        std::make_tuple(TestOperations::FIND, 15, 0),
        std::make_tuple(TestOperations::FIND, 5, 1)
    })
);

// 테스트케이스 4
TEST_F(SetAVLTestFixture, SetAVLTest4)
{
    ASSERT_EQ(0, set_.Insert(20));
    ASSERT_EQ(1, set_.Insert(10));
    ASSERT_EQ(1, set_.Insert(30));
    ASSERT_EQ(2, set_.Insert(0));
    ASSERT_EQ(2, set_.Insert(15));
    ASSERT_EQ(2, set_.Insert(25));
    ASSERT_EQ(2, set_.Insert(40));
    ASSERT_EQ(3, set_.Insert(22));
    ASSERT_EQ(3, set_.Insert(27));
    ASSERT_EQ(1, set_.Erase(30));
    ASSERT_EQ(2, set_.Find(40));
    set_.Maximum(20); // 40 2
    std::cout << "\n";
    set_.Maximum(40); // 40 2
    std::cout << "\n";
    set_.Minimum(40); // 27 3
    std::cout << "\n";
    set_.Maximum(25); // 40 2
    std::cout << "\n";
    set_.Minimum(25); // 22 2
    std::cout << "\n";
}

// 테스트케이스 5
TEST_F(SetAVLTestFixture, SetAVLTest5)
{
    for (int key = 1; key <= 7; key++)
        set_.Insert(key);
    ASSERT_EQ(0, set_.Find(4));
    ASSERT_EQ(1, set_.Find(2));
    ASSERT_EQ(1, set_.Find(6));
    set_.Maximum(4); // 7 2
    std::cout << "\n";
    set_.Minimum(4); // 1 2
    std::cout << "\n";
}

// 테스트케이스 6 (삭제하려고 하는 노드의 자식이 없는 경우)
// TEST_F(SetAVLTestFixture, SetAVLTest6)
// {
//     ASSERT_EQ(0, set_.Insert(16));

//     ASSERT_EQ(1, set_.Insert(8));
//     ASSERT_EQ(1, set_.Insert(19));

//     ASSERT_EQ(2, set_.Insert(4));
//     ASSERT_EQ(2, set_.Insert(12));
//     ASSERT_EQ(2, set_.Insert(18));
//     ASSERT_EQ(2, set_.Insert(20));

//     ASSERT_EQ(3, set_.Insert(2));
//     ASSERT_EQ(3, set_.Insert(6));
//     ASSERT_EQ(3, set_.Insert(10));
//     ASSERT_EQ(3, set_.Insert(14));
//     ASSERT_EQ(3, set_.Insert(17));

//     ASSERT_EQ(4, set_.Insert(1));
//     ASSERT_EQ(4, set_.Insert(3));
//     ASSERT_EQ(4, set_.Insert(5));
//     ASSERT_EQ(4, set_.Insert(7));
//     ASSERT_EQ(4, set_.Insert(9));
//     ASSERT_EQ(4, set_.Insert(11));
//     ASSERT_EQ(4, set_.Insert(13));
//     ASSERT_EQ(4, set_.Insert(15));

//     ASSERT_EQ(2, set_.Erase(20));
//     ASSERT_EQ(19, set_.GetSize());

//     ASSERT_EQ(0, set_.Find(8));
//     ASSERT_EQ(1, set_.Find(4));
//     ASSERT_EQ(1, set_.Find(16));

//     set_.Maximum(8); // 19 3
//     std::cout << "\n";
//     set_.Minimum(8); // 1 3
//     std::cout << "\n";
//     set_.Minimum(16); // 9 4
//     std::cout << "\n";
// }

// 테스트케이스 7 (삭제하려고 하는 노드의 자식이 2개인 경우)
TEST_F(SetAVLTestFixture, SetAVLTest7)
{
    ASSERT_EQ(0, set_.Insert(14));

    ASSERT_EQ(1, set_.Insert(5));
    ASSERT_EQ(1, set_.Insert(17));

    ASSERT_EQ(2, set_.Insert(2));
    ASSERT_EQ(2, set_.Insert(8));
    ASSERT_EQ(2, set_.Insert(15));
    ASSERT_EQ(2, set_.Insert(20));

    ASSERT_EQ(3, set_.Insert(1));
    ASSERT_EQ(3, set_.Insert(4));
    ASSERT_EQ(3, set_.Insert(6));
    ASSERT_EQ(3, set_.Insert(12));
    ASSERT_EQ(3, set_.Insert(16));
    ASSERT_EQ(3, set_.Insert(18));
    ASSERT_EQ(3, set_.Insert(21));

    ASSERT_EQ(4, set_.Insert(3));
    ASSERT_EQ(4, set_.Insert(7));
    ASSERT_EQ(4, set_.Insert(10));
    ASSERT_EQ(4, set_.Insert(13));
    ASSERT_EQ(4, set_.Insert(19));
    ASSERT_EQ(5, set_.Insert(9));
    ASSERT_EQ(5, set_.Insert(11));

    ASSERT_EQ(1, set_.Erase(17));

    ASSERT_EQ(0, set_.Find(8));
    ASSERT_EQ(1, set_.Find(5));
    ASSERT_EQ(1, set_.Find(14));
    ASSERT_EQ(2, set_.Find(2));
    ASSERT_EQ(2, set_.Find(6));
    ASSERT_EQ(2, set_.Find(12));
    ASSERT_EQ(2, set_.Find(18));
    ASSERT_EQ(3, set_.Find(1));
    ASSERT_EQ(3, set_.Find(4));
    ASSERT_EQ(3, set_.Find(7));
    ASSERT_EQ(3, set_.Find(10));
    ASSERT_EQ(3, set_.Find(13));
    ASSERT_EQ(3, set_.Find(15));
    ASSERT_EQ(3, set_.Find(20));
    ASSERT_EQ(4, set_.Find(3));
    ASSERT_EQ(4, set_.Find(9));
    ASSERT_EQ(4, set_.Find(11));
    ASSERT_EQ(4, set_.Find(16));
    ASSERT_EQ(4, set_.Find(19));
    ASSERT_EQ(4, set_.Find(21));

    set_.Maximum(8); // 21 4
    std::cout << "\n";
    set_.Minimum(8); // 1 3
    std::cout << "\n";
    set_.Maximum(5); // 7 3
    std::cout << "\n";
    set_.Minimum(5); // 1 3
    std::cout << "\n";
    set_.Maximum(14); // 21 4
    std::cout << "\n";
    set_.Minimum(14); // 9 4
    std::cout << "\n";
}

// // 테스트케이스 8 (삭제하려고 하는 노드의 자식이 2개인 경우)
TEST_F(SetAVLTestFixture, SetAVLTest8)
{
    ASSERT_EQ(0, set_.Insert(21));
    ASSERT_EQ(1, set_.Insert(13));
    ASSERT_EQ(1, set_.Insert(29));
    ASSERT_EQ(2, set_.Insert(8));
    ASSERT_EQ(2, set_.Insert(18));
    ASSERT_EQ(2, set_.Insert(24));
    ASSERT_EQ(2, set_.Insert(31));
    ASSERT_EQ(3, set_.Insert(5));
    ASSERT_EQ(3, set_.Insert(10));
    ASSERT_EQ(3, set_.Insert(15));
    ASSERT_EQ(3, set_.Insert(20));
    ASSERT_EQ(3, set_.Insert(23));
    ASSERT_EQ(3, set_.Insert(27));
    ASSERT_EQ(3, set_.Insert(30));
    ASSERT_EQ(3, set_.Insert(32));
    ASSERT_EQ(4, set_.Insert(3));
    ASSERT_EQ(4, set_.Insert(6));
    ASSERT_EQ(4, set_.Insert(9));
    ASSERT_EQ(4, set_.Insert(11));
    ASSERT_EQ(4, set_.Insert(14));
    ASSERT_EQ(4, set_.Insert(17));
    ASSERT_EQ(4, set_.Insert(19));
    ASSERT_EQ(4, set_.Insert(22));
    ASSERT_EQ(4, set_.Insert(25));
    ASSERT_EQ(4, set_.Insert(28));
    ASSERT_EQ(4, set_.Insert(33));
    ASSERT_EQ(5, set_.Insert(2));
    ASSERT_EQ(5, set_.Insert(4));
    ASSERT_EQ(5, set_.Insert(7));
    ASSERT_EQ(5, set_.Insert(12));
    ASSERT_EQ(5, set_.Insert(16));
    ASSERT_EQ(5, set_.Insert(26));
    ASSERT_EQ(6, set_.Insert(1));

    ASSERT_EQ(2, set_.Erase(31));

    ASSERT_EQ(0, set_.Find(13));
    ASSERT_EQ(1, set_.Find(8));
    ASSERT_EQ(1, set_.Find(21));
    ASSERT_EQ(2, set_.Find(5));
    ASSERT_EQ(2, set_.Find(10));
    ASSERT_EQ(2, set_.Find(18));
    ASSERT_EQ(2, set_.Find(27));
    ASSERT_EQ(3, set_.Find(3));
    ASSERT_EQ(3, set_.Find(6));
    ASSERT_EQ(3, set_.Find(9));
    ASSERT_EQ(3, set_.Find(11));
    ASSERT_EQ(3, set_.Find(15));
    ASSERT_EQ(3, set_.Find(20));
    ASSERT_EQ(3, set_.Find(24));
    ASSERT_EQ(3, set_.Find(29));
    ASSERT_EQ(4, set_.Find(2));
    ASSERT_EQ(4, set_.Find(4));
    ASSERT_EQ(4, set_.Find(7));
    ASSERT_EQ(4, set_.Find(12));
    ASSERT_EQ(4, set_.Find(14));
    ASSERT_EQ(4, set_.Find(17));
    ASSERT_EQ(4, set_.Find(19));
    ASSERT_EQ(4, set_.Find(23));
    ASSERT_EQ(4, set_.Find(25));
    ASSERT_EQ(4, set_.Find(28));
    ASSERT_EQ(4, set_.Find(32));
    ASSERT_EQ(5, set_.Find(1));
    ASSERT_EQ(5, set_.Find(16));
    ASSERT_EQ(5, set_.Find(22));
    ASSERT_EQ(5, set_.Find(26));
    ASSERT_EQ(5, set_.Find(30));
    ASSERT_EQ(5, set_.Find(33));

    set_.Maximum(13); // 33 5
    std::cout << "\n";
    set_.Minimum(13); // 1 5
    std::cout << "\n";
    set_.Maximum(8); // 12 4
    std::cout << "\n";
    set_.Maximum(5); // 7 4
    std::cout << "\n";
    set_.Maximum(3); // 4 4
    std::cout << "\n";
    set_.Minimum(10); // 9 3
    std::cout << "\n";
    set_.Minimum(21); // 14 4
    std::cout << "\n";
    set_.Maximum(18); // 20 3
    std::cout << "\n";
    set_.Maximum(15); // 17 4
    std::cout << "\n";
    set_.Minimum(27); // 22 5
    std::cout << "\n";
    set_.Minimum(29); // 28 4
    std::cout << "\n";
}

// 테스트케이스 9 (삭제하려고 하는 노드의 자식이 2개인 경우)
TEST_F(SetAVLTestFixture, SetAVLTest9)
{
    ASSERT_EQ(0, set_.Insert(5));
    ASSERT_EQ(1, set_.Insert(2));
    ASSERT_EQ(1, set_.Insert(8));
    ASSERT_EQ(2, set_.Insert(1));
    ASSERT_EQ(2, set_.Insert(4));
    ASSERT_EQ(2, set_.Insert(6));
    ASSERT_EQ(2, set_.Insert(11));
    ASSERT_EQ(3, set_.Insert(3));
    ASSERT_EQ(3, set_.Insert(7));
    ASSERT_EQ(3, set_.Insert(10));
    ASSERT_EQ(3, set_.Insert(12));
    ASSERT_EQ(4, set_.Insert(9));

    ASSERT_EQ(1, set_.Erase(2));

    ASSERT_EQ(0, set_.Find(8));
    ASSERT_EQ(1, set_.Find(5));
    ASSERT_EQ(1, set_.Find(11));
    ASSERT_EQ(2, set_.Find(3));
    ASSERT_EQ(2, set_.Find(6));
    ASSERT_EQ(2, set_.Find(10));
    ASSERT_EQ(2, set_.Find(12));
    ASSERT_EQ(3, set_.Find(1));
    ASSERT_EQ(3, set_.Find(4));
    ASSERT_EQ(3, set_.Find(7));
    ASSERT_EQ(3, set_.Find(9));

    set_.Maximum(8); // 12 2
    std::cout << "\n";
    set_.Minimum(8); // 1 3
    std::cout << "\n";
    set_.Maximum(5); // 7 3
    std::cout << "\n";
    set_.Maximum(3); // 4 3
    std::cout << "\n";
    set_.Minimum(6); // 6 2
    std::cout << "\n";
    set_.Minimum(11); // 9 3
    std::cout << "\n";
    set_.Maximum(10); // 10 2
    std::cout << "\n";
}

// 테스트케이스 10 (삭제하려고 하는 노드의 자식이 2개인 경우)
TEST_F(SetAVLTestFixture, SetAVLTest10)
{
    ASSERT_EQ(0, set_.Insert(5));
    ASSERT_EQ(1, set_.Insert(2));
    ASSERT_EQ(1, set_.Insert(10));
    ASSERT_EQ(2, set_.Insert(1));
    ASSERT_EQ(2, set_.Insert(4));
    ASSERT_EQ(2, set_.Insert(8));
    ASSERT_EQ(2, set_.Insert(12));
    ASSERT_EQ(3, set_.Insert(3));
    ASSERT_EQ(3, set_.Insert(7));
    ASSERT_EQ(3, set_.Insert(9));
    ASSERT_EQ(3, set_.Insert(11));
    ASSERT_EQ(3, set_.Insert(13));
    ASSERT_EQ(4, set_.Insert(6));

    ASSERT_EQ(1, set_.Erase(2));

    ASSERT_EQ(0, set_.Find(8));
    ASSERT_EQ(1, set_.Find(5));
    ASSERT_EQ(1, set_.Find(10));
    ASSERT_EQ(2, set_.Find(3));
    ASSERT_EQ(2, set_.Find(7));
    ASSERT_EQ(2, set_.Find(9));
    ASSERT_EQ(2, set_.Find(12));
    ASSERT_EQ(3, set_.Find(1));
    ASSERT_EQ(3, set_.Find(4));
    ASSERT_EQ(3, set_.Find(6));
    ASSERT_EQ(3, set_.Find(11));
    ASSERT_EQ(3, set_.Find(13));

    set_.Maximum(8); // 13 3
    std::cout << "\n";
    set_.Minimum(8); // 1 3
    std::cout << "\n";
    set_.Maximum(5); // 7 2
    std::cout << "\n";
    set_.Maximum(3); // 4 3
    std::cout << "\n";
    set_.Minimum(10); // 9 2
    std::cout << "\n";
    set_.Minimum(12); // 11 3
    std::cout << "\n";
}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}