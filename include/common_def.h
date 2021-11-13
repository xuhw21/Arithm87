#pragma once

#ifndef COMMON_DEF__
#define COMMON_DEF__

/* size of arithmetic coding values. */
#define CODE_VALUE_BITS 16    // number of bits in a code value
typedef unsigned int CODEVALUE;       // type of an arithmetic code value 

#define TOP_VALUE (((long)1 << CODE_VALUE_BITS) - 1)    // largest code value 65535

/* half and quarter points in the code value range. */
#define FIRST_QTR ((TOP_VALUE >> 2) +1) // point after first quarter 16384
#define HALF      (2 * FIRST_QTR)       // point after first half    32768
#define THIRD_QTR (3 * FIRST_QTR)       // point after third quater  49152

#endif
