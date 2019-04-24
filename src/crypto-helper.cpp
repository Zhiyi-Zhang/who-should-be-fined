#include "crypto-helper.hpp"
#include "tinycrypt/tc_aes.h"
#include "tinycrypt/tc_cbc_mode.h"
#include "tinycrypt/tc_constants.h"
#include "isaac.hpp"

uint64_t
readRandInt64()
{
  uint64_t seedVal = 0;
  std::ifstream urandom("/dev/urandom", std::ios::in|std::ios::binary);
  if (urandom) {
    urandom.read(reinterpret_cast<char*>(&seedVal), sizeof(seedVal));
  }
  else {
    std::cerr << "Cannot read random value from /dev/urandom" << std::endl;
  }
  return seedVal;
}

void
generateRandomBytes(uint8_t* output, unsigned int size)
{
  uint64_t seedVal = readRandInt64();
  isaac64_engine generator(seedVal);
  output = new uint8_t[size];
  unsigned int offset = 0;
  uint64_t randNum = 0;
  while (offset < size) {
    randNum = generator();
    memcpy(output + offset, (uint8_t*)&randNum, (size - offset < 8) ? size - offset : 8);
    offset += 8;
  }
}

int
aes128_cbc_encrypt(const uint8_t* input_value, uint32_t input_size,
                   uint8_t* output_value, uint32_t& output_size,
                   const uint8_t* aes_iv, const uint8_t* aes_key)
{
  struct tc_aes_key_sched_struct schedule;
  if (tc_aes128_set_encrypt_key(&schedule, aes_key) != TC_CRYPTO_SUCCESS) {
    std::cerr << "Cannot set aes enc key" << std::endl;
    return -2;
  }

  // padding
  int rem = input_size % TC_AES_BLOCK_SIZE;
  if (rem != 0) {
    uint32_t real_input_size = (input_size / TC_AES_BLOCK_SIZE + 1) * TC_AES_BLOCK_SIZE;
    uint8_t* real_input = new uint8_t[real_input_size];
    memcpy(real_input, input_value, input_size);
    memset(real_input + input_size, rem, rem);

    output_size = real_input_size + TC_AES_BLOCK_SIZE;
    output_value = new uint8_t[output_size];
    if (tc_cbc_mode_encrypt(output_value, output_size,
                            real_input, input_size / TC_AES_BLOCK_SIZE + 1, aes_iv, &schedule) != TC_CRYPTO_SUCCESS) {
      std::cerr << "enc failed" << std::endl;
      delete[] real_input;
      return -3;
    }
    delete[] real_input;
  }
  else {
    output_size = input_size + TC_AES_BLOCK_SIZE;
    output_value = new uint8_t[output_size];
    if (tc_cbc_mode_encrypt(output_value, output_size,
                            input_value, input_size, aes_iv, &schedule) != TC_CRYPTO_SUCCESS) {
      std::cerr << "enc failed" << std::endl;
      return -3;
    }
  }
  return 0;
}

int
aes128_cbc_decrypt(const uint8_t* input_value, uint8_t input_size,
                   uint8_t* output_value, uint32_t& output_size, const uint8_t* aes_key)
{
  struct tc_aes_key_sched_struct schedule;
  if (tc_aes128_set_decrypt_key(&schedule, aes_key) != TC_CRYPTO_SUCCESS) {
    std::cerr << "Cannot set aes dec key" << std::endl;
    return -2;
  }

  output_size = input_size - TC_AES_BLOCK_SIZE;
  output_value = new uint8_t[output_size];
  if (tc_cbc_mode_decrypt(output_value, input_size - TC_AES_BLOCK_SIZE,
                          input_value + TC_AES_BLOCK_SIZE, input_size - TC_AES_BLOCK_SIZE,
                          input_value, &schedule) == 0) {
    std::cerr << "dec failed" << std::endl;
    return -3;
  }
  return 0;
}

void
aes128_cbc_encrypt_file(const std::string& fileName, const std::string& outputFileName, const uint8_t* iv, const uint8_t* aesKey)
{
  using namespace std;
  ifstream ifs(fileName, ios::binary | ios::ate);
  ifstream::pos_type pos = ifs.tellg();
  int length = pos;
  char* pChars = new char[length];
  ifs.seekg(0, ios::beg);
  ifs.read(pChars, length);
  ifs.close();

  uint8_t* encryptedContent = nullptr;
  uint32_t encryptedContentSize = 0;
  aes128_cbc_encrypt((uint8_t*)pChars, length, encryptedContent, encryptedContentSize, iv, aesKey);
  ofstream fout;
  fout.open(outputFileName, ios::binary | ios::out);
  fout.write((char*)&encryptedContent, encryptedContentSize);
  fout.close();

  delete[] pChars;
  delete[] encryptedContent;
  return;
}

void
aes128_cbc_decrypt_file(const std::string& fileName, const std::string& outputFileName, const uint8_t* aesKey)
{
  using namespace std;
  ifstream ifs(fileName, ios::binary | ios::ate);
  ifstream::pos_type pos = ifs.tellg();
  int length = pos;
  char* pChars = new char[length];
  ifs.seekg(0, ios::beg);
  ifs.read(pChars, length);
  ifs.close();

  uint8_t* decryptedContent = nullptr;
  uint32_t decryptedContentSize = 0;
  aes128_cbc_decrypt((uint8_t*)pChars, length, decryptedContent, decryptedContentSize, aesKey);
  ofstream fout;
  fout.open(outputFileName, ios::binary | ios::out);
  fout.write((char*)&decryptedContent, decryptedContentSize);
  fout.close();

  delete[] pChars;
  delete[] decryptedContent;
  return;
}