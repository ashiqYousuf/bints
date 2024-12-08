#ifndef BINT_H
#define BINT_H

#include <stdint.h>

#define MAX_BITS 1024
#define WORD_SIZE 32 // Using uint32_t as base unit
#define NUM_BLOCKS (MAX_BITS / WORD_SIZE)

// BigInt structure
typedef struct {
    uint32_t blocks[NUM_BLOCKS]; // Array of 32-bit blocks
} bint;

// Function prototypes
void initBigInt(bint* num);
void parseBigIntFromHex(bint* num, const char* hex);
void getHexFromBInt(bint *num);
void addBigInt(const bint* a, const bint* b, bint* result);
void multiplyBigInt(const bint* a, const bint* b, bint* result);
void printBigInt(const bint* num);

#endif // BINT_H
