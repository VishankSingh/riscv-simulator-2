/**
 * File Name: test_vm.cpp
 * Author: Vishank Singh
 * Github: https://github.com/VishankSingh
 */

#include <gtest/gtest.h>
#include "../include/vm/rvss/rvss_vm.h"
#include "../include/assembler/assembler.h"

TEST(VmTest, ImmGenTest1) {
  RVSSVM vm;
  uint32_t lui_instruction = 0x100001b7;
  int32_t imm = vm.ImmGenerator(lui_instruction);
  ASSERT_EQ(imm, 0x10000);

  uint32_t auipc_instruction = 0x10000197;
  imm = vm.ImmGenerator(auipc_instruction);
  ASSERT_EQ(imm, 0x10000);

  uint32_t jal_instruction = 0x1320056f;
  imm = vm.ImmGenerator(jal_instruction);
  ASSERT_EQ(imm, 0x132);

  uint32_t jalr_instruction = 0x00008067;
  imm = vm.ImmGenerator(jalr_instruction);
  ASSERT_EQ(imm, 0x0);

  uint32_t branch_instruction = 0xfc000ae3;
  imm = vm.ImmGenerator(branch_instruction);
  ASSERT_EQ(imm, -44);

  uint32_t load_instruction = 0x00002283;
  imm = vm.ImmGenerator(load_instruction);
  ASSERT_EQ(imm, 0x0);

  uint32_t store_instruction = 0x00112023;
  imm = vm.ImmGenerator(store_instruction);
  ASSERT_EQ(imm, 0x0);

  uint32_t immediate_instruction = 0x00100093;
  imm = vm.ImmGenerator(immediate_instruction);
  ASSERT_EQ(imm, 0x1);

  uint32_t lui_instruction2 = 0x000000b7;
  imm = vm.ImmGenerator(lui_instruction2);
  ASSERT_EQ(imm, 0x0);

  uint32_t auipc_instruction2 = 0x00000097;
  imm = vm.ImmGenerator(auipc_instruction2);
  ASSERT_EQ(imm, 0x0);
}

TEST(VmTest, ExecutionTest1) {
  RVSSVM vm;
  AssembledProgram program;
  program.text_buffer.push_back(0x00b50633);
  program.text_buffer.push_back(0x00b55633);
    vm.LoadProgram(program);
  vm.registers_.WriteGpr(10, 10);
  vm.registers_.WriteGpr(11, 20);
  // uint32_t add_instruction = 0x00b50633;
  // vm.current_instruction_ = add_instruction;
  vm.Step();
  int64_t result = vm.registers_.ReadGpr(12);
  ASSERT_EQ(result, 30);
  ASSERT_EQ(vm.execution_result_, 30);
  vm.registers_.WriteGpr(10, 0b1101);
  vm.registers_.WriteGpr(11, 2);
  vm.Step();
  int64_t result2 = vm.registers_.ReadGpr(12);
  ASSERT_EQ(result2, 3);
  ASSERT_EQ(vm.execution_result_, 3);

}

TEST(VmTest, ExecutionTest2) {
  RVSSVM vm;
  AssembledProgram program;
  program.text_buffer.push_back(0x00b55633);
    vm.LoadProgram(program);
  vm.registers_.WriteGpr(10, 0b1101);
  vm.registers_.WriteGpr(11, 2);
  vm.Step();
  int64_t result = vm.registers_.ReadGpr(12);
  ASSERT_EQ(result, 3);
  ASSERT_EQ(vm.execution_result_, 3);
}

TEST(VmTest, ExecutionTest3) {
  RVSSVM vm;
  AssembledProgram program;
  program.text_buffer.push_back(0x01700513);
  program.text_buffer.push_back(0x01b50513);
    vm.LoadProgram(program);
  vm.Step();
  int64_t result = vm.registers_.ReadGpr(10);
  ASSERT_EQ(result, 23);
  ASSERT_EQ(vm.execution_result_, 23);
  vm.Step();
  int64_t result2 = vm.registers_.ReadGpr(10);
  ASSERT_EQ(result2, 50);
  ASSERT_EQ(vm.execution_result_, 50);
}

