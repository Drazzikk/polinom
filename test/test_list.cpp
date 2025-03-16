#include "gtest.h"
#include "list.h"

TEST(ListTest, DefaultConstructorCreatesEmptyList)
{
    List<int> list;
    EXPECT_EQ(list.get_size(), 0);
    EXPECT_EQ(list.begin(), list.end());
}

TEST(ListTest, PushFrontAddsElementToFront)
{
    List<int> list;
    list.push_front(1);
    list.push_front(2);

    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(*list.begin(), 2);
}

TEST(ListTest, PushBackAddsElementToEnd)
{
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    EXPECT_EQ(list.get_size(), 2);

    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
}

TEST(ListTest, PopFrontRemovesFirstElement)
{
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.pop_front();

    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(*list.begin(), 2);
}

TEST(ListTest, PopFrontOnEmptyListThrowsException)
{
    List<int> list;
    EXPECT_THROW(list.pop_front(), std::logic_error);
}

TEST(ListTest, InsertAddsElementAfterGivenNode)
{
    List<int> list;
    list.push_back(1);
    list.push_back(3);

    auto it = list.begin();
    list.insert(2, it.get_current());

    EXPECT_EQ(list.get_size(), 3);

    auto it2 = list.begin();
    EXPECT_EQ(*it2, 1);
    ++it2;
    EXPECT_EQ(*it2, 2);
    ++it2;
    EXPECT_EQ(*it2, 3);
}

TEST(ListTest, InsertAtNullptrAddsToFront)
{
    List<int> list;
    list.push_back(2);

    list.insert(1, nullptr);

    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(*list.begin(), 1);
}

TEST(ListTest, ClearRemovesAllElements)
{
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.clear();

    EXPECT_EQ(list.get_size(), 0);
    EXPECT_EQ(list.begin(), list.end());
}

TEST(ListTest, CopyConstructorCopiesList)
{
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    List<int> list2 = list1;

    EXPECT_EQ(list2.get_size(), 2);

    auto it = list2.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
}

TEST(ListTest, AssignmentOperatorCopiesList)
{
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    List<int> list2;
    list2.push_back(3);

    list2 = list1;

    EXPECT_EQ(list2.get_size(), 2);

    auto it = list2.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
}

TEST(ListTest, SelfAssignmentDoesNotChangeList)
{
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    list = list;

    EXPECT_EQ(list.get_size(), 2);

    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
}

TEST(ListTest, IteratorWorksCorrectly)
{
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto it = list.begin();

    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(it, list.end());
}

TEST(ListTest, IteratorComparisonWorksCorrectly)
{
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    auto it1 = list.begin();
    auto it2 = list.begin();

    EXPECT_EQ(it1, it2);

    ++it1;
    EXPECT_NE(it1, it2);
}

TEST(ListTest, IteratorDereferenceThrowsOnEnd)
{
    List<int> list;
    list.push_back(1);

    auto it = list.begin();
    ++it;

    EXPECT_THROW(*it, std::logic_error);
}

TEST(ListTest, InsertAfterLastAddsToEnd)
{
    List<int> list;
    list.push_back(1);

    auto it = list.begin();
    list.insert(2, it.get_current());

    EXPECT_EQ(list.get_size(), 2);

    auto it2 = list.begin();
    EXPECT_EQ(*it2, 1);
    ++it2;
    EXPECT_EQ(*it2, 2);
}

TEST(ListTest, MultiplePushAndPopOperationsWorkCorrectly)
{
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_front(0);

    EXPECT_EQ(list.get_size(), 3);

    auto it = list.begin();
    EXPECT_EQ(*it, 0);
    ++it;
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);

    list.pop_front();
    list.pop_front();

    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(*list.begin(), 2);
}