# Platformer Engine

[![CPP Clang Tidy Linter](https://github.com/SPC-H-Avans/PlatformerEngine/actions/workflows/clang.yml/badge.svg)](https://github.com/SPC-H-Avans/PlatformerEngine/actions/workflows/clang.yml)
[![Build](https://github.com/SPC-H-Avans/PlatformerEngine/actions/workflows/build.yml/badge.svg)](https://github.com/SPC-H-Avans/PlatformerEngine/actions/workflows/build.yml)
[![Doxygen](https://github.com/SPC-H-Avans/PlatformerEngine/actions/workflows/doxygen.yml/badge.svg)](https://github.com/SPC-H-Avans/PlatformerEngine/actions/workflows/doxygen.yml)

# Getting Started
- Install [VCPKG](https://vcpkg.io/en/index.html)
- Clone the repository
- Run `git submodule update --init --recursive`
- Run `vcpkg integrate install`
- Add the following CMake options:
    - `-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake`
    - `-DVCPKG_TARGET_TRIPLET=[x64-windows | x64-osx | arm64-osx | x64-linux ]` (depending on your platform)

# Contributing
- Create a new branch
- Make your changes
- Create a pull request and assign it to two team members. The GitHub Actions must succeed and both team members must approve the pull request before it can be merged.

# Documentation
- [Doxygen](https://engine.mrproper.dev)
