/**
 * @file instructions.h
 * @brief Contains the declarations for the InstructionEncoding struct and related functions.
 * @author Vishank Singh, https://github.com/VishankSingh
 */

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <bitset>
#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>
#include <array>
#include <type_traits>

namespace instruction_set {


enum Instruction {
  // Utility categorical encodings
  kRtype, 
  kItype, 
  kStype, 
  kBtype, 
  kJtype, 
  // kUtype,
  kLoadType,
  
  kCsrType, // CSR type instructions


  // Real instructions
  kadd, 
  ksub, 
  ksll, 
  kslt, 
  ksltu,
  kxor, 
  ksrl, 
  ksra, 
  kor, 
  kand,

  kaddw, 
  ksubw, 
  ksllw, 
  ksrlw, 
  ksraw,

  kaddi, 
  kxori, 
  kori, 
  kandi, 
  kslli, 
  ksrli, 
  ksrai, 
  kslti, 
  ksltiu,
  kaddiw, 
  kslliw, 
  ksrliw, 
  ksraiw,
  klb, 
  klh, 
  klw, 
  kld, 
  klbu, 
  klhu, 
  klwu,
  ksb, 
  ksh, 
  ksw, 
  ksd,
  kbeq, 
  kbne, 
  kblt, 
  kbge, 
  kbltu, 
  kbgeu,
  klui, 
  kauipc,
  kjal, 
  kjalr,
  kecall,
  kcsrrw, 
  kcsrrs, 
  kcsrrc, 
  kcsrrwi, 
  kcsrrsi, 
  kcsrrci,
  kla, 
  knop, 
  kli, 
  kmv, 
  knot, 
  kneg, 
  knegw,
  ksextw, 
  kseqz, 
  ksnez, 
  ksltz, 
  ksgtz,
  kbeqz, 
  kbnez, 
  kblez, 
  kbgez, 
  kbltz, 
  kbgtz,
  kbgt, 
  kble, 
  kbgtu, 
  kbleu,
  kj, 
  kjr, 
  kret, 
  kcall, 
  ktail, 
  kfence, 
  kfence_i,

  kmul, 
  kmulh, 
  kmulhsu, 
  kmulhu, 
  kdiv, 
  kdivu, 
  krem, 
  kremu,
  kmulw, 
  kdivw, 
  kdivuw, 
  kremw, 
  kremuw,

  kflw, 
  kfsw, 
  kfmadd_s, 
  kfmsub_s, 
  kfnmsub_s, 
  kfnmadd_s,
  kfadd_s, 
  kfsub_s, 
  kfmul_s, 
  kfdiv_s, 
  kfsqrt_s,
  kfsgnj_s, 
  kfsgnjn_s, 
  kfsgnjx_s,
  kfmin_s, 
  kfmax_s,
  kfcvt_w_s, 
  kfcvt_wu_s, 
  kfmv_x_w, 
  kfmv_w_x,
  kfeq_s, 
  kflt_s, 
  kfle_s,
  kfclass_s, 
  kfcvt_s_w, 
  kfcvt_s_wu,
  kfcvt_l_s, 
  kfcvt_lu_s, 
  kfcvt_s_l, 
  kfcvt_s_lu,

  kfld, kfsd, 
  kfmadd_d, 
  kfmsub_d, 
  kfnmsub_d, 
  kfnmadd_d,
  kfadd_d, 
  kfsub_d, 
  kfmul_d, 
  kfdiv_d, 
  kfsqrt_d,
  kfsgnj_d, 
  kfsgnjn_d, 
  kfsgnjx_d,
  kfmin_d, 
  kfmax_d,
  kfcvt_s_d, 
  kfcvt_d_s,
  kfeq_d, 
  kflt_d, 
  kfle_d,
  kfclass_d, 
  kfcvt_w_d, 
  kfcvt_wu_d, 
  kfcvt_d_w, 
  kfcvt_d_wu,
  kfcvt_l_d, 
  kfcvt_lu_d, 
  kfmv_x_d, 
  kfcvt_d_l, 
  kfcvt_d_lu, 
  kfmv_d_x,
  kSIMD_add32, 
  kSIMD_sub32, 
  kSIMD_mul32, 
  kSIMD_load32,
  kSIMD_rem32, 
  kSIMD_div32,
  // klbf16,
  // ksbf16,
  kfadd_bf16,
  kfsub_bf16,
  kfmul_bf16,
  kfdiv_bf16,
  INVALID,

  COUNT // sentinel for length

};

// TODO: use enum class for instruction encoding


struct InstructionEncoding {
  Instruction instr;
  int opcode;
  int funct2;
  int funct3;
  int funct5;
  int funct6;
  int funct7;

