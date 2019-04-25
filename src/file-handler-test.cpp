#include "file-handler.hpp"
#include "crypto-helper.hpp"
#include <fstream>

void
generateKeywordsForAllReceivers()
{
  /*======================For The First Time Parse Data========================*/
  // // get the keywords
  // auto results = parseKeyWords("../../netflix-prize-data/movie_titles.csv");
  // std::list<std::string> fileNames;
  // fileNames.push_back("../../netflix-prize-data/combined_data_1.txt");
  // fileNames.push_back("../../netflix-prize-data/combined_data_2.txt");
  // fileNames.push_back("../../netflix-prize-data/combined_data_3.txt");
  // fileNames.push_back("../../netflix-prize-data/combined_data_4.txt");
  // // get the keyword's popularity
  // obtainPopularity(results, fileNames);
  // // output the results to heatmap
  // std::ofstream heatMapFile;
  // heatMapFile.open("../heatmap.txt");
  // for (auto it = results.begin(); it != results.end(); it++) {
  //   heatMapFile << std::fixed << it->first << "," << it->second << std::endl;
  // }
  // heatMapFile.close();
  /*====================Otherwise, directly read from heatmap====================*/
  // auto results = parseHeatMap("../heatmap.txt");
  auto results = parseHeatMapOnlyKeys("../../datasets/heatmap.txt");

  /*============================Strip popular records============================*/
  // std::list<uint16_t> afterStrip;
  // std::list<uint16_t> popKeys;
  // stripPopularRecords(results, afterStrip, popKeys);

  /*============================Shuffle static keywords===========================*/
  shuffleList(results);
  std::ofstream shuffledListFile;
  shuffledListFile.open("../../datasets/shuffled.txt");
  for (auto it = results.begin(); it != results.end(); it++) {
    shuffledListFile << *it << std::endl;
  }
  shuffledListFile.close();

  // get keywords for receiver A, B, C
  std::list<uint16_t> forA, forB, forC;
  keyWordsForReceiver(results, forA, 1);
  keyWordsForReceiver(results, forB, 2);
  keyWordsForReceiver(results, forC, 3);
  std::cout << "entries toA, toB, toC: " << forA.size() << ", " << forB.size() << ", " << forC.size() << std::endl;

  // write to txt files
  std::ofstream forAFile, forBFile, forCFile;
  forAFile.open("../../datasets/forAFile.txt");
  forBFile.open("../../datasets/forBFile.txt");
  forCFile.open("../../datasets/forCFile.txt");
  auto itA = forA.begin();
  auto itB = forB.begin();
  auto itC = forC.begin();
  while (itA != forA.end() && itB != forB.end() && itC != forC.end()) {
    if (itA != forA.end()) {
      forAFile << *itA << std::endl;
      itA++;
    }
    if (itB != forB.end()) {
      forBFile << *itB << std::endl;
      itB++;
    }
    if (itC != forC.end()) {
      forCFile << *itC << std::endl;
      itC++;
    }
  }
  forAFile.close();
  forBFile.close();
  forCFile.close();
}

void
prepareDataToSend()
{
  std::list<uint16_t> keywordsA = parseKeyWordsFile("../../datasets/forAFile.txt");
  std::list<std::string> fileNames;
  fileNames.push_back("../../netflix-prize-data/combined_data_1.txt");
  fileNames.push_back("../../netflix-prize-data/combined_data_2.txt");
  fileNames.push_back("../../netflix-prize-data/combined_data_3.txt");
  fileNames.push_back("../../netflix-prize-data/combined_data_4.txt");

  extractKeyWordsRows(fileNames, keywordsA, "../../datasets/A");
}

void
testAESEncryption()
{
  std::string input = "abcdefg1234,567abcdefg1234,567\nabcdefg1234567abcdefg1234567abcdefg\n1234567abcdefg1234,567abcdefg1234567AAABBBCCCabcdefg1234567abcdefg1234567abcdefg1234567abcd,efg12345\n67abcdefg1234567abcdefg1234567abcdefg1234567AAABBBCCC";
  uint8_t aesKey[16] = {0};
  uint8_t iv[16] = {0};
  generateRandomBytes(aesKey, 16);
  generateRandomBytes(iv, 16);

  uint8_t* output = nullptr;
  uint32_t usedSize = 0;
  aes128_cbc_encrypt((uint8_t*)input.c_str(), input.size(), &output, usedSize, iv, aesKey);

  uint8_t* decrypted = nullptr;
  uint32_t usedSizeDec = 0;
  aes128_cbc_decrypt(output, usedSize, &decrypted, usedSizeDec, aesKey);

  std::string afterDec((char*)decrypted, usedSizeDec);
  std::cout << "after decryption: \n" << afterDec << std::endl
  << "before encryption: \n"  << input << std::endl;

  delete[] decrypted;
  delete[] output;
}

void
testAesFile()
{
  uint8_t aesKey[16] = {0};
  uint8_t iv[16] = {0};
  generateRandomBytes(aesKey, 16);
  generateRandomBytes(iv, 16);
  aes128_cbc_encrypt_file("../../datasets/A/2", "../../datasets/A-enc/2", iv, aesKey);
  aes128_cbc_decrypt_file("../../datasets/A-enc/2", "../../datasets/A-dec/2", aesKey);
}

int
main(int argc, char* argv[])
{
  return 0;
}
