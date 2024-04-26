#include <stdio.h>

typedef struct {
    unsigned char character;
    unsigned int length;
    unsigned int encoding;
} Entry;

void printInputToBinary(unsigned int input, unsigned int lengthToPrint) {
    unsigned int mask = 1;
    mask <<= (lengthToPrint - 1);

    for (int i = 0; i < lengthToPrint; i++) {
        printf("%d", (input & mask) ? 1 : 0);
        mask >>= 1;
    }
}

int main() {
    unsigned int numberOfEntries;
    scanf("%x", &numberOfEntries);
    if (numberOfEntries == 0) numberOfEntries = 256;

    Entry table[numberOfEntries];
    for (int i = 0; i < numberOfEntries; i++) {
        unsigned int character;
        unsigned int length;
        unsigned int encoding;

        scanf("%x %x %x", &character, &length, &encoding);

        table[i].character = character;

        unsigned int lengthInDecimal = length >> 4;
        table[i].length = lengthInDecimal;

        unsigned int encodingPartOfLength = (length & 0x0F) << 8;
        unsigned int encodingFromLengthAndEncoding = ((encodingPartOfLength | encoding)) >> (12 - table[i].length);
        table[i].encoding = encodingFromLengthAndEncoding;
    }

    unsigned int temp;
    unsigned int noOfCompressedChar;

    for (int i = 0; i < 4; ++i) {
        scanf("%x", &temp);
        noOfCompressedChar = (noOfCompressedChar << 8) | temp;
    }

    if (noOfCompressedChar == 0x00) {
        for (int i = 0; i < numberOfEntries; ++i) {
            printf("0x%2.2x : %d ", table[i].character, table[i].length);

            printInputToBinary(table[i].encoding, table[i].length);
            printf("\n");
        }
        //Start of Problem 2
    } else {
        unsigned int D = 0;
        unsigned int byte;
        unsigned int bit = 0;
        unsigned int bitLength = 0;

        for (int i = 0; i < noOfCompressedChar;) {
            scanf("%x", &byte);

            for (int j = 7; j >= 0 && i < noOfCompressedChar; --j) {
                //extract bit from byte
                bit = (byte >> j) & 1;

                //add bit to D and increase bit length
                D = (D << 1) | bit;
                bitLength++;

                for (int k = 0; k < numberOfEntries; ++k) {
                    if (table[k].encoding == D && table[k].length == bitLength) {
                        printf("%c", table[k].character);
                        D = 0;
                        bitLength = 0;
                        i++;
                    }
                }
            }
        }
    }
    return 0;
}