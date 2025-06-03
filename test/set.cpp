#include "../include/set.hpp"

#include <gtest/gtest.h>

class SetTest : public ::testing::Test {
 protected:
  Set<int> intSet;
  Set<std::string> stringSet;
};

TEST_F(SetTest, IsEmptyInitially) {
  EXPECT_FALSE(intSet.search(0));
  EXPECT_FALSE(intSet.search(10));
}

TEST_F(SetTest, InsertNewElement) {
  EXPECT_TRUE(intSet.insert(10));
  EXPECT_TRUE(intSet.search(10));

  EXPECT_TRUE(stringSet.insert("hello"));
  EXPECT_TRUE(stringSet.search("hello"));
}

TEST_F(SetTest, InsertExistingElement) {
  ASSERT_TRUE(intSet.insert(20));
  EXPECT_FALSE(intSet.insert(20));
  EXPECT_TRUE(intSet.search(20));

  ASSERT_TRUE(stringSet.insert("world"));
  EXPECT_FALSE(stringSet.insert("world"));
  EXPECT_TRUE(stringSet.search("world"));
}

TEST_F(SetTest, InsertMultipleElements) {
  EXPECT_TRUE(intSet.insert(5));
  EXPECT_TRUE(intSet.insert(15));
  EXPECT_TRUE(intSet.insert(25));

  EXPECT_TRUE(intSet.search(5));
  EXPECT_TRUE(intSet.search(15));
  EXPECT_TRUE(intSet.search(25));
  EXPECT_FALSE(intSet.search(10));
}

TEST_F(SetTest, RemoveExistingElement) {
  intSet.insert(30);
  ASSERT_TRUE(intSet.search(30));

  EXPECT_TRUE(intSet.remove(30));
  EXPECT_FALSE(intSet.search(30));

  stringSet.insert("test");
  ASSERT_TRUE(stringSet.search("test"));
  EXPECT_TRUE(stringSet.remove("test"));
  EXPECT_FALSE(stringSet.search("test"));
}

TEST_F(SetTest, RemoveNonExistingElement) {
  EXPECT_FALSE(intSet.remove(40));

  intSet.insert(45);
  EXPECT_FALSE(intSet.remove(50));
  EXPECT_TRUE(intSet.search(45));
}

TEST_F(SetTest, RemoveMultipleElements) {
  intSet.insert(100);
  intSet.insert(200);
  intSet.insert(300);

  EXPECT_TRUE(intSet.remove(200));
  EXPECT_FALSE(intSet.search(200));
  EXPECT_TRUE(intSet.search(100));
  EXPECT_TRUE(intSet.search(300));

  EXPECT_TRUE(intSet.remove(100));
  EXPECT_FALSE(intSet.search(100));
  EXPECT_TRUE(intSet.search(300));

  EXPECT_FALSE(intSet.remove(150));
}

TEST_F(SetTest, RemoveUntilEmpty) {
  intSet.insert(1);
  intSet.insert(2);

  EXPECT_TRUE(intSet.remove(1));
  EXPECT_TRUE(intSet.remove(2));

  EXPECT_FALSE(intSet.search(1));
  EXPECT_FALSE(intSet.search(2));
  EXPECT_FALSE(intSet.remove(1));
}

TEST_F(SetTest, searchOnEmptySet) { EXPECT_FALSE(intSet.search(55)); }

TEST_F(SetTest, searchAfterInsertionsAndRemovals) {
  EXPECT_TRUE(intSet.insert(60));
  EXPECT_TRUE(intSet.search(60));
  EXPECT_FALSE(intSet.search(70));

  EXPECT_TRUE(intSet.insert(70));
  EXPECT_TRUE(intSet.search(70));
  EXPECT_TRUE(intSet.search(60));

  EXPECT_TRUE(intSet.remove(60));
  EXPECT_FALSE(intSet.search(60));
  EXPECT_TRUE(intSet.search(70));

  EXPECT_FALSE(intSet.remove(60));
  EXPECT_FALSE(intSet.search(60));
  EXPECT_TRUE(intSet.search(70));
}

TEST_F(SetTest, ComplexSequenceOfOperations) {
  EXPECT_TRUE(intSet.insert(10));
  EXPECT_TRUE(intSet.insert(20));
  EXPECT_TRUE(intSet.insert(5));

  EXPECT_TRUE(intSet.search(10));
  EXPECT_TRUE(intSet.search(20));
  EXPECT_TRUE(intSet.search(5));
  EXPECT_FALSE(intSet.search(15));

  EXPECT_FALSE(intSet.insert(10));

  EXPECT_TRUE(intSet.remove(20));
  EXPECT_FALSE(intSet.search(20));
  EXPECT_TRUE(intSet.search(10));
  EXPECT_TRUE(intSet.search(5));

  EXPECT_FALSE(intSet.remove(25));

  EXPECT_TRUE(intSet.remove(5));
  EXPECT_TRUE(intSet.remove(10));

  EXPECT_FALSE(intSet.search(10));
  EXPECT_FALSE(intSet.search(5));
  EXPECT_FALSE(intSet.remove(10));
}
