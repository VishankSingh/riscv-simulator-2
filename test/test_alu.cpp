#include <gtest/gtest.h>
#include "../include/vm/alu.h"

TEST(ALUTest, AddTest) {
  alu::Alu alu;
  auto result = alu.execute(alu::AluOp::kAdd, 10, 20);
  ASSERT_EQ(result.first, 30);
  ASSERT_FALSE(result.second);
}

TEST(ALUTest, SubTest) {
  alu::Alu alu;
  auto result = alu.execute(alu::AluOp::kSub, 10, 20);
  ASSERT_EQ(result.first, -10);
  ASSERT_FALSE(result.second);
}

TEST(ALUTest, MulTest) {
  alu::Alu alu;
  auto result = alu.execute(alu::AluOp::kMul, 10, 20);
  ASSERT_EQ(result.first, 200);
  ASSERT_FALSE(result.second);
}

TEST(ALUTest, SllTest) {
  alu::Alu alu;
  auto result = alu.execute(alu::AluOp::kSll, 0b1010, 1);
  ASSERT_EQ(result.first, 0b10100);
  ASSERT_FALSE(result.second);
}

TEST(ALUTest, SrlTest) {
  alu::Alu alu;
  auto result = alu.execute(alu::AluOp::kSrl, 0b1010, 1);
  ASSERT_EQ(result.first, 0b101);
  ASSERT_FALSE(result.second);
}

TEST(ALUTest, SraTest) {
  alu::Alu alu;
  auto result = alu.execute(alu::AluOp::kSra, 0xfffffffffffffffa, 2);
  ASSERT_EQ(result.first, 0xfffffffffffffffe);
  ASSERT_FALSE(result.second);
}

TEST(SHITTest, shittyTest) {
  int a = 19;
  EXPECT_EQ(a, 19);
}