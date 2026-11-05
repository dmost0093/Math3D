# ============================================================
# 1) CMake 최소 버전 / 프로젝트
# ============================================================
# 3.25: FetchContent의 SYSTEM 옵션, 프리셋 version 6 지원
cmake_minimum_required(VERSION 3.25)

project(Math3D
    VERSION 0.1.0
    DESCRIPTION "렌더링 공부용 3D 수학 라이브러리"
    LANGUAGES CXX)

# ============================================================
# 2) C++ 표준
# ============================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)   # C++20 못 하면 에러 (조용히 낮추지 않음)
set(CMAKE_CXX_EXTENSIONS OFF)         # gnu++20 말고 c++20 (컴파일러 확장 금지)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ============================================================
# 3) 빌드 옵션
# ============================================================
# 이 레포를 직접 열었을 때만 테스트를 기본으로 켬.
# 나중에 렌더러 레포에서 add_subdirectory / FetchContent로 가져다 쓸 땐
# Math3D 테스트까지 빌드할 필요가 없으니까 꺼짐.
option(MATH3D_BUILD_TESTS "Math3D 단위 테스트 빌드" ${PROJECT_IS_TOP_LEVEL})
option(MATH3D_ENABLE_ASAN "AddressSanitizer 활성화" OFF)

# MSVC: ASan과 /RTC1은 동시에 못 씀 → Debug 플래그에서 제거
if(MSVC AND MATH3D_ENABLE_ASAN)
    string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
endif()

# ============================================================
# 4) 공통 타깃 설정 함수 (경고 + 새니타이저)
# ============================================================
function(math3d_configure_target target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /WX /permissive- /utf-8)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()

    if(MATH3D_ENABLE_ASAN)
        if(MSVC)
            target_compile_options(${target} PRIVATE /fsanitize=address /Zi)
        else()
            target_compile_options(${target} PRIVATE -fsanitize=address -fno-omit-frame-pointer)
            target_link_options(${target} PRIVATE -fsanitize=address)
        endif()
    endif()
endfunction()

# ============================================================
# 5) 라이브러리 (헤더 온리)
# ============================================================
# INTERFACE 라이브러리: 컴파일할 .cpp가 없고, 링크하는 쪽에 include 경로만 전달.
# 수학 함수는 constexpr/inline이라 헤더에 있어야 인라이닝이 잘 됨 (glm도 같은 방식).
add_library(math3d INTERFACE)
add_library(math3d::math3d ALIAS math3d)   # 쓰는 쪽에선 이 이름으로 링크

target_include_directories(math3d INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(math3d INTERFACE cxx_std_20)  # 쓰는 쪽도 C++20 이상 강제

# ============================================================
# 6) 테스트 (Catch2)
# ============================================================
if(MATH3D_BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.8.1
        GIT_SHALLOW    TRUE
        SYSTEM)
    FetchContent_MakeAvailable(Catch2)

    enable_testing()
    add_executable(math3d_tests
        tests/test_vec3.cpp)
    target_link_libraries(math3d_tests PRIVATE math3d::math3d Catch2::Catch2WithMain)
    math3d_configure_target(math3d_tests)

    # 테스트 실행 파일 하나를 통째로 등록.
    # (catch_discover_tests는 Windows에서 한글 TEST_CASE 이름이 코드페이지 때문에
    #  깨져서 테스트를 못 찾는 경우가 있어서 안 씀. 개별 결과는 Catch2 출력에 다 나옴)
    add_test(NAME math3d_tests COMMAND math3d_tests)
endif()
