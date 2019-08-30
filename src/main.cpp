#include <fstream>

int main(int argc, char const *argv[])
{
  std::string fileName = "/Users/ZhangZhiyi/Develop/who-should-be-fined/datasets/heart.csv";
  std::ifstream data(fileName);
  std::string line = "";
  int lineCounter = 0;
  while (std::getline(data, line)) {
    if (lineCounter == 0) {
      lineCounter++;
      continue;
    }
    lineCounter++;
  }
  data.close();
  return 0;
}
