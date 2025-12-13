#include <fstream>
#include <iostream>
#include <string>
#include <vector>

long long findBestJoltage(std::string bank, int depth = 2) {
  long long bestJoltage = -1;

  for (int startIndex = 0; startIndex < bank.length() - depth; ++startIndex) {
    std::vector<int> digits;

    int currentStartIndex = startIndex;

    for (int d = 0; d < depth; ++d) {
      int max = -1;
      int indexOfMax = -1;
      int depthLim = bank.length() - (depth - d - 1);

      for (int i = currentStartIndex; i < depthLim; ++i) {
        int digit = bank[i] - '0';
        if (max < digit) {
          max = digit;
          indexOfMax = i;
        }
      }

      digits.push_back(max);
      currentStartIndex = indexOfMax + 1;
    }

    long long currentJoltage = 0;

    for (auto digit : digits) {
      currentJoltage = currentJoltage * 10 + digit;
    }

    if (currentJoltage > bestJoltage) {
      bestJoltage = currentJoltage;
    }
  }

  return bestJoltage;
}

long long sumBestJoltages(std::ifstream &inputStream, int issueNumber) {
  std::string line;
  long long sum = 0;

  int depth = issueNumber == 1 ? 2 : 12;

  while (std::getline(inputStream, line)) {
    sum += findBestJoltage(line, depth);
  }

  return sum;
}

int main(int argc, char **argv) {
  const char *path = argv[1];

  std::ifstream inputFile(path);
  if (!inputFile.is_open()) {
    std::cerr << "Failed to open file: " << path << std::endl;
    return 1;
  }

  long long result = sumBestJoltages(inputFile, 1);
  std::cout << "Part 1: " << result << std::endl;

  inputFile.clear();
  inputFile.seekg(0, std::ios::beg);

  result = sumBestJoltages(inputFile, 2);

  std::cout << "Part 2: " << result << std::endl;

  return 0;
}
