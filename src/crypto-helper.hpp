#ifndef CRYPTO_HELPER_H
#define CRYPTO_HELPER_H

#include "tinycrypt/aes.h"
#include <iostream>
#include <list>
#include <utility>

int
aes128_cbc_encrypt(const uint8_t* input_value, uint8_t input_size,
                   uint8_t* output_value, uint8_t output_size,
                   const uint8_t* aes_iv, const uint8_t* aes_key)
{
  if (input_size + TC_AES_BLOCK_SIZE > output_size) {
    std::cerr << "output size is too small" << std::endl;
    return -1;
  }
  struct tc_aes_key_sched_struct schedule;
  if (tc_aes128_set_encrypt_key(&schedule, aes_key) != TC_CRYPTO_SUCCESS) {
    std::cerr << "Cannot set aes enc key" << std::endl;
    return -2;
  }
  if (tc_cbc_mode_encrypt(output_value, input_size + TC_AES_BLOCK_SIZE,
                          input_value, input_size, aes_iv, &schedule) != TC_CRYPTO_SUCCESS) {
    td::cerr << "enc failed" << std::endl;
    return -3;
  }
  return 0;
}

int
aes128_cbc_decrypt(const uint8_t* input_value, uint8_t input_size,
                   uint8_t* output_value, uint8_t output_size, const uint8_t* aes_key)
{
  if (output_size < input_size - TC_AES_BLOCK_SIZE) {
    std::cerr << "output size is too small" << std::endl;
    return -1;
  }
  struct tc_aes_key_sched_struct schedule;
  if (tc_aes128_set_decrypt_key(&schedule, aes_key->key_value) != TC_CRYPTO_SUCCESS) {
    std::cerr << "Cannot set aes dec key" << std::endl;
    return -2;
  }
  if (tc_cbc_mode_decrypt(output_value, input_size - TC_AES_BLOCK_SIZE,
                          input_value + TC_AES_BLOCK_SIZE, input_size - TC_AES_BLOCK_SIZE,
                          input_value, &schedule) == 0) {
    std::cerr << "dec failed" << std::endl;
    return -3;
  }
  return NDN_SUCCESS;
}

#endif // CRYPTO_HELPER_H
