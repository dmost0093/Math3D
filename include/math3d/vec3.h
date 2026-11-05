#pragma once

#include <cmath>


namespace math3d{
    struct Vec3 {
        float x = 0.0f, y = 0.0f, z = 0.0f;
        constexpr Vec3& operator+=(Vec3 v){ 
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }
        constexpr Vec3& operator-=(Vec3 v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }
        constexpr Vec3& operator*=(float scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }
        constexpr Vec3& operator/=(float scalar) { return *this *= (1.0f / scalar); }
    };

    constexpr Vec3 operator+(Vec3 a, Vec3 b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }
    constexpr Vec3 operator-(Vec3 a, Vec3 b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }
    constexpr Vec3 operator*(Vec3 v, float scalar) { return {v.x * scalar, v.y * scalar, v.z * scalar}; }
    constexpr Vec3 operator*(float scalar, Vec3 v) { return v * scalar; }
   
    constexpr Vec3 operator/(Vec3 v, float scalar) { return {v.x / scalar, v.y / scalar, v.z / scalar}; }
    constexpr Vec3 operator-(Vec3 v) { return {-v.x, -v.y, -v.z}; }
    

    constexpr float dot(Vec3 a, Vec3 b) { return (a.x * b.x) + (a.y * b.y) + (a.z * b.z); } // Dot product of the two vector(3D)

    constexpr Vec3 cross(Vec3 a, Vec3 b) {// Cross product of the two vector(3D)
        return {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z, 
            a.x * b.y - a.y * b.x};
    }

    
    constexpr float lengthSquared(Vec3 v) { return dot(v, v); }
    inline float length(Vec3 v) { return std::sqrt(lengthSquared(v)); }
    inline Vec3 normalize(Vec3 v) { 
        const float magnitude = length(v);
        if (magnitude == 0.0f)          
            return {};
        return v/magnitude;
    }

    
 } // namespace math3d