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
} bint;

void initBigInt(bint* num, const char* hex) {
    memset(num->blocks, 0, sizeof(num->blocks));
    num->num_bits = 0;
}

void printBigInt(const bint* num) {
    for (size_t i = 0; i < NUM_BLOCKS; ++i) {
        printf("[%08X] ", num->blocks[i]);
    }
    printf("\n");
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
        printf("Invalid hex string\n");
        exit(1); // exit program
    }
}


char* getHexFromBInt(bint *num) {
    size_t size = sizeof(char) * (MAX_BITS / 4 + 1);

    char* hex = malloc(size); // Max size of hex string = 256 (1024/4) because 256 * 4 = 1024
    memset(hex, '\0', size);

    int index = NUM_BLOCKS - 1;

    while (index && !(num->blocks[index])) index--;

    if (index < 0) {
        strcpy(hex, "0");
        return hex;
    }

    char *ptr = hex;

    while (index >= 0) {
        sprintf(ptr, "%08X", num->blocks[index--]);
        ptr += 8;
    }

    return hex;
}

void parseBigIntFromHex(bint* num, const char* hex) {
    initBigInt(num, hex);

    size_t len = strlen(hex);
    size_t wordIndex = 0;
    size_t bitPos = 0;

    for (int i = len-1; i >= 0; i--) {
        // 1A 110000BC FFFF0011 <=> [FFFF0011, 110000BC, 0000001A, ..., 00000000]
        char c = hex[i];
        uint32_t value = get_value(c);

        (num->blocks[wordIndex]) |= (value << bitPos);
        bitPos += 4; // Each hex digit is 4 bits

        if (bitPos >= WORD_SIZE) {
            bitPos = 0;
            wordIndex++;
            if (wordIndex >= NUM_BLOCKS) {
                printf("Hex string exceeds maximum supported size.\n");
                exit(1);
            }
        }
    }
    num->num_bits = len * 4; // Each hex digit contributes 4 bits
}

void addBigInt(const bint* a, const bint* b, bint* result) {
    uint64_t carry = 0; // Use 64 bits to handle overflow

    for (int i = 0; i < NUM_BLOCKS; i++) { // Start from least significant block
        uint64_t sum = (uint64_t)a->blocks[i] + (uint64_t)b->blocks[i] + carry;
        result->blocks[i] = (uint32_t)(sum & 0xFFFFFFFF); // Store lower 32 bits
        carry = sum >> 32; // Upper 32 bits becomes carry
    }

    if (carry != 0) {
        printf("Overflow in addition\n");
        exit(1);
    }

    result->num_bits = a->num_bits > b->num_bits ? a->num_bits : b->num_bits;
}


int main() {
    bint n1, n2, sum;
    char s1[100], s2[100];

    scanf("%s %s", s1, s2);
    parseBigIntFromHex(&n1, s1);
    parseBigIntFromHex(&n2, s2);
    printBigInt(&n1);
    printBigInt(&n2);

    addBigInt(&n1, &n2, &sum);
    printBigInt(&sum);
    printf("%s\n", getHexFromBInt(&sum));

    return 0;
}
