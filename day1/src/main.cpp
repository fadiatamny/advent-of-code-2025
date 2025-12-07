#include <fstream>
#include <iostream>

int processFile(std::ifstream &inputStream) {
  int result = 0;
  int count = 50;
  char letter = 'a';
  int number = 0;

  int lineCount = 0;

  while (inputStream >> letter >> number) {
    ++lineCount;

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

  std::cout << "Total lines processed: " << lineCount << std::endl;

  return result;
}

int main(int argc, char **argv) {
  const char *path = argv[1];

  std::ifstream inputFile(path);
  if (!inputFile.is_open()) {
    std::cerr << "Failed to open file: " << path << std::endl;
    return 1;
  }

  int result = processFile(inputFile);
  std::cout << result << std::endl;

  return 0;
}
