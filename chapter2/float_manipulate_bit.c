#include <stdio.h>
#include <stdbool.h>
#include <limits.h>


/**
   Bit-level floating-point coding rules
In the following problems, you will write code to implement floating-point func-
tions, operating directly on bit-level representations of floating-point numbers.
Your code should exactly replicate the conventions for IEEE floating-point oper-
ations, including using round-to-even mode when rounding is required.
Toward this end, we define data type float_bits to be equivalent to un-
signed:
 Access bit-level representation floating-point number
 typedef unsigned float_bits;

Rather than using data type float in your code, you will use float_bits.
You may use both int and unsigned data types, including unsigned and integer
constants and operations. You may not use any unions, structs, or arrays. Most
significantly, you may not use any floating-point data types, operations, or con-
stants. Instead, your code should perform the bit manipulations that implement
the specified floating-point operations.
 */

typedef unsigned float_bits;

static const int BIAS = 127;
int exp_mask = 0xff;

int fraction_len = 23;
int exp_len = 8;
int exp_fraction_len = 31;

unsigned extract_exp(float_bits f) {
    return (f >> fraction_len) & exp_mask;
}

int fraction_mask = 0x7fffff;


void test_float_twice();

unsigned extract_fraction(float_bits f) {
    return (f & fraction_mask);
}

unsigned extract_sign(float_bits f) {
    return f >> (exp_fraction_len);
}


bool is_nan(float_bits f) {
    unsigned exp = extract_exp(f);
    if (exp == 0xff && extract_fraction(f) != 0) {
        return true;
    }
    return false;
}

bool is_denormalized(float_bits f) {
    if (extract_exp(f) == 0
        && extract_fraction(f) != 0) {
        return true;
    }
    return false;
}

bool is_infinity(float_bits f) {
    if (extract_fraction(f) == 0
        && extract_exp(f) == exp_mask) {
        return true;
    }
    return false;
}

float_bits set_fraction(float_bits f, unsigned int fraction) {
    return (f & ~fraction_mask) | (fraction & fraction_mask);
}

float_bits set_exp(float_bits f, unsigned exp) {
    return (f & ~(exp_mask << fraction_len)) | ((exp & exp_mask) << fraction_len);
}

/*
 * 2.91 ◆◆
 * Compute -f. If f is NaN, then return f.
 */
float_bits float_negate(float_bits f) {
    if (is_nan(f)) {
        return f;
    }
    unsigned sign = extract_sign(f);
    return sign == 0 ? f | (1 << exp_fraction_len) : f | (0 << exp_fraction_len);
}

/*
 * 2.93 ◆◆◆
 * Compute 2*f. If f is NaN, then return f.
 */
float_bits float_twice(float_bits f) {
    if (is_nan(f) || is_infinity(f)) {
        return f;
    }
    if (is_denormalized(f)) {
        if (extract_fraction(f) & 0x400000) { // f * 2 will not be denormalized
            return set_fraction(set_exp(f, 1), extract_fraction(f) << 1);
        }
        return set_fraction(f, extract_fraction(f) << 1);
    }
    // normal
    return set_exp(f, extract_exp(f) << 1);
}

/*
 * 2.95 ◆◆◆◆
 * Compute (int) f.
 * If conversion causes overflow or f is NaN, return 0x80000000
 */
int float_f2i(float_bits f) {
    unsigned int OVERFLOW = 0x80000000;
    if (is_nan(f)) {
        return OVERFLOW;
    }
    unsigned sign = extract_sign(f);
    unsigned exp = extract_exp(f);
    unsigned fraction = extract_fraction(f);
    if (exp < BIAS) { // |f| < 1
        return 0;
    }
    unsigned real_exp = exp - BIAS;
    if (real_exp >= 31) { // overflow or INT_MIN
        return OVERFLOW;
    }
    unsigned real_fraction;
    if (real_exp > fraction_len) {
        real_fraction = fraction << (real_exp - fraction_len);
    } else {
        real_fraction = fraction >> (fraction - real_exp);
    }
    int r = 1 << real_exp | real_fraction;
    return sign == 0 ? r : -r;
}

/*
 * 2.96 ◆◆◆◆
 * Compute (float) i
 */
float_bits float_i2f(int i) {

}

void main() {
    test_float_twice();
}

void test_float_twice() {
    float_bits f[] = {0xffffffff, 0xff800000, 0x00000001, 0x00400000, 0x007fffff, 0x004fffff, 0x0080000f, 0x00800000};
    for (int i = 0; i < sizeof(f) / sizeof(f[0]); ++i) {
        printf("%x->%x\n", f[i], float_twice(f[i]));
    }
//    for (unsigned j = 0; j <= 0xffffffff; ++j) {
//        printf("%x->%x\n", j, float_twice(j));
//    }
}