  constexpr InstructionEncoding(Instruction instr = Instruction::INVALID, int opcode = -1, int funct2 = -1, int funct3 = -1, int funct5 = -1, int funct6 = -1, int funct7 = -1)
  : instr(instr), opcode(opcode), funct2(funct2), funct3(funct3), funct5(funct5), funct6(funct6), funct7(funct7) {}
};

inline constexpr std::array<InstructionEncoding, static_cast<size_t>(Instruction::COUNT)> compiletime_instruction_encoding_array = {{
  InstructionEncoding(Instruction::kRtype,      0b0110011, -1, -1, -1, -1, -1), // kRtype
  InstructionEncoding(Instruction::kItype,      0b0010011, -1, -1, -1, -1, -1), // kItype
  InstructionEncoding(Instruction::kStype,      0b0100011, -1, -1, -1, -1, -1), // kStype
  InstructionEncoding(Instruction::kBtype,      0b1100011, -1, -1, -1, -1, -1), // kBtype
  InstructionEncoding(Instruction::kJtype,      0b1101111, -1, -1, -1, -1, -1), // kJtype
  // InstructionEncoding(Instruction::kUtype,      0b0110111, -1, -1, -1, -1, -1), // kUtype
  InstructionEncoding(Instruction::kLoadType,   0b0000011, -1, -1, -1, -1, -1), // kLoadType

  InstructionEncoding(Instruction::kCsrType,  0b1110011, -1, -1, -1, -1, -1), // kCsrType

  InstructionEncoding(Instruction::kadd,        0b0110011, -1, 0b000, -1, -1, 0b0000000), // kadd
  InstructionEncoding(Instruction::ksub,        0b0110011, -1, 0b000, -1, -1, 0b0100000), // ksub
  InstructionEncoding(Instruction::ksll,        0b0110011, -1, 0b001, -1, -1, 0b0000000), // ksll
  InstructionEncoding(Instruction::kslt,        0b0110011, -1, 0b010, -1, -1, 0b0000000), // kslt
  InstructionEncoding(Instruction::ksltu,       0b0110011, -1, 0b011, -1, -1, 0b0000000), // ksltu
  InstructionEncoding(Instruction::kxor,        0b0110011, -1, 0b100, -1, -1, 0b0000000), // kxor
  InstructionEncoding(Instruction::ksrl,        0b0110011, -1, 0b101, -1, -1, 0b0000000), // ksrl
  InstructionEncoding(Instruction::ksra,        0b0110011, -1, 0b101, -1, -1, 0b0100000), // ksra
  InstructionEncoding(Instruction::kor,         0b0110011, -1, 0b110, -1, -1, 0b0000000), // kor
  InstructionEncoding(Instruction::kand,        0b0110011, -1, 0b111, -1, -1, 0b0000000), 
  
// similarly newly added simple R type instructions 
  InstructionEncoding(Instruction::kSIMD_add32, 0b0110011, -1, 0b000, -1 ,-1, 0b0001011), 
  InstructionEncoding(Instruction::kSIMD_sub32, 0b0110011, -1, 0b001, -1 ,-1, 0b0001011), 
  InstructionEncoding(Instruction::kSIMD_mul32, 0b0110011, -1, 0b011, -1 ,-1, 0b0001011), 
  InstructionEncoding(Instruction::kSIMD_load32, 0b0110011, -1, 0b111, -1 ,-1, 0b0001011), 
  InstructionEncoding(Instruction::kSIMD_div32, 0b0110011, -1, 0b100, -1 ,-1, 0b0001011),
  InstructionEncoding(Instruction::kSIMD_rem32, 0b0110011, -1, 0b101, -1 ,-1, 0b0001011), 
// end of the new istrcutions

  InstructionEncoding(Instruction::kmul,        0b0110011, -1, 0b000, -1, -1, 0b0000001), // kmul
  InstructionEncoding(Instruction::kmulh,       0b0110011, -1, 0b001, -1, -1, 0b0000001), // kmulh
  InstructionEncoding(Instruction::kmulhsu,     0b0110011, -1, 0b010, -1, -1, 0b0000001), // kmulhsu
  InstructionEncoding(Instruction::kmulhu,      0b0110011, -1, 0b011, -1, -1, 0b0000001), // kmulhu
  InstructionEncoding(Instruction::kdiv,        0b0110011, -1, 0b100, -1, -1, 0b0000001), // kdiv
  InstructionEncoding(Instruction::kdivu,       0b0110011, -1, 0b101, -1, -1, 0b0000001), // kdivu
  InstructionEncoding(Instruction::krem,        0b0110011, -1, 0b110, -1, -1, 0b0000001), // krem
  InstructionEncoding(Instruction::kremu,       0b0110011, -1, 0b111, -1, -1, 0b0000001), // kremu


  InstructionEncoding(Instruction::kaddw,       0b0111011, -1, 0b000, -1, -1, 0b0000000), // kaddw
  InstructionEncoding(Instruction::ksubw,       0b0111011, -1, 0b000, -1, -1, 0b0100000), // ksubw
  InstructionEncoding(Instruction::ksllw,       0b0111011, -1, 0b001, -1, -1, 0b0000000), // ksllw
  InstructionEncoding(Instruction::ksrlw,       0b0111011, -1, 0b101, -1, -1, 0b0000000), // ksrlw
  InstructionEncoding(Instruction::ksraw,       0b0111011, -1, 0b101, -1, -1, 0b0100000), // ksraw
  
  InstructionEncoding(Instruction::kmulw,       0b0111011, -1, 0b000, -1, -1, 0b0000001), // kmulw
  InstructionEncoding(Instruction::kdivw,       0b0111011, -1, 0b100, -1, -1, 0b0000001), // kdivw
  InstructionEncoding(Instruction::kdivuw,      0b0111011, -1, 0b101, -1, -1, 0b0000001), // kdivuw
  InstructionEncoding(Instruction::kremw,       0b0111011, -1, 0b110, -1, -1, 0b0000001), // kremw
  InstructionEncoding(Instruction::kremuw,      0b0111011, -1, 0b111, -1, -1, 0b0000001), // kremuw

  InstructionEncoding(Instruction::kecall,      0b1110011, -1, 0b000, -1, -1, 0b0000000), // kecall

  
  InstructionEncoding(Instruction::kaddi,       0b0010011, -1, 0b000, -1, -1, -1), // addi
  InstructionEncoding(Instruction::kslli,       0b0010011, -1, 0b001, -1, -1, 0b0000000), // kslli
  InstructionEncoding(Instruction::kslti,       0b0010011, -1, 0b010, -1, -1, -1), // kslti
  InstructionEncoding(Instruction::ksltiu,      0b0010011, -1, 0b011, -1, -1, -1), // ksltiu
  InstructionEncoding(Instruction::kxori,       0b0010011, -1, 0b100, -1, -1, -1), // kxori
  InstructionEncoding(Instruction::ksrli,       0b0010011, -1, 0b101, -1, -1, 0b0000000), // ksrli
  InstructionEncoding(Instruction::ksrai,       0b0010011, -1, 0b101, -1, -1, 0b0100000), // ksrai
  InstructionEncoding(Instruction::kori,        0b0010011, -1, 0b110, -1, -1, -1), // kori
  InstructionEncoding(Instruction::kandi,       0b0010011, -1, 0b111, -1, -1, -1), // kandi

  InstructionEncoding(Instruction::kaddiw,      0b0011011, -1, 0b000, -1, -1, -1), // kaddiw
  InstructionEncoding(Instruction::kslliw,      0b0011011, -1, 0b001, -1, -1, 0b0000000), // kslliw
  InstructionEncoding(Instruction::ksrliw,      0b0011011, -1, 0b101, -1, -1, 0b0000000), // ksrliw
  InstructionEncoding(Instruction::ksraiw,      0b0011011, -1, 0b101, -1, -1, 0b0100000), // ksraiw

  InstructionEncoding(Instruction::klb,         0b0000011, -1, 0b000, -1, -1, -1), // klb
  InstructionEncoding(Instruction::klh,         0b0000011, -1, 0b001, -1, -1, -1), // klh
  InstructionEncoding(Instruction::klw,         0b0000011, -1, 0b010, -1, -1, -1), // klw
  InstructionEncoding(Instruction::kld,         0b0000011, -1, 0b011, -1, -1, -1), // kld
  InstructionEncoding(Instruction::klbu,        0b0000011, -1, 0b100, -1, -1, -1), // klbu
  InstructionEncoding(Instruction::klhu,        0b0000011, -1, 0b101, -1, -1, -1), // klhu
  InstructionEncoding(Instruction::klwu,        0b0000011, -1, 0b110, -1, -1, -1), // klwu

  InstructionEncoding(Instruction::kjalr,       0b1100111, -1, 0b000, -1, -1, -1), // kjalr

  InstructionEncoding(Instruction::ksb,         0b0100011, -1, 0b000, -1, -1, -1), // ksb
  InstructionEncoding(Instruction::ksh,         0b0100011, -1, 0b001, -1, -1, -1), // ksh
  InstructionEncoding(Instruction::ksw,         0b0100011, -1, 0b010, -1, -1, -1), // ksw
  InstructionEncoding(Instruction::ksd,         0b0100011, -1, 0b011, -1, -1, -1), // ksd

  InstructionEncoding(Instruction::kbeq,        0b1100011, -1, 0b000, -1, -1, -1), // kbeq
  InstructionEncoding(Instruction::kbne,        0b1100011, -1, 0b001, -1, -1, -1), // kbne
  InstructionEncoding(Instruction::kblt,        0b1100011, -1, 0b100, -1, -1, -1), // kblt
  InstructionEncoding(Instruction::kbge,        0b1100011, -1, 0b101, -1, -1, -1), // kbge
  InstructionEncoding(Instruction::kbltu,       0b1100011, -1, 0b110, -1, -1, -1), // kbltu
  InstructionEncoding(Instruction::kbgeu,       0b1100011, -1, 0b111, -1, -1, -1), // kbgeu

  InstructionEncoding(Instruction::klui,        0b0110111, -1, -1, -1, -1, -1), // klui
  InstructionEncoding(Instruction::kauipc,      0b0010111, -1, -1, -1, -1, -1), // kauipc
  
  InstructionEncoding(Instruction::kjal,        0b1101111, -1, -1, -1, -1, -1), // kjal

  // csr

  InstructionEncoding(Instruction::kcsrrw,      0b1110011, -1, 0b001, -1, -1, -1), // kcsrrw
  InstructionEncoding(Instruction::kcsrrs,      0b1110011, -1, 0b010, -1, -1, -1), // kcsrrs
  InstructionEncoding(Instruction::kcsrrc,      0b1110011, -1, 0b011, -1, -1, -1), // kcsrrc
  InstructionEncoding(Instruction::kcsrrwi,     0b1110011, -1, 0b101, -1, -1, -1), // kcsrrwi
  InstructionEncoding(Instruction::kcsrrsi,     0b1110011, -1, 0b110, -1, -1, -1), // kcsrrsi
  InstructionEncoding(Instruction::kcsrrci,     0b1110011, -1, 0b111, -1, -1, -1), // kcsrrci


  InstructionEncoding(Instruction::kfsgnj_s,    0b1010011, -1, 0b000, -1, -1, 0b0010000), // kfsgnj_s
  InstructionEncoding(Instruction::kfsgnjn_s,   0b1010011, -1, 0b001, -1, -1, 0b0010000), // kfsgnjn_s
  InstructionEncoding(Instruction::kfsgnjx_s,   0b1010011, -1, 0b010, -1, -1, 0b0010000), // kfsgnjx_s 
  
  InstructionEncoding(Instruction::kfmin_s,     0b1010011, -1, 0b000, -1, -1, 0b0010100), // kfmin_s
  InstructionEncoding(Instruction::kfmax_s,     0b1010011, -1, 0b001, -1, -1, 0b0010100), // kfmax_s
  
  InstructionEncoding(Instruction::kfle_s,      0b1010011, -1, 0b000, -1, -1, 0b1010000), // kfle_s
  InstructionEncoding(Instruction::kflt_s,      0b1010011, -1, 0b001, -1, -1, 0b1010000), // kflt_s
  InstructionEncoding(Instruction::kfeq_s,      0b1010011, -1, 0b010, -1, -1, 0b1010000), // kfeq_s
  
  InstructionEncoding(Instruction::kfsgnj_d,    0b1010011, -1, 0b000, -1, -1, 0b0010001), // kfsgnj_d
  InstructionEncoding(Instruction::kfsgnjn_d,   0b1010011, -1, 0b001, -1, -1, 0b0010001), // kfsgnjn_d
  InstructionEncoding(Instruction::kfsgnjx_d,   0b1010011, -1, 0b010, -1, -1, 0b0010001), // kfsgnjx_d
  
  InstructionEncoding(Instruction::kfmin_d,     0b1010011, -1, 0b000, -1, -1, 0b0010101), // kfmin_d
  InstructionEncoding(Instruction::kfmax_d,     0b1010011, -1, 0b001, -1, -1, 0b0010101), // kfmax_d
  
  InstructionEncoding(Instruction::kfle_d,      0b1010011, -1, 0b000, -1, -1, 0b1010001), // kfle_d
  InstructionEncoding(Instruction::kflt_d,      0b1010011, -1, 0b001, -1, -1, 0b1010001), // kflt_d
  InstructionEncoding(Instruction::kfeq_d,      0b1010011, -1, 0b010, -1, -1, 0b1010001), // kfeq_d

  InstructionEncoding(Instruction::kflw,        0b0000111, -1, 0b010, -1, -1, -1), // kflw
  InstructionEncoding(Instruction::kfsw,        0b0100111, -1, 0b010, -1, -1, -1), // kfsw
  InstructionEncoding(Instruction::kfld,        0b0000111, -1, 0b011, -1, -1, -1), // kfld
  InstructionEncoding(Instruction::kfsw,        0b0100111, -1, 0b011, -1, -1, -1), // kfsd


  InstructionEncoding(Instruction::kfadd_s,     0b1010011, -1, -1, -1, -1, 0b0000000), // kfadd_s
  InstructionEncoding(Instruction::kfsub_s,     0b1010011, -1, -1, -1, -1, 0b0000100), // kfsub_s
  InstructionEncoding(Instruction::kfmul_s,     0b1010011, -1, -1, -1, -1, 0b0001000), // kfmul_s
  InstructionEncoding(Instruction::kfdiv_s,     0b1010011, -1, -1, -1, -1, 0b0001100), // kfdiv_s

  InstructionEncoding(Instruction::kfadd_d,     0b1010011, -1, -1, -1, -1, 0b0000001), // kfadd_d
  InstructionEncoding(Instruction::kfsub_d,     0b1010011, -1, -1, -1, -1, 0b0000101), // kfsub_d
  InstructionEncoding(Instruction::kfmul_d,     0b1010011, -1, -1, -1, -1, 0b0001001), // kfmul_d
  InstructionEncoding(Instruction::kfdiv_d,     0b1010011, -1, -1, -1, -1, 0b0001101), // kfdiv_d

  // newly added simple R type instructions for Bfloat16 

  InstructionEncoding(Instruction::kfadd_bf16, 0b1010011, -1, -1, -1, -1, 0b0000010), // kfadd_bf16
  InstructionEncoding(Instruction::kfsub_bf16, 0b1010011, -1, -1, -1, -1, 0b0000110), // kfsub_bf16
  InstructionEncoding(Instruction::kfmul_bf16, 0b1010011, -1, -1, -1, -1, 0b0001010), // kfmul_bf16
  InstructionEncoding(Instruction::kfdiv_bf16, 0b1010011, -1, -1, -1, -1, 0b0001110), // kfdiv_bf16


  // end of the new istrcutions
  

  InstructionEncoding(Instruction::kfsqrt_s,    0b1010011, -1, -1, 0b00000, -1, 0b0101100), // kfsqrt_s
  InstructionEncoding(Instruction::kfcvt_w_s,   0b1010011, -1, -1, 0b00000, -1, 0b1100000), // kfcvt_w_s
  InstructionEncoding(Instruction::kfcvt_wu_s,  0b1010011, -1, -1, 0b00001, -1, 0b1100000), // kfcvt_wu_s
  InstructionEncoding(Instruction::kfcvt_l_s,   0b1010011, -1, -1, 0b00010, -1, 0b1100000), // kfcvt_l_s
  InstructionEncoding(Instruction::kfcvt_lu_s,  0b1010011, -1, -1, 0b00011, -1, 0b1100000), // kfcvt_lu_s
  InstructionEncoding(Instruction::kfcvt_s_w,   0b1010011, -1, -1, 0b00000, -1, 0b1101000), // kfcvt_s_w
  InstructionEncoding(Instruction::kfcvt_s_wu,  0b1010011, -1, -1, 0b00001, -1, 0b1101000), // kfcvt_s_wu
  InstructionEncoding(Instruction::kfcvt_s_l,   0b1010011, -1, -1, 0b00010, -1, 0b1101000), // kfcvt_s_l
  InstructionEncoding(Instruction::kfcvt_s_lu,  0b1010011, -1, -1, 0b00011, -1, 0b1101000), // kfcvt_s_lu


  InstructionEncoding(Instruction::kfsqrt_d,    0b1010011, -1, -1, 0b00000, -1, 0b0101101), // kfsqrt_d 
  InstructionEncoding(Instruction::kfcvt_w_d,   0b1010011, -1, -1, 0b00000, -1, 0b1100001), // kfcvt_w_d
  InstructionEncoding(Instruction::kfcvt_wu_d,  0b1010011, -1, -1, 0b00001, -1, 0b1100001), // kfcvt_wu_d
  InstructionEncoding(Instruction::kfcvt_l_d,   0b1010011, -1, -1, 0b00010, -1, 0b1100001), // kfcvt_l_d
  InstructionEncoding(Instruction::kfcvt_lu_d,  0b1010011, -1, -1, 0b00011, -1, 0b1100001), // kfcvt_lu_d
  InstructionEncoding(Instruction::kfcvt_d_w,   0b1010011, -1, -1, 0b00000, -1, 0b1101001), // kfcvt_d_w
  InstructionEncoding(Instruction::kfcvt_d_wu,  0b1010011, -1, -1, 0b00001, -1, 0b1101001), // kfcvt_d_wu
  InstructionEncoding(Instruction::kfcvt_d_l,   0b1010011, -1, -1, 0b00010, -1, 0b1101001), // kfcvt_d_l
  InstructionEncoding(Instruction::kfcvt_d_lu,  0b1010011, -1, -1, 0b00011, -1, 0b1101001), // kfcvt_d_lu


  InstructionEncoding(Instruction::kfcvt_s_d,   0b1010011, -1, -1, 0b00001, -1, 0b0100000), // kfcvt_s_d
  InstructionEncoding(Instruction::kfcvt_d_s,   0b1010011, -1, -1, 0b00000, -1, 0b0100001), // kfcvt_d_s

  InstructionEncoding(Instruction::kfmv_x_w,    0b1010011, -1, 0b000, 0b00000, -1, 0b1110000), // kfmv_x_w
  InstructionEncoding(Instruction::kfmv_x_d,    0b1010011, -1, 0b000, 0b00000, -1, 0b1110001), // kfmv_x_d
  InstructionEncoding(Instruction::kfmv_w_x,    0b1010011, -1, 0b000, 0b00000, -1, 0b1111000), // kfmv_w_x
  InstructionEncoding(Instruction::kfmv_d_x,    0b1010011, -1, 0b000, 0b00000, -1, 0b1111001), // kfmv_d_x
  InstructionEncoding(Instruction::kfclass_s,   0b1010011, -1, 0b001, 0b00000, -1, 0b1110000), // kfclass_s
  InstructionEncoding(Instruction::kfclass_d,   0b1010011, -1, 0b001, 0b00000, -1, 0b1110001), // kfclass_d

      
  InstructionEncoding(Instruction::kfmadd_s, 0b1000011, 0b00, -1, -1, -1, -1), // kfmadd_s
  InstructionEncoding(Instruction::kfmsub_s, 0b1000111, 0b00, -1, -1, -1, -1), // kfmsub_s 
  InstructionEncoding(Instruction::kfnmsub_s, 0b1001011, 0b00, -1, -1, -1, -1), // kfnmsub_s
  InstructionEncoding(Instruction::kfnmadd_s, 0b1001111, 0b00, -1, -1, -1, -1), // kfnmadd_s
  
  InstructionEncoding(Instruction::kfmadd_d, 0b1000011, 0b01, -1, -1, -1, -1), // kfmadd_d
  InstructionEncoding(Instruction::kfmsub_d, 0b1000111, 0b01, -1, -1, -1, -1), // kfmsub_d 
  InstructionEncoding(Instruction::kfnmsub_d, 0b1001011, 0b01, -1, -1, -1, -1), // kfnmsub_d
  InstructionEncoding(Instruction::kfnmadd_d, 0b1001111, 0b01, -1, -1, -1, -1), // kfnmadd_d


}};

const std::array<InstructionEncoding, static_cast<size_t>(Instruction::COUNT)> runtime_instruction_encoding_array = compiletime_instruction_encoding_array;

constexpr const InstructionEncoding& get_instr_encoding(Instruction instr) {
  if (std::is_constant_evaluated()) {
    for (const auto& enc : compiletime_instruction_encoding_array) {
      if (enc.instr == instr) {
        return enc;
      }
    }
    for (const auto& enc : compiletime_instruction_encoding_array) {
      if (enc.instr == Instruction::INVALID) {
        return enc;
      }
    }

  } else {
    for (const auto& enc : runtime_instruction_encoding_array) {
      if (enc.instr == instr) {
        return enc;
      }
    }
    for (const auto& enc : runtime_instruction_encoding_array) {
      if (enc.instr == Instruction::INVALID) {
        return enc;
      }
    }
  }

  __builtin_unreachable();
}


extern std::unordered_map<std::string, Instruction> instruction_string_map;



struct RTypeInstructionEncoding {
  std::bitset<7> opcode;
  std::bitset<3> funct3;
  std::bitset<7> funct7;

