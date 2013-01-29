#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "otp.h"

uint8_t*
otp_encrypt(char *plaintext, uint8_t *key)
{
    int     i, length;
    uint8_t *ciphertext;

    length = strlen(plaintext);

    ciphertext = (uint8_t*)calloc(length, sizeof(uint8_t));

    for (i = 0; i < length; i++) {
        ciphertext[i] = plaintext[i] ^ key[i];
    }

    return ciphertext;
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

    while ((option = getopt(argc, argv, "k:p:")) != -1) {
        switch (option) {
            case 'k':
                key_string = optarg;
                break;
            case 'p':
                plaintext = optarg;
                break;
        }
    }

    assert( key_string && plaintext );

    length = strlen(plaintext);

    assert( (strlen(key_string) / 2) >= length );

    key        = hex_to_bytes(key_string);
    encryption = otp_encrypt(plaintext, key);
    ciphertext = bytes_to_hex(encryption, length);

    printf("%s\n", ciphertext);

    free(key);
    free(encryption);
    free(ciphertext);

    return 0;
}
