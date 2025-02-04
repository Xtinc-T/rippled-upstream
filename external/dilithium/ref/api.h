#ifndef API_H
#define API_H

#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

#define pqcrystals_dilithium2_PUBLICKEYBYTES 1312
#define pqcrystals_dilithium2_SECRETKEYBYTES 2528
#define pqcrystals_dilithium2_BYTES 2420

#define pqcrystals_dilithium2_ref_PUBLICKEYBYTES pqcrystals_dilithium2_PUBLICKEYBYTES
#define pqcrystals_dilithium2_ref_SECRETKEYBYTES pqcrystals_dilithium2_SECRETKEYBYTES
#define pqcrystals_dilithium2_ref_BYTES pqcrystals_dilithium2_BYTES

int pqcrystals_dilithium2_ref_keypair(uint8_t *pk, uint8_t *sk);

int pqcrystals_dilithium2_ref_signature(uint8_t *sig, size_t *siglen,
                                        const uint8_t *m, size_t mlen,
                                        const uint8_t *sk);

int pqcrystals_dilithium2_ref(uint8_t *sm, size_t *smlen,
                              const uint8_t *m, size_t mlen,
                              const uint8_t *sk);

int pqcrystals_dilithium2_ref_verify(const uint8_t *sig, size_t siglen,
                                     const uint8_t *m, size_t mlen,
                                     const uint8_t *pk);

int pqcrystals_dilithium2_ref_open(uint8_t *m, size_t *mlen,
                                   const uint8_t *sm, size_t smlen,
                                   const uint8_t *pk);

// New function prototype for generating key pair from seed
int pqcrystals_dilithium2_ref_keypair_seed(uint8_t *pk, uint8_t *sk, const uint8_t *seed);

#define crypto_sign_keypair pqcrystals_dilithium2_ref_keypair
#define crypto_sign_signature pqcrystals_dilithium2_ref_signature
#define crypto_sign_verify pqcrystals_dilithium2_ref_verify
#define crypto_sign_publickey pqcrystals_dilithium2_ref_publickey
#define crypto_keypair_seed pqcrystals_dilithium2_ref_keypair_seed


#define pqcrystals_dilithium2aes_ref_PUBLICKEYBYTES pqcrystals_dilithium2_ref_PUBLICKEYBYTES
#define pqcrystals_dilithium2aes_ref_SECRETKEYBYTES pqcrystals_dilithium2_ref_SECRETKEYBYTES
#define pqcrystals_dilithium2aes_ref_BYTES pqcrystals_dilithium2_ref_BYTES

int pqcrystals_dilithium2aes_ref_keypair(uint8_t *pk, uint8_t *sk);

int pqcrystals_dilithium2aes_ref_signature(uint8_t *sig, size_t *siglen,
                                           const uint8_t *m, size_t mlen,
                                           const uint8_t *sk);

int pqcrystals_dilithium2aes_ref(uint8_t *sm, size_t *smlen,
                                 const uint8_t *m, size_t mlen,
                                 const uint8_t *sk);

int pqcrystals_dilithium2aes_ref_verify(const uint8_t *sig, size_t siglen,
                                        const uint8_t *m, size_t mlen,
                                        const uint8_t *pk);

int pqcrystals_dilithium2aes_ref_open(uint8_t *m, size_t *mlen,
                                      const uint8_t *sm, size_t smlen,
                                      const uint8_t *pk);
                            
int pqcrystals_dilithium2aes_ref_keypair_seed(uint8_t *pk, uint8_t *sk, const uint8_t *seed);

#define pqcrystals_dilithium3_PUBLICKEYBYTES 1952
#define pqcrystals_dilithium3_SECRETKEYBYTES 4000
#define pqcrystals_dilithium3_BYTES 3293

#define pqcrystals_dilithium3_ref_PUBLICKEYBYTES pqcrystals_dilithium3_PUBLICKEYBYTES
#define pqcrystals_dilithium3_ref_SECRETKEYBYTES pqcrystals_dilithium3_SECRETKEYBYTES
#define pqcrystals_dilithium3_ref_BYTES pqcrystals_dilithium3_BYTES

int pqcrystals_dilithium3_ref_keypair(uint8_t *pk, uint8_t *sk);

int pqcrystals_dilithium3_ref_signature(uint8_t *sig, size_t *siglen,
                                        const uint8_t *m, size_t mlen,
                                        const uint8_t *sk);

int pqcrystals_dilithium3_ref(uint8_t *sm, size_t *smlen,
                              const uint8_t *m, size_t mlen,
                              const uint8_t *sk);

int pqcrystals_dilithium3_ref_verify(const uint8_t *sig, size_t siglen,
                                     const uint8_t *m, size_t mlen,
                                     const uint8_t *pk);

