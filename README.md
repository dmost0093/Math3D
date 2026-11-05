# Math3D

렌더링 공부용으로 직접 만드는 3D 수학 라이브러리 (C++20, 헤더 온리).
참고: *3D Math Primer for Graphics and Game Development* (gamemath.com)

## 빌드 & 테스트

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

## 다른 프로젝트에서 쓰기

```cmake
include(FetchContent)
FetchContent_Declare(Math3D
    GIT_REPOSITORY https://github.com/<user>/Math3D.git
    GIT_TAG        main)
FetchContent_MakeAvailable(Math3D)

target_link_libraries(my_renderer PRIVATE math3d::math3d)
```

```cpp
```

## 진행 상황

- [ ] Vec3 기본 연산 (+, -, 스칼라 곱, dot, cross, length, normalize)
- [ ] Vec3 나머지 연산
- [ ] 좌표 공간 변환 (Ch3)
- [ ] Mat3 / Mat4 (Ch4~6)
- [ ] 쿼터니언 (Ch8)
