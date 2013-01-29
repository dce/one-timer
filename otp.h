#ifndef OTP_H
#define OTP_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int
hctoi(char c)
{
    int i;

    switch (c) {
        case '0': i = 0;  break;
        case '1': i = 1;  break;
        case '2': i = 2;  break;
        case '3': i = 3;  break;
        case '4': i = 4;  break;
        case '5': i = 5;  break;
        case '6': i = 6;  break;
        case '7': i = 7;  break;
        case '8': i = 8;  break;
        case '9': i = 9;  break;
        case 'a': i = 10; break;
        case 'b': i = 11; break;
        case 'c': i = 12; break;
        case 'd': i = 13; break;
        case 'e': i = 14; break;
        case 'f': i = 15; break;
        default:
            printf("Invalid hex char.\n");
            exit(1);
    }

    return i;
}

char
itohc(int i) {
    char c;

    switch (i) {
        case 0:  c = '0'; break;
        case 1:  c = '1'; break;
        case 2:  c = '2'; break;
        case 3:  c = '3'; break;
        case 4:  c = '4'; break;
        case 5:  c = '5'; break;
        case 6:  c = '6'; break;
        case 7:  c = '7'; break;
        case 8:  c = '8'; break;
        case 9:  c = '9'; break;
        case 10: c = 'a'; break;
        case 11: c = 'b'; break;
        case 12: c = 'c'; break;
        case 13: c = 'd'; break;
        case 14: c = 'e'; break;
        case 15: c = 'f'; break;
        default:
            printf("Invalid hex int.\n");
            exit(1);
    }

    return c;
}

uint8_t*
hex_to_bytes(char *hex_string)
{
    int     i, c1, c2, hex_length;
    uint8_t *bytes;

    hex_length  = strlen(hex_string);
    bytes       = (uint8_t*)calloc(hex_length / 2, sizeof(uint8_t));

    for (i = 0; i < hex_length / 2; i++) {
        c1 = hctoi(hex_string[2 * i]);
        c2 = hctoi(hex_string[2 * i + 1]);
        bytes[i] = (c1 << 4) + c2;
    }

    return bytes;
}

char*
bytes_to_hex(uint8_t *bytes, int length)
{
    int  i;
    char *hex_string;

    hex_string = (char*)calloc(length * 2 + 1, sizeof(char));

    for (i = 0; i < length; i++) {
        hex_string[2 * i]     = itohc(bytes[i] >> 4);
        hex_string[2 * i + 1] = itohc(bytes[i] % 16);
    }

    hex_string[length * 2] = '\0';

    return hex_string;
}

#endif
