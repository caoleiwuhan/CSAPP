/* 
 * CSE 410 HW1 (Data Lab)
 * 
 * Stefan Behr, sbehr
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to this homework by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. See warning 1.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
       return ~(~x|~y);
}
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  return ~(~x&~y);
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  int neg1;
  neg1 = !(~x); // if x == -1, neg1 == 1, else, neg1 == 0
  return !((~(x+1)^x)|neg1); // add 1, flip, xor, becomes 0 if Tmax (or if -1)
}
/*
 * isZero - returns 1 if x == 0, and 0 otherwise 
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x) {
  return !x;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  /* 
     // initial correct solution, then I realized it could be much simpler :)
     int mask, sign_mask;
     mask = ~(~0 << (n + ~0)); // (n-1)-bit wide mask 
     sign_mask = ((1 << 31) & x) >> (32 + ~n + 1); // get sign bit, shift right by 32-n bits
     return !(((x & mask) | sign_mask) ^ x); // get first n-1 bits of x, paste in leading "sign bits", compare to x
  */

  // A 32-bit 2's complement int can be represented as an n-bit (1<=n<=32) 2's
  // comp. int if the (32 - n) leading bits are all the same value as the nth bit.
  int shift = 33 + ~n; // == 32 + (~n + 1) == 32 - n
  return !(((x << shift) >> shift) ^ x); // copy nth bit into (32 - n) high order bits, compare result w/original
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  int mask, shift;
  mask = 255; // byte-wide mask of 1s
  shift = n << 3; // == n*2^3 == n*8; treat n as desired byte-shift of 8-bit mask; scale up to bit-shift
  x = x & (mask << shift); // shift mask, isolate desired byte
  return (x >> shift) & mask; // shift isolated byte to 0th byte, zero out leading sign bits from right-shift
}
/* 
 * isNegative - return 1 if x < 0, return 0 otherwise 
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x) {
  x = x >> 31; // x < 0: x -> all 1s == -1; x >= 0: x -> all 0s == 0
  x = x + 1;   // -1 -> 0; 0 -> 1
  return !x;      // 0 -> 1; 1 -> 0
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  return 2;
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  int diff, same, diff_sign, same_sign;
  same = !(x ^ y);
  diff = x + (~y + 1); // x - y
  same_sign = ((x ^ y) >> 31) + 1; // 1 if x, y both neg or both non-neg, 0 otherwise
  diff_sign = (diff >> 31) & 1; // sign of diff variable, to determine if diff < 0 or >= 0
  // ack, incomplete :(
  return diff & !same;
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
  int mask, shift;
  mask = 255; // byte-wide mask of 1s
  shift = n << 3; // == n*2^3 == n * 8
  mask = ~(mask << shift); // shift byte-wide mask, flip to get byte-wide mask of 0s
  c = c << shift; // shift bits of c into nth byte
  return (x & mask) | c; // apply mask to x, zeroing x's nth byte, replacing it with byte given by c 
}
/* 
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n) {
  int high_mask, low_mask; // n-bit-wide masks for high order, low order bits
  int save_bits; // high order bits to save and rotate onto beginning of x
  int mask_shift; // will hold 32-n, i.e., distance to shift left_mask
  mask_shift = 33 + ~n; // 32-n == 32+(-n) == 32+(~n+1)
  high_mask = ~0 << mask_shift; // used to save high order bits that wrap to front
  low_mask = ~(~0 << n); // n-bit-wide low order mask, for zapping potential leading 1s after right-shift
  save_bits = ((x & high_mask) >> mask_shift) & low_mask; // save n high-order bits, move them to right, zap leading 1s
  return (x << n) | save_bits; // shift n left, paste in wraparound bits on right
}
/* 
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4 
 */
int isNonZero(int x) {
  /*
  // Initial attempt, using idea of ORing all of x's individual bits to see
  // if a 1-bit exists (equivalent to logical negation of the result of ANDing all of the
  // bits of x's bitwise complement). Turned out to be too long, though correct (13 ops).
  int shift16, shift8, shift4, shift2, shift1;
  shift16 = 16;
  shift8 = 8;
  shift4 = 4;
  shift2 = 2;
  shift1 = 1;
  x = ~x;
  x = x & (x << shift16); // 16
  x = x & (x << shift8); // 8
  x = x & (x << shift4); // 4
  x = x & (x << shift2); // 2
  x = x & (x << shift1); // 1
  return (x >> 31) + 1;
  */
  
  int x_sign, negx_sign;
  x_sign = (x >> 31) & 1; // get x's sign bit
  negx_sign = ((~x + 1) >> 31) & 1; // negate x, get its sign bit
  // x's and -x's sign bits should be opposite, except when x == 0x0 or 0x8000000.
  // In the former exception, both sign bits are 0, and in the latter, both are 1, so
  // ORing them gives the appropriate return value.
  return x_sign | negx_sign;
}