  RTypeInstructionEncoding(unsigned int opcode, unsigned int funct3, unsigned int funct7)
      : opcode(opcode), funct3(funct3), funct7(funct7) {}
};

struct I1TypeInstructionEncoding {
  std::bitset<7> opcode;
  std::bitset<3> funct3;

  I1TypeInstructionEncoding(unsigned int opcode, unsigned int funct3)
      : opcode(opcode), funct3(funct3) {}
};

struct I2TypeInstructionEncoding {
  std::bitset<7> opcode;
  std::bitset<3> funct3;
  std::bitset<6> funct6;

  I2TypeInstructionEncoding(unsigned int opcode, unsigned int funct3, unsigned int funct6)
      : opcode(opcode), funct3(funct3), funct6(funct6) {}
};

struct I3TypeInstructionEncoding {
  std::bitset<7> opcode;
  std::bitset<3> funct3;
  std::bitset<7> funct7;

  I3TypeInstructionEncoding(unsigned int opcode, unsigned int funct3, unsigned int funct7)
      : opcode(opcode), funct3(funct3), funct7(funct7) {}
};

struct STypeInstructionEncoding {
  std::bitset<7> opcode;
  std::bitset<3> funct3;

  STypeInstructionEncoding(unsigned int opcode, unsigned int funct3)
      : opcode(opcode), funct3(funct3) {}
};

struct BTypeInstructionEncoding {
  std::bitset<7> opcode;
  std::bitset<3> funct3;

