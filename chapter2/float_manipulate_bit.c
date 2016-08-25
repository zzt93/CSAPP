#include <stdio.h>

#define POS_INFINITY 1e400
#define NEG_INFINITY (-POS_INFINITY)
#define NEG_ZERO -0.0
#define NEG_ZERO (-1.0/POS_INFINITY)

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

/*
  2.91 ◆◆
Following the bit-level floating-point coding rules, implement the function with
the following prototype:
/* Compute -f. If f is NaN, then return f. */
float_bits float_negate(float_bits f) {
    unsigned exp = f >> 23 & 0xff;
    if (exp == 0xff) {
        return f;
    }
    unsigned sign = f >> 31;
    return sign == 0 ? f | (1 << 31) : f | (0 << 31);
}