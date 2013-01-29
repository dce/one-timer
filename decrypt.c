#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "otp.h"

char*
otp_decrypt(uint8_t *ciphertext, uint8_t *key, int length)
{
    int  i;
    char *plaintext;

    plaintext = (char*)calloc(length + 1, sizeof(char));

    for (i = 0; i < length; i++) {
        plaintext[i] = ciphertext[i] ^ key[i];
    }

    plaintext[length] = '\0';

    return plaintext;
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

    while ((option = getopt(argc, argv, "k:c:")) != -1) {
        switch (option) {
            case 'k':
                key_string = optarg;
                break;
            case 'c':
                ciphertext = optarg;
                break;
        }
    }

    assert( key_string && ciphertext );

    length = strlen(ciphertext);

    assert( strlen(key_string) >= length );

    key        = hex_to_bytes(key_string);
    encryption = hex_to_bytes(ciphertext);
    plaintext  = otp_decrypt(encryption, key, length / 2);

    printf("%s\n", plaintext);

    free(plaintext);
    free(key);
    free(encryption);

    return 0;
}