  BTypeInstructionEncoding(unsigned int opcode, unsigned int funct3)
      : opcode(opcode), funct3(funct3) {}
};

struct UTypeInstructionEncoding {
  std::bitset<7> opcode;

  UTypeInstructionEncoding(unsigned int opcode)
      : opcode(opcode) {}
};

struct JTypeInstructionEncoding {
  std::bitset<7> opcode;

  JTypeInstructionEncoding(unsigned int opcode)
      : opcode(opcode) {}
};

struct CSR_RTypeInstructionEncoding {
  std::bitset<7> opcode;
  std::bitset<3> funct3;

  CSR_RTypeInstructionEncoding(unsigned int opcode, unsigned int funct3)
      : opcode(opcode), funct3(funct3) {}
};

struct CSR_ITypeInstructionEncoding {
  std::bitset<7> opcode;
  std::bitset<3> funct3;

  CSR_ITypeInstructionEncoding(unsigned int opcode, unsigned int funct3)
      : opcode(opcode), funct3(funct3) {}
};

// Fextension instructions===========================================================================

struct FDRTypeInstructionEncoding { // fsgnj
  std::bitset<7> opcode;
  std::bitset<3> funct3;
  std::bitset<7> funct7;

  FDRTypeInstructionEncoding(unsigned int opcode, unsigned int funct3, unsigned int funct7)
      : opcode(opcode), funct3(funct3), funct7(funct7) {}
};

struct FDR1TypeInstructionEncoding { // fadd, fsub, fmul
  std::bitset<7> opcode;
  std::bitset<7> funct7;

