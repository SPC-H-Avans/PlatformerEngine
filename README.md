# Platformer Engine

[![CPP Clang Tidy Linter](https://github.com/SPC-H-Avans/PlatformerEngine/actions/workflows/clang.yml/badge.svg)](https://github.com/SPC-H-Avans/PlatformerEngine/actions/workflows/clang.yml)
[![Build](https://github.com/SPC-H-Avans/PlatformerEngine/actions/workflows/build.yml/badge.svg)](https://github.com/SPC-H-Avans/PlatformerEngine/actions/workflows/build.yml)
[![Doxygen](https://github.com/SPC-H-Avans/PlatformerEngine/actions/workflows/doxygen.yml/badge.svg)](https://github.com/SPC-H-Avans/PlatformerEngine/actions/workflows/doxygen.yml)

# Getting Started
- Install [VCPKG](https://vcpkg.io/en/index.html)
- Clone the repository
- Follow MacOS instructions if you are on MacOS, if you are on Windows follow the Windows instructions, otherwise continue
- Run `git submodule update --init --recursive`
- Run `vcpkg integrate install`
- Add the following CMake options:
    - `-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake`
    - `-DVCPKG_TARGET_TRIPLET=[x64-windows | x64-osx | arm64-osx | x64-linux ]` (depending on your platform)
    - When using CLion, go to `File (Preferences on MacOS) > Settings > Build, Execution, Deployment > CMake > CMake Options` and add the options there

## MacOS
- Install [Brew](https://docs.brew.sh/Installation)
- Install CMake: `brew install cmake`
- Install GCC: `brew install gcc`
- Install VCPKG to the terminal:
  - `./vcpkg integrate bash`
  - `./vcpkg integrate zsh`
- Continue with the instructions above


## Windows
- Add the VCPKG directory to your PATH environment variable
- Continue with the instructions above

# Contributing
- Create a new branch
- Make your changes
- Update the CHANGELOG.md file
- Create a pull request and assign it to two team members. The GitHub Actions must succeed and both team members must approve the pull request before it can be merged.

# Documentation
- [Doxygen](https://engine.mrproper.dev)
