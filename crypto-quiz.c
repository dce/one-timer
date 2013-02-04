#include "otp.h"

#define MESSAGE_LENGTH 83
#define THRESHOLD 5

int
main(int argc, char *argv[])
{
  int     i, j, k,
          space_counts[MESSAGE_LENGTH];

  uint8_t *ct[10],
          *key,
          *target,
          xor;
  
  key = calloc(MESSAGE_LENGTH, sizeof(uint8_t));

  ct[0]  = hex_to_bytes("315c4eeaa8b5f8aaf9174145bf43e1784b8fa00dc71d885a804e5ee9fa40b16349c146fb778cdf2d3aff021dfff5b403b510d0d0455468aeb98622b137dae857553ccd8883a7bc37520e06e515d22c954eba50");
  ct[1]  = hex_to_bytes("234c02ecbbfbafa3ed18510abd11fa724fcda2018a1a8342cf064bbde548b12b07df44ba7191d9606ef4081ffde5ad46a5069d9f7f543bedb9c861bf29c7e205132eda9382b0bc2c5c4b45f919cf3a9f1cb741");
  ct[2]  = hex_to_bytes("32510ba9a7b2bba9b8005d43a304b5714cc0bb0c8a34884dd91304b8ad40b62b07df44ba6e9d8a2368e51d04e0e7b207b70b9b8261112bacb6c866a232dfe257527dc29398f5f3251a0d47e503c66e935de812");
  ct[3]  = hex_to_bytes("32510ba9aab2a8a4fd06414fb517b5605cc0aa0dc91a8908c2064ba8ad5ea06a029056f47a8ad3306ef5021eafe1ac01a81197847a5c68a1b78769a37bc8f4575432c198ccb4ef63590256e305cd3a9544ee41");
  ct[4]  = hex_to_bytes("3f561ba9adb4b6ebec54424ba317b564418fac0dd35f8c08d31a1fe9e24fe56808c213f17c81d9607cee021dafe1e001b21ade877a5e68bea88d61b93ac5ee0d562e8e9582f5ef375f0a4ae20ed86e935de812");
  ct[5]  = hex_to_bytes("32510bfbacfbb9befd54415da243e1695ecabd58c519cd4bd2061bbde24eb76a19d84aba34d8de287be84d07e7e9a30ee714979c7e1123a8bd9822a33ecaf512472e8e8f8db3f9635c1949e640c621854eba0d");
  ct[6]  = hex_to_bytes("32510bfbacfbb9befd54415da243e1695ecabd58c519cd4bd90f1fa6ea5ba47b01c909ba7696cf606ef40c04afe1ac0aa8148dd066592ded9f8774b529c7ea125d298e8883f5e9305f4b44f915cb2bd05af513");
  ct[7]  = hex_to_bytes("315c4eeaa8b5f8bffd11155ea506b56041c6a00c8a08854dd21a4bbde54ce56801d943ba708b8a3574f40c00fff9e00fa1439fd0654327a3bfc860b92f89ee04132ecb9298f5fd2d5e4b45e40ecc3b9d59e941");
  ct[8]  = hex_to_bytes("271946f9bbb2aeadec111841a81abc300ecaa01bd8069d5cc91005e9fe4aad6e04d513e96d99de2569bc5e50eeeca709b50a8a987f4264edb6896fb537d0a716132ddc938fb0f836480e06ed0fcd6e9759f404");
  ct[9]  = hex_to_bytes("466d06ece998b7a2fb1d464fed2ced7641ddaa3cc31c9941cf110abbf409ed39598005b3399ccfafb61d0315fca0a314be138a9f32503bedac8067f03adbf3575c3b8edc9ba7f537530541ab0f9f3cd04ff50d");

  target = hex_to_bytes("32510ba9babebbbefd001547a810e67149caee11d945cd7fc81a05e9f85aac650e9052ba6a8cd8257bf14d13e6f0a803b54fde9e77472dbff89d71b57bddef121336cb85ccb8f3315f4b52e301d16e9f52f904");

  for (i = 0; i < 10; i++) {
    
    // zero out the space counts array
    for (j = 0; j < MESSAGE_LENGTH; j++) {
      space_counts[j] = 0;
    }

    // for each message not currently under inspection
    for (j = 0; j < 10; j++) {
      if (i != j) {
        for (k = 0; k < MESSAGE_LENGTH; k++) {
          xor = ct[i][k] ^ ct[j][k];

          // 'A' ^ ' ' == 'a' && 'a' ^ ' ' == 'A'
          // if the result of XORing the messages is a letter,
          // there's a good chance that corresponds to a space
          // in one of the original messages.
          
          if ((xor >= 'a' && xor <= 'z') || (xor >= 'A' && xor <= 'Z')) {
            space_counts[k]++;
          }
        }
      }
    }

    // if we saw a bunch of spaces for a certain byte
    // there's a good chance that's a space in the original
    // message. XOR the encrypted byte with ' ' (32) to
    // get that piece of the key.

    for (j = 0; j < MESSAGE_LENGTH; j++) {
      if (space_counts[j] > THRESHOLD) {
        key[j] = ct[i][j] ^ 32;
      }
    }
  }

  for (j = 0; j < MESSAGE_LENGTH; j++) {
    printf("%c", target[j] ^ key[j]);
  }

  printf("\n");

  return 0;
}
