#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

bool isInRange(const std::string &range, long long selectedValue) {
  size_t dashPos = range.find('-');
  if (dashPos == std::string::npos) {
    return false;
  }

  long long start = std::stoll(range.substr(0, dashPos));
  long long end = std::stoll(range.substr(dashPos + 1));

  return selectedValue >= start && selectedValue <= end;
}

int analyzeFile(std::ifstream &input) {
  std::string line;
  int count = 0;
  std::vector<std::string> ingredientRanges;

  while (std::getline(input, line)) {
    if (line.empty()) {
      break;
    }

    ingredientRanges.push_back(line);
  }

  while (std::getline(input, line)) {
    long long selectedValue = std::stoll(line);
    for (std::string range : ingredientRanges) {
      if (isInRange(range, selectedValue)) {
        count++;
        break;
      }
    }
  }

  return count;
}

long long analyzeFile2(std::ifstream &input) {
  std::string line;
  std::vector<std::pair<long long, long long>> ranges;

  while (std::getline(input, line)) {
    if (line.empty()) {
      break;
    }

    size_t dashPos = line.find('-');
    if (dashPos == std::string::npos) {
      continue;
    }

    long start = std::stoll(line.substr(0, dashPos));
    long end = std::stoll(line.substr(dashPos + 1));

    ranges.push_back({start, end});
  }

  std::sort(ranges.begin(), ranges.end());

  long long total = 0;
  long long start = ranges[0].first;
  long long end = ranges[0].second;

  for (size_t i = 1; i < ranges.size(); ++i) {
    if (ranges[i].first <= end + 1) {
      end = std::max(end, ranges[i].second);
    } else {
      total += end - start + 1;
      start = ranges[i].first;
      end = ranges[i].second;
    }
  }

  return total + (end - start + 1);
}

int main(int argc, char **argv) {
  const char *path = argv[1];

  std::ifstream inputFile(path);
  if (!inputFile.is_open()) {
    std::cerr << "Failed to open file: " << path << std::endl;
    return 1;
  }

  int result = analyzeFile(inputFile);
  std::cout << "Part 1: " << result << std::endl;

  inputFile.clear();
  inputFile.seekg(0, std::ios::beg);

  long long result2 = analyzeFile2(inputFile);

  std::cout << "Part 2: " << result2 << std::endl;

  return 0;
}
