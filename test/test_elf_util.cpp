#include <gtest/gtest.h>

#include "../include/assembler/elf_util.h"

TEST(ElfUtilTest, ElfHeaderTest) {
  ElfHeader elfHeader;
  ASSERT_EQ(elfHeader.e_ident[0], 0x7F);
  ASSERT_EQ(elfHeader.e_ident[1], 'E');
  ASSERT_EQ(elfHeader.e_ident[2], 'L');
  ASSERT_EQ(elfHeader.e_ident[3], 'F');
  ASSERT_EQ(elfHeader.e_ident[4], 1);
  ASSERT_EQ(elfHeader.e_ident[5], 1);
  ASSERT_EQ(elfHeader.e_ident[6], 1);
  ASSERT_EQ(elfHeader.e_ident[7], 0);
  ASSERT_EQ(elfHeader.e_type, 2);
  ASSERT_EQ(elfHeader.e_machine, 0xF3);
  ASSERT_EQ(elfHeader.e_version, 1);
  ASSERT_EQ(elfHeader.e_entry, 0x1000);
  ASSERT_EQ(elfHeader.e_phoff, 0);
  ASSERT_EQ(elfHeader.e_shoff, 0);
  ASSERT_EQ(elfHeader.e_flags, 0);
  ASSERT_EQ(elfHeader.e_ehsize, sizeof(ElfHeader));
  ASSERT_EQ(elfHeader.e_phentsize, 0);
  ASSERT_EQ(elfHeader.e_phnum, 0);
  ASSERT_EQ(elfHeader.e_shentsize, 40);
  ASSERT_EQ(elfHeader.e_shnum, 3);
  ASSERT_EQ(elfHeader.e_shstrndx, 2);
}