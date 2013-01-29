#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "otp.h"

uint8_t*
otp_crack(char *plaintext, uint8_t *encryption)
{
    int     i, length;
    uint8_t *key;

    length = strlen(plaintext);

    key = (uint8_t*)calloc(length, sizeof(uint8_t));

    for (i = 0; i < length; i++) {
        key[i] = plaintext[i] ^ encryption[i];
    }

    return key;
}

int
main(int argc, char *argv[])
{
    int     option,
            length;

    char    *key_string = NULL,
            *plaintext  = NULL,
            *ciphertext = NULL;

    uint8_t *key        = NULL,
            *encryption = NULL;

    while ((option = getopt(argc, argv, "c:p:")) != -1) {
        switch (option) {
            case 'c':
                ciphertext = optarg;
                break;
            case 'p':
                plaintext = optarg;
                break;
        }
    }

    assert( ciphertext && plaintext );

    length = strlen(plaintext);

    assert( (strlen(ciphertext) / 2) == length );

    encryption = hex_to_bytes(ciphertext);
    key        = otp_crack(plaintext, encryption);
    key_string = bytes_to_hex(key, length);

    printf("%s\n", key_string);

    free(key);
    free(key_string);
    free(encryption);

    return 0;
}
