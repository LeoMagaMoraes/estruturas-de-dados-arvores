#include "../include/map.hpp"

#include <gtest/gtest.h>

#include <stdexcept>
#include <string>


struct MyValue {
  int id;
  std::string data;

  
  MyValue() : id(0), data("default") {}
  MyValue(int i, std::string d) : id(i), data(std::move(d)) {}

  
  bool operator==(const MyValue& other) const {
    return id == other.id && data == other.data;
  }
  
  bool operator!=(const MyValue& other) const { return !(*this == other); }
};


class MapTest : public ::testing::Test {
 protected:
  Map<int, int> intIntMap;
  Map<std::string, MyValue> stringMyValueMap;
  Map<int, std::string> intStringMap;
};


TEST_F(MapTest, IsEmptyInitially) {
  
  
  const auto& const_map_test = intIntMap;
  ASSERT_THROW(const_map_test[0],
               std::out_of_range);  
  EXPECT_FALSE(intIntMap.remove(0));
  const auto& const_stringMyValueMap = stringMyValueMap;
  ASSERT_THROW(const_stringMyValueMap["test"], std::out_of_range);
  EXPECT_FALSE(stringMyValueMap.remove("test"));
}


TEST_F(MapTest, OperatorSquareBrackets_InsertNew) {
  intIntMap[10] = 100;
  EXPECT_EQ(intIntMap[10], 100);

  stringMyValueMap["alpha"] = MyValue(1, "apple");
  EXPECT_EQ(stringMyValueMap["alpha"].id, 1);
  EXPECT_EQ(stringMyValueMap["alpha"].data, "apple");

  
  
  intStringMap[5];  
                    
  EXPECT_EQ(intStringMap[5], "");  

  MyValue defaultVal;        
  stringMyValueMap["beta"];  
  EXPECT_EQ(stringMyValueMap["beta"].id, defaultVal.id);
  EXPECT_EQ(stringMyValueMap["beta"].data, defaultVal.data);
}

TEST_F(MapTest, OperatorSquareBrackets_AccessExisting) {
  intIntMap[20] = 200;
  EXPECT_EQ(intIntMap[20], 200);

  intIntMap[20] = 201;  
  EXPECT_EQ(intIntMap[20], 201);

  stringMyValueMap["gamma"] = MyValue(2, "grape");
  EXPECT_EQ(stringMyValueMap["gamma"].data, "grape");

  stringMyValueMap["gamma"].data = "guava";  
  EXPECT_EQ(stringMyValueMap["gamma"].data, "guava");
  EXPECT_EQ(stringMyValueMap["gamma"].id, 2);  
}

TEST_F(MapTest, OperatorSquareBrackets_ChainAndDefaultConstruction) {
  
  
  EXPECT_EQ(intStringMap[100], "");  
  intStringMap[100] = "hello";
  EXPECT_EQ(intStringMap[100], "hello");

  EXPECT_EQ(stringMyValueMap["new_key"].data, "default");  
  stringMyValueMap["new_key"].id = 99;
  EXPECT_EQ(stringMyValueMap["new_key"].id, 99);
  EXPECT_EQ(stringMyValueMap["new_key"].data,
            "default");  
}


TEST_F(MapTest, OperatorSquareBracketsConst_AccessExisting) {
  intIntMap[30] = 300;
  const Map<int, int>& constMap = intIntMap;
  EXPECT_EQ(constMap[30], 300);

  stringMyValueMap["delta"] = MyValue(3, "date");
  const Map<std::string, MyValue>& constStringMap = stringMyValueMap;
  EXPECT_EQ(constStringMap["delta"].id, 3);
}

TEST_F(MapTest, OperatorSquareBracketsConst_AccessNonExisting_ShouldThrow) {
  const Map<int, int>& constMap = intIntMap;
  ASSERT_THROW(constMap[35], std::out_of_range);

  const Map<std::string, MyValue>& constStringMap = stringMyValueMap;
  ASSERT_THROW(constStringMap["epsilon"], std::out_of_range);
}


TEST_F(MapTest, Remove_ExistingElement) {
  intIntMap[40] = 400;
  ASSERT_EQ(intIntMap[40], 400);  
  EXPECT_TRUE(intIntMap.remove(40));
  const auto& const_intIntMap = intIntMap;
  ASSERT_THROW(const_intIntMap[40],
               std::out_of_range);  

  stringMyValueMap["zeta"] = MyValue(4, "zucchini");
  
  
  
  
  stringMyValueMap["zeta"];  
  EXPECT_TRUE(stringMyValueMap.remove("zeta"));
  const auto& const_stringMyValueMap = stringMyValueMap;
  ASSERT_THROW(const_stringMyValueMap["zeta"], std::out_of_range);
}

TEST_F(MapTest, Remove_NonExistingElement) {
  EXPECT_FALSE(intIntMap.remove(45));  

  intIntMap[50] = 500;
  EXPECT_FALSE(intIntMap.remove(55));  
  EXPECT_EQ(intIntMap[50], 500);       
}

TEST_F(MapTest, Remove_MultipleAndCheckOrder) {
  intIntMap[10] = 10;
  intIntMap[5] = 5;
  intIntMap[15] = 15;

  EXPECT_TRUE(intIntMap.remove(5));
  const auto& const_intIntMap = intIntMap;
  ASSERT_THROW(const_intIntMap[5], std::out_of_range);
  EXPECT_EQ(intIntMap[10], 10);
  EXPECT_EQ(intIntMap[15], 15);

  EXPECT_TRUE(intIntMap.remove(15));
  ASSERT_THROW(const_intIntMap[15], std::out_of_range);
  EXPECT_EQ(intIntMap[10], 10);

  EXPECT_FALSE(intIntMap.remove(5));  
}


TEST_F(MapTest, ComplexSequenceOfOperations) {
  
  stringMyValueMap["one"] = MyValue(1, "A");
  stringMyValueMap["two"] = MyValue(2, "B");
  stringMyValueMap["three"] = MyValue(3, "C");

  EXPECT_EQ(stringMyValueMap["one"].data, "A");
  EXPECT_EQ(stringMyValueMap["two"].id, 2);

  
  stringMyValueMap["one"].data = "Apple";
  EXPECT_EQ(stringMyValueMap["one"].data, "Apple");

  
  EXPECT_TRUE(stringMyValueMap.remove("two"));
  const auto& constMap = stringMyValueMap;
  ASSERT_THROW(constMap["two"], std::out_of_range);  

  
  ASSERT_THROW(constMap["two"], std::out_of_range);
  EXPECT_EQ(constMap["one"].data, "Apple");

  
  stringMyValueMap["four"] = MyValue(4, "D");
  EXPECT_EQ(stringMyValueMap["four"].id, 4);

  
  EXPECT_TRUE(stringMyValueMap.remove("one"));
  EXPECT_TRUE(stringMyValueMap.remove("three"));
  EXPECT_TRUE(stringMyValueMap.remove("four"));

  
  ASSERT_THROW(constMap["one"], std::out_of_range);
  ASSERT_THROW(constMap["three"], std::out_of_range);
}

TEST_F(MapTest, ScopeAndDestruction) {
  
  
  {
    Map<int, MyValue> scopedMap;
    scopedMap[1] = MyValue(101, "scoped_A");
    scopedMap[2] = MyValue(102, "scoped_B");
    scopedMap[1].data = "Modified_scoped_A";
    scopedMap.remove(2);
    
  }
  
  
  SUCCEED();  

  {
    Map<int, int> intMapScoped;
    intMapScoped[10] = 1;
    intMapScoped[20] = 2;
  }
  SUCCEED();
}
