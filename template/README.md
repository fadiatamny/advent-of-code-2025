# C++ Project Template

A modern C++ project template with Meson build system, automated testing, and CI/CD integration.

## Features

- **Meson Build System**: Fast and reliable builds
- **C++20 Standard**: Modern C++ features
- **Code Quality Tools**:
  - `clang-format`: Automatic code formatting
  - `clang-tidy`: Static analysis and linting
  - `cppcheck`: Additional static analysis
- **Testing Framework**: Integrated test structure
- **GitHub Actions**: Automated PR checks
- **Development Scripts**: Quick build, test, and run commands

## Prerequisites

Install the following tools:

```bash
# Ubuntu/Debian
sudo apt-get install -y \
    meson \
    ninja-build \
    clang-format \
    clang-tidy \
    cppcheck \
    g++ \
    pkg-config

# macOS
brew install meson ninja clang-format llvm cppcheck
```

## Project Structure

```
.
├── .github/
│   └── workflows/
│       └── pr-checks.yml      # CI/CD pipeline
├── src/
│   ├── main.cpp               # Main application entry point
│   └── meson.build            # Source build configuration
├── tests/
│   └── meson.build            # Test configuration
├── build.sh                   # Full build script (format, lint, build, test)
├── test.sh                    # Quick test script
├── dev.sh                     # Development script (build and run)
├── meson.build                # Root build configuration
├── .clangd                    # Language server configuration
├── .cppcheck-suppressions     # Cppcheck suppressions
└── .gitignore                 # Git ignore rules
```

## Getting Started

### 1. Customize the Template

1. Update `meson.build`:
   - Change `project_name` to your project name
   - Update version number
2. Modify `src/main.cpp` with your application code
3. Add your modules to `src/` directory

### 2. Initial Setup

```bash
# Setup build directory
meson setup dist

# Or run the build script (recommended)
./build.sh
```

### 3. Development Workflow

```bash
# Full build with formatting, linting, and testing
./build.sh

# Quick test after making changes
./test.sh

# Build and run the application
./dev.sh
```

## Scripts

### `build.sh`
Complete build pipeline:
1. Format code with `clang-format`
2. Run `clang-tidy` static analysis
3. Run `cppcheck` static analysis
4. Compile the project
5. Run all tests

### `test.sh`
Quick build and test:
1. Compile the project
2. Run all tests

### `dev.sh`
Development cycle:
1. Run full build
2. Execute the application

## Adding Tests

1. Create a test directory under `tests/`:
   ```bash
   mkdir tests/MyModule
   ```

2. Create test file `tests/MyModule/MyModule.test.cpp`:
   ```cpp
   #include <cassert>
   
   void test_example() {
       assert(1 + 1 == 2);
   }
   
   int main() {
       test_example();
       return 0;
   }
   ```

3. Create `tests/MyModule/meson.build`:
   ```meson
   test_srcs = [
     'MyModule.test.cpp',
     '../../src/MyModule.cpp',  # Include source files if needed
   ]
   
   mymodule_test = executable(
     'MyModuleTest',
     test_srcs,
     include_directories : src_inc,
   )
   
   test('mymodule', mymodule_test)
   ```

4. Add to `tests/meson.build`:
   ```meson
   subdir('MyModule')
   ```

## CI/CD

The template includes GitHub Actions workflow (`.github/workflows/pr-checks.yml`) that runs on pull requests:

- **Format Check**: Ensures code is properly formatted
- **clang-tidy**: Static analysis for code quality
- **cppcheck**: Additional static analysis
- **Build**: Compiles the project (allows one retry)
- **Tests**: Runs all test suites

Pull requests must pass all checks to be merged.

## Code Quality

### Formatting
Code is automatically formatted using `clang-format`. Run `build.sh` to format all files.

### Static Analysis
Two static analysis tools are used:
- **clang-tidy**: Catches common bugs and enforces best practices
- **cppcheck**: Additional checks for undefined behavior and errors

Suppressions can be added to `.cppcheck-suppressions` as needed.

## Editor Integration

### VS Code
Install the `clangd` extension for IDE features like:
- Autocomplete
- Go to definition
- Find references
- Inline diagnostics

The `.clangd` file provides fallback configuration.

### Other Editors
Most modern editors support clangd. The project generates `compile_commands.json` in the `dist/` directory for proper IDE integration.

## License

Update with your license of choice.

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Ensure `build.sh` passes
5. Submit a pull request