int pqcrystals_dilithium3_ref_open(uint8_t *m, size_t *mlen,
                                   const uint8_t *sm, size_t smlen,
                                   const uint8_t *pk);

int pqcrystals_dilithium3_ref_keypair_seed(uint8_t *pk, uint8_t *sk, const uint8_t *seed);

#define pqcrystals_dilithium3aes_ref_PUBLICKEYBYTES pqcrystals_dilithium3_ref_PUBLICKEYBYTES
#define pqcrystals_dilithium3aes_ref_SECRETKEYBYTES pqcrystals_dilithium3_ref_SECRETKEYBYTES
#define pqcrystals_dilithium3aes_ref_BYTES pqcrystals_dilithium3_ref_BYTES


int pqcrystals_dilithium3aes_ref_keypair(uint8_t *pk, uint8_t *sk);

int pqcrystals_dilithium3aes_ref_signature(uint8_t *sig, size_t *siglen,
                                           const uint8_t *m, size_t mlen,
                                           const uint8_t *sk);

int pqcrystals_dilithium3aes_ref(uint8_t *sm, size_t *smlen,
                                 const uint8_t *m, size_t mlen,
                                 const uint8_t *sk);

int pqcrystals_dilithium3aes_ref_verify(const uint8_t *sig, size_t siglen,
                                        const uint8_t *m, size_t mlen,
                                        const uint8_t *pk);

int pqcrystals_dilithium3aes_ref_open(uint8_t *m, size_t *mlen,
                                      const uint8_t *sm, size_t smlen,
                                      const uint8_t *pk);

int pqcrystals_dilithium3aes_ref_keypair_seed(uint8_t *pk, uint8_t *sk, const uint8_t *seed);

#define pqcrystals_dilithium5_PUBLICKEYBYTES 2592
#define pqcrystals_dilithium5_SECRETKEYBYTES 4864
#define pqcrystals_dilithium5_BYTES 4595

#define pqcrystals_dilithium5_ref_PUBLICKEYBYTES pqcrystals_dilithium5_PUBLICKEYBYTES
#define pqcrystals_dilithium5_ref_SECRETKEYBYTES pqcrystals_dilithium5_SECRETKEYBYTES
#define pqcrystals_dilithium5_ref_BYTES pqcrystals_dilithium5_BYTES

int pqcrystals_dilithium5_ref_keypair(uint8_t *pk, uint8_t *sk);

int pqcrystals_dilithium5_ref_signature(uint8_t *sig, size_t *siglen,
                                        const uint8_t *m, size_t mlen,
                                        const uint8_t *sk);

int pqcrystals_dilithium5_ref(uint8_t *sm, size_t *smlen,
                              const uint8_t *m, size_t mlen,
                              const uint8_t *sk);

int pqcrystals_dilithium5_ref_verify(const uint8_t *sig, size_t siglen,
                                     const uint8_t *m, size_t mlen,
                                     const uint8_t *pk);

int pqcrystals_dilithium5_ref_open(uint8_t *m, size_t *mlen,
                                   const uint8_t *sm, size_t smlen,
                                   const uint8_t *pk);

int pqcrystals_dilithium5_ref_keypair_seed(uint8_t *pk, uint8_t *sk, const uint8_t *seed);

#define pqcrystals_dilithium5aes_ref_PUBLICKEYBYTES pqcrystals_dilithium5_ref_PUBLICKEYBYTES
#define pqcrystals_dilithium5aes_ref_SECRETKEYBYTES pqcrystals_dilithium5_ref_SECRETKEYBYTES
#define pqcrystals_dilithium5aes_ref_BYTES pqcrystals_dilithium5_ref_BYTES

int pqcrystals_dilithium5aes_ref_keypair(uint8_t *pk, uint8_t *sk);

int pqcrystals_dilithium5aes_ref_signature(uint8_t *sig, size_t *siglen,
                                           const uint8_t *m, size_t mlen,
                                           const uint8_t *sk);

int pqcrystals_dilithium5aes_ref(uint8_t *sm, size_t *smlen,
                                 const uint8_t *m, size_t mlen,
                                 const uint8_t *sk);

int pqcrystals_dilithium5aes_ref_verify(const uint8_t *sig, size_t siglen,
                                        const uint8_t *m, size_t mlen,
                                        const uint8_t *pk);

int pqcrystals_dilithium5aes_ref_open(uint8_t *m, size_t *mlen,
                                      const uint8_t *sm, size_t smlen,
                                      const uint8_t *pk);

int pqcrystals_dilithium5aes_ref_keypair_seed(uint8_t *pk, uint8_t *sk, const uint8_t *seed);


#ifdef __cplusplus
}
#endif

#endif
