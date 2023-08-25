#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint16_t calculateParity(uint8_t data) {
        // Move data bits to correct position
        uint16_t encodedData = 0;
        encodedData |= (data & 0b00000001) << 2; 
        encodedData |= (data & 0b00001110) << 3; 
        encodedData |= (data & 0b11110000) << 4;

        // Calculate parity bits
        int sum1 = 0;
        int sum2 = 0;
        int sum4 = 0;
        int sum8 = 0;
        for (int i = 1; i <= 12; i++) {
                if ((i & 1U) == 1U) {
                        sum1 ^= (encodedData & (1U << (i - 1))) >> (i - 1);
                }

                if ((i & 2U) == 2U) {
                        sum2 ^= (encodedData & (1U << (i - 1))) >> (i - 1);
                }

                if ((i & 4U) == 4U) {
                        sum4 ^= (encodedData & (1U << (i - 1))) >> (i - 1);
                }

                if ((i & 8U) == 8U) {
                        sum8 ^= (encodedData & (1U << (i - 1))) >> (i - 1);
                }
        }

        encodedData |= sum1;
        encodedData |= sum2 << 1;
        encodedData |= sum4 << 3;
        encodedData |= sum8 << 7;

        return encodedData;
}

uint8_t checkParity(uint16_t encodedData) {
        int sum1 = 0;
        int sum2 = 0;
        int sum4 = 0;
        int sum8 = 0;
        for (int i = 1; i <= 12; i++) {
                if ((i & 1U) == 1U) {
                        sum1 ^= (encodedData & (1U << (i - 1))) >> (i - 1);
                }

                if ((i & 2U) == 2U) {
                        sum2 ^= (encodedData & (1U << (i - 1))) >> (i - 1);
                }

                if ((i & 4U) == 4U) {
                        sum4 ^= (encodedData & (1U << (i - 1))) >> (i - 1);
                }

                if ((i & 8U) == 8U) {
                        sum8 ^= (encodedData & (1U << (i - 1))) >> (i - 1);
                }
        }

        uint8_t errorCode = 0;
        errorCode |= sum1;
        errorCode |= sum2 << 1;
        errorCode |= sum4 << 2;
        errorCode |= sum8 << 3;

	return errorCode;
}

int main() {
        uint8_t data = 0b01011001;
        uint16_t encodedData = 0;

        encodedData = calculateParity(data);

        for (int i = 11; i >= 0; i--) {
                printf("%d", (encodedData & (1U << i)) >> i);
        }
        printf("\n");

        if (checkParity(encodedData) == 0) {
                printf("No error\n");
        }
        else {
		printf("Error detected\n");
                printf("Error Code : %d\n", checkParity(encodedData));
	}

        uint16_t exampleData = 0b010101101110; // 6th bit is flipped

        if (checkParity(exampleData) == 0) {
                printf("No error\n");
        }
        else {
                printf("Error detected\n");
                printf("Error Code : %d\n", checkParity(exampleData)); // Will print 6
        }

        return 0;
}

