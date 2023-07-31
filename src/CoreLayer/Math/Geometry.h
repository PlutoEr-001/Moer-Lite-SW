#pragma once

#include <algorithm>
#include <FastMath/FastMath.h>
#include <FastMath/VecMat.h>
//* 对于绝大部分图形应用来说，32位的浮点数足以满足计算精度需求且速度更快，故lite版仅支持float
//* 在4维齐次坐标下对点以及向量进行变换时会有不同处理，故相较于直接使用数学意义上的向量，我们进行了一个简单的封装

//* 表示三维空间中的一个向量
struct Vector3f {
public:
  //* 构造函数
  Vector3f(float f = .0f) { xyz = vecmat::vec3f::fill(f); }
  Vector3f(float _x, float _y, float _z) : xyz(_x, _y, _z) {}
  //* 加法重载
  Vector3f operator+(const Vector3f &rhs) const {
    return Vector3f(xyz + rhs.xyz);
  }
  Vector3f &operator+=(const Vector3f &rhs) {
    xyz += rhs.xyz;
    return *this;
  }

  //* 减法重载
  Vector3f operator-(const Vector3f &rhs) const {
    return Vector3f(xyz - rhs.xyz);
  }
  Vector3f &operator-=(const Vector3f &rhs) {
    xyz -= rhs.xyz;
    return *this;
  }

  //* 与标量相乘
  Vector3f operator*(float f) const { return Vector3f(xyz * f); }
  Vector3f &operator*=(float f) {
    xyz *= f;
    return *this;
  }

  //* 与标量相除
  Vector3f operator/(float f) const { return Vector3f(xyz / f); }
  Vector3f &operator/=(float f) {
    xyz /= f;
    return *this;
  }

  //* 两个向量按位相乘
  //! 如果想要计算点乘，使用dot(Vector3f, Vector3f)函数
  Vector3f operator*(const Vector3f &rhs) const {
    return Vector3f(xyz.cwiseMult(rhs.xyz));
  }
  Vector3f &operator*=(const Vector3f &rhs) {
    xyz = xyz.cwiseMult(rhs.xyz);
    return *this;
  }
  //* 两个向量按位相除
  Vector3f operator/(const Vector3f &rhs) const {
    return Vector3f(xyz.cwiseDiv(rhs.xyz));
  }
  Vector3f &operator/=(const Vector3f &rhs) {
    xyz = xyz.cwiseDiv(rhs.xyz);
    return *this;
  }

  //* 访问x, y, z，此处不对i进行检查
  float operator[](int i) const { return xyz[i]; }
  float &operator[](int i) { return xyz[i]; }

  //* 打印向量的值
  void debugPrint() const { xyz.debug_print(); }

  //* 如果当前向量是每个维度上都是0,则返回true
  bool isZero() const {
    return (xyz[0] == 0.f) && (xyz[1] == 0.f) && (xyz[2] == 0.f);
  }

  //* 返回向量的欧式长度
  float length() const { return xyz.len(); }

  //* 友函数/类声明
public:
  friend float dot(const Vector3f &v1, const Vector3f &v2);
  friend Vector3f cross(const Vector3f &v1, const Vector3f &v2);
  friend class Point3f;

private:
  Vector3f(const vecmat::vec3f &vec) : xyz(vec) {}
  vecmat::vec3f xyz;
};

//* 向量与标量相乘
inline Vector3f operator*(float f, const Vector3f &v) { return v * f; }

//* 两个向量点乘
inline float dot(const Vector3f &v1, const Vector3f &v2) {
  return vecmat::dot(v1.xyz, v2.xyz);
}

//* 两个向量叉乘
inline Vector3f cross(const Vector3f &v1, const Vector3f &v2) {
  return vecmat::cross(v1.xyz, v2.xyz);
}

//* 向量取反
inline Vector3f operator-(const Vector3f &vec) { return Vector3f(.0f) - vec; }

//* 向量单位化，不对0 向量做特殊处理
inline Vector3f normalize(const Vector3f &vec) {
  float len = vec.length();
  return vec / len;
}

//* 表示三维空间中的一个点
struct Point3f {
public:
  //* 构造函数
  Point3f(float f = .0f) { xyz = vecmat::vec3f::fill(f); }
  Point3f(float _x, float _y, float _z) : xyz(_x, _y, _z) {}

  //* 与向量相加
  Point3f operator+(const Vector3f &rhs) const {
    return Point3f(xyz + rhs.xyz);
  }
  Point3f &operator+=(const Vector3f &rhs) {
    xyz += rhs.xyz;
    return *this;
  }

  //* 与向量相减
  Point3f operator-(const Vector3f &rhs) const {
    return Point3f(xyz - rhs.xyz);
  }
  Point3f &operator-=(const Vector3f &rhs) {
    xyz -= rhs.xyz;
    return *this;
  }

  //* 与点相减
  Vector3f operator-(const Point3f &rhs) const {
    return Vector3f(xyz - rhs.xyz);
  }

  //* 访问x, y, z，此处不对i进行检查
  float operator[](int i) const { return xyz[i]; }
  float &operator[](int i) { return xyz[i]; }

  //* 打印点的值
  void debugPrint() const {
    printf("[point<%d>](", 3);
    for (int i = 0; i < 3; ++i) {
      std::cout << (i == 0 ? '\0' : ',') << xyz[i];
    }
    printf(")%c", '\n');
    fflush(stdout);
  }

