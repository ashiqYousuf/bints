#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "bint.h"

int main() {
    bint n1, n2, sum, mul;

    char s1[100], s2[100];

    scanf("%s %s", s1, s2);
    parseBigIntFromHex(&n1, s1);
    parseBigIntFromHex(&n2, s2);

    printBigInt(&n1);
    printBigInt(&n2);

    addBigInt(&n1, &n2, &sum);
    printBigInt(&sum);

    multiplyBigInt(&n1, &n2, &mul);
    printBigInt(&mul);
    getHexFromBInt(&mul);

    return 0;
}