  FDR1TypeInstructionEncoding(unsigned int opcode, unsigned int funct7)
      : opcode(opcode), funct7(funct7) {}
};

struct FDR2TypeInstructionEncoding { //fsqrt, have funct5 instead of rs2
  std::bitset<7> opcode;
  std::bitset<5> funct5;
  std::bitset<7> funct7;

  FDR2TypeInstructionEncoding(unsigned int opcode, unsigned int funct5, unsigned int funct7)
      : opcode(opcode), funct5(funct5), funct7(funct7) {}
};

struct FDR3TypeInstructionEncoding {
  std::bitset<7> opcode;
  std::bitset<3> funct3;
  std::bitset<5> funct5;
  std::bitset<7> funct7;

  FDR3TypeInstructionEncoding(unsigned int opcode, unsigned int funct3, unsigned int funct5, unsigned int funct7)
      : opcode(opcode), funct3(funct3), funct5(funct5), funct7(funct7) {}

};

struct FDR4TypeInstructionEncoding { //fmadd
  std::bitset<7> opcode;
  std::bitset<2> funct2;

  FDR4TypeInstructionEncoding(unsigned int opcode, unsigned int funct2)
      : opcode(opcode), funct2(funct2) {}
};

struct FDITypeInstructionEncoding {
  std::bitset<7> opcode;
  std::bitset<3> funct3;

