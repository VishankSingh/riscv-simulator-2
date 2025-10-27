#pragma once
#include <cstdint>
#include <cstring>
#include <limits>

float bfloat16_to_float(uint16_t bf16);
uint16_t float_to_bfloat16(float f);
