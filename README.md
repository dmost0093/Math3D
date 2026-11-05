# Math3D

A header-only 3D math library for real-time and offline rendering, written from scratch in C++20 as a learning project.

Based on *3D Math Primer for Graphics and Game Development* ([gamemath.com](https://gamemath.com)).

## Build & Test

Requires CMake 3.25+ and a C++20 compiler (MSVC, Clang, or GCC).

```bash
# Windows (Developer PowerShell for VS)
cmake --preset win-debug
cmake --build --preset win-debug
ctest --preset win-debug

# macOS
cmake --preset mac-debug
cmake --build --preset mac-debug
ctest --preset mac-debug
```

Debug presets enable AddressSanitizer. Use the `*-release` presets for benchmarks.

## Usage

Add it to another CMake project with FetchContent:

```cmake
include(FetchContent)
FetchContent_Declare(Math3D
    GIT_REPOSITORY https://github.com/dmost0093/Math3D.git
    GIT_TAG        main)
FetchContent_MakeAvailable(Math3D)

target_link_libraries(my_renderer PRIVATE math3d::math3d)
```

```cpp
#include "math3d/vec3.h"

math3d::Vec3 a{1, 0, 0};
math3d::Vec3 b{0, 1, 0};
math3d::Vec3 n = math3d::cross(a, b);  // {0, 0, 1}
```

Tests are built only when Math3D is the top-level project, so consumers don't pull in Catch2.

## Design Notes

- **Header-only**: small, hot functions need to be visible for inlining.
- **Pass small types by value**: `Vec3` is 12 bytes, so copying is as cheap as passing a reference.
- **`float`, not `double`**: matches GPU data layouts.
- **`constexpr` where possible**: enables compile-time checks with `static_assert`.

## Roadmap

- [x] Vec3 basics (+, -, scalar multiply, dot, cross, length, normalize)
- [ ] Remaining Vec3 operations
- [ ] Coordinate space transforms (Ch. 3)
- [ ] Mat3 / Mat4 (Ch. 4–6)
- [ ] Quaternions (Ch. 8)