  FDITypeInstructionEncoding(unsigned int opcode, unsigned int funct3)
      : opcode(opcode), funct3(funct3) {}
};

struct FDSTypeInstructionEncoding {
  std::bitset<7> opcode;
  std::bitset<3> funct3;

  FDSTypeInstructionEncoding(unsigned int opcode, unsigned int funct3)
      : opcode(opcode), funct3(funct3) {}
};

/**
 * @brief Enum that represents different syntax types for instructions.
 */
enum class SyntaxType {
  O_GPR_C_GPR_C_GPR,       ///< Opcode general-register , general-register , register
  O_GPR_C_GPR_C_I,        ///< Opcode general-register , general-register , immediate
  O_GPR_C_I,            ///< Opcode general-register , immediate
  O_GPR_C_GPR_C_IL,       ///< Opcode general-register , general-register , immediate , instruction_label
  O_GPR_C_GPR_C_DL,       ///< Opcode register , register , immediate , data_label
  O_GPR_C_IL,           ///< Opcode register , instruction_label
  O_GPR_C_DL,           ///< Opcode register , data_label
  O_GPR_C_I_LP_GPR_RP,    ///< Opcode register , immediate , lparen ( register )rparen
  O,                  ///< Opcode
  PSEUDO,              ///< Pseudo instruction

