/**
 * File Name: elf_util.h
 * Author: Vishank Singh
 * Github: https://github.com/VishankSingh
 */
#ifndef ELF_UTIL_H
#define ELF_UTIL_H


#include "../vm_asm_mw.h"

struct ElfHeader {
  uint8_t e_ident[16] = {0x7F, 'E', 'L', 'F', 1, 1, 1, 0}; // ELF magic number
  uint16_t e_type = 2;        // Executable file
  uint16_t e_machine = 0xF3;  // RISC-V
  uint32_t e_version = 1;
  uint32_t e_entry = 0x1000;  // Entry point (adjust later)
  uint32_t e_phoff = 0;       // No program headers for now
  uint32_t e_shoff = 0;       // Section headers offset (to be calculated)
  uint32_t e_flags = 0;       // Architecture-specific flags
  uint16_t e_ehsize = sizeof(ElfHeader);
  uint16_t e_phentsize = 0;
  uint16_t e_phnum = 0;
  uint16_t e_shentsize = 40;  // Section header entry size
  uint16_t e_shnum = 3;       // Number of sections
  uint16_t e_shstrndx = 2;    // Section header string table index
};

struct ElfSectionHeader {
  uint32_t sh_name;      // Index into string table
  uint32_t sh_type;      // Section type (e.g., SHT_PROGBITS)
  uint32_t sh_flags;     // Flags (e.g., executable, writable)
  uint32_t sh_addr;      // Memory address (for executables)
  uint32_t sh_offset;    // Offset in ELF file
  uint32_t sh_size;      // Section size
  uint32_t sh_link;
  uint32_t sh_info;
  uint32_t sh_addralign; // Alignment requirements
  uint32_t sh_entsize;   // Entry size for symbol tables
};

void generateElfFile(const AssembledProgram &program, const std::string &output_filename);

#endif // ELF_UTIL_H