  //* 友函数/类声明
public:
  friend class Vector3f;

private:
  Point3f(const vecmat::vec3f &vec) : xyz(vec) {}
  vecmat::vec3f xyz;
};

using Vector2i = vecmat::vec2i;
using Matrix4f = vecmat::mat44f;
using Vector2f = vecmat::vec<2, float>;
//struct Vector2f {
//public:
//    //* 构造函数
//    Vector2f(float f = .0f) { xy = vecmat::vec2f::fill(f); }
//    Vector2f(float _x, float _y) : xy(_x, _y) {}
//    //* 加法重载
//    Vector2f operator+(const Vector2f &rhs) const {
//        return Vector2f(xy + rhs.xy);
//    }
//    Vector2f &operator+=(const Vector2f &rhs) {
//        xy += rhs.xy;
//        return *this;
//    }
//
//    //* 减法重载
//    Vector2f operator-(const Vector2f &rhs) const {
//        return Vector2f(xy - rhs.xy);
//    }
//    Vector2f &operator-=(const Vector2f &rhs) {
//        xy -= rhs.xy;
//        return *this;
//    }
//
//    //* 与标量相乘
//    Vector2f operator*(float f) const { return Vector2f(xy * f); }
//    Vector2f &operator*=(float f) {
//        xy *= f;
//        return *this;
//    }
//
//    //* 与标量相除
//    Vector2f operator/(float f) const { return Vector2f(xy / f); }
//    Vector2f &operator/=(float f) {
//        xy /= f;
//        return *this;
//    }
//
//    //* 两个向量按位相乘
//    //! 如果想要计算点乘，使用dot(Vector3f, Vector3f)函数
//    Vector2f operator*(const Vector2f &rhs) const {
//        return Vector2f(xy.cwiseMult(rhs.xy));
//    }
//    Vector2f &operator*=(const Vector2f &rhs) {
//        xy = xy.cwiseMult(rhs.xy);
//        return *this;
//    }
//    //* 两个向量按位相除
//    Vector2f operator/(const Vector2f &rhs) const {
//        return Vector2f(xy.cwiseDiv(rhs.xy));
//    }
//    Vector2f &operator/=(const Vector2f &rhs) {
//        xy = xy.cwiseDiv(rhs.xy);
//        return *this;
//    }
//
//    //* 访问x, y, z，此处不对i进行检查
//    float operator[](int i) const { return xy[i]; }
//    float &operator[](int i) { return xy[i]; }
//
//    //* 打印向量的值
//    void debugPrint() const { xy.debug_print(); }
//
//    //* 如果当前向量是每个维度上都是0,则返回true
//    bool isZero() const {
//        return (xy[0] == 0.f) && (xy[1] == 0.f);
//    }
//
//    //* 返回向量的欧式长度
//    float length() const { return xy.len(); }
//
//    //* 友函数/类声明
//public:
//    friend float dot(const Vector2f &v1, const Vector2f &v2);
//    friend Vector2f cross(const Vector2f &v1, const Vector2f &v2);
//    friend class Point2f;
//
//private:
//    Vector2f(const vecmat::vec2f &vec) : xy(vec) {}
//    vecmat::vec2f xy;
//};
//
////* 向量与标量相乘
//inline Vector2f operator*(float f, const Vector2f &v) { return v * f; }
//
////* 两个向量点乘
//inline float dot(const Vector2f &v1, const Vector2f &v2) {
//    return vecmat::dot(v1.xy, v2.xy);
//}
//
////* 向量取反
//inline Vector2f operator-(const Vector2f &vec) { return Vector2f(.0f) - vec; }
//
////* 向量单位化，不对0 向量做特殊处理
//inline Vector2f normalize(const Vector2f &vec) {
//    float len = vec.length();
//    return vec / len;
//}

//二维空间中的一个点
struct Point2f {
public:
    //* 构造函数
    Point2f(float f = .0f) { xy = vecmat::vec2f::fill(f); }
    Point2f(float _x, float _y) : xy(_x, _y) {}

    //* 与向量相加
    Point2f operator+(const Vector2f &rhs) const {
        return Point2f(xy + rhs);
    }
    Point2f &operator+=(const Vector2f &rhs) {
        xy += rhs;
        return *this;
    }

    //* 与向量相减
    Point2f operator-(const Vector2f &rhs) const {
        return Point2f(xy - rhs);
    }
    Point2f &operator-=(const Vector2f &rhs) {
        xy -= rhs;
        return *this;
    }

    //* 与点相减
    Vector2f operator-(const Point2f &rhs) const {
        return Vector2f(xy - rhs.xy);
    }

    //* 访问x, y, z，此处不对i进行检查
    float operator[](int i) const { return xy[i]; }
    float &operator[](int i) { return xy[i]; }

    //* 打印点的值
    void debugPrint() const {
        printf("[point<%d>](", 3);
        for (int i = 0; i < 2; ++i) {
            std::cout << (i == 0 ? '\0' : ',') << xy[i];
        }
        printf(")%c", '\n');
        fflush(stdout);
    }

private:
    Point2f(const vecmat::vec2f &vec) : xy(vec) {}
    vecmat::vec2f xy;
};
