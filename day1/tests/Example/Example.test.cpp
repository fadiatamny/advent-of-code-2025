#include <cassert>
#include <iostream>

void test_basic_assertion() {
  assert(1 + 1 == 2);
  std::cout << "✓ Basic assertion test passed" << std::endl;
}

void test_string_comparison() {
  std::string hello = "Hello";
  std::string world = "World";
  assert(hello != world);
  std::cout << "✓ String comparison test passed" << std::endl;
}

void test_arithmetic() {
  int a = 10;
  int b = 5;
  assert(a + b == 15);
  assert(a - b == 5);
  assert(a * b == 50);
  assert(a / b == 2);
  std::cout << "✓ Arithmetic test passed" << std::endl;
}

int main() {
  std::cout << "Running Example Tests..." << std::endl;

  test_basic_assertion();
  test_string_comparison();
  test_arithmetic();

  std::cout << "All tests passed!" << std::endl;
  return 0;
}