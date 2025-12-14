#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool isKernelValid(const std::string &prev, const std::string &curr,
                   const std::string &next, int index) {
  int atCount = 0;

  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0)
        continue;

      char ch = ' ';

      int col = index + j;
      if (col < 0)
        continue;

      switch (i) {
      case -1:
        if (!prev.empty() && col < prev.length()) {
          ch = prev[col];
        }
        break;
      case 0:
        if (col < curr.length()) {
          ch = curr[col];
        }
        break;
      case 1:
        if (!next.empty() && col < next.length()) {
          ch = next[col];
        }
        break;
      }

      if (ch == '@') {
        atCount++;
      }
    }
  }

  return atCount < 4;
}

int analyzeInput(std::ifstream &input) {
  std::string prev, curr, next;
  int count = 0;
  int lineNumber = 0;

  if (!std::getline(input, curr)) {
    return 0;
  }

  lineNumber++;

  if (!std::getline(input, next)) {
    for (int i = 0; i < curr.length(); i++) {
      if (curr[i] == '@' && isKernelValid(prev, curr, next, i)) {
        count++;
      }
    }
    return count;
  }
  lineNumber++;

  for (int i = 0; i < curr.length(); i++) {
    if (curr[i] == '@' && isKernelValid("", curr, next, i)) {
      count++;
    }
  }

  std::string newLine;
  while (std::getline(input, newLine)) {
    lineNumber++;
    prev = curr;
    curr = next;
    next = newLine;

    for (int i = 0; i < curr.length(); i++) {
      if (curr[i] == '@' && isKernelValid(prev, curr, next, i)) {
        count++;
      }
    }
  }

  for (int i = 0; i < next.length(); i++) {
    if (next[i] == '@' && isKernelValid(curr, next, "", i)) {
      count++;
    }
  }

  return count;
}

int analyzeBoard(std::ifstream &input) {
  std::vector<std::string> board;
  std::string line;

  while (std::getline(input, line)) {
    board.push_back(line);
  }

  int count = 0;
  bool changed = true;

  while (changed) {
    changed = false;

    for (int row = 0; row < board.size(); row++) {
      for (int col = 0; col < board[row].length(); col++) {
        if (board[row][col] == '@') {
          int atCount = 0;

          for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
              if (i == 0 && j == 0)
                continue;

              int r = row + i;
              int c = col + j;

              if (r >= 0 && r < board.size() && c >= 0 &&
                  c < board[r].length()) {
                if (board[r][c] == '@') {
                  atCount++;
                }
              }
            }
          }

          if (atCount < 4) {
            board[row][col] = 'x';
            count++;
            changed = true;
          }
        }
      }
    }
  }

  return count;
}

int main(int argc, char **argv) {
  const char *path = argv[1];

  std::ifstream inputFile(path);
  if (!inputFile.is_open()) {
    std::cerr << "Failed to open file: " << path << std::endl;
    return 1;
  }

  /**
   * PLAN:
   *
   * read always 2 lines atleast
   * keep 3 in memory
   * prev
   * current
   * next
   *
   *  go over each line char by char
   *  in each char check for kernel of 9 squares it being in ceter of it
   *  if char is @
   *  and if any of the kernels include @ more than 3 times we skip
   *  or if any of the kernels include @ less than 4 then we add 1 to count
   *
   *  we return count
   */

  int result = analyzeInput(inputFile);
  std::cout << "Part 1: " << result << std::endl;

  inputFile.clear();
  inputFile.seekg(0, std::ios::beg);

  result = analyzeBoard(inputFile);

  std::cout << "Part 2: " << result << std::endl;

  return 0;
}
