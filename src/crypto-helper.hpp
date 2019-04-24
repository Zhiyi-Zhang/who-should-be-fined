#ifndef CRYPTO_HELPER_H
#define CRYPTO_HELPER_H

#include <iostream>
#include <fstream>
#include <list>
#include <utility>

uint64_t
readRandInt64();

void
generateRandomBytes(uint8_t* output, unsigned int size);

// will allocate output_value via new. Pls do delete[] output_value after calling this func
int
aes128_cbc_encrypt(const uint8_t* input_value, uint32_t input_size,
                   uint8_t** output_value, uint32_t& output_size,
                   const uint8_t* aes_iv, const uint8_t* aes_key);

// will allocate output_value via new. Pls do delete[] output_value after calling this func
int
aes128_cbc_decrypt(const uint8_t* input_value, uint8_t input_size,
                   uint8_t** output_value, uint32_t& output_size, const uint8_t* aes_key);

void
aes128_cbc_encrypt_file(const std::string& fileName, const std::string& outputFileName, const uint8_t* iv, const uint8_t* aesKey);

void
aes128_cbc_decrypt_file(const std::string& fileName, const std::string& outputFileName, const uint8_t* aesKey);

#endif // CRYPTO_HELPER_H
