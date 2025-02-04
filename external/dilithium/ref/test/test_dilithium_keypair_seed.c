#include <stdio.h>
#include <stdint.h>
#include <string.h>
// Include the header where the function is declared
#include "../sign.h"

#define SEEDBYTES 32  // Define the seed size, adjust as necessary
#define CRYPTO_PUBLICKEYBYTES 1312  // Example size, adjust according to your implementation
#define CRYPTO_SECRETKEYBYTES 2528  // Example size, adjust according to your implementation

void print_hex(const char* label, const uint8_t* data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main() {
    uint8_t seed[SEEDBYTES] = {0};  // Initialize a seed with zeros or any fixed value
    uint8_t pk[CRYPTO_PUBLICKEYBYTES];
    uint8_t sk[CRYPTO_SECRETKEYBYTES];

    // Fill the seed with a known pattern for testing
    for (int i = 0; i < SEEDBYTES; i++) {
        seed[i] = (uint8_t)i;
    }

    // Generate the key pair using the seed
    int result = crypto_keypair_seed(pk, sk, seed);

    if (result == 0) {
        printf("Key pair generated successfully.\n");
        print_hex("Public Key", pk, CRYPTO_PUBLICKEYBYTES);
        print_hex("Secret Key", sk, CRYPTO_SECRETKEYBYTES);
    } else {
        printf("Key pair generation failed.\n");
    }

    return 0;
}