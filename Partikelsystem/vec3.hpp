//
//  vec3.hpp
//  Partikelsystem
//
//  Created by Rafaella Karassavidou on 26.04.23.
//

#ifndef vec3_hpp
#define vec3_hpp

#include <cmath>
#include <iostream>
#include <random>
#include <stdio.h>

using std::sqrt;

inline float random_float() { return (2.0 * rand() / (RAND_MAX + 1.0)) - 1.0; }

inline float random_float(float min, float max) {
    return min + (max - min) * random_float();
}

class vec3 {
  public:
    vec3() : e{0, 0, 0} {}
    vec3(float e0, float e1, float e2) : e{e0, e1, e2} {}

    float x() const { return e[0]; }
    float y() const { return e[1]; }
    float z() const { return e[2]; }

    void setX(float x) { e[0] = x; }
    void setY(float y) { e[1] = y; }
    void setZ(float z) { e[2] = z; }

    vec3 &operator=(const vec3 &v) {
        e[0] = v.e[0];
        e[1] = v.e[1];
        e[2] = v.e[2];
        return *this;
    }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    float operator[](int i) const { return e[i]; }
    float &operator[](int i) { return e[i]; }

    vec3 &operator+=(const vec3 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3 &operator*=(const float t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3 &operator/=(const float t) { return *this *= 1 / t; }

    float length() const { return sqrt(length_squared()); }

    float length_squared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    vec3 &normalize() {
        float k = 1.0 / length();
        e[0] *= k;
        e[1] *= k;
        e[2] *= k;
        return *this;
    }

    vec3 &operator-=(const vec3 &v) {
        e[0] -= v.e[0];
        e[1] -= v.e[1];
        e[2] -= v.e[2];
        return *this;
    }

  public:
    float e[3];
};

using point3 = vec3;
using color = vec3;

inline float clamp(float x, float min, float max) {
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

// vec3 Functions
inline point3 random_point() {
    // return (2.0 * rand() / (RAND_MAX + 1.0)) - 1.0;

    float randX =
        2.6f + static_cast<float>(rand()) / (RAND_MAX / (4.0f - 2.6f));
    float randY =
        3.8f + static_cast<float>(rand()) / (RAND_MAX / (4.0f - 3.8f));
    float randZ =
        -3.0f + static_cast<float>(rand()) / (RAND_MAX / (3.0f - (-3.0f)));

    return point3(randX, randY, randZ);
}

inline std::ostream &operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator+(const vec3 &u, float t) {
    return vec3(u.e[0] + t, u.e[1] + t, u.e[2] + t);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(float t, const vec3 &v) {
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3 &v, float t) {
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator/(vec3 v, float t) { return (1 / t) * v; }

inline float dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 reflect(const vec3 &v, const vec3 &n) {
    return v - 2.0 * dot(v, n) * n;
}

#endif /* vec3_hpp */
