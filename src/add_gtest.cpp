#include "gtest/gtest.h"

int add(int a, int b) {return a + b;}

TEST(AddTest, PositiveTest) {
  auto result = add(1, 2);
  EXPECT_EQ(result, 3);
}