TEST(VmTest, ExecutionTest4) {
  AssembledProgram program = assemble("/home/vis/Desk/codes/assembler/examples/branch_test.s");
  RVSSVM vm;
    vm.LoadProgram(program);
  vm.Step();
  vm.Step();
  vm.Fetch();
  vm.Decode();
  vm.Execute();
  ASSERT_EQ(vm.branch_flag_, true);
  ASSERT_EQ(vm.program_counter_, 0x0);
  vm.Step();

  // vm.memory();
  // vm.WriteBack();
}

TEST(VmTest, ExecutionTest5) {
  AssembledProgram program = assemble("/home/vis/Desk/codes/assembler/examples/load_test.s");
  RVSSVM vm;
    vm.LoadProgram(program);
  vm.Fetch();
  vm.Decode();
  vm.Execute();
  ASSERT_EQ(vm.execution_result_, 0);
  vm.WriteMemory();
  vm.WriteBack();

  ASSERT_EQ(vm.registers_.ReadGpr(10), 0x0000000000003503);

}

TEST(VmTest, ExecutionTest6) {
  AssembledProgram program = assemble("/home/vis/Desk/codes/assembler/examples/load_store_test_1.s");
  RVSSVM vm;
    vm.LoadProgram(program);
  vm.Step();
  ASSERT_EQ(vm.registers_.ReadGpr(10), 0x1000059300003503);
  vm.Step();
  ASSERT_EQ(vm.registers_.ReadGpr(11), 0x0000000000000100);
  vm.Step();
  uint64_t result3 = vm.memory_controller_.ReadDoubleWord(0x100);
  ASSERT_EQ(result3, 0x1000059300003503);

}

TEST(VmTest, ExecutionTest7) {
  AssembledProgram program = assemble("/home/vis/Desk/codes/assembler/examples/load_store_test_2.s");
  RVSSVM vm;
    vm.LoadProgram(program);
  vm.Step();
  ASSERT_EQ(vm.registers_.ReadGpr(12), 0xffffffffffffffff);
  vm.Step();
  ASSERT_EQ(vm.registers_.ReadGpr(10), 0x0000000000000100);
  vm.Step();
  uint64_t result3 = vm.memory_controller_.ReadByte(0x100);
  ASSERT_EQ(result3, 0xff);
  uint64_t result4 = vm.memory_controller_.ReadDoubleWord(0x100);
  ASSERT_EQ(result4, 0xff);
  vm.Step();
  ASSERT_EQ(vm.registers_.ReadGpr(13), 0xffffffffffffffff);

}

TEST(VmTest, ExecutionTest8) {
  AssembledProgram program = assemble("/home/vis/Desk/codes/assembler/examples/load_test_2.s");
  RVSSVM vm;
    vm.LoadProgram(program);
  vm.registers_.WriteGpr(3, 0x10000000); // set the data section address
  vm.Step();
  ASSERT_EQ(vm.registers_.ReadGpr(10), 121);
}

TEST(VmTest, ExecutionTest9) {
  AssembledProgram program = assemble("/home/vis/Desk/codes/assembler/examples/branch_test.s");
  RVSSVM vm;
    vm.LoadProgram(program);

  for (int i = 1; i < 5; i++) {
    vm.Step();
    vm.Step();
    vm.Step();
    ASSERT_EQ(vm.registers_.ReadGpr(10), 50*i);
  }
}

// TEST(VmTest, ExecutionTest10) {
//     AssembledProgram program = assemble("/home/vis/Desk/codes/assembler/examples/jal_test.s");
//     RVSSVM vm;
//     vm.LoadProgram(program);
//     vm.registers_.WriteGpr(3, 0x10000000); // set the data section address
//     vm.Step();
//     vm.Step();
//     vm.Step();
//     ASSERT_EQ(vm.program_counter_, 0x0);
//     ASSERT_EQ(vm.registers_.ReadGpr(1), 0xc);
// }

TEST(VmTest, ExecutionTest11) {
  AssembledProgram program = assemble("/home/vis/Desk/codes/assembler/examples/lui_auipc_test.s");
  RVSSVM vm;
    vm.LoadProgram(program);
  vm.Step();
  ASSERT_EQ(vm.registers_.ReadGpr(3), 0x0000000000100000);
  vm.Step();
  ASSERT_EQ(vm.registers_.ReadGpr(4), 0x0000000000100004);
}