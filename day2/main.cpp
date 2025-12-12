#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool isInvalidId_part1(std::string str) {
  int length = str.length();
  if (length % 2 != 0) {
    return false;
  }

  for (int i = 0, j = length / 2; j < str.length(); ++j, ++i) {
    if (str[i] != str[j]) {
      return false;
    }
  }

  return true;
}

bool isInvalidId_part2(std::string str) {
  int matchTimes = 0;

  /**
   * 123123123
   * valid cuz
   * window of 123
   * is repeated till the end
   *
   * 1110
   * is invalid
   * cuz
   * 1 window is not repeated till end
   * 11 is not repeated till end
   * 111 is not repeated till end
   */

  for (int i = 1; i <= str.length() - 1; ++i) {
    std::string subsequenceToLookFor = str.substr(0, i);

    int windowSize = subsequenceToLookFor.length();
    int windowSizeJumps = str.length() / windowSize;

    if (str.length() % windowSize != 0) {
      continue;
    }

    bool allMatch = true;

    for (int y = 1; y <= windowSizeJumps - 1; ++y) {
      std::string window = str.substr(y * windowSize, windowSize);

      if (window.compare(subsequenceToLookFor) != 0) {
        allMatch = false;
        break;
      }
    }

    if (allMatch) {
      return true;
    }
  }

  return false;
}

long invalidIdsInRangeSum(const std::string &range, int issueNumber) {
  size_t dashPos = range.find('-');
  long start = std::stol(range.substr(0, dashPos));
  long end = std::stol(range.substr(dashPos + 1));

  long sum = 0;
  for (auto id = start; id <= end; ++id) {

    if (issueNumber == 1 && isInvalidId_part1(std::to_string(id))) {
      sum += id;
    }
    if (issueNumber == 2 && isInvalidId_part2(std::to_string(id))) {
      sum += id;
    }
  }

  return sum;
}

long sumInvalidIdsFromStream(std::ifstream &inputStream, int issueNumber) {
  std::string line;
  long sum = 0;

  while (std::getline(inputStream, line)) {
    std::vector<std::string> ranges;
    std::string token;
    std::stringstream stringStream(line);
    char delim = ',';

    while (std::getline(stringStream, token, delim)) {
      ranges.push_back(token);
    }

    for (auto &range : ranges) {
      sum += invalidIdsInRangeSum(range, issueNumber);
    }
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

  long result = sumInvalidIdsFromStream(inputFile, 1);
  std::cout << "Part 1: " << result << std::endl;

  inputFile.clear();
  inputFile.seekg(0, std::ios::beg);

  result = sumInvalidIdsFromStream(inputFile, 2);

  std::cout << "Part 2: " << result << std::endl;

  return 0;
}
