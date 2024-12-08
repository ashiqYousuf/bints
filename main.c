#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BITS 1024
#define WORD_SIZE 32 // Using uint32_t as base unit
#define NUM_BLOCKS (MAX_BITS / WORD_SIZE)


typedef struct {
    uint32_t blocks[NUM_BLOCKS];
    size_t num_bits;
    const char* hex;
} bint;


void initBigInt(bint* num, const char* hex) {
    memset(num->blocks, 0, sizeof(num->blocks));
    num->num_bits = 0;
    num->hex = hex;
}

uint32_t get_value(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    } else {
        exit(1); // exit program
    }
}

void parseBigIntFromHex(bint* num, const char* hex) {
    initBigInt(num, hex);

    size_t len = strlen(hex);
    size_t wordIndex = 0;
    size_t bitPos = 0;

    for (int i = len - 1; i >= 0; --i) {
        char c = hex[i];
        uint32_t value = get_value(c);

        num->blocks[wordIndex] <<= 4;
        (num->blocks[wordIndex]) |= value;
        bitPos += 4; // Each hex digit is 4 bits
        if (bitPos >= WORD_SIZE) {
            bitPos = 0;
            wordIndex++;
            if (wordIndex >= NUM_BLOCKS) {
                printf("Hex string exceeds maximum supported size.\n");
                return;
            }
        }
    }
    num->num_bits = len * 4; // Each hex digit contributes 4 bits
}

void printBigInt(const bint* num) {
    for (size_t i = 0; i < NUM_BLOCKS; ++i) {
        printf("[%08X] ", num->blocks[i]);
    }
    printf("\n");
    printf("hex: %s\n", num->hex);
}

int main() {
    bint num;
    parseBigIntFromHex(&num, "1A110000BC");
    printBigInt(&num);
    return 0;
}
