#include <cstdlib>
#include <fstream>
#include <iostream>

int howManyTimesWeHit0(std::ifstream &inputStream) {
  int result = 0;
  int count = 50;
  char letter = 'a';
  int number = 0;

  while (inputStream >> letter >> number) {
    switch (letter) {
    case 'L':
      count -= (number % 100);
      if (count < 0) {
        count += 100;
      }
      break;
    case 'R':
      count += (number % 100);
      if (count > 99) {
        count -= 100;
      }
      break;
    }

    if (count == 0) {
      ++result;
    }
  }

  if (count == 0) {
    ++result;
  }

  return result;
}

int howManyTimesWeCross0(std::ifstream &inputStream) {
  int result = 0;
  int count = 50;
  char letter = 'a';
  int number = 0;
  int rotations = 0;

  while (inputStream >> letter >> number) {
    int old_count = count;
    rotations = std::abs(number / 100);
    result += rotations;

    switch (letter) {
    case 'L':
      count -= (number % 100);
      if (count <= 0 && old_count > 0) {
        result++;
      }
      if (count < 0) {
        count += 100;
      }
      break;
    case 'R':
      count += (number % 100);
      if (count >= 100) {
        result++;
      }
      if (count > 99) {
        count -= 100;
      }
      break;
    }
  }

  return result;
}

int main(int argc, char **argv) {
  const char *path = argv[1];

  std::ifstream inputFile(path);
  if (!inputFile.is_open()) {
    std::cerr << "Failed to open file: " << path << std::endl;
    return 1;
  }

  int result = howManyTimesWeHit0(inputFile);
  std::cout << result << std::endl;

  inputFile.clear();
  inputFile.seekg(0, std::ios::beg);

  result = howManyTimesWeCross0(inputFile);
  std::cout << result << std::endl;

  return 0;
}
