#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "math3d/vec3.h"

using math3d::Vec3;
using Catch::Matchers::WithinAbs;

// constexpr 함수는 컴파일 타임에 검사 가능 → 틀리면 빌드 자체가 실패
static_assert(math3d::dot(Vec3{1, 0, 0}, Vec3{0, 1, 0}) == 0.0f);

TEST_CASE("덧셈과 뺄셈", "[vec3]") {
    Vec3 a{1, 2, 3};
    Vec3 b{4, 5, 6};

    Vec3 sum = a + b;
    REQUIRE(sum.x == 5.0f);
    REQUIRE(sum.y == 7.0f);
    REQUIRE(sum.z == 9.0f);

    Vec3 diff = b - a;
    REQUIRE(diff.x == 3.0f);
    REQUIRE(diff.y == 3.0f);
    REQUIRE(diff.z == 3.0f);
}

TEST_CASE("스칼라 곱은 양쪽 순서 모두 동작", "[vec3]") {
    Vec3 v{1, -2, 3};
    Vec3 l = 2.0f * v;
    Vec3 r = v * 2.0f;
    REQUIRE(l.x == r.x);
    REQUIRE(l.y == r.y);
    REQUIRE(l.z == r.z);
    REQUIRE(l.y == -4.0f);
}

TEST_CASE("cross: x축 x y축 = z축 (오른손 좌표계)", "[vec3]") {
    Vec3 z = math3d::cross({1, 0, 0}, {0, 1, 0});
    REQUIRE(z.x == 0.0f);
    REQUIRE(z.y == 0.0f);
    REQUIRE(z.z == 1.0f);
}

TEST_CASE("cross 결과는 두 입력과 수직", "[vec3]") {
    Vec3 a{1, 2, 3};
    Vec3 b{-4, 0, 5};
    Vec3 c = math3d::cross(a, b);
    REQUIRE(math3d::dot(c, a) == 0.0f);
    REQUIRE(math3d::dot(c, b) == 0.0f);
}

TEST_CASE("normalize 결과의 길이는 1", "[vec3]") {
    // sqrt를 거치면 오차가 생기니 == 대신 허용 오차로 비교
    REQUIRE_THAT(math3d::length(math3d::normalize({3, 4, 12})), WithinAbs(1.0f, 1e-6f));
}
