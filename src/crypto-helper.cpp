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
  unsigned int offset = 0;
  uint64_t randNum = 0;
  while (offset < size) {
    randNum = generator();
    memcpy(output + offset, (uint8_t*)&randNum, (size - offset < 8) ? size - offset : 8);
    offset += 8;
  }
}

static const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";


static inline bool is_base64(uint8_t c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string
base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = ( char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;
}

std::vector<uint8_t>
base64_decode(std::string const& encoded_string) {
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  uint8_t char_array_4[4], char_array_3[3];
  std::vector<uint8_t> ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
          ret.push_back(char_array_3[i]);
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret.push_back(char_array_3[j]);
  }

  return ret;
}

int
aes128_cbc_encrypt(const uint8_t* input_value, uint32_t input_size,
                   uint8_t** output_value, uint32_t& output_size,
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
    *output_value = new uint8_t[output_size];
    if (tc_cbc_mode_encrypt(*output_value, output_size,
                            real_input, real_input_size, aes_iv, &schedule) != TC_CRYPTO_SUCCESS) {
      std::cerr << "enc failed" << std::endl;
      delete[] real_input;
      return -3;
    }
    delete[] real_input;
  }
  else {
    output_size = input_size + TC_AES_BLOCK_SIZE;
    *output_value = new uint8_t[output_size];
    if (tc_cbc_mode_encrypt(*output_value, output_size,
                            input_value, input_size, aes_iv, &schedule) != TC_CRYPTO_SUCCESS) {
      std::cerr << "enc failed" << std::endl;
      return -3;
    }
  }
  return 0;
}

int
aes128_cbc_decrypt(const uint8_t* input_value, uint32_t input_size,
                   uint8_t** output_value, uint32_t& output_size, const uint8_t* aes_key)
{
  struct tc_aes_key_sched_struct schedule;
  if (tc_aes128_set_decrypt_key(&schedule, aes_key) != TC_CRYPTO_SUCCESS) {
    std::cerr << "Cannot set aes dec key" << std::endl;
    return -2;
  }

  output_size = input_size - TC_AES_BLOCK_SIZE;
  *output_value = new uint8_t[output_size];
  if (tc_cbc_mode_decrypt(*output_value, output_size,
                          input_value + TC_AES_BLOCK_SIZE, output_size, input_value, &schedule) == 0) {
    std::cerr << "dec failed" << std::endl;
    return -3;
  }
  return 0;
}

void
aes128_cbc_encrypt_file(const std::string& fileName, const std::string& outputFileName, const uint8_t* iv, const uint8_t* aesKey)
{
  using namespace std;
  std::ifstream inputFile(fileName);
  std::string input((std::istreambuf_iterator<char>(inputFile)),
                    std::istreambuf_iterator<char>());
  inputFile.close();

  uint8_t* encryptedContent = nullptr;
  uint32_t encryptedContentSize = 0;
  aes128_cbc_encrypt((uint8_t*)input.c_str(), input.length(), &encryptedContent, encryptedContentSize, iv, aesKey);
  ofstream fileOut;
  fileOut.open(outputFileName, ios::binary | ios::out);
  fileOut.write((char*)encryptedContent, encryptedContentSize);
  fileOut.close();

  delete[] encryptedContent;
  return;
}

void
aes128_cbc_decrypt_file(const std::string& fileName, const std::string& outputFileName, const uint8_t* aesKey)
{
  using namespace std;
  ifstream ifs(fileName, ios::binary | ios::in | ios::ate);
  ifstream::pos_type pos = ifs.tellg();
  int length = pos;
  char* pChars = new char[length];
  ifs.seekg(0, ios::beg);
  ifs.read(pChars, length);
  ifs.close();

  uint8_t* decryptedContent = nullptr;
  uint32_t decryptedContentSize = 0;
  aes128_cbc_decrypt((uint8_t*)pChars, length, &decryptedContent, decryptedContentSize, aesKey);
  ofstream fileOut;
  fileOut.open(outputFileName);
  fileOut << std::string((char*)decryptedContent, decryptedContentSize) << std::endl;
  fileOut.close();

  delete[] pChars;
  delete[] decryptedContent;
  return;
}
