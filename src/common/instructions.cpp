/** @cond DOXYGEN_IGNORE */
/**
 * File Name: instructions.cpp
 * Author: Vishank Singh
 * Github: https://github.com/VishankSingh
 */
/** @endcond */

#include "common/instructions.h"

#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>
#include <array>

namespace instruction_set {

std::unordered_map<std::string, Instruction> instruction_string_map = {
    {"add", Instruction::kadd},
    {"sub", Instruction::ksub},
    {"and", Instruction::kand},
    {"or", Instruction::kor},
    {"xor", Instruction::kxor},
    {"sll", Instruction::ksll},
    {"srl", Instruction::ksrl},
    {"sra", Instruction::ksra},
    {"slt", Instruction::kslt},
    {"sltu", Instruction::ksltu},
    {"SIMD_add32",Instruction::kSIMD_add32}, // newly added instructions 
    {"SIMD_sub32",Instruction::kSIMD_sub32},
    {"SIMD_mul32",Instruction::kSIMD_mul32},
    {"SIMD_load32",Instruction::kSIMD_load32},
    {"SIMD_div32",Instruction::kSIMD_div32},
    {"SIMD_rem32",Instruction::kSIMD_rem32},
    {"fadd_bf16",Instruction::kfadd_bf16},
    {"fsub_bf16",Instruction::kfsub_bf16},
    {"fmul_bf16",Instruction::kfmul_bf16},
    {"fdiv_bf16",Instruction::kfdiv_bf16},
    {"SIMD_add16",Instruction::kSIMD_add16},
    {"SIMD_sub16",Instruction::kSIMD_sub16},
    // end new instructions
    {"addw", Instruction::kaddw},
    {"subw", Instruction::ksubw},
    {"sllw", Instruction::ksllw},
    {"srliw", Instruction::ksrliw},
    {"sraiw", Instruction::ksraiw},

    {"sllw", Instruction::ksllw},
    {"srlw", Instruction::ksrlw},
    {"sraw", Instruction::ksraw},

    {"mul", Instruction::kmul},
    {"mulh", Instruction::kmulh},
    {"mulhsu", Instruction::kmulhsu},
    {"mulhu", Instruction::kmulhu},
    {"div", Instruction::kdiv},
    {"divu", Instruction::kdivu},
    {"rem", Instruction::krem},
    {"remu", Instruction::kremu},

    {"mulw", Instruction::kmulw},
    {"divw", Instruction::kdivw},
    {"divuw", Instruction::kdivuw},
    {"remw", Instruction::kremw},
    {"remuw", Instruction::kremuw},

    {"addi", Instruction::kaddi},
    {"xori", Instruction::kxori},
    {"ori", Instruction::kori},
    {"andi", Instruction::kandi},
    {"slli", Instruction::kslli},
    {"srli", Instruction::ksrli},
    {"srai", Instruction::ksrai},
    {"slti", Instruction::kslti},
    {"sltiu", Instruction::ksltiu},

    {"addiw", Instruction::kaddiw},
    {"slliw", Instruction::kslliw},
    {"srliw", Instruction::ksrliw},
    {"sraiw", Instruction::ksraiw},

    {"lb", Instruction::klb},
    {"lh", Instruction::klh},
    {"lw", Instruction::klw},
    {"ld", Instruction::kld},
    {"lbu", Instruction::klbu},
    {"lhu", Instruction::klhu},
    {"lwu", Instruction::klwu},

    {"sb", Instruction::ksb},
    {"sh", Instruction::ksh},
    {"sw", Instruction::ksw},
    {"sd", Instruction::ksd},

    {"beq", Instruction::kbeq},
    {"bne", Instruction::kbne},
    {"blt", Instruction::kblt},
    {"bge", Instruction::kbge},
    {"bltu", Instruction::kbltu},
    {"bgeu", Instruction::kbgeu},

    {"lui", Instruction::klui},
    {"auipc", Instruction::kauipc},

    {"jal", Instruction::kjal},
    {"jalr", Instruction::kjalr},

    {"ecall", Instruction::kecall},

    {"csrrw", Instruction::kcsrrw},
    {"csrrs", Instruction::kcsrrs},
    {"csrrc", Instruction::kcsrrc},
    {"csrrwi", Instruction::kcsrrwi},
    {"csrrsi", Instruction::kcsrrsi},
    {"csrrci", Instruction::kcsrrci},

    {"fsgnj.s", Instruction::kfsgnj_s},
    {"fsgnjn.s", Instruction::kfsgnjn_s},
    {"fsgnjx.s", Instruction::kfsgnjx_s},
    {"fmin.s", Instruction::kfmin_s},
    {"fmax.s", Instruction::kfmax_s},
    {"fle.s", Instruction::kfle_s},
    {"flt.s", Instruction::kflt_s},
    {"feq.s", Instruction::kfeq_s},

    {"fsgnj.d", Instruction::kfsgnj_d},
    {"fsgnjn.d", Instruction::kfsgnjn_d},
    {"fsgnjx.d", Instruction::kfsgnjx_d},
    {"fmin.d", Instruction::kfmin_d},
    {"fmax.d", Instruction::kfmax_d},
    {"fle.d", Instruction::kfle_d},
    {"flt.d", Instruction::kflt_d},
    {"feq.d", Instruction::kfeq_d},

    {"fadd.s", Instruction::kfadd_s},
    {"fsub.s", Instruction::kfsub_s},
    {"fmul.s", Instruction::kfmul_s},
    {"fdiv.s", Instruction::kfdiv_s},
    {"fsqrt.s", Instruction::kfsqrt_s},

    {"fadd.d", Instruction::kfadd_d},
    {"fsub.d", Instruction::kfsub_d},
    {"fmul.d", Instruction::kfmul_d},
    {"fdiv.d", Instruction::kfdiv_d},
    {"fsqrt.d", Instruction::kfsqrt_d},

    {"fcvt.w.s", Instruction::kfcvt_w_s},
    {"fcvt.wu.s", Instruction::kfcvt_wu_s},
    {"fcvt.l.s", Instruction::kfcvt_l_s},
    {"fcvt.lu.s", Instruction::kfcvt_lu_s},
    {"fcvt.s.w", Instruction::kfcvt_s_w},
    {"fcvt.s.wu", Instruction::kfcvt_s_wu},
    {"fcvt.s.l", Instruction::kfcvt_s_l},
    {"fcvt.s.lu", Instruction::kfcvt_s_lu},

    {"fcvt.w.d", Instruction::kfcvt_w_d},
    {"fcvt.wu.d", Instruction::kfcvt_wu_d},
    {"fcvt.l.d", Instruction::kfcvt_l_d},
    {"fcvt.lu.d", Instruction::kfcvt_lu_d},
    {"fcvt.d.w", Instruction::kfcvt_d_w},
    {"fcvt.d.wu", Instruction::kfcvt_d_wu},
    {"fcvt.d.l", Instruction::kfcvt_d_l},
    {"fcvt.d.lu", Instruction::kfcvt_d_lu},

    {"fcvt.s.d", Instruction::kfcvt_s_d},
    {"fcvt.d.s", Instruction::kfcvt_d_s},

    {"fmv.x.s", Instruction::kfmv_x_w},
    {"fmv.x.d", Instruction::kfmv_x_d},
    {"fmv.s.x", Instruction::kfmv_w_x},
    {"fmv.d.x", Instruction::kfmv_d_x},
    {"fclass.s", Instruction::kfclass_s},
    {"fclass.d", Instruction::kfclass_d},

    {"fmadd.s", Instruction::kfmadd_s},
    {"fmsub.s", Instruction::kfmsub_s},
    {"fnmsub.s", Instruction::kfnmsub_s},
    {"fnmadd.s", Instruction::kfnmadd_s},
    {"fmadd.d", Instruction::kfmadd_d},
    {"fmsub.d", Instruction::kfmsub_d},
    {"fnmsub.d", Instruction::kfnmsub_d},
    {"fnmadd.d", Instruction::kfnmadd_d},

    {"flw", Instruction::kflw},
    {"fsw", Instruction::kfsw},
    {"fld", Instruction::kfld},
    {"fsd", Instruction::kfsd}

};


static const std::unordered_set<std::string> valid_instructions = {
    "add", "sub", "and", "or", "xor", "sll", "srl", "sra", "slt", "sltu",
    "addw", "subw", "sllw", "srlw", "sraw",
    "addi", "xori", "ori", "andi", "slli", "srli", "srai", "slti", "sltiu",
    "addiw", "slliw", "srliw", "sraiw",
    "lb", "lh", "lw", "ld", "lbu", "lhu", "lwu",
    "sb", "sh", "sw", "sd",
    "beq", "bne", "blt", "bge", "bltu", "bgeu",
    "lui", "auipc",
    "jal", "jalr",
    "ecall","SIMD_add32","SIMD_sub32","SIMD_mul32","SIMD_load32","SIMD_div32","SIMD_rem32",
    "fadd_bf16","fsub_bf16","fmul_bf16","fdiv_bf16","SIMD_add16","SIMD_sub16", // newly added instructions 

    "csrrw", "csrrs", "csrrc", "csrrwi", "csrrsi", "csrrci",
    
    "la", "nop", "li", "mv", "not", "neg", "negw",
    "sext.w", "seqz", "snez", "sltz", "sgtz",
    "beqz", "bnez", "blez", "bgez", "bltz", "bgtz",
    "bgt", "ble", "bgtu", "bleu",
    "j", "jr", "ret", "call", "tail", "fence", "fence_i",

    "mul", "mulh", "mulhsu", "mulhu", "div", "divu", "rem", "remu",
    "mulw", "divw", "divuw", "remw", "remuw",

    // RV64F
    "flw", "fsw", "fmadd.s", "fmsub.s", "fnmsub.s", "fnmadd.s",
    "fadd.s", "fsub.s", "fmul.s", "fdiv.s", "fsqrt.s",
    "fsgnj.s", "fsgnjn.s", "fsgnjx.s",
    "fmin.s", "fmax.s",
    "fcvt.w.s", "fcvt.wu.s", "fmv.x.w",
    "feq.s", "flt.s", "fle.s",
    "fclass.s", "fcvt.s.w", "fcvt.s.wu", "fmv.w.x",
    "fcvt.l.s", "fcvt.lu.s", "fcvt.s.l", "fcvt.s.lu",

    // RV64D
    "fld", "fsd", "fmadd.d", "fmsub.d", "fnmsub.d", "fnmadd.d",
    "fadd.d", "fsub.d", "fmul.d", "fdiv.d", "fsqrt.d",
    "fsgnj.d", "fsgnjn.d", "fsgnjx.d",
    "fmin.d", "fmax.d",
    "fcvt.s.d", "fcvt.d.s",
    "feq.d", "flt.d", "fle.d",
    "fclass.d", "fcvt.w.d", "fcvt.wu.d", "fcvt.d.w", "fcvt.d.wu",
    "fcvt.l.d", "fcvt.lu.d", "fmv.x.d", "fcvt.d.l", "fcvt.d.lu", "fmv.d.x"

};

static const std::unordered_set<std::string> RTypeInstructions = {
    // Base RV32I
    "add", "sub", "and", "or", "xor", "sll", "srl", "sra", "slt", "sltu",

    // RV64
    "addw", "subw", "sllw", "srlw", "sraw","SIMD_add32","SIMD_sub32","SIMD_mul32","SIMD_load32","SIMD_div32","SIMD_rem32","SIMD_add16","SIMD_sub16",

    // M Extension
    "mul", "mulh", "mulhsu", "mulhu", "div", "divu", "rem", "remu",

    // M Extension RV64
    "mulw", "divw", "divuw", "remw", "remuw",

};

static const std::unordered_set<std::string> ITypeInstructions = {
    "addi", "xori", "ori", "andi", "slli", "srli", "srai", "slti", "sltiu",
    "addiw", "slliw", "srliw", "sraiw",
    "lb", "lh", "lw", "ld", "lbu", "lhu", "lwu",
    "jalr"
};

static const std::unordered_set<std::string> I1TypeInstructions = {
    "addi", "xori", "ori", "andi", "sltiu", "slti",
    "addiw",
    "lb", "lh", "lw", "ld", "lbu", "lhu", "lwu",
    "jalr"
};

static const std::unordered_set<std::string> I2TypeInstructions = {
    "slli", "srli", "srai",
    "slliw", "srliw", "sraiw"
};

static const std::unordered_set<std::string> I3TypeInstructions = {
    "ecall"
};

static const std::unordered_set<std::string> STypeInstructions = {
    "sb", "sh", "sw", "sd"
};

static const std::unordered_set<std::string> BTypeInstructions = {
    "beq", "bne", "blt", "bge", "bltu", "bgeu"
};

static const std::unordered_set<std::string> UTypeInstructions = {
    "lui", "auipc"
};

static const std::unordered_set<std::string> JTypeInstructions = {
    "jal"
};

static const std::unordered_set<std::string> PseudoInstructions = {
    "la", "nop", "li", "mv", "not", "neg", "negw",
    "sext.w", "seqz", "snez", "sltz", "sgtz",
    "beqz", "bnez", "blez", "bgez", "bltz", "bgtz",
    "bgt", "ble", "bgtu", "bleu",
    "j", "jr", "ret", "call", "tail", "fence", "fence_i",
};

static const std::unordered_set<std::string> BaseExtensionInstructions = {
    "add", "sub", "and", "or", "xor", "sll", "srl", "sra", "slt", "sltu",
    "addw", "subw", "sllw", "srlw", "sraw",
    "addi", "xori", "ori", "andi", "slli", "srli", "srai", "slti", "sltiu",
    "addiw", "slliw", "srliw", "sraiw",
    "lb", "lh", "lw", "ld", "lbu", "lhu", "lwu",
    "sb", "sh", "sw", "sd",
    "beq", "bne", "blt", "bge", "bltu", "bgeu",
    "lui", "auipc",
    "jal", "jalr",
    "ecall",
};

static const std::unordered_set<std::string> CSRRInstructions = {
    "csrrw", "csrrs", "csrrc",
};

static const std::unordered_set<std::string> CSRIInstructions = {
    "csrrwi", "csrrsi", "csrrci",
};

static const std::unordered_set<std::string> CSRInstructions = {
    "csrrw", "csrrs", "csrrc", "csrrwi", "csrrsi", "csrrci",
};

static const std::unordered_set<std::string> MExtensionInstructions = {
    "mul", "mulh", "mulhsu", "mulhu", "div", "divu", "rem", "remu",
    "mulw", "divw", "divuw", "remw", "remuw",
};

//====================================================================================
static const std::unordered_set<std::string> FDExtensionRTypeInstructions = {
    "fsgnj.s", "fsgnjn.s", "fsgnjx.s", "fmin.s", "fmax.s",
    "feq.s", "flt.s", "fle.s",
    "fsgnj.d", "fsgnjn.d", "fsgnjx.d", "fmin.d", "fmax.d",
    "feq.d", "flt.d", "fle.d",
};

static const std::unordered_set<std::string> FDExtensionR1TypeInstructions = {
    "fadd.s", "fsub.s", "fmul.s", "fdiv.s",
    "fadd.d", "fsub.d", "fmul.d", "fdiv.d",
    "fadd_bf16", "fsub_bf16", "fdiv_bf16", "fmul_bf16", // new Bfloat16 Instructions
};

static const std::unordered_set<std::string> FDExtensionR2TypeInstructions = {
    "fsqrt.s",
    "fcvt.w.s", "fcvt.wu.s",
    "fcvt.s.w", "fcvt.s.wu",
    "fcvt.l.s", "fcvt.lu.s",
    "fcvt.s.l", "fcvt.s.lu",
    "fsqrt.d",
    "fcvt.s.d", "fcvt.d.s",
    "fcvt.w.d", "fcvt.wu.d",
    "fcvt.d.w", "fcvt.d.wu",

    "fcvt.l.d", "fcvt.lu.d",
    "fcvt.d.l", "fcvt.d.lu",
};

static const std::unordered_set<std::string> FDExtensionR3TypeInstructions = {
    "fmv.x.w", "fmv.w.x",
    "fclass.s",
    "fclass.d",
    "fmv.x.d", "fmv.d.x",
};

static const std::unordered_set<std::string> FDExtensionR4TypeInstructions = {
    "fmadd.s", "fmsub.s", "fnmsub.s", "fnmadd.s",
    "fmadd.d", "fmsub.d", "fnmsub.d", "fnmadd.d",
};

static const std::unordered_set<std::string> FDExtensionITypeInstructions = {
    "flw", "fld",
};

static const std::unordered_set<std::string> FDExtensionSTypeInstructions = {
    "fsw", "fsd",
};

static const std::unordered_set<std::string> FExtensionInstructions = {
    "flw", "fsw", "fmadd.s", "fmsub.d", "fnmsub.s", "fnmadd.s",
    "fadd.s", "fsub.s", "fmul.s", "fdiv.s", "fsqrt.s",
    "fsgnj.s", "fsgnjn.s", "fsgnjx.s",
    "fmin.s", "fmax.s",
    "fcvt.w.s", "fcvt.wu.s", "fmv.x.w",
    "feq.s", "flt.s", "fle.s",
    "fclass.s", "fcvt.s.w", "fcvt.s.wu", "fmv.w.x",
    "fcvt.l.s", "fcvt.lu.s", "fcvt.s.l", "fcvt.s.lu",
};

static const std::unordered_set<std::string> DExtensionInstructions = {};

std::unordered_map<std::string, RTypeInstructionEncoding> R_type_instruction_encoding_map = {
    {"add", {0b0110011, 0b000, 0b0000000}}, // O_GPR_C_GPR_C_GPR
    {"sub", {0b0110011, 0b000, 0b0100000}}, // O_GPR_C_GPR_C_GPR
    {"xor", {0b0110011, 0b100, 0b0000000}}, // O_GPR_C_GPR_C_GPR
    
    {"SIMD_add32",{0b0110011, 0b000, 0b0001011}},
    {"SIMD_sub32",{0b0110011, 0b001, 0b0001011}},
    {"SIMD_load32",{0b0110011, 0b111, 0b0001011}},
    {"SIMD_mul32",{0b0110011, 0b011, 0b0001011}},
    {"SIMD_div32",{0b0110011, 0b100, 0b0001011}},
    {"SIMD_rem32",{0b0110011, 0b101, 0b0001011}},
    {"SIMD_add16",{0b0110011, 0b010, 0b0001011}},
    {"SIMD_sub16",{0b0110011, 0b110, 0b0001011}},
    {"or", {0b0110011, 0b110, 0b0000000}}, // O_GPR_C_GPR_C_GPR
    {"and", {0b0110011, 0b111, 0b0000000}}, // O_GPR_C_GPR_C_GPR
    {"sll", {0b0110011, 0b001, 0b0000000}}, // O_GPR_C_GPR_C_GPR
    {"srl", {0b0110011, 0b101, 0b0000000}}, // O_GPR_C_GPR_C_GPR
    {"sra", {0b0110011, 0b101, 0b0100000}}, // O_GPR_C_GPR_C_GPR
    {"slt", {0b0110011, 0b010, 0b0000000}}, // O_GPR_C_GPR_C_GPR
    {"sltu", {0b0110011, 0b011, 0b0000000}}, // O_GPR_C_GPR_C_GPR

    {"addw", {0b0111011, 0b000, 0b0000000}}, // O_GPR_C_GPR_C_GPR
    {"subw", {0b0111011, 0b000, 0b0100000}}, // O_GPR_C_GPR_C_GPR
    {"sllw", {0b0111011, 0b001, 0b0000000}}, // O_GPR_C_GPR_C_GPR
    {"srlw", {0b0111011, 0b101, 0b0000000}}, // O_GPR_C_GPR_C_GPR
    {"sraw", {0b0111011, 0b101, 0b0100000}}, // O_GPR_C_GPR_C_GPR

//==RV64M======================================================================================
    {"mul", {0b0110011, 0b000, 0b0000001}}, // O_GPR_C_GPR_C_GPR
    {"mulh", {0b0110011, 0b001, 0b0000001}}, // O_GPR_C_GPR_C_GPR
    {"mulhsu", {0b0110011, 0b010, 0b0000001}}, // O_GPR_C_GPR_C_GPR
    {"mulhu", {0b0110011, 0b011, 0b0000001}}, // O_GPR_C_GPR_C_GPR
    {"div", {0b0110011, 0b100, 0b0000001}}, // O_GPR_C_GPR_C_GPR
    {"divu", {0b0110011, 0b101, 0b0000001}}, // O_GPR_C_GPR_C_GPR
    {"rem", {0b0110011, 0b110, 0b0000001}}, // O_GPR_C_GPR_C_GPR
    {"remu", {0b0110011, 0b111, 0b0000001}}, // O_GPR_C_GPR_C_GPR

    {"mulw", {0b0111011, 0b000, 0b0000001}}, // O_GPR_C_GPR_C_GPR
    {"divw", {0b0111011, 0b100, 0b0000001}}, // O_GPR_C_GPR_C_GPR
    {"divuw", {0b0111011, 0b101, 0b0000001}}, // O_GPR_C_GPR_C_GPR
    {"remw", {0b0111011, 0b110, 0b0000001}}, // O_GPR_C_GPR_C_GPR
    {"remuw", {0b0111011, 0b111, 0b0000001}}, // O_GPR_C_GPR_C_GPR

};

std::unordered_map<std::string, I1TypeInstructionEncoding> I1_type_instruction_encoding_map = {
    {"addi", {0b0010011, 0b000}}, // O_GPR_C_GPR_C_I
    {"xori", {0b0010011, 0b100}}, // O_GPR_C_GPR_C_I
    {"ori", {0b0010011, 0b110}}, // O_GPR_C_GPR_C_I
    {"andi", {0b0010011, 0b111}}, // O_GPR_C_GPR_C_I
    {"sltiu", {0b0010011, 0b011}}, // O_GPR_C_GPR_C_I
    {"slti", {0b0010011, 0b010}}, // O_GPR_C_GPR_C_I

    {"addiw", {0b0011011, 0b000}}, // O_GPR_C_GPR_C_I

    {"lb", {0b0000011, 0b000}}, // O_GPR_C_I_LP_GPR_RP, O_GPR_C_DL
    {"lh", {0b0000011, 0b001}}, // O_GPR_C_I_LP_GPR_RP, O_GPR_C_DL
    {"lw", {0b0000011, 0b010}}, // O_GPR_C_I_LP_GPR_RP, O_GPR_C_DL
    {"ld", {0b0000011, 0b011}}, // O_GPR_C_I_LP_GPR_RP, O_GPR_C_DL
    {"lbu", {0b0000011, 0b100}}, // O_GPR_C_I_LP_GPR_RP,
    {"lhu", {0b0000011, 0b101}}, // O_GPR_C_I_LP_GPR_RP,
    {"lwu", {0b0000011, 0b110}}, // O_GPR_C_I_LP_GPR_RP,

    {"jalr", {0b1100111, 0b000}}, // O_GR_C_I, O_GPR_C_IL
};

std::unordered_map<std::string, I3TypeInstructionEncoding> I3_type_instruction_encoding_map = {
    {"ecall", {0b1110011, 0b000, 0b0000000}}, // O
};

std::unordered_map<std::string, I2TypeInstructionEncoding> I2_type_instruction_encoding_map = {
    {"slli", {0b0010011, 0b001, 0b000000}}, // O_GPR_C_GPR_C_I
    {"srli", {0b0010011, 0b101, 0b000000}}, // O_GPR_C_GPR_C_I
    {"srai", {0b0010011, 0b101, 0b010000}}, // O_GPR_C_GPR_C_I

    {"slliw", {0b0011011, 0b001, 0b000000}}, // O_GPR_C_GPR_C_I
    {"srliw", {0b0011011, 0b101, 0b000000}}, // O_GPR_C_GPR_C_I
    {"sraiw", {0b0011011, 0b101, 0b010000}}, // O_GPR_C_GPR_C_I
};

std::unordered_map<std::string, STypeInstructionEncoding> S_type_instruction_encoding_map = {
    {"sb", {0b0100011, 0b000}}, // O_GPR_C_GPR_C_I
    {"sh", {0b0100011, 0b001}}, // O_GPR_C_GPR_C_I
    {"sw", {0b0100011, 0b010}}, // O_GPR_C_GPR_C_I
    {"sd", {0b0100011, 0b011}}, // O_GPR_C_GPR_C_I
};

std::unordered_map<std::string, BTypeInstructionEncoding> B_type_instruction_encoding_map = {
    {"beq", {0b1100011, 0b000}}, // O_GPR_C_GPR_C_I, O_GPR_C_GPR_C_IL
    {"bne", {0b1100011, 0b001}}, // O_GPR_C_GPR_C_I, O_GPR_C_GPR_C_IL
    {"blt", {0b1100011, 0b100}}, // O_GPR_C_GPR_C_I, O_GPR_C_GPR_C_IL
    {"bge", {0b1100011, 0b101}}, // O_GPR_C_GPR_C_I, O_GPR_C_GPR_C_IL
    {"bltu", {0b1100011, 0b110}}, // O_GPR_C_GPR_C_I, O_GPR_C_GPR_C_IL
    {"bgeu", {0b1100011, 0b111}}, // O_GPR_C_GPR_C_I, O_GPR_C_GPR_C_IL
};

std::unordered_map<std::string, UTypeInstructionEncoding> U_type_instruction_encoding_map = {
    {"lui", {0b0110111}}, // O_GR_C_I
    {"auipc", {0b0010111}}, // O_GR_C_I
};

std::unordered_map<std::string, JTypeInstructionEncoding> J_type_instruction_encoding_map = {
    {"jal", {0b1101111}}, // O_GPR_C_IL
};

std::unordered_map<std::string, CSR_RTypeInstructionEncoding> CSR_R_type_instruction_encoding_map{
    {"csrrw", {0b1110011, 0b001}}, // O_GPR_C_CSR_C_GPR
    {"csrrs", {0b1110011, 0b010}}, // O_GPR_C_CSR_C_GPR
    {"csrrc", {0b1110011, 0b011}}, // O_GPR_C_CSR_C_GPR
};

std::unordered_map<std::string, CSR_ITypeInstructionEncoding> CSR_I_type_instruction_encoding_map{
    {"csrrwi", {0b1110011, 0b101}}, // O_GPR_C_CSR_C_I
    {"csrrsi", {0b1110011, 0b110}}, // O_GPR_C_CSR_C_I
    {"csrrci", {0b1110011, 0b111}}, // O_GPR_C_CSR_C_I
};

std::unordered_map<std::string, FDRTypeInstructionEncoding> F_D_R_type_instruction_encoding_map = {
    {"fsgnj.s", {0b1010011, 0b000, 0b0010000}}, // O_FPR_C_FPR_C_FPR
    {"fsgnjn.s", {0b1010011, 0b001, 0b0010000}}, // O_FPR_C_FPR_C_FPR
    {"fsgnjx.s", {0b1010011, 0b010, 0b0010000}}, // O_FPR_C_FPR_C_FPR

    {"fmin.s", {0b1010011, 0b000, 0b0010100}}, // O_FPR_C_FPR_C_FPR
    {"fmax.s", {0b1010011, 0b001, 0b0010100}}, // O_FPR_C_FPR_C_FPR

    {"feq.s", {0b1010011, 0b010, 0b1010000}}, // O_GPR_C_FPR_C_FPR // affect all
    {"flt.s", {0b1010011, 0b001, 0b1010000}}, // O_GPR_C_FPR_C_FPR // affect all
    {"fle.s", {0b1010011, 0b000, 0b1010000}}, // O_GPR_C_FPR_C_FPR // affect all

    {"feq.d", {0b1010011, 0b010, 0b1010001}}, // O_GPR_C_FPR_C_FPR
    {"flt.d", {0b1010011, 0b001, 0b1010001}}, // O_GPR_C_FPR_C_FPR
    {"fle.d", {0b1010011, 0b000, 0b1010001}}, // O_GPR_C_FPR_C_FPR

    {"fsgnj.d", {0b1010011, 0b000, 0b0010001}}, // O_FPR_C_FPR_C_FPR
    {"fsgnjn.d", {0b1010011, 0b001, 0b0010001}}, // O_FPR_C_FPR_C_FPR
    {"fsgnjx.d", {0b1010011, 0b010, 0b0010001}}, // O_FPR_C_FPR_C_FPR

    {"fmin.d", {0b1010011, 0b000, 0b0010101}}, // O_FPR_C_FPR_C_FPR
    {"fmax.d", {0b1010011, 0b001, 0b0010101}}, // O_FPR_C_FPR_C_FPR
};

std::unordered_map<std::string, FDR1TypeInstructionEncoding> F_D_R1_type_instruction_encoding_map = {
    {"fadd.s", {0b1010011, 0b0000000}}, // O_FPR_C_FPR_C_FPR
    {"fsub.s", {0b1010011, 0b0000100}}, // O_FPR_C_FPR_C_FPR
    {"fmul.s", {0b1010011, 0b0001000}}, // O_FPR_C_FPR_C_FPR
    {"fdiv.s", {0b1010011, 0b0001100}}, // O_FPR_C_FPR_C_FPR

    {"fadd.d", {0b1010011, 0b0000001}}, // O_FPR_C_FPR_C_FPR
    {"fsub.d", {0b1010011, 0b0000101}}, // O_FPR_C_FPR_C_FPR
    {"fmul.d", {0b1010011, 0b0001001}}, // O_FPR_C_FPR_C_FPR
    {"fdiv.d", {0b1010011, 0b0001101}}, // O_FPR_C_FPR_C_FPR

    // Bfloat 16
    {"fadd_bf16", {0b1010011, 0b0000010}}, // O_FPR_C_FPR_C_FPR
    {"fsub_bf16", {0b1010011, 0b0000110}}, // O_FPR_C_FPR_C_FPR
    {"fmul_bf16", {0b1010011, 0b0001010}}, // O_FPR_C_FPR_C_FPR
    {"fdiv_bf16", {0b1010011, 0b0001110}}, // O_FPR_C_FPR_C_FPR
};

std::unordered_map<std::string, FDR2TypeInstructionEncoding> F_D_R2_type_instruction_encoding_map = {
    {"fsqrt.s", {0b1010011, 0b00000, 0b0101100}}, // O_FPR_C_FPR

    {"fcvt.w.s", {0b1010011, 0b00000, 0b1100000}}, // O_GPR_C_FPR // affect all
    {"fcvt.wu.s", {0b1010011, 0b00001, 0b1100000}}, // O_GPR_C_FPR // affect all
    {"fcvt.l.s", {0b1010011, 0b00010, 0b1100000}}, // O_GPR_C_FPR // affect all
    {"fcvt.lu.s", {0b1010011, 0b00011, 0b1100000}}, // O_GPR_C_FPR // affect all

    {"fcvt.s.w", {0b1010011, 0b00000, 0b1101000}}, // O_FPR_C_GPR
    {"fcvt.s.wu", {0b1010011, 0b00001, 0b1101000}}, // O_FPR_C_GPR
    {"fcvt.s.l", {0b1010011, 0b00010, 0b1101000}}, // O_FPR_C_GPR
    {"fcvt.s.lu", {0b1010011, 0b00011, 0b1101000}}, // O_FPR_C_GPR


    {"fsqrt.d", {0b1010011, 0b00000, 0b0101101}}, // O_FPR_C_FPR

    {"fcvt.w.d", {0b1010011, 0b00000, 0b1100001}}, // O_GPR_C_FPR
    {"fcvt.wu.d", {0b1010011, 0b00001, 0b1100001}}, // O_GPR_C_FPR
    {"fcvt.l.d", {0b1010011, 0b00010, 0b1100001}}, // O_GPR_C_FPR
    {"fcvt.lu.d", {0b1010011, 0b00011, 0b1100001}}, // O_GPR_C_FPR

    {"fcvt.d.w", {0b1010011, 0b00000, 0b1101001}}, // O_FPR_C_GPR
    {"fcvt.d.wu", {0b1010011, 0b00001, 0b1101001}}, // O_FPR_C_GPR
    {"fcvt.d.l", {0b1010011, 0b00010, 0b1101001}}, // O_FPR_C_GPR
    {"fcvt.d.lu", {0b1010011, 0b00011, 0b1101001}}, // O_FPR_C_GPR


    {"fcvt.s.d", {0b1010011, 0b00001, 0b0100000}}, // O_FPR_C_FPR
    {"fcvt.d.s", {0b1010011, 0b00000, 0b0100001}}, // O_FPR_C_FPR

};

std::unordered_map<std::string, FDR3TypeInstructionEncoding> F_D_R3_type_instruction_encoding_map = {
    {"fmv.w.x", {0b1010011, 0b000, 0b00000, 0b1111000}}, // O_FPR_C_GPR
    {"fmv.x.w", {0b1010011, 0b000, 0b00000, 0b1110000}}, // O_GPR_C_FPR // affect all
    {"fclass.s", {0b1010011, 0b001, 0b00000, 0b1110000}}, // O_GPR_C_FPR // affect all

    {"fmv.d.x", {0b1010011, 0b000, 0b00000, 0b1111001}}, // O_FPR_C_GPR
    {"fmv.x.d", {0b1010011, 0b000, 0b00000, 0b1110001}}, // O_GPR_C_FPR
    {"fclass.d", {0b1010011, 0b001, 0b00000, 0b1110001}}, // O_GPR_C_FPR
};

std::unordered_map<std::string, FDR4TypeInstructionEncoding> F_D_R4_type_instruction_encoding_map = {
    {"fmadd.s", {0b1000011, 0b00}}, // O_FPR_C_FPR_C_FPR_C_FPR
    {"fmsub.s", {0b1000111, 0b00}}, // O_FPR_C_FPR_C_FPR_C_FPR
    {"fnmsub.s", {0b1001011, 0b00}}, // O_FPR_C_FPR_C_FPR_C_FPR
    {"fnmadd.s", {0b1001111, 0b00}}, // O_FPR_C_FPR_C_FPR_C_FPR

    {"fmadd.d", {0b1000011, 0b01}}, // O_FPR_C_FPR_C_FPR_C_FPR
    {"fmsub.d", {0b1000111, 0b01}}, // O_FPR_C_FPR_C_FPR_C_FPR
    {"fnmsub.d", {0b1001011, 0b01}}, // O_FPR_C_FPR_C_FPR_C_FPR
    {"fnmadd.d", {0b1001111, 0b01}}, // O_FPR_C_FPR_C_FPR_C_FPR
};

std::unordered_map<std::string, FDITypeInstructionEncoding> F_D_I_type_instruction_encoding_map = {
    {"flw", {0b0000111, 0b010}}, // O_FPR_C_I_LP_GPR_RP, O_FPR_C_DL
    {"fld", {0b0000111, 0b011}}, // O_FPR_C_I_LP_GPR_RP, O_FPR_C_DL
};

std::unordered_map<std::string, FDSTypeInstructionEncoding> F_D_S_type_instruction_encoding_map = {
    {"fsw", {0b0100111, 0b010}}, // O_FPR_C_I_LP_GPR_RP
    {"fsd", {0b0100111, 0b011}}, // O_FPR_C_I_LP_GPR_RP
};

/*
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

    DL -> Data Label
    IL -> Instruction Label
*/
std::unordered_map<std::string, std::vector<SyntaxType>> instruction_syntax_map = {
    {"add", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"sub", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"xor", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"or", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"and", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"sll", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"srl", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"sra", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"slt", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"sltu", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"SIMD_add32", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"SIMD_sub32", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"SIMD_mul32", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"SIMD_load32", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"SIMD_div32", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"SIMD_rem32", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"SIMD_add16", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"SIMD_sub16", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"addi", {SyntaxType::O_GPR_C_GPR_C_I}},
    {"xori", {SyntaxType::O_GPR_C_GPR_C_I}},
    {"ori", {SyntaxType::O_GPR_C_GPR_C_I}},
    {"andi", {SyntaxType::O_GPR_C_GPR_C_I}},
    {"slli", {SyntaxType::O_GPR_C_GPR_C_I}},
    {"srli", {SyntaxType::O_GPR_C_GPR_C_I}},
    {"srai", {SyntaxType::O_GPR_C_GPR_C_I}},
    {"slti", {SyntaxType::O_GPR_C_GPR_C_I}},
    {"sltiu", {SyntaxType::O_GPR_C_GPR_C_I}},

    {"lb", {SyntaxType::O_GPR_C_I_LP_GPR_RP, SyntaxType::O_GPR_C_DL}},
    {"lh", {SyntaxType::O_GPR_C_I_LP_GPR_RP, SyntaxType::O_GPR_C_DL}},
    {"lw", {SyntaxType::O_GPR_C_I_LP_GPR_RP, SyntaxType::O_GPR_C_DL}},
    {"ld", {SyntaxType::O_GPR_C_I_LP_GPR_RP, SyntaxType::O_GPR_C_DL}},
    {"lbu", {SyntaxType::O_GPR_C_I_LP_GPR_RP}},
    {"lhu", {SyntaxType::O_GPR_C_I_LP_GPR_RP}},
    {"lwu", {SyntaxType::O_GPR_C_I_LP_GPR_RP}},

    {"sb", {SyntaxType::O_GPR_C_I_LP_GPR_RP}},
    {"sh", {SyntaxType::O_GPR_C_I_LP_GPR_RP}},
    {"sw", {SyntaxType::O_GPR_C_I_LP_GPR_RP}},
    {"sd", {SyntaxType::O_GPR_C_I_LP_GPR_RP}},

    {"beq", {SyntaxType::O_GPR_C_GPR_C_I, SyntaxType::O_GPR_C_GPR_C_IL}},
    {"bne", {SyntaxType::O_GPR_C_GPR_C_I, SyntaxType::O_GPR_C_GPR_C_IL}},
    {"blt", {SyntaxType::O_GPR_C_GPR_C_I, SyntaxType::O_GPR_C_GPR_C_IL}},
    {"bge", {SyntaxType::O_GPR_C_GPR_C_I, SyntaxType::O_GPR_C_GPR_C_IL}},
    {"bltu", {SyntaxType::O_GPR_C_GPR_C_I, SyntaxType::O_GPR_C_GPR_C_IL}},
    {"bgeu", {SyntaxType::O_GPR_C_GPR_C_I, SyntaxType::O_GPR_C_GPR_C_IL}},

    {"lui", {SyntaxType::O_GPR_C_I}},
    {"auipc", {SyntaxType::O_GPR_C_I}},

    {"jal", {SyntaxType::O_GPR_C_I, SyntaxType::O_GPR_C_IL}},

    {"jalr", {SyntaxType::O_GPR_C_I_LP_GPR_RP}},

    {"ecall", {SyntaxType::O}},

///////////////////////////////////////////////////////////////////////////////////

    {"csrrw", {SyntaxType::O_GPR_C_CSR_C_GPR}},
    {"csrrs", {SyntaxType::O_GPR_C_CSR_C_GPR}},
    {"csrrc", {SyntaxType::O_GPR_C_CSR_C_GPR}},
    {"csrrwi", {SyntaxType::O_GPR_C_CSR_C_I}},
    {"csrrsi", {SyntaxType::O_GPR_C_CSR_C_I}},
    {"csrrci", {SyntaxType::O_GPR_C_CSR_C_I}},

    {"fence", {SyntaxType::O}},
    {"fence_i", {SyntaxType::O}},

///////////////////////////////////////////////////////////////////////////////////

    {"nop", {SyntaxType::PSEUDO}},
    {"li", {SyntaxType::PSEUDO}},
    {"la", {SyntaxType::PSEUDO}},
    {"mv", {SyntaxType::PSEUDO}},
    {"not", {SyntaxType::PSEUDO}},
    {"neg", {SyntaxType::PSEUDO}},
    {"negw", {SyntaxType::PSEUDO}},
    {"sext.w", {SyntaxType::PSEUDO}},
    {"seqz", {SyntaxType::PSEUDO}},
    {"snez", {SyntaxType::PSEUDO}},
    {"sltz", {SyntaxType::PSEUDO}},
    {"sgtz", {SyntaxType::PSEUDO}},
    {"beqz", {SyntaxType::PSEUDO}},
    {"bnez", {SyntaxType::PSEUDO}},
    {"blez", {SyntaxType::PSEUDO}},
    {"bgez", {SyntaxType::PSEUDO}},
    {"bltz", {SyntaxType::PSEUDO}},
    {"bgtz", {SyntaxType::PSEUDO}},
    {"bgt", {SyntaxType::PSEUDO}},
    {"ble", {SyntaxType::PSEUDO}},
    {"bgtu", {SyntaxType::PSEUDO}},
    {"bleu", {SyntaxType::PSEUDO}},
    {"j", {SyntaxType::PSEUDO}},
    {"jr", {SyntaxType::PSEUDO}},
    {"ret", {SyntaxType::PSEUDO}},
    {"call", {SyntaxType::PSEUDO}},
    {"tail", {SyntaxType::PSEUDO}},
    {"fence", {SyntaxType::PSEUDO}},
    {"fence_i", {SyntaxType::PSEUDO}},

///////////////////////////////////////////////////////////////////////////////////
    {"mul", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"mulh", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"mulhsu", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"mulhu", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"div", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"divu", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"rem", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"remu", {SyntaxType::O_GPR_C_GPR_C_GPR}},

    {"mulw", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"divw", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"divuw", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"remw", {SyntaxType::O_GPR_C_GPR_C_GPR}},
    {"remuw", {SyntaxType::O_GPR_C_GPR_C_GPR}},

///////////////////////////////////////////////////////////////////////////////////

    {"flw", {SyntaxType::O_FPR_C_I_LP_GPR_RP}},
    {"fsw", {SyntaxType::O_FPR_C_I_LP_GPR_RP}},

    {"fmadd.s", {SyntaxType::O_FPR_C_FPR_C_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_FPR_C_FPR_C_RM}},
    {"fmsub.s", {SyntaxType::O_FPR_C_FPR_C_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_FPR_C_FPR_C_RM}},
    {"fnmsub.s", {SyntaxType::O_FPR_C_FPR_C_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_FPR_C_FPR_C_RM}},
    {"fnmadd.s", {SyntaxType::O_FPR_C_FPR_C_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_FPR_C_FPR_C_RM}},

    {"fadd.s", {SyntaxType::O_FPR_C_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_FPR_C_RM}},
    {"fsub.s", {SyntaxType::O_FPR_C_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_FPR_C_RM}},
    {"fmul.s", {SyntaxType::O_FPR_C_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_FPR_C_RM}},
    {"fdiv.s", {SyntaxType::O_FPR_C_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_FPR_C_RM}},

    {"fadd_bf16", {SyntaxType::O_FPR_C_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_FPR_C_RM}},
    {"fsub_bf16", {SyntaxType::O_FPR_C_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_FPR_C_RM}},
    {"fmul_bf16", {SyntaxType::O_FPR_C_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_FPR_C_RM}},
    {"fdiv_bf16", {SyntaxType::O_FPR_C_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_FPR_C_RM}},

    {"fsqrt.s", {SyntaxType::O_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_RM}},

    {"fsgnj.s", {SyntaxType::O_FPR_C_FPR_C_FPR}},
    {"fsgnjn.s", {SyntaxType::O_FPR_C_FPR_C_FPR}},
    {"fsgnjx.s", {SyntaxType::O_FPR_C_FPR_C_FPR}},
    {"fmin.s", {SyntaxType::O_FPR_C_FPR_C_FPR}},
    {"fmax.s", {SyntaxType::O_FPR_C_FPR_C_FPR}},

    {"feq.s", {SyntaxType::O_GPR_C_FPR_C_FPR}},
    {"flt.s", {SyntaxType::O_GPR_C_FPR_C_FPR}},
    {"fle.s", {SyntaxType::O_GPR_C_FPR_C_FPR}},

    {"fclass.s", {SyntaxType::O_GPR_C_FPR}},

    {"fmv.x.w", {SyntaxType::O_GPR_C_FPR}}, // x[n][0:31] to f[m][0:31], 32-bit floating-point value from an f (floating-point) register into an x (integer) register without conversion
    {"fmv.w.x", {SyntaxType::O_FPR_C_GPR}}, // f[n][0:31] to x[m][0:31],

    {"fcvt.w.s", {SyntaxType::O_GPR_C_FPR, SyntaxType::O_GPR_C_FPR_C_RM}}, // f32->int32
    {"fcvt.wu.s", {SyntaxType::O_GPR_C_FPR, SyntaxType::O_GPR_C_FPR_C_RM}}, // f32->uint32
    {"fcvt.l.s", {SyntaxType::O_GPR_C_FPR, SyntaxType::O_GPR_C_FPR_C_RM}}, // f32->int64
    {"fcvt.lu.s", {SyntaxType::O_GPR_C_FPR, SyntaxType::O_GPR_C_FPR_C_RM}}, // f32->uint64

    {"fcvt.s.w", {SyntaxType::O_FPR_C_GPR, SyntaxType::O_FPR_C_GPR_C_RM}}, // int32->f32
    {"fcvt.s.wu", {SyntaxType::O_FPR_C_GPR, SyntaxType::O_FPR_C_GPR_C_RM}}, // uint32->f32
    {"fcvt.s.l", {SyntaxType::O_FPR_C_GPR, SyntaxType::O_FPR_C_GPR_C_RM}}, // int64->f32
    {"fcvt.s.lu", {SyntaxType::O_FPR_C_GPR, SyntaxType::O_FPR_C_GPR_C_RM}}, // uint64->f32


///////////////////////////////////////////////////////////////////////////////////

    {"fld", {SyntaxType::O_FPR_C_I_LP_GPR_RP}},
    {"fsd", {SyntaxType::O_FPR_C_I_LP_GPR_RP}},

    {"fmadd.d", {SyntaxType::O_FPR_C_FPR_C_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_FPR_C_FPR_C_RM}},
    {"fmsub.d", {SyntaxType::O_FPR_C_FPR_C_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_FPR_C_FPR_C_RM}},
    {"fnmsub.d", {SyntaxType::O_FPR_C_FPR_C_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_FPR_C_FPR_C_RM}},
    {"fnmadd.d", {SyntaxType::O_FPR_C_FPR_C_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_FPR_C_FPR_C_RM}},

    {"fadd.d", {SyntaxType::O_FPR_C_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_FPR_C_RM}},
    {"fsub.d", {SyntaxType::O_FPR_C_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_FPR_C_RM}},
    {"fmul.d", {SyntaxType::O_FPR_C_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_FPR_C_RM}},
    {"fdiv.d", {SyntaxType::O_FPR_C_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_FPR_C_RM}},

    {"fsqrt.d", {SyntaxType::O_FPR_C_FPR, SyntaxType::O_FPR_C_FPR_C_RM}},

    {"fsgnj.d", {SyntaxType::O_FPR_C_FPR_C_FPR}},
    {"fsgnjn.d", {SyntaxType::O_FPR_C_FPR_C_FPR}},
    {"fsgnjx.d", {SyntaxType::O_FPR_C_FPR_C_FPR}},
    {"fmin.d", {SyntaxType::O_FPR_C_FPR_C_FPR}},
    {"fmax.d", {SyntaxType::O_FPR_C_FPR_C_FPR}},

    {"feq.d", {SyntaxType::O_GPR_C_FPR_C_FPR}},
    {"flt.d", {SyntaxType::O_GPR_C_FPR_C_FPR}},
    {"fle.d", {SyntaxType::O_GPR_C_FPR_C_FPR}},

    {"fclass.d", {SyntaxType::O_GPR_C_FPR}},

    {"fcvt.w.d", {SyntaxType::O_GPR_C_FPR, SyntaxType::O_FPR_C_GPR_C_RM}}, // f64->int32, sign extends
    {"fcvt.wu.d", {SyntaxType::O_GPR_C_FPR, SyntaxType::O_FPR_C_GPR_C_RM}}, // f64->uint32, sign extends
    {"fcvt.l.d", {SyntaxType::O_GPR_C_FPR, SyntaxType::O_FPR_C_GPR_C_RM}}, // f64->int64
    {"fcvt.lu.d", {SyntaxType::O_GPR_C_FPR, SyntaxType::O_FPR_C_GPR_C_RM}}, // f64->uint64

    {"fcvt.d.w", {SyntaxType::O_FPR_C_GPR, SyntaxType::O_GPR_C_FPR_C_RM}}, // int32->f64
    {"fcvt.d.wu", {SyntaxType::O_FPR_C_GPR, SyntaxType::O_GPR_C_FPR_C_RM}}, // uint32->f64
    {"fcvt.d.l", {SyntaxType::O_FPR_C_GPR, SyntaxType::O_FPR_C_GPR_C_RM}}, // int64->f64
    {"fcvt.d.lu", {SyntaxType::O_FPR_C_GPR, SyntaxType::O_FPR_C_GPR_C_RM}}, // uint64->f64

    {"fcvt.s.d", {SyntaxType::O_FPR_C_FPR, SyntaxType::O_GPR_C_FPR_C_RM}}, // f64->f32
    {"fcvt.d.s", {SyntaxType::O_FPR_C_FPR, SyntaxType::O_GPR_C_FPR_C_RM}}, // f32->f64

    {"fmv.x.d", {SyntaxType::O_GPR_C_FPR}}, // x[n][0:63] to f[m][0:63], 64-bit floating-point value from an f (floating-point) register into an x (integer) register without conversion
    {"fmv.d.x", {SyntaxType::O_FPR_C_GPR}}, // f[n][0:63] to x[m][0:63], 64-bit floating-point value from an x (integer) register into an f (floating-point) register without conversion

};

bool isValidInstruction(const std::string &instruction) {
  return valid_instructions.find(instruction)!=valid_instructions.end();
}

bool isValidRTypeInstruction(const std::string &instruction) {
  return RTypeInstructions.find(instruction)!=RTypeInstructions.end();
}

bool isValidITypeInstruction(const std::string &instruction) {
  return (I1TypeInstructions.find(instruction)!=I1TypeInstructions.end()) ||
      (I2TypeInstructions.find(instruction)!=I2TypeInstructions.end()) ||
      (I3TypeInstructions.find(instruction)!=I3TypeInstructions.end());
}

bool isValidI1TypeInstruction(const std::string &instruction) {
  return I1TypeInstructions.find(instruction)!=I1TypeInstructions.end();
}

bool isValidI2TypeInstruction(const std::string &instruction) {
  return I2TypeInstructions.find(instruction)!=I2TypeInstructions.end();
}

bool isValidI3TypeInstruction(const std::string &instruction) {
  return I3TypeInstructions.find(instruction)!=I3TypeInstructions.end();
}

bool isValidSTypeInstruction(const std::string &instruction) {
  return STypeInstructions.find(instruction)!=STypeInstructions.end();
}

bool isValidBTypeInstruction(const std::string &instruction) {
  return BTypeInstructions.find(instruction)!=BTypeInstructions.end();
}

bool isValidUTypeInstruction(const std::string &instruction) {
  return UTypeInstructions.find(instruction)!=UTypeInstructions.end();
}

bool isValidJTypeInstruction(const std::string &instruction) {
  return JTypeInstructions.find(instruction)!=JTypeInstructions.end();
}

bool isValidPseudoInstruction(const std::string &instruction) {
  return PseudoInstructions.find(instruction)!=PseudoInstructions.end();
}

bool isValidBaseExtensionInstruction(const std::string &instruction) {
  return BaseExtensionInstructions.find(instruction)!=BaseExtensionInstructions.end();
}

bool isValidMExtensionInstruction(const std::string &instruction) {
  return MExtensionInstructions.find(instruction)!=MExtensionInstructions.end();
}

bool isValidCSRRTypeInstruction(const std::string &instruction) {
  return CSRRInstructions.find(instruction)!=CSRRInstructions.end();
}

bool isValidCSRITypeInstruction(const std::string &instruction) {
  return CSRIInstructions.find(instruction)!=CSRIInstructions.end();
}

bool isValidCSRInstruction(const std::string &instruction) {
  return (CSRRInstructions.find(instruction)!=CSRRInstructions.end()) ||
      (CSRIInstructions.find(instruction)!=CSRIInstructions.end());
}

bool isValidFDRTypeInstruction(const std::string &instruction) {
  return (FDExtensionRTypeInstructions.find(instruction)!=FDExtensionRTypeInstructions.end());
}

bool isValidFDR1TypeInstruction(const std::string &instruction) {
  return (FDExtensionR1TypeInstructions.find(instruction)!=FDExtensionR1TypeInstructions.end());
}

bool isValidFDR2TypeInstruction(const std::string &instruction) {
  return (FDExtensionR2TypeInstructions.find(instruction)!=FDExtensionR2TypeInstructions.end());
}

bool isValidFDR3TypeInstruction(const std::string &instruction) {
  return (FDExtensionR3TypeInstructions.find(instruction)!=FDExtensionR3TypeInstructions.end());
}

bool isValidFDR4TypeInstruction(const std::string &instruction) {
  return (FDExtensionR4TypeInstructions.find(instruction)!=FDExtensionR4TypeInstructions.end());
}

bool isValidFDITypeInstruction(const std::string &instruction) {
  return (FDExtensionITypeInstructions.find(instruction)!=FDExtensionITypeInstructions.end());
}

bool isValidFDSTypeInstruction(const std::string &instruction) {
  return (FDExtensionSTypeInstructions.find(instruction)!=FDExtensionSTypeInstructions.end());
}

bool isFInstruction(const uint32_t &instruction) {
  uint8_t opcode = (instruction & 0b1111111);
  uint8_t funct3 = (instruction >> 12) & 0b111;
  uint8_t funct7 = (instruction >> 25) & 0b1111111;

  switch (opcode) {
    case 0b0000111: // flw
    case 0b0100111: {// fsw
      if (funct3==0b010) {
        return true; // flw
      }
      break;
    }
    case 0b1010011: {
      if (!(funct7 & 0b1)) {
        if (funct7==0b0100000) {
          return false; // fcvt.s.d
        }
        return true;
      }
    }
    default: break;
  }

  return false;
}

bool isBFloat16Instruction(const uint32_t &instruction) {
  uint8_t opcode = (instruction & 0b1111111);
  uint8_t funct7 = (instruction >> 25) & 0b1111111;

  switch (opcode) {
    case 0b1010011: { 
      switch (funct7) {
        case 0b0000010: // kfadd_bf16
        case 0b0000110: // kfsub_bf16
        case 0b0001010: // kfmul_bf16
        case 0b0001110: // kfdiv_bf16
          return true; 
        default:
          return false; 
      }
    }
    default:
      break;
  }

  return false;
}

bool isDInstruction(const uint32_t &instruction) {
  uint8_t opcode = (instruction & 0b1111111);
  uint8_t funct3 = (instruction >> 12) & 0b111;
  uint8_t funct7 = (instruction >> 25) & 0b1111111;
  

  switch (opcode) {
    case 0b0000111: // fld
    case 0b0100111: {// fsd
      if (funct3==0b011) {
        return true; // fld
      }
      break;
    }
    case 0b1010011: {
      if (funct7 & 0b1) {
        return true;
      } else if (funct7==0b0100000) {
        return true; // fcvt.s.d
      }
    }
    default: break;
  }
  return false;
}

std::string getExpectedSyntaxes(const std::string &opcode) {
  static const std::unordered_map<std::string, std::string> opcodeSyntaxMap = {
      {"nop", "nop"},
      {"li", "li <reg>, <imm>"},
      {"mv", "mv <reg>, <reg>"},
      {"not", "not <reg>, <reg>"},
      {"neg", "neg <reg>, <reg>"},
      {"seqz", "seqz <reg>, <reg>"},
      {"snez", "snez <reg>, <reg>"},
      {"sltz", "sltz <reg>, <reg>"},
      {"sgtz", "sgtz <reg>, <reg>"},
      {"beqz", "beqz <reg>, <text label>"},
      {"bnez", "bnez <reg>, <text label>"},
      {"blez", "blez <reg>, <text label>"},
      {"bgez", "bgez <reg>, <text label>"},
      {"bltz", "bltz <reg>, <text label>"},
      {"bgtz", "bgtz <reg>, <text label>"},
      {"j", "j <text label>"},
      {"jr", "jr <reg>"},
      {"la", "la <reg>, <text label>"},
      {"call", "call <text label>"},
      {"tail", "tail <text label>"},
      {"fence", "fence"}
  };

  auto opcodeIt = opcodeSyntaxMap.find(opcode);
  if (opcodeIt!=opcodeSyntaxMap.end()) {
    return opcodeIt->second;
  }

  static const std::unordered_map<SyntaxType, std::string> syntaxTypeToString = {
      {SyntaxType::O, "<empty>"},
      {SyntaxType::O_GPR_C_GPR_C_GPR, "<gp-reg>, <gp-reg>, <gp-reg>"},
      {SyntaxType::O_GPR_C_GPR_C_I, "<gp-reg>, <gp-reg>, <imm>"},
      {SyntaxType::O_GPR_C_GPR_C_IL, "<gp-reg>, <gp-reg>, <text-label>"},
      {SyntaxType::O_GPR_C_GPR_C_DL, "<gp-reg>, <gp-reg>, <data-label>"},
      {SyntaxType::O_GPR_C_I_LP_GPR_RP, "<gp-reg>, <gp-imm>(<gp-reg>)"},
      {SyntaxType::O_GPR_C_I, "<gp-reg>, <imm>"},
      {SyntaxType::O_GPR_C_IL, "<gp-reg>, <text-label>"},
      {SyntaxType::O_GPR_C_DL, "<gp-reg>, <data-label>"},
      {SyntaxType::O_GPR_C_CSR_C_GPR, "<gp-reg>, <csr>, <gp-reg>"},
      {SyntaxType::O_GPR_C_CSR_C_I, "<gp-reg>, <csr>, <uimm>"},
      {SyntaxType::O_FPR_C_FPR_C_FPR_C_FPR, "<fp-reg>, <fp-reg>, <fp-reg>, <fp-reg>"},
      {SyntaxType::O_FPR_C_FPR_C_FPR_C_FPR_C_RM, "<fp-reg>, <fp-reg>, <fp-reg>, <fp-reg>, <rm>"},
      {SyntaxType::O_FPR_C_FPR_C_FPR, "<fp-reg>, <fp-reg>, <fp-reg>"},
      {SyntaxType::O_FPR_C_FPR_C_FPR_C_RM, "<fp-reg>, <fp-reg>, <fp-reg>, <rm>"},
      {SyntaxType::O_FPR_C_FPR, "<fp-reg>, <fp-reg>"},
      {SyntaxType::O_FPR_C_FPR_C_RM, "<fp-reg>, <fp-reg>, <rm>"},
      {SyntaxType::O_FPR_C_GPR, "<fp-reg>, <gp-reg>"},
      {SyntaxType::O_FPR_C_GPR_C_RM, "<fp-reg>, <gp-reg>, <rm>"},
      {SyntaxType::O_GPR_C_FPR, "<gp-reg>, <fp-reg>"},
      {SyntaxType::O_GPR_C_FPR_C_RM, "<gp-reg>, <fp-reg>, <rm>"},
      {SyntaxType::O_GPR_C_FPR_C_FPR, "<gp-reg>, <fp-reg>, <fp-reg>"},
      {SyntaxType::O_FPR_C_I_LP_GPR_RP, "<fp-reg>, <imm>(<gp-reg>)"},
  };

  std::string syntaxes;
  const auto &syntaxList = instruction_syntax_map[opcode];
  for (size_t i = 0; i < syntaxList.size(); ++i) {
    if (i > 0) {
      syntaxes += " or ";
    }
    auto syntaxIt = syntaxTypeToString.find(syntaxList[i]);
    if (syntaxIt!=syntaxTypeToString.end()) {
      syntaxes += opcode + " " + syntaxIt->second;
    }
  }

  return syntaxes;
}

} // namespace instruction_set