  O_GPR_C_CSR_C_GPR,       ///< Opcode general-register , csr , general-register
  O_GPR_C_CSR_C_I,        ///< Opcode general-register , csr , immediate

  O_FPR_C_FPR_C_FPR_C_FPR,    ///< Opcode floating-point-register , floating-point-register , floating-point-register , floating-point-register
  O_FPR_C_FPR_C_FPR_C_FPR_C_RM,    ///< Opcode floating-point-register , floating-point-register , floating-point-register , rounding_mode
  O_FPR_C_FPR_C_FPR,        ///< Opcode floating-point-register , floating-point-register , floating-point-register
  O_FPR_C_FPR_C_FPR_C_RM,    ///< Opcode floating-point-register , floating-point-register , floating-point-register , rounding_mode
  O_FPR_C_FPR,            ///< Opcode floating-point-register , floating-point-register
  O_FPR_C_FPR_C_RM,           ///< Opcode floating-point-register , floating-point-register , rounding_mode

  O_FPR_C_GPR,            ///< Opcode floating-point-register , general-register
  O_FPR_C_GPR_C_RM,           ///< Opcode floating-point-register , general-register , rounding_mode
  O_GPR_C_FPR,           ///< Opcode general-register , floating-point-register
  O_GPR_C_FPR_C_RM,       ///< Opcode general-register , floating-point-register , rounding_mode
  O_GPR_C_FPR_C_FPR,       ///< Opcode general-register , floating-point-register , floating-point-register
  O_FPR_C_I_LP_GPR_RP,    ///< Opcode floating-point-register , immediate , lparen ( general-register ) rparen
};

extern std::unordered_map<std::string, RTypeInstructionEncoding> R_type_instruction_encoding_map;
extern std::unordered_map<std::string, I1TypeInstructionEncoding> I1_type_instruction_encoding_map;
extern std::unordered_map<std::string, I2TypeInstructionEncoding> I2_type_instruction_encoding_map;
extern std::unordered_map<std::string, I3TypeInstructionEncoding> I3_type_instruction_encoding_map;
extern std::unordered_map<std::string, STypeInstructionEncoding> S_type_instruction_encoding_map;
extern std::unordered_map<std::string, BTypeInstructionEncoding> B_type_instruction_encoding_map;
extern std::unordered_map<std::string, UTypeInstructionEncoding> U_type_instruction_encoding_map;
extern std::unordered_map<std::string, JTypeInstructionEncoding> J_type_instruction_encoding_map;
extern std::unordered_map<std::string, CSR_RTypeInstructionEncoding> CSR_R_type_instruction_encoding_map;
extern std::unordered_map<std::string, CSR_ITypeInstructionEncoding> CSR_I_type_instruction_encoding_map;

extern std::unordered_map<std::string, FDRTypeInstructionEncoding> F_D_R_type_instruction_encoding_map;
extern std::unordered_map<std::string, FDR1TypeInstructionEncoding> F_D_R1_type_instruction_encoding_map;
extern std::unordered_map<std::string, FDR2TypeInstructionEncoding> F_D_R2_type_instruction_encoding_map;
extern std::unordered_map<std::string, FDR3TypeInstructionEncoding> F_D_R3_type_instruction_encoding_map;
extern std::unordered_map<std::string, FDR4TypeInstructionEncoding> F_D_R4_type_instruction_encoding_map;
extern std::unordered_map<std::string, FDITypeInstructionEncoding> F_D_I_type_instruction_encoding_map;
extern std::unordered_map<std::string, FDSTypeInstructionEncoding> F_D_S_type_instruction_encoding_map;

/**
 * @brief A map that associates instruction names with their expected syntax.
 * 
 * This map stores the expected syntax for various instructions, indexed by their names.
 */
extern std::unordered_map<std::string, std::vector<SyntaxType>> instruction_syntax_map;

bool isValidInstruction(const std::string &instruction);

bool isValidRTypeInstruction(const std::string &name);
bool isValidITypeInstruction(const std::string &instruction);
bool isValidI1TypeInstruction(const std::string &instruction);
bool isValidI2TypeInstruction(const std::string &instruction);
bool isValidI3TypeInstruction(const std::string &instruction);
bool isValidSTypeInstruction(const std::string &instruction);
bool isValidBTypeInstruction(const std::string &instruction);
bool isValidUTypeInstruction(const std::string &instruction);
bool isValidJTypeInstruction(const std::string &instruction);

bool isValidPseudoInstruction(const std::string &instruction);

bool isValidBaseExtensionInstruction(const std::string &instruction);

bool isValidMExtensionInstruction(const std::string &instruction);

bool isValidCSRRTypeInstruction(const std::string &instruction);
bool isValidCSRITypeInstruction(const std::string &instruction);
bool isValidCSRInstruction(const std::string &instruction);

bool isValidFDRTypeInstruction(const std::string &instruction);
bool isValidFDR1TypeInstruction(const std::string &instruction);
bool isValidFDR2TypeInstruction(const std::string &instruction);
bool isValidFDR3TypeInstruction(const std::string &instruction);
bool isValidFDR4TypeInstruction(const std::string &instruction);
bool isValidFDITypeInstruction(const std::string &instruction);
bool isValidFDSTypeInstruction(const std::string &instruction);

bool isFInstruction(const uint32_t &instruction);
bool isBFloat16Instruction(const uint32_t &instruction);
bool isDInstruction(const uint32_t &instruction);

std::string getExpectedSyntaxes(const std::string &opcode);

} // namespace instruction_set


#endif // INSTRUCTIONS_H
