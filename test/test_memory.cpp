/**
 * File Name: test_memory.cpp
 * Author: Vishank Singh
 * Github: https://github.com/VishankSingh
 */

#include <gtest/gtest.h>
#include "../include/vm/main_memory.h"

TEST(MemoryTest, ReadWriteTest) {
  Memory memory;
  memory.Write(0, 1);
  memory.Write(1024, 2);
  memory.Write(2048, 3);
  memory.Write(268435456, 4);

  EXPECT_EQ(memory.Read(0), 1);
  EXPECT_EQ(memory.Read(1024), 2);
  EXPECT_EQ(memory.Read(2048), 3);
  EXPECT_EQ(memory.Read(268435456), 4);

}

TEST(MemoryTest, ReadWriteByteTest) {
  Memory memory;
  memory.WriteByte(0, 1);
  memory.WriteByte(1024, 2);
  memory.WriteByte(2048, 3);
  memory.WriteByte(268435456, 4);

  EXPECT_EQ(memory.ReadByte(0), 1);
  EXPECT_EQ(memory.ReadByte(1024), 2);
  EXPECT_EQ(memory.ReadByte(2048), 3);
  EXPECT_EQ(memory.ReadByte(268435456), 4);

}

TEST(MemoryTest, ReadWriteHalfWordTest) {
  Memory memory;
  memory.WriteHalfWord(0, 1);
  memory.WriteHalfWord(1024, 2);
  memory.WriteHalfWord(2048, 3);
  memory.WriteHalfWord(268435456, 4);

  EXPECT_EQ(memory.ReadHalfWord(0), 1);
  EXPECT_EQ(memory.ReadHalfWord(1024), 2);
  EXPECT_EQ(memory.ReadHalfWord(2048), 3);
  EXPECT_EQ(memory.ReadHalfWord(268435456), 4);

}

TEST(MemoryTest, ReadWriteLargeFloatTest) {
  Memory memory;

  float large_value1 = 5.3242353f;
  float large_value2 = -12345.789f;
  float large_value3 = 9.876543f;
  float large_value4 = 3.4028235e+38f;

  memory.WriteFloat(0, large_value1);
  memory.WriteFloat(1024, large_value2);
  memory.WriteFloat(2048, large_value3);
  memory.WriteFloat(4096, large_value4);

  EXPECT_FLOAT_EQ(memory.ReadFloat(0), large_value1);
  EXPECT_FLOAT_EQ(memory.ReadFloat(1024), large_value2);
  EXPECT_FLOAT_EQ(memory.ReadFloat(2048), large_value3);
  EXPECT_FLOAT_EQ(memory.ReadFloat(4096), large_value4);
}

TEST(MemoryTest, ReadWriteLargeDoubleTest) {
  Memory memory;

  double large_value1 = 5.3242353453425;
  double large_value2 = -123456.789123456;
  double large_value3 = 9.876543210987654;
  double large_value4 = 1.7976931348623157e+308;

  memory.WriteDouble(0, large_value1);
  memory.WriteDouble(1024, large_value2);
  memory.WriteDouble(2048, large_value3);
  memory.WriteDouble(4096, large_value4);

  EXPECT_DOUBLE_EQ(memory.ReadDouble(0), large_value1);
  EXPECT_DOUBLE_EQ(memory.ReadDouble(1024), large_value2);
  EXPECT_DOUBLE_EQ(memory.ReadDouble(2048), large_value3);
  EXPECT_DOUBLE_EQ(memory.ReadDouble(4096), large_value4);
}


