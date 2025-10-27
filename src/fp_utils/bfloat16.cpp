#include "fp_utils/bfloat16.h"
#include <cstring>
#include <cstdint>

using namespace std;

float bfloat16_to_float(uint16_t bf16) {
    uint32_t bits = ((uint32_t)bf16) << 16;
    float f;
    std::memcpy(&f, &bits, sizeof(float));
    return f;
}


uint16_t float_to_bfloat16(float f) {
    uint32_t bits;
    std::memcpy(&bits, &f, sizeof(bits));
    
    // Note: This is truncation, not rounding.
    // For rounding-to-nearest-even, more complex logic would be needed:
    // uint32_t lsb = (bits >> 16) & 1;
    // uint32_t rounding_bias = 0x7FFF + lsb;
    // bits += rounding_bias;
    
    uint16_t bf16 = static_cast<uint16_t>(bits >> 16);
    return bf16;
}
